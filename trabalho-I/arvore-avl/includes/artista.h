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

int maior(int x, int y);
int pegaAltura(Artista* raiz);
void rotacaoSimplesDireita(Artista** raiz);
void rotacaoSimplesEsquerda(Artista** raiz);
void rotacaoDuplaDireita(Artista** raiz);
void rotacaoDuplaEsquerda(Artista** raiz);
int alturaNo(Artista* raiz);
int fatorBalanceamento(Artista* raiz);
Artista* criarArtista(char* nome, char* tipo, char* estiloM);
int insereArtista(Artista** raiz, Artista* novo, char* nome);
void imprimirArtistas(Artista* R);
void buscaArtista(Artista* R, const char* nome, Artista** resultado);
void cadastrarArtista(Artista** raiz, char* nome, char* tipo, char* estilo);
void mostrarMusicasDeAlbum(Artista* raiz, char* nomeArtista, char* tituloAlbum);
void mostrarDadosDeMusica(Artista* raiz, char* tituloMusica);
void mostrarArtistasPorTipo(Artista* raiz, const char* tipo);
void mostrarArtistasPorEstilo(Artista* raiz, const char* estilo);
void mostrarArtistasPorEstiloETipo(Artista* raiz, const char* estilo, const char* tipo);
int temAlbumDoAno(Album* raiz, const char* ano);
void mostrarAlbunsPorAnoDeTodosArtistas(Artista* raiz, const char* ano);
void mostrarMusicas(Musica* raiz);
void mostrarAlbuns(Album* raiz);
void mostrarMusicasDoArtista(Artista* raiz, const char* nomeArtista);
void liberarArvoreArtistas(Artista* raiz);

#endif // ARTISTA_H
