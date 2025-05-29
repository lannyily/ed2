#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/cidade.h"
#include "../includes/cores.h"

Cidade* criarNo(char* nomeCity, int tamPopu){
    Cidade* nova = (Cidade*)malloc(sizeof(Cidade));

    strcpy(nova->nomeCity, nomeCity);
    nova->tamPopu = tamPopu;
    nova->arv_cep = NULL;
    nova->cor = RED;
    nova->Pai = NULL;
    nova->Dir = NULL;
    nova->Esq = NULL;
    return nova;
}

int cor();

int trocarCor();

int balancear();

int insereCidade(Cidade** Raiz, Cidade *Pai,char* nomeCity, int tamPopu){
    Cidade *atual = *Raiz;

    int inseriu = 0;
    if(*Raiz == NULL){
        
        Cidade* nova = criarNo(nomeCity, tamPopu);
        if((*Raiz)->Pai == NULL){
            (*Raiz)->cor = BLACK; // A raiz deve ser sempre preta
        }
        Raiz = nova;
        inseriu = 1;
    }
    // se a cidade existe e o nome em ordem alfabético é menor, insere na subárvore esquerda
    if(strcmp((*Raiz)->nomeCity, atual->nomeCity) < 0){
        insereCidade(&(*Raiz)->Esq, atual, nomeCity, tamPopu);
        if(cor((*Raiz)->Esq) == RED){
            trocarCor(*Raiz);
        }

      // se a cidade existe e o nome em ordem alfabético é maior, insere na subárvore direita  
    } else if(strcmp((*Raiz)->nomeCity, atual->nomeCity) > 0){
        insereCidade(&(*Raiz)->Dir, atual, nomeCity, tamPopu);
        if(cor((*Raiz)->Dir) == RED){
            trocarCor(*Raiz);
        }
    }else {
        // Cidade já existe, não insere
        printf("Cidade ja existe!\n");
    }
    balancear(*Raiz);
    return inseriu;
}