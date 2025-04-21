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

    struct MusicasPlaylist *Esq;
    struct MusicasPlaylist *Dir;
}MusicasPlaylist;

MusicasPlaylist* criar(char* nomeA, char* tituloA, char* tituloM);
void buscarMusicaPlaylist(MusicasPlaylist* raiz, char* tituloM, MusicasPlaylist** resultado);
int addMusica(MusicasPlaylist** R, MusicasPlaylist* musica);
void cadastrarMusicasPlaylist(struct Playlist* raiz, char* nomePlaylist, char* nomeA, char* tituloA, char* tituloM);
MusicasPlaylist *removerMusicaPlaylist(MusicasPlaylist* raiz, const char* tituloM);
//void imprimirMusicasPlaylist(MusicasPlaylist* R, const char* nomePlaylist);

#endif