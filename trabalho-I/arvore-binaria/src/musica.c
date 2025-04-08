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
          printf("A música \"%s\" foi cadastrada no álbum \"%s\"\n", titulo, nomeAlbum);
      } else {
          printf("A música \"%s\" já está cadastrada no álbum \"%s\"\n", titulo, nomeAlbum);
      }
  } else {
      printf("Álbum \"%s\" não encontrado!\n", nomeAlbum);
  }
}