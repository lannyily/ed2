#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"
#include "../includes/cidade.h"
#include "../includes/cep.h"

enum Cores corCep(Cep* cep){
    return cep != NULL ? cep->cor : BLACK;
}


Cep* rotacaoEsqCep(Cep** Raiz){
    Cep* aux = (*Raiz)->Dir;
    (*Raiz)->Dir = aux->Esq;
    aux->Esq = *Raiz;
    aux->cor = (*Raiz)->cor;
    (*Raiz)->cor = RED;
    return aux;
}

Cep* rotacaoDirCep(Cep** Raiz){
    Cep* aux = (*Raiz)->Esq;
    (*Raiz)->Esq = aux->Dir;
    aux->Dir = *Raiz;
    aux->cor = (*Raiz)->cor;
    (*Raiz)->cor = RED;
    return aux;
}

void trocarCorCep(Cep** Raiz){
    (*Raiz)->cor = !(*Raiz)->cor;

    if((*Raiz)->Esq != NULL){
        (*Raiz)->Esq->cor = !(*Raiz)->Esq->cor;
    }

    if((*Raiz)->Dir != NULL){
        (*Raiz)->Dir->cor = !(*Raiz)->Dir->cor;
    }

}

void buscaCep(Cep* Raiz, char* cep, Cep** resultado) {
    *resultado = NULL;

    if(Raiz != NULL) {
        if(strcmp(Raiz->Cep, cep) == 0) {
            *resultado = Raiz;
        } else if(strcmp(cep, Raiz->Cep) < 0) {
            buscaCep(Raiz->Esq, cep, resultado);
        } else {
            buscaCep(Raiz->Dir, cep, resultado);
        }
    }
}

Cep* criarNoCep(char* cep){
    Cep* novo = (Cep*)malloc(sizeof(Cep));

    strcpy(novo->Cep, cep);
    novo->cor = RED;

    novo->Dir = NULL;
    novo->Esq = NULL;

    return novo;
}

int insereCep(Cep** Raiz, Cep* No){
    int inseriu = 1;

    if(*Raiz == NULL){
        *Raiz = No;
    } else {
        if(strcmp((*Raiz)->Cep, No->Cep) > 0){
            inseriu = insereCep(&((*Raiz)->Esq), No);
        } else if (strcmp((*Raiz)->Cep, No->Cep) < 0){
            inseriu = insereCep(&((*Raiz)->Dir), No);
        } else {
            inseriu = 0;
        }

        if(inseriu){
            if(corCep((*Raiz)->Dir) == RED && corCep((*Raiz)->Esq) == BLACK){
                *Raiz = rotacaoEsqCep(Raiz);
            }

            if(corCep((*Raiz)->Esq) == RED && corCep((*Raiz)->Esq->Esq) == RED){
                *Raiz = rotacaoDirCep(Raiz);
            }

            if(corCep((*Raiz)->Esq) == RED && corCep((*Raiz)->Dir) == RED){
                trocarCorCep(Raiz);
            }
        }
    }
    return inseriu;
}

void cadastrarCep(Estado* lista,  char* nomeEst, char* nomeCity, char* cep){
    Estado* estado = NULL;
    buscaEstado(lista, nomeEst, &estado);

    if(estado != NULL){

        Cidade* cidade = NULL;
        buscaCidade(estado->cidades, nomeCity, &cidade);

        if(cidade != NULL){
            Cep* novoCep = criarNoCep(cep);

            if(insereCep(&(cidade->ceps), novoCep)){
                printf("Cep \"%s\" cadastrado com sucesso!\n", nomeCity);
            } else {
                printf("Esse CEP ja existe!\n");
            }
        } else {
            printf("Cidade \"%s\" nao encontrada!\n", nomeCity);
        }
    } else {
        printf("Estado \"%s\" nao encontrado!\n", nomeEst);
    }
}

void imprimirCidadesCeps(Cidade* raiz) {
    if (raiz != NULL) {
        imprimirCidadesCeps(raiz->Esq);
        printf("  - %s (Populacao: %d, Cor: %s)\n", raiz->nomeCity, raiz->tamPopu, raiz->cor == 0 ? "BLACK" : "RED");
        if (raiz->ceps != NULL) {
            printf("    Ceps:\n");
            imprimirCeps(raiz->ceps);
        }
        imprimirCidadesCeps(raiz->Dir);
    }
}

void imprimirCeps(Cep* raiz){
    if(raiz != NULL){
        imprimirCeps(raiz->Esq);
        printf("        - %s (Cor: %s)\n", raiz->Cep, raiz->cor == 0 ? "BLACK" : "RED");
        imprimirCeps(raiz->Dir);
    }
}