#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"

Estado* criarNo(char* nomeEstado, char* nomeCapital, int quantCity, int tamPopu){
    Estado* novo = (Estado*)malloc(sizeof(Estado));

    strcpy(novo->nomeEst, nomeEstado);
    strcpy(novo->nomeCap, nomeCapital);
    novo->quantCity = quantCity;
    novo->tamPopu = tamPopu;

    novo->Ant = NULL;
    novo->Prox = NULL;

    return novo;
}

void inserirEstadosOrdenado(Estado** lista, char* nomeEstado, char* nomeCapital, int quantCity, int tamPopu){
    Estado* novo = criarNo(nomeEstado, nomeCapital, quantCity, tamPopu);
    
    if (*lista == NULL) {
        *lista = novo;
    }

    Estado* atual = *lista;
    Estado* anterior = NULL;

    while (atual != NULL && strcmp(novo->nomeEst, atual->nomeEst) > 0){
        anterior = atual;
        atual = atual->Prox;
    }

    if (anterior == NULL){
        novo->Prox = *lista;
        (*lista)->Ant = novo;
        *lista = novo;
    } else {
        novo->Prox = atual;
        novo->Ant = anterior;
        anterior->Prox = novo;
        if (atual != NULL){
            atual->Ant = novo;
        }
    }
}
