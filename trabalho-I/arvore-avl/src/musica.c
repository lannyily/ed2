#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/musica.h"
#include "../Includes/album.h" 
#include "../Includes/artista.h"
#include "../includes/playlist.h"



int maiorM(int alt1, int alt2){
    if(alt1 > alt2){
        return alt1;
    } else {
        return alt2;
    }
}


int alturaNoM(Musica* no){
    if (no == NULL) {
        return -1;
    } else {
        return no->altura;
    }
}

void rotacaoEsqM(Musica** raiz){
    if((*raiz)->Dir != NULL){
        
        Musica* aux = (*raiz)->Dir;
        (*raiz)->Dir = aux->Esq;
        aux->Esq = *raiz;


        (*raiz)->altura = maiorM(alturaNoM((*raiz)->Esq), alturaNoM((*raiz)->Dir)) + 1;
        aux->altura = maiorM(alturaNoM(aux->Dir), (*raiz)->altura) + 1;

        (*raiz) = aux;
    }

}


void rotacaoDirM(Musica** raiz){
    if((*raiz)->Esq != NULL){
        
        Musica* aux = (*raiz)->Esq;
        (*raiz)->Esq = aux->Dir;
        aux->Dir = *raiz;

        (*raiz)->altura = maiorM(alturaNoM((*raiz)->Esq), alturaNoM((*raiz)->Dir)) + 1;
        aux->altura = maiorM(alturaNoM(aux->Esq), (*raiz)->altura) + 1;

        (*raiz) = aux;
    }
}

int fatorBalanceamentoM(Musica* raiz){
    int bl;
    if (raiz != NULL) {
        bl = alturaNoM(raiz->Esq) - alturaNoM(raiz->Dir);
    } else {
        bl = 0;
    }
    return bl;
}

void balanceamentoM(Musica** raiz){
    int fb = fatorBalanceamentoM(*raiz);
    

    if (fb == 2) {  
        
        int fbEsq = fatorBalanceamentoM((*raiz)->Esq);
        if (fbEsq < 0) {  
            rotacaoEsqM(&(*raiz)->Esq);  
        }
        rotacaoDirM(raiz);
    } else if (fb == -2) {  
       
        int fbDir = fatorBalanceamentoM((*raiz)->Dir);
        if (fbDir > 0) {  
            rotacaoDirM(&(*raiz)->Dir);
        }
        rotacaoEsqM(raiz);
    }
}

void cadastrarMusica(struct Artista* raiz,  char* nomeArtista,  char* tituloAlbum,  char* tituloMusica, int duracao) {
    struct Artista* artista = NULL;
    buscaArtista(raiz, (char*)nomeArtista, &artista);

    if (artista != NULL) {
        Album* album = NULL;
        buscaAlbum(artista->albuns, (char*)tituloAlbum, &album);

        if (album != NULL) {
            Musica* novaMusica = criarMusica((char*)tituloMusica, duracao);
            if (insereMusica(&(album->musicas), novaMusica)) {
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

int insereMusica(Musica** R, Musica* No) {
    int inseriu = 1; 

    if (*R == NULL) {
        *R = No;
        
    } else{
        int comparacao = strcmp(No->titulo, (*R)->titulo);

        if (comparacao < 0) {
            if (insereMusica(&((*R)->Esq), No)){
                (*R)->altura = maiorM(alturaNoM((*R)->Esq), alturaNoM((*R)->Dir)) + 1;
                balanceamentoM(R);
            }
        } else if (comparacao > 0) {
            if(insereMusica(&((*R)->Dir), No)){
                (*R)->altura = maiorM(alturaNoM((*R)->Esq), alturaNoM((*R)->Dir)) + 1;
                balanceamentoM(R);
            }
        }
    }

    return inseriu; 
}

void imprimirMusicas(Musica* R) {
    if (R != NULL) {

        imprimirMusicas(R->Esq); 
        printf("Titulo: %s, Duracao: %d minutos\n", R->titulo, R->quantMinutos);
        imprimirMusicas(R->Dir); 
    }
}

void buscarMusica(Musica* R,  char* titulo, Musica** resultado) {
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

int ehFilhoM(Musica* m) {
    return (m->Esq == NULL && m->Dir == NULL);
}



Musica* souFilhoM(Musica* m) {
    Musica* resultado;
    if (m->Esq != NULL && m->Dir == NULL) {
        resultado = m->Esq;
    } else if (m->Dir != NULL && m->Esq == NULL) {
        resultado = m->Dir;
    } else {
        resultado = NULL;
    }
    return resultado;
}



Musica* enderecoMenorEsqM(Musica* m) {
    Musica* atual = m;
    while (atual != NULL && atual->Esq != NULL) {
        atual = atual->Esq;
    }
    return atual;
}

int removerMusica(Musica** raiz, char* titulo){
    int removeu = 1;

    if(*raiz != NULL){
        if(strcmp(titulo, (*raiz)->titulo) == 0){
           
            Musica *filho, *aux;

            if(ehFilhoM(*raiz)){
                
                aux = *raiz;
                *raiz = NULL;
                free(aux);
            } else {
                
                if((filho = souFilhoM(*raiz)) != NULL){
                    
                    aux = *raiz;
                    *raiz = filho;
                    free(aux);

                } else {
                    Musica* menor;
                    menor = enderecoMenorEsqM((*raiz)->Dir);
                     
                    strcpy((*raiz)->titulo, menor->titulo);
                    removerMusica(&((*raiz)->Dir), menor->titulo);

                }
            }
        } else {
            if(strcmp(titulo, (*raiz)->titulo) < 0){
                removeu = removerMusica(&((*raiz)->Esq), titulo);
            } else {
                removeu = removerMusica(&((*raiz)->Dir), titulo);
            }
        }

        if(*raiz != NULL){
            (*raiz)->altura = maiorM(alturaNoM((*raiz)->Esq), alturaNoM((*raiz)->Dir)) + 1;
            balanceamentoM(raiz);   
        }

    } else {
        printf("Musica \"%s\" nao encontrada!\n", titulo);
        removeu = 0;
    }
    return removeu;
}


int musicaEmPlaylists(Playlist* raiz,  char* titulo) {
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

void removerMusicaDeAlbum(struct Artista* raiz, struct Playlist* playlists,  char* nomeArtista,  char* tituloAlbum,  char* tituloMusica) {
    struct Artista* artista = NULL;
    buscaArtista(raiz, nomeArtista, &artista);

    if (artista != NULL) {
        Album* album = NULL;
        buscaAlbum(artista->albuns, tituloAlbum, &album);

        if (album != NULL) {
            if (!musicaEmPlaylists(playlists, tituloMusica)) {
                removerMusica(&album->musicas, tituloMusica);
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

void liberarMusicas(Musica* raiz) {
    if (raiz != NULL) {
        liberarMusicas(raiz->Esq);
        liberarMusicas(raiz->Dir);
        free(raiz);
    }
}
