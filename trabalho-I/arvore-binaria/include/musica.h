#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "album.h"

#ifndef MUSICA_H
#define MUSICA_H


typedef struct Musica {
    char titulo[20];
    int quantMinutos;

    struct Musica* Esq;
    struct Musica* Dir;
}Musica;

Musica* criarMusica(char* titulo, int quantMinutos);
int insereMusica(Musica **R, Musica *No);
void CadastrarMusica(Album* raiz, char* nomeAlbum, char* titulo, int quantMinutos);

#endif