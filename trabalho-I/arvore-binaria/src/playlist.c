#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/playlist.h"
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"


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
int inserirPlaylist(Playlist **raiz, Playlist *novaPlaylist) {
    int inseriu = 0;

    if (*raiz == NULL) {
        *raiz = novaPlaylist;
        inseriu = 1;
    } else {
        int comparacao = strcmp(novaPlaylist->nome, (*raiz)->nome);

        if (comparacao < 0) {
            inseriu = inserirPlaylist(&((*raiz)->esquerda), novaPlaylist);
        } else if (comparacao > 0) {
            inseriu = inserirPlaylist(&((*raiz)->direita), novaPlaylist);
        }
        // Se for igual, não insere e mantém inseriu = 0
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
        if(inserirPlaylist(raiz, novaPlaylist)){
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
        // Encontrou a playlist
       // liberarMusicas(raiz->musicas); // Libera a árvore de músicas

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