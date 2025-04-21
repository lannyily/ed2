#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/musica.h"
#include "../Includes/album.h" 
#include "../Includes/artista.h"
#include "../includes/playlist.h"

void cadastrarMusica(struct Artista* raiz, const char* nomeArtista, const char* tituloAlbum, const char* tituloMusica, int duracao) {
    struct Artista* artista = NULL;
    buscaArtista(raiz, (char*)nomeArtista, &artista);

    if (artista != NULL) {
        Album* album = NULL;
        buscaAlbum(artista->albuns, (char*)tituloAlbum, &album);

        if (album != NULL) {
            Musica* novaMusica = criarMusica((char*)tituloMusica, duracao);
            if (insereMusica(&(album->musicas), novaMusica)) {
                printf("Música \"%s\" cadastrada com sucesso no álbum \"%s\" do artista \"%s\".\n", tituloMusica, tituloAlbum, nomeArtista);
            } else {
                printf("Erro ao cadastrar a música \"%s\". Ela já existe no álbum.\n", tituloMusica);
            }
        } else {
            printf("Álbum \"%s\" não encontrado para o artista \"%s\".\n", tituloAlbum, nomeArtista);
        }
    } else {
        printf("Artista \"%s\" não encontrado.\n", nomeArtista);
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
    if (*R == NULL) {
        *R = No;
        return 1; // Retorna 1 para indicar que a música foi inserida com sucesso
    }

    if (strcmp(No->titulo, (*R)->titulo) < 0) {
        return insereMusica(&((*R)->Esq), No); // Tenta inserir na subárvore esquerda
    } else if (strcmp(No->titulo, (*R)->titulo) > 0) {
        return insereMusica(&((*R)->Dir), No); // Tenta inserir na subárvore direita
    }

    return 0; // Retorna 0 se a música já existir
}

void CadastrarMusica(Album* raiz, char* nomeAlbum, char* titulo, int quantMinutos) {
  Album *album;
  album = NULL;

  buscaAlbum(raiz, nomeAlbum, &album); 

  if (album != NULL) {
      Musica* novaMusica = criarMusica(titulo, quantMinutos);
      if (insereMusica(&(album->musicas), novaMusica)) {
          album->quantMusicas++;
          printf("A musica \"%s\" foi cadastrada no álbum \"%s\"\n", titulo, nomeAlbum);
      } else {
          printf("A musica \"%s\" ja está cadastrada no álbum \"%s\"\n", titulo, nomeAlbum);
      }
  } else {
      printf("Álbum \"%s\" nao encontrado!\n", nomeAlbum);
  }
}

void imprimirMusicas(Musica* R) {
    if (R != NULL) {
        imprimirMusicas(R->Esq); // Percorre a subárvore esquerda
        printf("Título: %s, Duração: %d minutos\n", R->titulo, R->quantMinutos);
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

void liberarMusicas(Musica* raiz) {
    if (raiz == NULL) return;
    liberarMusicas(raiz->Esq);
    liberarMusicas(raiz->Dir);
    free(raiz);
}

/*

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

    return raiz;
}

void liberarMusicas(Musica *raiz) {
    if (raiz != NULL) {
        liberarMusicas(raiz->Esq);
        liberarMusicas(raiz->Dir);
        free(raiz);
    }
}

int musicaEmPlaylists(Playlist* raiz, const char* titulo) {
    Musica* resultado = NULL;

    if (raiz != NULL) {
        buscarMusica(raiz->musicas, titulo, &resultado);
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
                printf("Música \"%s\" removida do álbum \"%s\" do artista \"%s\".\n", tituloMusica, tituloAlbum, nomeArtista);
            } else {
                printf("Música \"%s\" não pode ser removida porque está em uma playlist.\n", tituloMusica);
            }
        } else {
            printf("Álbum \"%s\" não encontrado.\n", tituloAlbum);
        }
    } else {
        printf("Artista \"%s\" não encontrado.\n", nomeArtista);
    }
}
*/