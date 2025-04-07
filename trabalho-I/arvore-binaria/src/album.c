#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/album.h"
#include "artista.c"

Album* criarAlbum(char* titulo, char* anoLancamento){
    Album* no = (Album*)malloc(sizeof(Album));

    strcpy(no->titulo, titulo);
    strcpy(no->anoDeLancamento, anoLancamento);
    no->quantMusicas = 0;

    no->Dir = NULL;
    no->Esq = NULL;

    return no; 
}

int insereAlbum(Album** R, Album* No){
    int inseriu = 0;
    
    if (*R == NULL) {
        *R = No;
    }
    else if (strcmp(No->titulo, (*R)->titulo) < 0) {
        inseriu = insere(&((*R)->Esq), No);
    }
    else if (strcmp(No->titulo, (*R)->titulo) > 0) {
        inseriu = insere(&((*R)->Dir), No);
    }
    else {
        inseriu = 1;  
    }
    return inseriu;
}

void cadastrarAlbum(Artista* raiz, char* nomeA, char* titulo, char* anoLancamento){
    Artista* artista = buscaArtista(raiz, nomeA);
    
    if (artista != NULL) {
        Album* novoAlbum = criarAlbum(titulo, anoLancamento);
        if (insereAlbum(&(artista->albuns), novoAlbum)) {
            artista->numAlbuns++;
            printf("Álbum \"%s\" cadastrado para o artista \"%s\"\n", titulo, nomeA);
        } else {
            printf("Álbum \"%s\" já existe para o artista \"%s\"\n", titulo, nomeA);
        }
    } else {
        printf("Artista \"%s\" não encontrado!\n", nomeA);
    }
}
