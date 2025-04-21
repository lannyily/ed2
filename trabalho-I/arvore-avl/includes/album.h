#ifndef ALBUM_H
#define ALBUM_H

#include "musica.h"

// Declaração antecipada para evitar dependência circular
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
void buscaAlbum(Album* R, const char* nome, Album** resultado);
void imprimirAlbuns(Album* R);
void imprimirAlbunsPorAno(Album* R, char* ano);
int comparaString(const char* str1, const char* str2);
void liberarAlbuns(Album* raiz);

#endif // ALBUM_H