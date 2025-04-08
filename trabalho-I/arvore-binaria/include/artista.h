#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef ARTISTA_H
#define ARTISTA_H

typedef struct Album Album;

typedef struct Artista {
    char nome[50];
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
void mostrarArtistasPorTipo(Artista* R, char* tipo);
void mostrarArtistasPorEstilo(Artista* R, char* estilo);
void mostrarArtistasPorEstiloETipo(Artista* R, char* estilo, char* tipo);
void mostrarAlbunsDeArtista(Artista* raiz, char* nomeArtista);
void mostrarAlbunsPorAnoDeArtista(Artista* raiz, char* nomeArtista, char* ano);
void mostrarMusicasDeAlbum(Artista* raiz, char* nomeArtista, char* tituloAlbum);
void mostrarAlbunsPorAnoDeTodosArtistas(Artista* R, char* ano);
void mostrarDadosDeMusica(Artista* raiz, char* tituloMusica);
#endif