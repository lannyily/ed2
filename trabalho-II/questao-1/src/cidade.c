#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/cidade.h"

Cidade* criarNo(char* nomeCity, int tamPopu){
    Cidade* nova = (Cidade*)malloc(sizeof(Cidade));

    strcpy(nova->nomeCity, nomeCity);
    nova->tamPopu = tamPopu;

    nova->Dir = NULL;
    nova->Esq = NULL;
    return nova;
}

int cor();

int trocarCor();

int balancear();

int insereCidade(Cidade** Raiz, char* nomeCity, int tamPopu){
    Cidade* nova = criarNo(nomeCity, tamPopu);

    if(*Raiz == NULL){
        *Raiz = nova;
    }
    if(strcmp((*Raiz)->nomeCity, nova->nomeCity) > 0){
        insereCidade(&(*Raiz)->Esq, nova);
        if(cor(Raiz->Esq) == 0){
            trocarCor(*Raiz);
        }
    } else if(strcmp((*Raiz)->nomeCity, nova->nomeCity) > 0){
        insereCidade(&(*Raiz)->Dir, nova);
        if(cor(Raiz->Dir) == 0){
            trocarCor(*Raiz);
        }
    }
    balancear(*Raiz);
}