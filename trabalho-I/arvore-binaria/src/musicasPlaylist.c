#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/playlist.h"
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"
#include "../includes/musicasPlaylist.h"

MusicasPlaylist* criar(char* nomeA, char* tituloA, char* tituloM){
    MusicasPlaylist* no = (MusicasPlaylist*)malloc(sizeof(MusicasPlaylist));

    strcpy(no->tituloM, tituloM);
    strcpy(no->tituloA, tituloA);
    strcpy(no->nome, nomeA);

    no->Dir = NULL;
    no->Esq = NULL;
    return no;
}

void buscarMusicaPlaylist(MusicasPlaylist* raiz, char* tituloM, MusicasPlaylist** resultado){
    *resultado = NULL;

    if (raiz != NULL){
        if(strcmp(raiz->tituloM, tituloM) == 0){
            *resultado = raiz;
        } else if (strcmp(tituloM, raiz->tituloM) < 0){
            buscarMusicaPlaylist(raiz->Esq, tituloM, resultado);
        } else {
            buscarMusicaPlaylist(raiz->Dir, tituloM, resultado);
        }
    }
}

int addMusica(MusicasPlaylist** R, MusicasPlaylist* musica){
    int inseriu = 0;

    if (*R == NULL){
        *R = musica;
        inseriu = 1;
    }

    if (strcmp(musica->tituloM, (*R)->tituloM) < 0){
        inseriu = addMusica(&((*R)->Esq), musica);
    } else if (strcmp(musica->tituloM, (*R)->tituloM) > 0){
        inseriu = addMusica(&((*R)->Dir), musica);
    }
    return inseriu;
}


void cadastrarMusicasPlaylist(Playlist* nomePlaylist, MusicasPlaylist* raiz, char* nomeA, char* tituloA, char* tituloM){
    MusicasPlaylist* buscaTitulo = NULL;
    buscarMusicaPlaylist(raiz, tituloM, &buscaTitulo);
    if (buscaTitulo == NULL){
        MusicasPlaylist* novaMusica = criar(nomeA, tituloA, tituloM);
        if(addMusica(&(nomePlaylist->musicas), novaMusica)){
            printf("Musica \"%s\" adicionada a playlist \"%s\"!\n");
        }
    } else {
        printf("Musica \"%s\" ja esta nessa playlist!\n");
    }
}