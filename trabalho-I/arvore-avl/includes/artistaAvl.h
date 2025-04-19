#ifndef ARTISTA_H
#define ARTISTA_H

#include "albumAvl.h"

typedef struct Artista{
  char nome[50];
  char tipo[20];
  char estiloMusical[20];
  int numAlbuns;
  Album *albuns;

  struct Artista *esq;
  struct Artista *dir;
  int fatorBalanceamento;
  int altura;
}Artista;

Artista* criarArtista(char* nome, char* tipo, char* estiloM);
int insereArtista(Artista** R, Artista* No);
void imprimirArtistas(Artista* R);
void buscaArtista(Artista* R, const char* nome, Artista** resultado);
void cadastrarArtista(Artista** raiz, char* nome, char* tipo, char* estilo);
void mostrarMusicasDeAlbum(Artista* raiz, char* nomeArtista, char* tituloAlbum);
void mostrarDadosDeMusica(Artista* raiz, char* tituloMusica);
void mostrarArtistasPorTipo(Artista* raiz, const char* tipo);
void mostrarArtistasPorEstilo(Artista* raiz, const char* estilo);
void mostrarArtistasPorEstiloETipo(Artista* raiz, const char* estilo, const char* tipo);
void mostrarAlbunsPorAnoDeTodosArtistas(Artista* raiz, const char* ano);
#endif