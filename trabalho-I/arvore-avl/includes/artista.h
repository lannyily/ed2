#ifndef ARTISTA_H
#define ARTISTA_H

#include "album.h"

typedef struct Artista {
    char nome[50];
    char tipo[20];
    char estiloMusical[20];
    int numAlbuns;
    Album* albuns;

    int altura;

    struct Artista* Esq;
    struct Artista* Dir;
} Artista;

void rotacaoEsqA(Artista** raiz);
void rotacaoDirA(Artista** raiz);
int maiorA(int alt1, int alt2);
int pegaAlturaA(Artista* raiz);
int alturaNoA(Artista* no);
int fatorBalanceamentoA(Artista* raiz);
void balanceamentoA(Artista** raiz);
Artista* criarArtista(char* nome, char* tipo, char* estiloM);
int insereArtista(Artista** R, Artista* No);
void imprimirArtistas(Artista* R);
void buscaArtista(Artista* R,  char* nome, Artista** resultado);
void cadastrarArtista(Artista** raiz, char* nome, char* tipo, char* estilo);
void mostrarMusicasDeAlbum(Artista* raiz, char* nomeArtista, char* tituloAlbum);
void mostrarDadosDeMusica(Artista* raiz, char* tituloMusica);
void mostrarArtistasPorTipo(Artista* raiz, char* tipo);
void mostrarArtistasPorEstilo(Artista* raiz, char* estilo);
void mostrarArtistasPorEstiloETipo(Artista* raiz, char* estilo, char* tipo);
int temAlbumDoAno(Album* raiz, char* ano);
void mostrarAlbunsPorAnoDeTodosArtistas(Artista* raiz, char* ano);
void mostrarMusicas(Musica* raiz);
void mostrarAlbuns(Album* raiz);
void mostrarMusicasDoArtista(Artista* raiz, char* nomeArtista);
void liberarArtistas(Artista* raiz);

#endif 
