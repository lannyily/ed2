#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/artista.h"

Artista* criarArtista(char* nome, char* tipo, char* estiloM) {
    Artista* no = (Artista*)malloc(sizeof(Artista));

    strcpy(no->nome, nome);
    strcpy(no->tipo, tipo);
    strcpy(no->estiloMusical, estiloM);
    no->numAlbuns = 0;
    no->Esq = NULL;
    no->Dir = NULL;
    return no;
}


int insereArtista(Artista** R, Artista* No) {
    int inseriu = 0;
    
    if (*R == NULL) {
        *R = No;
    }
    else if (strcmp(No->nome, (*R)->nome) < 0) {
        inseriu = insere(&((*R)->Esq), No);
    }
    else if (strcmp(No->nome, (*R)->nome) > 0) {
        inseriu = insere(&((*R)->Dir), No);
    }
    else {
        inseriu = 1;  
    }
    return inseriu;
}

void imprimirArtistas(Artista* R){
    if (R != NULL){
        imprimirArtistas(R->Esq);
        printf("Nome: %s\n", R->nome);
        printf("Tipo: %s\n", R->tipo);
        printf("Estilo: %s\n", R->estiloMusical);
        printf("Numero de albuns: %d\n", R->numAlbuns);
        printf("\n");
        imprimirArtistas(R->Dir);
    }
}

int comparaString(char* nomeBusca, char* nome){
    if (*nomeBusca != 0) {                                                    
        if (*nome == 0) return 0;                                            
        if (*nomeBusca == *nome) return comparaString(++nomeBusca, ++nome); 
        return 0;                                                            
    } else {
        return (*nome == 0); // ambas terminaram juntas? são iguais
    }
}

int buscaArtista(Artista* R, char* nome){
    if (R == NULL) return 0;

    if (comparaString(R->nome, nome)) {
        return 1;
    } else if (strcmp(nome, R->nome) < 0) {
        return buscaArtista(R->Esq, nome);
    } else {
        return buscaArtista(R->Dir, nome);
    }
}

void cadastrarArtista(Artista** raiz, char* nome, char* tipo, char* estilo) {
    if (buscaArtista(*raiz, nome)){
        printf("%s ja existe\n", nome);
    } else {
        Artista* novo = criarArtista(nome, tipo, estilo);
        insere(raiz, novo);
    }
}
