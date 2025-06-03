#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/playlist.h"
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"



void buscarPlaylist(Playlist* raiz,  char* nome, Playlist** resultado) {
    *resultado = NULL;
    
    if (raiz != NULL){
        if (strcmp(raiz->nome, nome) == 0) {
            *resultado = raiz;
        } else if (strcmp(nome, raiz->nome) < 0) {
            buscarPlaylist(raiz->esquerda, nome, resultado);
        } else {
            buscarPlaylist(raiz->direita, nome, resultado);
        }
    }
    
}


Playlist* criarPlaylist(char *nome) {
    Playlist *nova = (Playlist *)malloc(sizeof(Playlist));
    
    strcpy(nova->nome, nome);
    nova->musicas = NULL; 
    nova->esquerda = NULL;
    nova->direita = NULL;
    
    return nova;
}

int inserirPlaylist(Playlist **raiz, Playlist *novaPlaylist) {
    int inseriu = 1;

    if (*raiz == NULL) {
        *raiz = novaPlaylist;
        
    } else {
        int comparacao = strcmp(novaPlaylist->nome, (*raiz)->nome);

        if (comparacao < 0) {
            inseriu = inserirPlaylist(&((*raiz)->esquerda), novaPlaylist);
        } else if (comparacao > 0) {
            inseriu = inserirPlaylist(&((*raiz)->direita), novaPlaylist);
        } else {
            inseriu = 0;
        } 
    }

    return inseriu;
}


void cadastrarPlaylist(Playlist** raiz, char* nome){
    Playlist* playlist = NULL;
    buscarPlaylist(*raiz, nome, &playlist);
    if(playlist != NULL){
        printf("Playlist \"%s\" já existe!\n", nome);
    } else {
        Playlist* novaPlaylist = criarPlaylist(nome);
        if(inserirPlaylist(raiz, novaPlaylist)){
            printf("Playlist \"%s\" adicionada!\n", nome);
        }
    }
}


int ehFilho(Playlist* p) {
    return (p->esquerda == NULL && p->direita == NULL);
}


Playlist* souFilho(Playlist* p) {
    Playlist* resultado;
    if (p->esquerda != NULL && p->direita == NULL) {
        resultado = p->esquerda;
    } else if (p->direita != NULL && p->esquerda == NULL) {
        resultado = p->direita;
    } else {
        resultado = NULL;
    }
    return resultado;
}


Playlist* enderecoMenorEsq(Playlist* p) {
    Playlist* atual = p;
    while (atual != NULL && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

int removerPlaylist(Playlist** raiz, char* nome){
   
    int removeu = 1;

    if(*raiz != NULL){
        if(strcmp(nome, (*raiz)->nome) == 0){
           
            Playlist *filho, *aux;
            if(ehFilho(*raiz)){
                printf("Playlist removida!\n");
                aux = *raiz;
                *raiz = NULL;
                liberarMusicasPlaylist(aux->musicas);
                free(aux);
            } else {
                
                if((filho = souFilho(*raiz)) != NULL){
                    printf("Playlist  removida!\n");
                    aux = *raiz;
                    *raiz = filho;
                    liberarMusicasPlaylist(aux->musicas);
                    free(aux);
                } else {
                    Playlist* menor;
                    menor = enderecoMenorEsq((*raiz)->direita);
                     
                    strcpy((*raiz)->nome, menor->nome);
                    removerPlaylist(&((*raiz)->direita), menor->nome);
                }
            }
        } else {
            if(strcmp(nome, (*raiz)->nome) < 0){
                removeu = removerPlaylist(&((*raiz)->esquerda), nome);
            } else {
                removeu = removerPlaylist(&((*raiz)->direita), nome);
            }
        }
    } else {
        printf("Playlist \"%s\" nao encontrada!\n", nome);
        removeu = 0;
    }
    return removeu;
}

void liberarPlaylists(Playlist* raiz) {
    if (raiz != NULL) {
        liberarPlaylists(raiz->esquerda);
        liberarPlaylists(raiz->direita);
        liberarMusicasPlaylist(raiz->musicas); 
        free(raiz);
    }
}

