#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"
#include "../includes/cidade.h"
#include "../includes/cep.h"

enum Cores corCidade(Cidade* cidade){
    return cidade != NULL ? cidade->cor : BLACK;
}


Cidade* rotacaoEsqCidade(Cidade** Raiz){
    Cidade* aux = (*Raiz)->Dir;
    (*Raiz)->Dir = aux->Esq;
    aux->Esq = *Raiz;
    aux->cor = (*Raiz)->cor;
    (*Raiz)->cor = RED;
    return aux;
}

Cidade* rotacaoDirCidade(Cidade** Raiz){
    Cidade* aux = (*Raiz)->Esq;
    (*Raiz)->Esq = aux->Dir;
    aux->Dir = *Raiz;
    aux->cor = (*Raiz)->cor;
    (*Raiz)->cor = RED;
    return aux;
}


void trocarCorCidade(Cidade** Raiz){
    (*Raiz)->cor = !(*Raiz)->cor;

    if((*Raiz)->Esq != NULL){
        (*Raiz)->Esq->cor = !(*Raiz)->Esq->cor;
    }

    if((*Raiz)->Dir != NULL){
        (*Raiz)->Dir->cor = !(*Raiz)->Dir->cor;
    }

}

void buscaCidade(Cidade* Raiz, char* nomeCity, Cidade** resultado){
    *resultado = NULL;

    if(Raiz != NULL){
        if(strcmp(Raiz->nomeCity, nomeCity) == 0){
            *resultado = Raiz;
        } else if (strcmp(nomeCity, Raiz->nomeCity) < 0){
            buscaCidade(Raiz->Esq, nomeCity, resultado);
        } else {
            buscaCidade(Raiz->Dir, nomeCity, resultado);
        }
    }
}

Cidade* criarNoCidade(char* nomeCity, int tamPopu){
    Cidade* nova = (Cidade*)malloc(sizeof(Cidade));

    strcpy(nova->nomeCity, nomeCity);
    nova->tamPopu = tamPopu;
    nova->cor = RED;
    nova->ceps = NULL;

    nova->Dir = NULL;
    nova->Esq = NULL;
    return nova;
}

int insereCidade(Cidade** Raiz, Cidade* No) {
    
    int inseriu = 1;

    if (*Raiz == NULL) {
        
        *Raiz = No;
    } else {
        
        if (strcmp((*Raiz)->nomeCity, No->nomeCity) > 0) {
            inseriu = insereCidade(&((*Raiz)->Esq), No);
        } else if (strcmp((*Raiz)->nomeCity, No->nomeCity) < 0) {
            inseriu = insereCidade(&((*Raiz)->Dir), No);
        } else {
            inseriu = 0; 
        }

        if(inseriu){
            if (corCidade((*Raiz)->Dir) == RED && corCidade((*Raiz)->Esq) == BLACK){
                *Raiz = rotacaoEsqCidade(Raiz);
            }
                
            if (corCidade((*Raiz)->Esq) == RED && corCidade((*Raiz)->Esq->Esq) == RED){
                *Raiz = rotacaoDirCidade(Raiz);
            }
                
            if (corCidade((*Raiz)->Esq) == RED && corCidade((*Raiz)->Dir) == RED){
                trocarCorCidade(Raiz);
            }
                
        }
    }

    return inseriu;
}

void cadastrarCidade(Estado* lista, char* nomeEst, char* nomeCity, int tamPopu){
    
    Estado* estado = NULL;
    buscaEstado(lista, nomeEst, &estado);
    
    if (estado != NULL){
        Cidade* nova = criarNoCidade(nomeCity,tamPopu);
        
        if (insereCidade(&(estado->cidades), nova)){
            printf("Cidade \"%s\" cadastrado com sucesso!\n", nomeCity);
            estado->quantCity++;

            if (strcmp(nomeCity, estado->nomeCap) == 0) {
                estado->capital = nova;
            }

        } else {
            printf("A Cidade ja existe!\n");
        }
    } else {
        printf("Estado \"%s\" nao encontrado!\n", nomeEst);
    }
}


void imprimirCidades(Cidade* raiz) {
    if (raiz != NULL){
        imprimirCidades(raiz->Esq);
        printf("  - %s (Populacao: %d, Cor: %s)\n", raiz->nomeCity, raiz->tamPopu, raiz->cor == 0 ? "BLACK" : "RED");
        imprimirCidades(raiz->Dir);
    }
}

void imprimirEstadosCidadesCeps(Estado* listaEstados) {
    Estado* atual = listaEstados;

    while (atual != NULL) {
        printf("Estado: %s\n", atual->nomeEst);
        printf("Capital: %s | Populacao: %d | Num Cidades: %d\n", atual->nomeCap, atual->tamPopu, atual->quantCity);
        imprimirCidadesCeps(atual->cidades);
        atual = atual->Prox;
    }
}