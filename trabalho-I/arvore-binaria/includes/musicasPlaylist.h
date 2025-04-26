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
void buscarMusicaPlaylist(MusicasPlaylist* raiz,  char* tituloM, MusicasPlaylist** resultado);
int addMusica(MusicasPlaylist** R, MusicasPlaylist* musica);
void cadastrarMusicasPlaylist(struct Playlist* raiz, char* nomePlaylist, char* nomeA, char* tituloA, char* tituloM);
int ehFilhoMP(MusicasPlaylist* mp);
MusicasPlaylist* souFilhoMP(MusicasPlaylist* mp);
MusicasPlaylist* enderecoMenorEsqMP(MusicasPlaylist* mp);
int removerMusicaPlaylist(MusicasPlaylist** raiz, char* tituloM);
void imprimirMusicasPlaylist(MusicasPlaylist* R);
void liberarMusicasPlaylist(MusicasPlaylist* raiz);

#endif