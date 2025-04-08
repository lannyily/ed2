#include "../include/musica.h"
#include "../include/album.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void buscaMusica(Musica* R, char* titulo, Musica** resultado) {
  *resultado = NULL; // Inicializa o resultado como NULL

  if (R != NULL) {
      if (strcmp(R->titulo, titulo) == 0) {
          *resultado = R; // Encontrou a música
      } else if (strcmp(titulo, R->titulo) < 0) {
          buscaMusica(R->Esq, titulo, resultado); // Continua na subárvore esquerda
      } else {
          buscaMusica(R->Dir, titulo, resultado); // Continua na subárvore direita
      }
  }
}