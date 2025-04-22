#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/playlist.h"
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"


int maiorPlaylist(int x, int y) {
    if (x > y){
        return x;
    } else {
        return y;
    }
}

int pegaAlturaPlaylist(Playlist* raiz){
    int altura = 0;
    if(raiz != NULL){
        int alturaEsq = pegaAlturaPlaylist(raiz->esquerda);
        int alturaDir = pegaAlturaPlaylist(raiz->direita);

        if(alturaEsq > alturaDir){
            altura = alturaEsq + 1;
        } else {
            altura = alturaDir + 1;
        }
    }
    return altura;
}

void rotacaoSimplesDireitaPlaylist(Playlist** raiz){
    if((*raiz)->esquerda != NULL){
        Playlist* aux = (*raiz)->esquerda;
        (*raiz)->esquerda = aux->direita;
        aux->direita = *raiz;
        (*raiz)->altura = maiorPlaylist(pegaAlturaPlaylist((*raiz)->esquerda), pegaAlturaPlaylist((*raiz)->direita)) + 1;
        aux->altura = maiorPlaylist(pegaAlturaPlaylist(aux->esquerda), (*raiz)->altura) + 1;
        (*raiz) = aux;
    }
}

void rotacaoSimplesEsquerdaPlaylist(Playlist** raiz){
    if((*raiz)->direita != NULL){
        Playlist* aux = (*raiz)->direita;
        (*raiz)->direita = aux->esquerda;
        aux->esquerda = *raiz;
        (*raiz)->altura = maiorPlaylist(pegaAlturaPlaylist((*raiz)->esquerda), pegaAlturaPlaylist((*raiz)->direita)) + 1;
        aux->altura = maiorPlaylist(pegaAlturaPlaylist(aux->direita), (*raiz)->altura) + 1;
        (*raiz) = aux;
    }
}

void rotacaoDuplaDireitaPlaylist(Playlist** raiz){
    rotacaoSimplesEsquerdaPlaylist(&(*raiz)->esquerda);
    rotacaoSimplesDireitaPlaylist(&(*raiz));
}

void rotacaoDuplaEsquerdaPlaylist(Playlist** raiz){
    rotacaoSimplesDireitaPlaylist(&(*raiz)->direita);
    rotacaoSimplesEsquerdaPlaylist(&(*raiz));
}

int alturaNoPlaylist(Playlist* raiz){
    return raiz == NULL ? -1 : raiz->altura;
}

int fatorBalanceamentoPlaylist(Playlist* raiz){
    int bl;
    bl = raiz != NULL ? abs(alturaNoPlaylist(raiz->esquerda) - alturaNoPlaylist(raiz->direita)) : 0;
    return bl;
}

// Busca uma playlist pelo nome
void buscarPlaylist(Playlist* raiz, const char* nome, Playlist** resultado) {
    *resultado = NULL;
    
    if (raiz != NULL){
        if (strcmp(raiz->nome, nome) == 0) {
            *resultado = raiz;
        } else if (strcmp(nome, raiz->nome) < 0) {
            buscarPlaylist(raiz->esquerda, nome, resultado);
        } else {
            buscarPlaylist(raiz->direita, nome, resultado);
        }
    }
    
}

// Cria uma nova playlist
Playlist* criarPlaylist(char *nome) {
    Playlist *nova = (Playlist *)malloc(sizeof(Playlist));
    
    strcpy(nova->nome, nome);
    nova->musicas = NULL; 
    nova->esquerda = NULL;
    nova->direita = NULL;
    
    return nova;
}

// Insere uma playlist na árvore binária de playlists
int inserirPlaylist(Playlist **raiz, Playlist *novaPlaylist, char* nome) {
    int inseriu = 0;

    if (*raiz == NULL) {
        *raiz = novaPlaylist;
        inseriu = 1;
    } else {
        int comparacao = strcmp(novaPlaylist->nome, (*raiz)->nome);

        if (comparacao < 0) {
            if(inseriu = inserirPlaylist(&((*raiz)->esquerda), novaPlaylist, nome) == 1){
                if(fatorBalanceamentoPlaylist(*raiz) >= 2){
                    if (strcmp((*raiz)->esquerda->nome, nome) == 1){
                        rotacaoSimplesDireitaPlaylist(&(*raiz));
                    } else {
                        rotacaoDuplaDireitaPlaylist(&(*raiz));
                    }
                }
            }
        } else if (comparacao > 0) {
           if( inseriu = inserirPlaylist(&((*raiz)->direita), novaPlaylist, nome) == 1){
                if(fatorBalanceamentoPlaylist(*raiz) >= 2){
                    if(strcmp((*raiz)->direita->nome, nome) == -1){
                        rotacaoSimplesEsquerdaPlaylist(&(*raiz));
                    }else {
                        rotacaoDuplaEsquerdaPlaylist(&(*raiz));
                    }
                }
           }
        }
        (*raiz)->altura = pegaAlturaPlaylist((*raiz));
    }

    return inseriu;
}


void cadastrarPlaylist(Playlist** raiz, char* nome){
    Playlist* playlist = NULL;
    buscarPlaylist(*raiz, nome, &playlist);
    if(playlist != NULL){
        printf("Playlist \"%s\" já existe!\n", nome);
    } else {
        Playlist* novaPlaylist = criarPlaylist(nome);
        if(inserirPlaylist(raiz, novaPlaylist, nome)){
            printf("Playlist \"%s\" adicionada!\n", nome);
        }
    }
}


Playlist* removerPlaylist(Playlist *raiz, char *nome) {
    if (raiz == NULL) {
        return NULL;
    }

    if (strcmp(nome, raiz->nome) < 0) {
        raiz->esquerda = removerPlaylist(raiz->esquerda, nome);
    } else if (strcmp(nome, raiz->nome) > 0) {
        raiz->direita = removerPlaylist(raiz->direita, nome);
    } else {
        printf("Playlist \"%s\" removida!\n");
        liberarPlaylists(raiz); // Libera a árvore de músicas

        Playlist *temp;

        if (raiz->esquerda == NULL) {
            temp = raiz->direita;
            free(raiz);
            raiz = temp;
        } else if (raiz->direita == NULL) {
            temp = raiz->esquerda;
            free(raiz);
            raiz = temp;
        } else {
            // Substitui pelo menor valor da subárvore direita
            Playlist *sucessor = raiz->direita;
            while (sucessor->esquerda != NULL) {
                sucessor = sucessor->esquerda;
            }

            // Copia os dados do sucessor para a raiz
            strcpy(raiz->nome, sucessor->nome);
            raiz->musicas = sucessor->musicas;

            // Remove o sucessor da subárvore direita
            raiz->direita = removerPlaylist(raiz->direita, sucessor->nome);
        }
    }

    return raiz;
}

void liberarMusicasPlaylist(MusicasPlaylist *raiz) {
    if (raiz != NULL) {
        liberarMusicasPlaylist(raiz->Esq);
        liberarMusicasPlaylist(raiz->Dir);
        free(raiz);
    }
}

void liberarPlaylists(Playlist *raiz) {
    if (raiz != NULL) {
        liberarPlaylists(raiz->esquerda);
        liberarPlaylists(raiz->direita);
        liberarMusicasPlaylist(raiz->musicas); // libera as músicas dessa playlist
        free(raiz);
    }
}

