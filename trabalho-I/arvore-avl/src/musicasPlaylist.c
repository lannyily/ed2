#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/playlist.h"
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"
#include "../includes/musicasPlaylist.h"

int maiorMusicasPlaylist(int x, int y) {
    if (x > y){
        return x;
    } else {
        return y;
    }
}

int pegaAlturaMusicasPlaylist(MusicasPlaylist* raiz){
    int altura = 0;
    if(raiz != NULL){
        int alturaEsq = pegaAlturaMusicasPlaylist(raiz->Esq);
        int alturaDir = pegaAlturaMusicasPlaylist(raiz->Dir);

        if(alturaEsq > alturaDir){
            altura = alturaEsq + 1;
        } else {
            altura = alturaDir + 1;
        }
    }
    return altura;
}

void rotacaoSimplesDireitaMusicasPlaylist(MusicasPlaylist** raiz){
    if((*raiz)->Esq != NULL){
        MusicasPlaylist* aux = (*raiz)->Esq;
        (*raiz)->Esq = aux->Dir;
        aux->Dir = *raiz;
        (*raiz)->altura = maiorMusicasPlaylist(pegaAlturaMusicasPlaylist((*raiz)->Esq), pegaAlturaMusicasPlaylist((*raiz)->Dir)) + 1;
        aux->altura = maiorMusicasPlaylist(pegaAlturaMusicasPlaylist(aux->Esq), (*raiz)->altura) + 1;
        (*raiz) = aux;
    }
}

void rotacaoSimplesEsquerdaMusicasPlaylist(MusicasPlaylist** raiz){
    if((*raiz)->Dir != NULL){
        MusicasPlaylist* aux = (*raiz)->Dir;
        (*raiz)->Dir = aux->Esq;
        aux->Esq = *raiz;
        (*raiz)->altura = maiorMusicasPlaylist(pegaAlturaMusicasPlaylist((*raiz)->Esq), pegaAlturaMusicasPlaylist((*raiz)->Dir)) + 1;
        aux->altura = maiorMusicasPlaylist(pegaAlturaMusicasPlaylist(aux->Esq), (*raiz)->altura) + 1;
        (*raiz) = aux;
    }
}

void rotacaoDuplaDireitaMusicasPlaylist(MusicasPlaylist** raiz){
    rotacaoSimplesEsquerdaMusicasPlaylist(&(*raiz)->Esq);
    rotacaoSimplesDireitaMusicasPlaylist(&(*raiz));
}

void rotacaoDuplaEsquerdaMusicasPlaylist(MusicasPlaylist** raiz){
    rotacaoSimplesDireitaMusicasPlaylist(&(*raiz)->Dir);
    rotacaoSimplesEsquerdaMusicasPlaylist(&(*raiz));
}

int alturaNoMusicasPlaylist(MusicasPlaylist* raiz){
    return raiz == NULL ? -1 : raiz->altura;
}

int fatorBalanceamentoMusicasPlaylist(MusicasPlaylist* raiz){
    int bl;
    bl = raiz != NULL ? abs(alturaNoMusicasPlaylist(raiz->Esq) - alturaNoMusicasPlaylist(raiz->Dir)) : 0;
    return bl;
}

MusicasPlaylist* criar(char* nomeA, char* tituloA, char* tituloM){
    MusicasPlaylist* no = (MusicasPlaylist*)malloc(sizeof(MusicasPlaylist));

    strcpy(no->tituloM, tituloM);
    strcpy(no->tituloA, tituloA);
    strcpy(no->nome, nomeA);

    no->Dir = NULL;
    no->Esq = NULL;
    return no;
}

void buscarMusicaPlaylist(MusicasPlaylist* raiz, const char* tituloM, MusicasPlaylist** resultado){
    *resultado = NULL;

    if (raiz != NULL){
        if(strcmp(raiz->tituloM, tituloM) == 0){
            *resultado = raiz;
        } else if (strcmp(tituloM, raiz->tituloM) < 0){
            buscarMusicaPlaylist(raiz->Esq, tituloM, resultado);
        } else {
            buscarMusicaPlaylist(raiz->Dir, tituloM, resultado);
        }
    }
}

