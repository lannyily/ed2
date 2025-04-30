#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "musica.h"
#include "musicasPlaylist.h"

typedef struct Playlist {
    char nome[100];
    MusicasPlaylist *musicas;

    int altura;

    struct Playlist *esquerda;
    struct Playlist *direita;
} Playlist;


int maiorP(int alt1, int alt2);
int alturaNoP(Playlist* no);
void rotacaoEsqP(Playlist** raiz);
void rotacaoDirP(Playlist** raiz);
int fatorBalanceamentoP(Playlist* raiz);
void balanceamentoP(Playlist** raiz);
Playlist* criarPlaylist(char *nome);
int inserirPlaylist(Playlist **raiz, Playlist *novaPlaylist);
void cadastrarPlaylist(Playlist** raiz, char* nome);
int ehFilho(Playlist* p);
Playlist* souFilho(Playlist* p);
Playlist* enderecoMenorEsq(Playlist* p);
int removerPlaylist(Playlist** raiz, char* nome);
void buscarPlaylist(Playlist* raiz,  char* nome, Playlist** resultado);
void liberarPlaylists(Playlist* raiz);

#endif 