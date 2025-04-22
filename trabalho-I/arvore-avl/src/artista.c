#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"

int maiorArtista(int x, int y) {
    if (x > y){
        return x;
    } else {
        return y;
    }
}

int pegaAlturaArtista(Artista* raiz){
    int altura = 0;
    if(raiz != NULL){
        int alturaEsq = pegaAlturaArtista(raiz->Esq);
        int alturaDir = pegaAlturaArtista(raiz->Dir);

        if(alturaEsq > alturaDir){
            altura = alturaEsq + 1;
        } else {
            altura = alturaDir + 1;
        }
    }
    return altura;
}

void rotacaoSimplesDireitaArtista(Artista** raiz){
    if((*raiz)->Esq != NULL){
        Artista* aux = (*raiz)->Esq;
        (*raiz)->Esq = aux->Dir;
        aux->Dir = *raiz;
        (*raiz)->altura = maiorArtista(pegaAlturaArtista((*raiz)->Esq), pegaAlturaArtista((*raiz)->Dir)) + 1;
        aux->altura = maiorArtista(pegaAlturaArtista(aux->Esq), (*raiz)->altura) + 1;
        (*raiz) = aux;
    }
}

void rotacaoSimplesEsquerdaArtista(Artista** raiz){
    if((*raiz)->Dir != NULL){
        Artista* aux = (*raiz)->Dir;
        (*raiz)->Dir = aux->Esq;
        aux->Esq = *raiz;
        (*raiz)->altura = maiorArtista(pegaAlturaArtista((*raiz)->Esq), pegaAlturaArtista((*raiz)->Dir)) + 1;
        aux->altura = maiorArtista(pegaAlturaArtista(aux->Dir), (*raiz)->altura) + 1;
        (*raiz) = aux;
    }
}

void rotacaoDuplaDireitaArtista(Artista** raiz){
    rotacaoSimplesEsquerdaArtista(&(*raiz)->Esq);
    rotacaoSimplesDireitaArtista(&(*raiz));
}

void rotacaoDuplaEsquerdaArtista(Artista** raiz){
    rotacaoSimplesDireitaArtista(&(*raiz)->Dir);
    rotacaoSimplesEsquerdaArtista(&(*raiz));
}

int alturaNoArtista(Artista* raiz){
    return raiz == NULL ? -1 : raiz->altura;
}

int fatorBalanceamentoArtista(Artista* raiz){
    int bl;
    bl = raiz != NULL ? abs(alturaNoArtista(raiz->Esq) - alturaNoArtista(raiz->Dir)) : 0;
    return bl;
}

Artista* criarArtista(char* nome, char* tipo, char* estiloM) {
    Artista* no = (Artista*)malloc(sizeof(Artista));

    strncpy(no->nome, nome, sizeof(no->nome) - 1);
    no->nome[sizeof(no->nome) - 1] = '\0'; // Garante que a string seja terminada corretamente
    strncpy(no->tipo, tipo, sizeof(no->tipo) - 1);
    no->tipo[sizeof(no->tipo) - 1] = '\0';
    strncpy(no->estiloMusical, estiloM, sizeof(no->estiloMusical) - 1);
    no->estiloMusical[sizeof(no->estiloMusical) - 1] = '\0';
    no->albuns = NULL;

    no->numAlbuns = 0;
    no->Esq = NULL;
    no->Dir = NULL;
    return no;
}

int insereArtista(Artista** raiz, Artista* novo, char* nome) {
    int inseriu = 0;

    if (*raiz == NULL) {
        *raiz = novo; // Insere o novo artista na posição correta
        inseriu = 1;
    } else {
        int comparacao = strcasecmp(novo->nome, (*raiz)->nome);
        if (comparacao < 0) {
            if (inseriu = insereArtista(&(*raiz)->Esq, novo, nome) == 1){ // Insere na subárvore esquerda
                if(fatorBalanceamentoArtista(*raiz) >= 2){
                    if(strcmp((*raiz)->Esq->nome, nome) == 1){
                        rotacaoSimplesDireitaArtista(&(*raiz));
                    }else {
                        rotacaoDuplaDireitaArtista(&(*raiz));
                    }
                }
            }
             
        } else if (comparacao > 0) {
            if (inseriu = insereArtista(&(*raiz)->Dir, novo, nome) == 1){ // Insere na subárvore direita
                if(fatorBalanceamentoArtista(*raiz) >= 2){
                    if(strcmp((*raiz)->Dir->nome, nome) == -1){
                        rotacaoSimplesEsquerdaArtista(&(*raiz));
                    }else {
                        rotacaoDuplaEsquerdaArtista(&(*raiz));
                    }
                }
            } 
        }
        (*raiz)->altura = pegaAlturaArtista((*raiz));
    }
    
    return inseriu;
}

