#ifndef ALBUM_H
#define ALBUM_H

#include "musica.h"


struct Artista;

typedef struct Album {
    char titulo[50];
    char anoDeLancamento[5];
    int quantMusicas;
    Musica *musicas;
    struct Album *Esq;
    struct Album *Dir;
} Album;

Album* criarAlbum(char* titulo, char* anoLancamento);
int insereAlbum(Album** R, Album* No);
void cadastrarAlbum(struct Artista* raiz, char* nomeA, char* titulo, char* anoLancamento); 
void buscaAlbum(Album* R,  char* nome, Album** resultado);
void imprimirAlbuns(Album* R);
void imprimirAlbunsPorAno(Album* R, char* ano);
void liberarAlbuns(Album* raiz);

#endif 