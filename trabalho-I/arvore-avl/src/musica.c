#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/musica.h"
#include "../Includes/album.h" 
#include "../Includes/artista.h"
#include "../includes/playlist.h"

int maiorMusica(int x, int y) {
    if (x > y){
        return x;
    } else {
        return y;
    }
}

int pegaAlturaMusica(Musica* raiz){
    int altura = 0;
    if(raiz != NULL){
        int alturaEsq = pegaAlturaMusica(raiz->Esq);
        int alturaDir = pegaAlturaMusica(raiz->Dir);

        if(alturaEsq > alturaDir){
            altura = alturaEsq + 1;
        } else {
            altura = alturaDir + 1;
        }
    }
    return altura;
}

void rotacaoSimplesDireitaMusica(Musica** raiz){
    if((*raiz)->Esq != NULL){
        Musica* aux = (*raiz)->Esq;
        (*raiz)->Esq = aux->Dir;
        aux->Dir = *raiz;
        (*raiz)->altura = maiorMusica(pegaAlturaMusica((*raiz)->Esq), pegaAlturaMusica((*raiz)->Dir)) + 1;
        aux->altura = maiorMusica(pegaAlturaMusica(aux->Esq), (*raiz)->altura) + 1;
        (*raiz) = aux;
    }
}

void rotacaoSimplesEsquerdaMusica(Musica** raiz){
    if((*raiz)->Dir != NULL){
        Musica* aux = (*raiz)->Dir;
        (*raiz)->Dir = aux->Esq;
        aux->Esq = *raiz;
        (*raiz)->altura = maiorMusica(pegaAlturaMusica((*raiz)->Esq), pegaAlturaMusica((*raiz)->Dir)) + 1;
        aux->altura = maiorMusica(pegaAlturaMusica(aux->Dir), (*raiz)->altura) + 1;
        (*raiz) = aux;
    }
}

void rotacaoDuplaDireitaMusica(Musica** raiz){
    rotacaoSimplesEsquerdaMusica(&(*raiz)->Esq);
    rotacaoSimplesDireitaMusica(&(*raiz));
}

void rotacaoDuplaEsquerdaMusica(Musica** raiz){
    rotacaoSimplesDireitaMusica(&(*raiz)->Dir);
    rotacaoSimplesEsquerdaMusica(&(*raiz));
}

int alturaNoMusica(Musica* raiz){
    return raiz == NULL ? -1 : raiz->altura;
}

int fatorBalanceamentoMusica(Musica* raiz){
    int bl;
    bl = raiz != NULL ? abs(alturaNoMusica(raiz->Esq) - alturaNoMusica(raiz->Dir)) : 0;
    return bl;
}

void cadastrarMusica(Artista* raiz, const char* nomeArtista, const char* tituloAlbum, const char* tituloMusica, int duracao) {
    struct Artista* artista = NULL;
    buscaArtista(raiz, (char*)nomeArtista, &artista);

    if (artista != NULL) {
        Album* album = NULL;
        buscaAlbum(artista->albuns, (char*)tituloAlbum, &album);

        if (album != NULL) {
            Musica* novaMusica = criarMusica((char*)tituloMusica, duracao);
            if (insereMusica(&(album->musicas), novaMusica, tituloMusica)) {
                album->quantMusicas++;
                printf("Musica \"%s\" cadastrada com sucesso no album \"%s\" do artista \"%s\"!\n", tituloMusica, tituloAlbum, nomeArtista);
            } else {
                printf("Erro ao cadastrar a musica \"%s\"! Ela ja existe no album!\n", tituloMusica);
            }
        } else {
            printf("Album \"%s\" nao encontrado para o artista \"%s\".\n", tituloAlbum, nomeArtista);
        }
    } else {
        printf("Artista \"%s\" nao encontrado.\n", nomeArtista);
    }
}

Musica* criarMusica(char* titulo, int quantMinutos) {
  Musica* no = (Musica*)malloc(sizeof(Musica));

  strcpy(no->titulo, titulo);
  no->quantMinutos = quantMinutos;

  no->Dir = NULL;
  no->Esq = NULL;

  return no; 
}

int insereMusica(Musica** R, Musica* No, const char* tituloMusica) {
    int inseriu = 0; 

    if (*R == NULL) {
        *R = No;
        inseriu = 1; // Retorna 1 para indicar que a música foi inserida com sucesso
    } else{
        int comparacao = strcmp(No->titulo, (*R)->titulo);

        if (comparacao < 0) {
            if(inseriu = insereMusica(&((*R)->Esq), No, tituloMusica) == 1){
                if(fatorBalanceamentoMusica(*R) >= 2){
                    if (strcmp((*R)->Esq->titulo, tituloMusica) == 1){
                        rotacaoSimplesDireitaMusica(&(*R));
                    } else {
                        rotacaoDuplaDireitaMusica(&(*R));
                    }
                }
            } 
        } else if (comparacao > 0) {
            if (inseriu = insereMusica(&((*R)->Dir), No, tituloMusica) == 1){
                if(fatorBalanceamentoMusica(*R) >= 2){
                    if(strcmp((*R)->Dir->titulo, tituloMusica) == -1){
                        rotacaoSimplesEsquerdaMusica(&(*R));
                    }else {
                        rotacaoDuplaEsquerdaMusica(&(*R));
                    }
                } 
            } // Tenta inserir na subárvore direita
        }
        (*R)->altura = pegaAlturaMusica((*R));
    }

    return inseriu; // Retorna 0 se a música já existir
}


