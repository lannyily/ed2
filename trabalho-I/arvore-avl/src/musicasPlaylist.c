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

void buscarMusicaPlaylist(MusicasPlaylist* raiz, const char* tituloM, MusicasPlaylist** resultado){
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


void cadastrarMusicasPlaylist(Playlist* raiz, char* nomePlaylist, char* nomeA, char* tituloA, char* tituloM){
    Playlist* encontrarNome = NULL;
    buscarPlaylist(raiz, nomePlaylist, &encontrarNome);

    if(encontrarNome != NULL){
        MusicasPlaylist* buscaTitulo = NULL;
        buscarMusicaPlaylist(raiz->musicas, tituloM, &buscaTitulo);

        if (buscaTitulo != NULL){
            printf("Musica \"%s\" ja esta nessa playlist!\n", tituloM);
        } else {
            MusicasPlaylist* novaMusica = criar(nomeA, tituloA, tituloM);
            if(addMusica(&(encontrarNome->musicas), novaMusica)){
                printf("Musica \"%s\" adicionada a playlist \"%s\"!\n", tituloM, nomePlaylist);
            }
        }
    } else {
        printf("Playlist \"%s\" nao encontrada\n", nomePlaylist);
    }
    
}

MusicasPlaylist *removerMusicaPlaylist(MusicasPlaylist* raiz, const char* tituloM){
    if (raiz == NULL){
        return NULL;
    }

    if (strcmp(tituloM, raiz->tituloM) < 0){
        raiz->Esq = removerMusicaPlaylist(raiz->Esq, tituloM);
    } else if (strcmp(tituloM, raiz->tituloM) > 0){
        raiz->Dir = removerMusicaPlaylist(raiz->Dir, tituloM);
    } else {

        printf("Musica \"%s\" removida da playlist!\n", raiz->tituloM);

        MusicasPlaylist* temp;
        if (raiz->Esq == NULL){
            temp = raiz->Dir;
            free(raiz);
            raiz = temp;
        } else if (raiz->Dir == NULL){
            temp = raiz->Esq;
            free(raiz);
            raiz = temp;
        } else{ // Encontrou a playlist
            MusicasPlaylist *sucessor = raiz->Dir;
            while (sucessor->Esq != NULL){
                sucessor = sucessor->Esq;
            } 

            strcpy(raiz->nome, sucessor->nome);
            strcpy(raiz->tituloA, sucessor->tituloA);
            strcpy(raiz->tituloM, sucessor->tituloM);
            raiz->Dir = removerMusicaPlaylist(raiz->Dir, sucessor->tituloM); //Remove o nó duplicado, ja que ele foi copiado

        }
    }
    return raiz;
}

void imprimirMusicasPlaylist(MusicasPlaylist* R){
    
    if(R != NULL){
        
        imprimirMusicasPlaylist(R->Esq);

        printf("Musica: %s, Album: %s, Artista: %s\n", R->tituloM, R->tituloA, R->nome);
        imprimirMusicasPlaylist(R->Dir);
    }
   
}

