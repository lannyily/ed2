#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "musica.h"
#include "musicasPlaylist.h"

typedef struct Playlist {
    char nome[100];
    int altura;
    MusicasPlaylist *musicas;
    struct Playlist *esquerda;
    struct Playlist *direita;
} Playlist;

int maiorPlaylist(int x, int y);
int pegaAlturaPlaylist(Playlist* raiz);
void rotacaoSimplesDireitaPlaylist(Playlist** raiz);
void rotacaoSimplesEsquerdaPlaylist(Playlist** raiz);
void rotacaoDuplaDireitaPlaylist(Playlist** raiz);
void rotacaoDuplaEsquerdaPlaylist(Playlist** raiz);
int alturaNoPlaylist(Playlist* raiz);
int fatorBalanceamentoPlaylist(Playlist* raiz);
Playlist* criarPlaylist(char *nome);
int inserirPlaylist(Playlist **raiz, Playlist *novaPlaylist, char* nome);
void cadastrarPlaylist(Playlist** raiz, char* nome);
Playlist* removerPlaylist(Playlist *raiz, char *nome);
void buscarPlaylist(Playlist* raiz, const char* nome, Playlist** resultado);
void liberarMusicasPlaylist(MusicasPlaylist *raiz);
void liberarPlaylists(Playlist *raiz);

#endif // PLAYLIST_H