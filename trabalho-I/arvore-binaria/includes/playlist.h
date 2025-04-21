#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "musica.h"
#include "musicasPlaylist.h"

typedef struct Playlist {
    char nome[100];
    MusicasPlaylist *musicas;
    struct Playlist *esquerda;
    struct Playlist *direita;
} Playlist;

Playlist* criarPlaylist(char *nome);
Playlist* inserirPlaylist(Playlist *raiz, Playlist *novaPlaylist);
Playlist* removerPlaylist(Playlist *raiz, char *nome);
void buscarPlaylist(Playlist* raiz, const char* nome, Playlist** resultado);

#endif // PLAYLIST_H