void imprimirArtistas(Artista* R) {
    if (R != NULL) {
        imprimirArtistas(R->Esq);
        printf("-------------------------------------------------------------\n");
        printf("%-15s %-10s %-15s %-5s\n", "Nome", "Tipo", "Estilo", "Albuns");
        printf("%-15s  %-10s  %-15s %-5d\n", R->nome, R->tipo, R->estiloMusical, R->numAlbuns);
        printf("-------------------------------------------------------------\n");
        imprimirArtistas(R->Dir);
    }
}

int comparaString(const char* str1, const char* str2) {
    return strcmp(str1, str2) == 0;
}

void buscaArtista(Artista* R, const char* nome, Artista** resultado) {
    *resultado = NULL;

    if (R != NULL) {
        if (strcmp(R->nome, nome) == 0) {
            *resultado = R;
        } else if (strcmp(nome, R->nome) < 0) {
            buscaArtista(R->Esq, nome, resultado);
        } else {
            buscaArtista(R->Dir, nome, resultado);
        }
    }
}

void cadastrarArtista(Artista** raiz, char* nome, char* tipo, char* estilo) {
    Artista* artista = NULL;
    buscaArtista(*raiz, nome, &artista); // Resultado da busca armazenado em 'artista'

    if (artista != NULL) {
        printf("Artista \"%s\" ja existe!\n", nome);
    } else {
        Artista* novo = criarArtista(nome, tipo, estilo);
        if (insereArtista(raiz, novo, nome)) {
            printf("Artista \"%s\" cadastrado com sucesso!\n", nome);
        }
    }
}

void mostrarArtistasPorTipo(Artista* raiz, const char* tipo) {
    if (raiz != NULL) {
        mostrarArtistasPorTipo(raiz->Esq, tipo);
        if (strcmp(raiz->tipo, tipo) == 0) {
            printf("Artista: %s, Tipo: %s, Estilo: %s\n", raiz->nome, raiz->tipo, raiz->estiloMusical);
        }
        mostrarArtistasPorTipo(raiz->Dir, tipo);
    }
}

void mostrarArtistasPorEstilo(Artista* raiz, const char* estilo) {
    if (raiz != NULL) {
        mostrarArtistasPorEstilo(raiz->Esq, estilo);
        if (strcmp(raiz->estiloMusical, estilo) == 0) {
            printf("Artista: %s, Tipo: %s, Estilo: %s\n", raiz->nome, raiz->tipo, raiz->estiloMusical);
        }
        mostrarArtistasPorEstilo(raiz->Dir, estilo);
    }
}

void mostrarArtistasPorEstiloETipo(Artista* raiz, const char* estilo, const char* tipo) {
    if (raiz != NULL) {
        mostrarArtistasPorEstiloETipo(raiz->Esq, estilo, tipo);
        if (strcmp(raiz->estiloMusical, estilo) == 0 && strcmp(raiz->tipo, tipo) == 0) {
            printf("Artista: %s, Tipo: %s, Estilo: %s\n", raiz->nome, raiz->tipo, raiz->estiloMusical);
        }
        mostrarArtistasPorEstiloETipo(raiz->Dir, estilo, tipo);
    }
}

void mostrarAlbunsDeArtista(Artista* raiz, char* nomeArtista) {
    Artista* artista = NULL;
    buscaArtista(raiz, nomeArtista, &artista);

    if (artista != NULL) {
        printf("Albuns do artista \"%s\":\n", artista->nome);
        imprimirAlbuns(artista->albuns);
    } else {
        printf("Artista \"%s\" nao encontrado!\n", nomeArtista);
    }
}

