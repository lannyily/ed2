#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "musica.h"

typedef struct Playlist {
    char nome[100];
    Musica *musicas;
    struct Playlist *esquerda;
    struct Playlist *direita;
} Playlist;

Playlist* criarPlaylist(char *nome);
Playlist* inserirPlaylist(Playlist *raiz, Playlist *novaPlaylist);
Playlist* removerPlaylist(Playlist *raiz, char *nome);
//Musica* inserirMusicas(Musica* raiz, Musica* nova);
//void inserirMusicaNaPlaylist(Playlist* playlist, Musica* novaMusica);
Playlist* buscarPlaylist(Playlist* raiz, const char* nome);
void imprimirPlaylist(Playlist *playlist);

#endif // PLAYLIST_H