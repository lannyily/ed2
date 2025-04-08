#include "../include/album.h"
#include "../include/artista.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        inseriu = insereAlbum(&((*R)->Esq), No);
    }
    else if (strcmp(No->titulo, (*R)->titulo) > 0) {
        inseriu = insereAlbum(&((*R)->Dir), No);
    }
    else {
        inseriu = 1;  
    }
    return inseriu;
}

void cadastrarAlbum(Artista* raiz, char* nomeA, char* titulo, char* anoLancamento) {
    Artista* artista = NULL;
    buscaArtista(raiz, nomeA, &artista); // Resultado da busca armazenado em 'artista'

    if (artista != NULL) {
        Album* album = NULL;
        buscaAlbum(artista->albuns, titulo, &album); // Resultado da busca armazenado em 'album'

        if (album == NULL) { // Se o álbum não foi encontrado
            Album* novoAlbum = criarAlbum(titulo, anoLancamento);
            if (insereAlbum(&(artista->albuns), novoAlbum)) {
                artista->numAlbuns++;
                printf("Álbum \"%s\" cadastrado para o artista \"%s\"\n", titulo, nomeA);
            }
        } else {
            printf("Álbum \"%s\" já existe para o artista \"%s\"\n", titulo, nomeA);
        }
    } else {
        printf("Artista \"%s\" não encontrado!\n", nomeA);
    }
}

void buscaAlbum(Album* R, char* nome, Album** resultado) {
    *resultado = NULL; // Inicializa o resultado como NULL

    if (R != NULL) {
        if (comparaString(R->titulo, nome)) {
            *resultado = R; // Encontrou o álbum
        } else if (strcmp(nome, R->titulo) < 0) {
            buscaAlbum(R->Esq, nome, resultado); // Continua na subárvore esquerda
        } else {
            buscaAlbum(R->Dir, nome, resultado); // Continua na subárvore direita
        }
    }
}