void imprimirMusicas(Musica* R) {
    if (R != NULL) {
        imprimirMusicas(R->Esq); // Percorre a subárvore esquerda
        printf("Titulo: %s, Duracao: %d minutos\n", R->titulo, R->quantMinutos);
        imprimirMusicas(R->Dir); // Percorre a subárvore direita
    }
}

void buscarMusica(Musica* R, const char* titulo, Musica** resultado) {
    *resultado = NULL;

    if (R != NULL){
        if (strcmp(R->titulo, titulo) == 0) {
            *resultado = R;
        } else if (strcmp(titulo, R->titulo) < 0) {
            buscarMusica(R->Esq, titulo, resultado);
        } else {
            buscarMusica(R->Dir, titulo, resultado);
        }
    }
}


// Remove uma música da árvore binária de músicas
Musica* removerMusica(Musica *raiz, const char *titulo) {
    if (raiz == NULL) {
        return NULL;
    }

    if (strcmp(titulo, raiz->titulo) < 0) {
        raiz->Esq = removerMusica(raiz->Esq, titulo);
    } else if (strcmp(titulo, raiz->titulo) > 0) {
        raiz->Dir = removerMusica(raiz->Dir, titulo);
    } else {
        printf("Musica \"%s\" removida!\n", titulo);
        // Encontrou a música
        if (raiz->Esq == NULL) {
            Musica *temp = raiz->Dir;
            free(raiz);
            return temp;
        } else if (raiz->Dir == NULL) {
            Musica *temp = raiz->Esq;
            free(raiz);
            return temp;
        }

        // Substitui pelo menor valor da subárvore direita
        Musica *temp = raiz->Dir;
        while (temp->Esq != NULL) {
            temp = temp->Esq;
        }
        strcpy(raiz->titulo, temp->titulo);
        raiz->Dir = removerMusica(raiz->Dir, temp->titulo);
    }

    raiz->altura = 1 + maiorMusica(alturaNoMusica(raiz->Esq), alturaNoMusica(raiz->Dir));

    int fb = fatorBalanceamentoMusica(raiz);

    if(fb > 1){
        if(fatorBalanceamentoMusica(raiz->Esq) >= 0){
            rotacaoSimplesDireitaMusica(&raiz);
        } else {
            rotacaoDuplaDireitaMusica(&raiz);
        }
    } else if (fb < -1){
        if(fatorBalanceamentoMusica(raiz->Dir) <= 0){
            rotacaoSimplesEsquerdaMusica(&raiz);
        } else {
            rotacaoDuplaEsquerdaMusica(&raiz);
        }
    }


    return raiz;
}

int musicaEmPlaylists(Playlist* raiz, const char* titulo) {
    MusicasPlaylist* resultado = NULL;

    if (raiz != NULL) {
        buscarMusicaPlaylist(raiz->musicas, titulo, &resultado);
        if (resultado != NULL) {
            return 1; 
        }
    
        if (musicaEmPlaylists(raiz->esquerda, titulo)) return 1;
        if (musicaEmPlaylists(raiz->direita, titulo)) return 1;
    }
    return 0; 
}

void removerMusicaDeAlbum(struct Artista* raiz, struct Playlist* playlists, const char* nomeArtista, const char* tituloAlbum, const char* tituloMusica) {
    struct Artista* artista = NULL;
    buscaArtista(raiz, nomeArtista, &artista);

    if (artista != NULL) {
        Album* album = NULL;
        buscaAlbum(artista->albuns, tituloAlbum, &album);

        if (album != NULL) {
            if (!musicaEmPlaylists(playlists, tituloMusica)) {
                album->musicas = removerMusica(album->musicas, tituloMusica);
                printf("Musica \"%s\" removida do album \"%s\" do artista \"%s\"!\n", tituloMusica, tituloAlbum, nomeArtista);
            } else {
                printf("Musica \"%s\" nao pode ser removida porque esta em uma playlist!\n", tituloMusica);
            }
        } else {
            printf("Album \"%s\" nao encontrado!\n", tituloAlbum);
        }
    } else {
        printf("Artista \"%s\" nao encontrado!\n", nomeArtista);
    }
}