int addMusica(MusicasPlaylist** R, MusicasPlaylist* musica, char* tituloM){
    int inseriu = 0;

    if (*R == NULL){
        *R = musica;
        inseriu = 1;
    }

    if (strcmp(musica->tituloM, (*R)->tituloM) < 0){
        if (inseriu = addMusica(&((*R)->Esq), musica, tituloM) == 1){
            if(fatorBalanceamentoMusicasPlaylist(*R) >= 2){
                if (strcmp((*R)->Esq->tituloM, tituloM) == 1){
                    rotacaoSimplesDireitaMusicasPlaylist(&(*R));
                } else {
                    rotacaoDuplaDireitaMusicasPlaylist(&(*R));
                }
            }
        }
    } else if (strcmp(musica->tituloM, (*R)->tituloM) > 0){
        if (inseriu = addMusica(&((*R)->Dir), musica, tituloM) == 1){
            if(fatorBalanceamentoMusicasPlaylist(*R) >= 2){
                if(strcmp((*R)->Dir->tituloM, tituloM) == -1){
                    rotacaoSimplesEsquerdaMusicasPlaylist(&(*R));
                }else {
                    rotacaoDuplaEsquerdaMusicasPlaylist(&(*R));
                }
            }
        }
    }
    return inseriu;
}


void cadastrarMusicasPlaylist(Playlist* raiz, char* nomePlaylist, char* nomeA, char* tituloA, char* tituloM){
    Playlist* encontrarNome = NULL;
    buscarPlaylist(raiz, nomePlaylist, &encontrarNome);

    if(encontrarNome != NULL){
        MusicasPlaylist* buscaTitulo = NULL;
        buscarMusicaPlaylist(raiz->musicas, tituloM, &buscaTitulo);

        if (buscaTitulo != NULL){
            printf("Musica \"%s\" ja esta nessa playlist!\n", tituloM);
        } else {
            MusicasPlaylist* novaMusica = criar(nomeA, tituloA, tituloM);
            if(addMusica(&(encontrarNome->musicas), novaMusica, tituloM)){
                printf("Musica \"%s\" adicionada a playlist \"%s\"!\n", tituloM, nomePlaylist);
            }
        }
    } else {
        printf("Playlist \"%s\" nao encontrada\n", nomePlaylist);
    }
    
}

MusicasPlaylist *removerMusicaPlaylist(MusicasPlaylist* raiz, const char* tituloM){
    if (raiz == NULL){
        return NULL;
    }

    if (strcmp(tituloM, raiz->tituloM) < 0){
        raiz->Esq = removerMusicaPlaylist(raiz->Esq, tituloM);
    } else if (strcmp(tituloM, raiz->tituloM) > 0){
        raiz->Dir = removerMusicaPlaylist(raiz->Dir, tituloM);
    } else {

        printf("Musica \"%s\" removida da playlist!\n", raiz->tituloM);

        MusicasPlaylist* temp;
        if (raiz->Esq == NULL){
            temp = raiz->Dir;
            free(raiz);
            raiz = temp;
        } else if (raiz->Dir == NULL){
            temp = raiz->Esq;
            free(raiz);
            raiz = temp;
        } else{ // Encontrou a playlist
            MusicasPlaylist *sucessor = raiz->Dir;
            while (sucessor->Esq != NULL){
                sucessor = sucessor->Esq;
            } 

            strcpy(raiz->nome, sucessor->nome);
            strcpy(raiz->tituloA, sucessor->tituloA);
            strcpy(raiz->tituloM, sucessor->tituloM);
            raiz->Dir = removerMusicaPlaylist(raiz->Dir, sucessor->tituloM); //Remove o nó duplicado, ja que ele foi copiado

        }
    }
    return raiz;
}

void imprimirMusicasPlaylist(MusicasPlaylist* R){
    
    if(R != NULL){
        
        imprimirMusicasPlaylist(R->Esq);

        printf("Musica: %s, Album: %s, Artista: %s\n", R->tituloM, R->tituloA, R->nome);
        imprimirMusicasPlaylist(R->Dir);
    }
   
}

