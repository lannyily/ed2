#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"


Estado* criarNoEstado(char* nomeEstado, char* nomeCapital){
    Estado* novo = (Estado*)malloc(sizeof(Estado));

    strcpy(novo->nomeEst, nomeEstado);
    strcpy(novo->nomeCap, nomeCapital);
    novo->quantCity = 0;
    novo->tamPopu = 0;
    novo->arvCidades = NULL;
    novo->capital = NULL;

    novo->Ant = NULL;
    novo->Prox = NULL;

    return novo;
}

void insertionSort(Estado** listaEstados){
    Estado* atual = *listaEstados;
    Estado* ordenar = NULL;

    while(atual != NULL){
        Estado* proximo = atual->Prox;
        atual->Ant = atual->Prox = NULL;

        if(ordenar == NULL || strcmp(ordenar->nomeEst, atual->nomeEst) >= 0){
            atual->Prox = ordenar;
            if(ordenar != NULL){
                ordenar->Ant = atual;
            }
            ordenar = atual;
        } else {
            Estado* temp = ordenar;

            while(temp->Prox != NULL && strcmp(temp->nomeEst, atual->nomeEst) < 0){
                temp = temp->Prox;
            }

            atual->Prox = temp->Prox;
            if(temp->Prox != NULL){
                temp->Prox->Ant = atual;
            }

            temp->Prox = atual;
            atual->Ant = temp;
        }
        atual = proximo;
    }
    *listaEstados = ordenar;
}

void inserirEstadosOrdenado(Estado** listaEstados, char* nomeEstado, char* nomeCapital){
    Estado* novoEstado = criarNoEstado(nomeEstado, nomeCapital);

    if (*listaEstados == NULL) {
        *listaEstados = novoEstado;
    } else {
        Estado* temp = *listaEstados;

        while(temp->Prox != NULL){
            temp = temp->Prox;
        }

        temp->Prox = novoEstado;
        novoEstado->Ant = temp;
    }
    insertionSort(listaEstados);
}

void buscaEstado(Estado* listaEstados, char* nomeEstado, Estado** resultado){
    *resultado = NULL;
    Estado* atual = listaEstados;

    while(atual != NULL){
        if(strcmp(atual->nomeEst, nomeEstado) == 0){
            *resultado = atual;
        }
        atual = atual->Prox;
    }
}


