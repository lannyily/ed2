#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef ARTISTA_H
#define ARTISTA_H

typedef struct Album Album;

typedef struct Artista {
    char nome[10];
    char tipo[10];
    char estiloMusical[10];
    int numAlbuns;
    Album* albuns;

    struct Artista* Esq;
    struct Artista* Dir;
}Artista;

Artista* criarArtista(char* nome, char* tipo, char* estiloM);
int insereArtista(Artista** R, Artista* No);
void imprimirArtistas(Artista* R);
int comparaString(char* nomeBusca, char* nome);
void buscaArtista(Artista* R, char* nome, Artista** resultado);
void cadastrarArtista(Artista** raiz, char* nome, char* tipo, char* estilo);

#endif