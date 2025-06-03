#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"

void buscaEstado(Estado* listaEstados, char* nomeEstado, Estado** resultado){
    *resultado = NULL;
    Estado* atual = listaEstados;

    while(atual != NULL){
        if(strcmp(listaEstados->nomeEst, nomeEstado) == 0){
            *resultado = atual;
        }
        atual = atual->Prox;
    }
}


Estado* criarNoEstado(char* nomeEstado, char* nomeCapital, int quantCity, int tamPopu){
    Estado* novo = (Estado*)malloc(sizeof(Estado));

    strcpy(novo->nomeEst, nomeEstado);
    strcpy(novo->nomeCap, nomeCapital);
    novo->quantCity = quantCity;
    novo->tamPopu = tamPopu;

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

void inserirEstadosOrdenado(Estado** listaEstados, char* nomeEstado, char* nomeCapital, int quantCity, int tamPopu){
    Estado* novoEstado = criarNoEstado(nomeEstado, nomeCapital, quantCity, tamPopu);

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



void imprimirEstados(Estado* listaEstados) {
    Estado* atual = listaEstados;

    while (atual != NULL) {
        printf("Estado: %s\n", atual->nomeEst);
        printf("Capital: %s | Populacao: %d | Num Cidades: %d\n", atual->nomeCap, atual->tamPopu, atual->quantCity);
        atual = atual->Prox;
    }
}

