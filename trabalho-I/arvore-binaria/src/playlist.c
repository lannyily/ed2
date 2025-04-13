#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/playlist.h"
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"


// Cria uma nova playlist
Playlist* criarPlaylist(const char *nome) {
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
    if (raiz == NULL || strcmp(raiz->nome, nome) == 0) {
        return raiz;
    }
    if (strcmp(nome, raiz->nome) < 0) {
        return buscarPlaylist(raiz->esquerda, nome);
    } else {
        return buscarPlaylist(raiz->direita, nome);
    }
}

// Insere uma música na árvore binária de músicas de uma playlist
Musica* inserirMusica(Musica *raiz, Musica *novaMusica) {
    if (raiz == NULL) {
        return novaMusica; // Insere a nova música na posição correta
    }

    if (strcmp(novaMusica->titulo, raiz->titulo) < 0) {
        raiz->Esq = inserirMusica(raiz->Esq, novaMusica);
    } else if (strcmp(novaMusica->titulo, raiz->titulo) > 0) {
        raiz->Dir = inserirMusica(raiz->Dir, novaMusica);
    } else {
        printf("Musica \"%s\" ja existe na playlist.\n", novaMusica->titulo);
    }

    return raiz;
}



// Imprime os dados de uma playlist e suas músicas
void imprimirPlaylist(Playlist *playlist) {
    if (playlist != NULL) {
        printf("Playlist: %s\n", playlist->nome);
        printf("Músicas:\n");
        imprimirMusicas(playlist->musicas); 
    } else {
        printf("Playlist não encontrada.\n");
    }
}

Playlist* removerPlaylist(Playlist *raiz, const char *nome) {
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

      if (raiz->esquerda == NULL) {
          Playlist *temp = raiz->direita;
          free(raiz);
          return temp;
      } else if (raiz->direita == NULL) {
          Playlist *temp = raiz->esquerda;
          free(raiz);
          return temp;
      }

      // Substitui pelo menor valor da subárvore direita
      Playlist *temp = raiz->direita;
      while (temp->esquerda != NULL) {
          temp = temp->esquerda;
      }
      strcpy(raiz->nome, temp->nome);
      raiz->musicas = temp->musicas;
      raiz->direita = removerPlaylist(raiz->direita, temp->nome);
  }

  return raiz;
}

