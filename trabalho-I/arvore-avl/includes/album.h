#ifndef ALBUM_H
#define ALBUM_H

#include "musica.h"


struct Artista;

typedef struct Album {
    char titulo[50];
    char anoDeLancamento[5];
    int quantMusicas;
    Musica *musicas;

    int altura;
    
    struct Album *Esq;
    struct Album *Dir;
} Album;

void rotacaoEsqAl(Album** raiz);
void rotacaoDirAl(Album** raiz);
int maiorAl(int alt1, int alt2);
int pegaAlturaAl(Album* raiz);
int alturaNoAl(Album* no);
int fatorBalanceamentoAl(Album* raiz);
void balanceamentoAl(Album** raiz);
Album* criarAlbum(char* titulo, char* anoLancamento);
int insereAlbum(Album** R, Album* No);
void cadastrarAlbum(struct Artista* raiz, char* nomeA, char* titulo, char* anoLancamento); 
void buscaAlbum(Album* R,  char* nome, Album** resultado);
void imprimirAlbuns(Album* R);
void imprimirAlbunsPorAno(Album* R, char* ano);
int comparaString( char* str1,  char* str2);
void liberarAlbuns(Album* raiz);

#endif 