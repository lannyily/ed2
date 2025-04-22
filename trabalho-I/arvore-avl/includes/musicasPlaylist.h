#ifndef MUSICAS_NA_PLAYLIST_H
#define MUSICAS_NA_PLAYLIST_H
#include "artista.h"
#include "album.h"
#include "musica.h"

struct Playlist;

typedef struct MusicasPlaylist{
    char tituloM[100];
    char tituloA[100];
    char nome[100];
    int altura;

    struct MusicasPlaylist *Esq;
    struct MusicasPlaylist *Dir;
}MusicasPlaylist;

int maiorMusicasPlaylist(int x, int y);
int pegaAlturaMusicasPlaylist(MusicasPlaylist* raiz);
void rotacaoSimplesDireitaMusicasPlaylist(MusicasPlaylist** raiz);
void rotacaoSimplesEsquerdaMusicasPlaylist(MusicasPlaylist** raiz);
void rotacaoDuplaDireitaMusicasPlaylist(MusicasPlaylist** raiz);
void rotacaoDuplaEsquerdaMusicasPlaylist(MusicasPlaylist** raiz);
int alturaNoMusicasPlaylist(MusicasPlaylist* raiz);
int fatorBalanceamentoMusicasPlaylist(MusicasPlaylist* raiz);
MusicasPlaylist* criar(char* nomeA, char* tituloA, char* tituloM);
void buscarMusicaPlaylist(MusicasPlaylist* raiz, const char* tituloM, MusicasPlaylist** resultado);
int addMusica(MusicasPlaylist** R, MusicasPlaylist* musica, char* tituloM);
void cadastrarMusicasPlaylist(struct Playlist* raiz, char* nomePlaylist, char* nomeA, char* tituloA, char* tituloM);
MusicasPlaylist *removerMusicaPlaylist(MusicasPlaylist* raiz, const char* tituloM);
void imprimirMusicasPlaylist(MusicasPlaylist* R);


#endif