void mostrarAlbunsPorAnoDeArtista(Artista* raiz, char* nomeArtista, char* ano) {
    Artista* artista = NULL;
    buscaArtista(raiz, nomeArtista, &artista);

    if (artista != NULL) {
        printf("Albuns do artista \"%s\" no ano \"%s\":\n", artista->nome, ano);
        imprimirAlbunsPorAno(artista->albuns, ano);
    } else {
        printf("Artista \"%s\" nao encontrado!\n", nomeArtista);
    }
}

void mostrarMusicasDeAlbum(Artista* raiz, char* nomeArtista, char* tituloAlbum) {
    Artista* artista = NULL;
    buscaArtista(raiz, nomeArtista, &artista);

    if (artista != NULL) {
        Album* album = NULL;
        buscaAlbum(artista->albuns, tituloAlbum, &album);

        if (album != NULL) {
            printf("Musicas do album \"%s\" do artista \"%s\":\n", album->titulo, artista->nome);
            imprimirMusicas(album->musicas); 
        } else {
            printf("Album \"%s\" nao encontrado para o artista \"%s\"!\n", tituloAlbum, nomeArtista);
        }
    } else {
        printf("Artista \"%s\" nao encontrado.\n", nomeArtista);
    }
}

int temAlbumDoAno(Album* raiz, const char* ano) {
    return raiz != NULL && (
        strcmp(raiz->anoDeLancamento, ano) == 0 ||
        temAlbumDoAno(raiz->Esq, ano) ||
        temAlbumDoAno(raiz->Dir, ano)
    );
}

void mostrarAlbunsPorAnoDeTodosArtistas(Artista* raiz, const char* ano) {
    if (raiz != NULL) {
        mostrarAlbunsPorAnoDeTodosArtistas(raiz->Esq, ano);

        if (temAlbumDoAno(raiz->albuns, ano)) {
            printf("Artista: \"%s\"\n", raiz->nome);
            imprimirAlbunsPorAno(raiz->albuns, (char*)ano);
        }

        mostrarAlbunsPorAnoDeTodosArtistas(raiz->Dir, ano);
    }
}

void mostrarDadosDeMusica(Artista* raiz, char* tituloMusica) {
    if (raiz != NULL) {
        mostrarDadosDeMusica(raiz->Esq, tituloMusica);

        Album* albumAtual = raiz->albuns;
        while (albumAtual != NULL) {
            Musica* musica = NULL;
            buscarMusica(albumAtual->musicas, tituloMusica, &musica); 

            if (musica != NULL) {
                printf("Musica: %s\n", musica->titulo);
                printf("Artista: %s\n", raiz->nome);
                printf("Album: %s\n", albumAtual->titulo);
                printf("Ano de Lançamento: %s\n", albumAtual->anoDeLancamento);
                return;
            }

            albumAtual = albumAtual->Dir;
        }

        mostrarDadosDeMusica(raiz->Dir, tituloMusica);
    }
}

void mostrarMusicas(Musica* raiz) {
    if (raiz == NULL) return;

    mostrarMusicas(raiz->Esq);
    printf("    Música: %s (%d min)\n", raiz->titulo, raiz->quantMinutos);
    mostrarMusicas(raiz->Dir);
}

void mostrarAlbuns(Album* raiz) {
    if (raiz == NULL) return;

    mostrarAlbuns(raiz->Esq);
    printf("  Álbum: %s (%s)\n", raiz->titulo, raiz->anoDeLancamento);
    mostrarMusicas(raiz->musicas);
    mostrarAlbuns(raiz->Dir);
}


void mostrarMusicasDoArtista(Artista* raiz, const char* nomeArtista) {
    if (raiz != NULL) {
        int cmp = strcmp(nomeArtista, raiz->nome);
        if (cmp < 0) {
            mostrarMusicasDoArtista(raiz->Esq, nomeArtista);
        } else if (cmp > 0) {
            mostrarMusicasDoArtista(raiz->Dir, nomeArtista);
        } else {
            // Artista encontrado
            printf("Musicas do artista: %s\n", raiz->nome);
            mostrarAlbuns(raiz->albuns);
        }
        
    } else{
        printf("Artista \"%s\" nao encontrado.\n", nomeArtista);
    }
    
}

void liberarArvoreArtistas(Artista* raiz) {
    if (raiz == NULL) return;
    liberarArvoreArtistas(raiz->Esq);
    liberarArvoreArtistas(raiz->Dir);
    liberarAlbuns(raiz->albuns);
    free(raiz);
}