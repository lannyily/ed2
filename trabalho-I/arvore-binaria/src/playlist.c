#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/playlist.h"
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"


// Cria uma nova playlist
Playlist* criarPlaylist(char *nome) {
    Playlist *nova = (Playlist *)malloc(sizeof(Playlist));
    if (nova != NULL) {
        strncpy(nova->nome, nome, sizeof(nova->nome) - 1);
        nova->nome[sizeof(nova->nome) - 1] = '\0';
        nova->musicas = NULL; 
        nova->esquerda = NULL;
        nova->direita = NULL;
    }
    return nova;
}

// Insere uma playlist na árvore binária de playlists
Playlist* inserirPlaylist(Playlist *raiz, Playlist *novaPlaylist) {
    if (raiz == NULL) {
      return novaPlaylist; // Insere a nova playlist na posição correta
    }

    if (strcmp(novaPlaylist->nome, raiz->nome) < 0) {
        raiz->esquerda = inserirPlaylist(raiz->esquerda, novaPlaylist);
    } else if (strcmp(novaPlaylist->nome, raiz->nome) > 0) {
        raiz->direita = inserirPlaylist(raiz->direita, novaPlaylist);
    } else {
        printf("Playlist \"%s\" ja existe.\n", novaPlaylist->nome);
    }

    return raiz;
}

// Busca uma playlist pelo nome
Playlist* buscarPlaylist(Playlist* raiz, const char* nome) {
    if (raiz == NULL) return NULL;

    if (strcmp(raiz->nome, nome) == 0) {
        return raiz;
    } else if (strcmp(nome, raiz->nome) < 0) {
        return buscarPlaylist(raiz->esquerda, nome);
    } else {
        return buscarPlaylist(raiz->direita, nome);
    }
}

/*
Musica* inserirMusicas(Musica* raiz, Musica* nova) {
    if (raiz == NULL) return nova;

    int cmp = strcmp(nova->titulo, raiz->titulo);

    if (cmp < 0)
        raiz->Esq = inserirMusica(raiz->Esq, nova);
    else if (cmp > 0)
        raiz->Dir = inserirMusica(raiz->Dir, nova);
    else
        printf("Música \"%s\" já existe na playlist.\n", nova->titulo);

    return raiz;
}

void inserirMusicaNaPlaylist(Playlist* playlist, Musica* novaMusica) {
    playlist->musicas = inserirMusica(playlist->musicas, novaMusica);
}

*/
// Imprime os dados de uma playlist e suas músicas, diminui a quantidade de returns
void imprimirPlaylist(Playlist *playlist) {
    if (playlist != NULL) {
        printf("Playlist: %s\n", playlist->nome);
        printf("Músicas:\n");
        imprimirMusicas(playlist->musicas); 
    } else {
        printf("Playlist não encontrada.\n");
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
        liberarMusicas(raiz->musicas); // Libera a árvore de músicas

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


