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

            insereAjustaCorCep(&(cidade->ceps), novoCep);
        } else {
            printf("Cidade \"%s\" nao encontrada!\n", nomeCity);
        }
    } else {
        printf("Estado \"%s\" nao encontrado!\n", nomeEst);
    }
}

Cep* insereAjustaCorCep(Cep** raiz, Cep* no){
    int inseriu;
    inseriu = insereCep(raiz, no);
    if(inseriu){
        if(raiz){
            (*raiz)->cor = BLACK;
        }
        printf("Cep \"%s\" inserido com sucesso!\n", no->Cep);
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

void buscaCep(Cep* Raiz, char* cep, Cep** resultado){
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

Cep* buscarCepEmCidade(Cidade* cidade, char* cep){
    Cep* resultado = NULL;

    if (cidade != NULL) {
        buscaCep(cidade->ceps, cep, &resultado);

        if (resultado == NULL){
            resultado = buscarCepEmCidade(cidade->Esq, cep);
        }

        if (resultado == NULL) {
            resultado = buscarCepEmCidade(cidade->Dir, cep);
        }
    }

    return resultado;
}

Cep* buscarCepEmEstado(Estado* estado, char* cep) {
    Cep* resultado = NULL;

    while (estado != NULL && resultado == NULL) {
        resultado = buscarCepEmCidade(estado->cidades, cep);
        estado = estado->Prox;
    }

    return resultado;
}

Cep* removerCep(Cep** Raiz, char* cep){
    if(*Raiz != NULL){
        if (strcmp(cep, (*Raiz)->Cep) < 0){
            if((*Raiz)->Esq != NULL && (*Raiz)->Esq->cor == BLACK && (*Raiz)->Esq->Esq != NULL && (*Raiz)->Esq->Esq == BLACK){
                rotacaoDirCep(Raiz);
            }
            (*Raiz)->Esq = removerCep(&(*Raiz)->Esq, cep);
        }
        else {
            if((*Raiz)->Esq != NULL && (*Raiz)->Esq->cor == RED){
                rotacaoDirCep(Raiz);
            }
            
            if(strcmp((*Raiz)->Cep, cep) == 0 && (*Raiz)->Dir == NULL){
                free(*Raiz);
                printf("CEP \"%s\" removido!\n", cep);
                return NULL;
            }

            if ((*Raiz)->Dir != NULL && (*Raiz)->Dir->cor == BLACK && (*Raiz)->Dir->Esq != NULL && (*Raiz)->Dir->Esq->cor == BLACK){
                rotacaoEsqCep(&(*Raiz)->Dir);
                if ((*Raiz)->Dir != NULL && (*Raiz)->Dir->Dir != NULL && (*Raiz)->Dir->Dir->cor == RED){
                    rotacaoEsqCep(Raiz);
                }

            }

            if (strcmp((*Raiz)->Cep, cep) == 0) {
                Cep* aux = (*Raiz)->Dir;
                
                while (aux->Esq != NULL){
                    aux = aux->Esq;
                }

                strcpy((*Raiz)->Cep, aux->Cep);

                (*Raiz)->Dir = removerCep(&(*Raiz)->Dir, (*Raiz)->Cep);
            } else {
                (*Raiz)->Dir = removerCep(&(*Raiz)->Dir, cep);
            }

        }
    }

    return *Raiz;
}


void liberarCep(Cep* raiz) {
    if (raiz != NULL) {
        liberarCep(raiz->Esq);
        liberarCep(raiz->Dir);
        free(raiz);
    }
}


void liberarCidade(Cidade* raiz) {
    if (raiz != NULL) {
        liberarCidade(raiz->Esq);
        liberarCidade(raiz->Dir);
        liberarCep(raiz->ceps);  
        free(raiz);
    }
}


void liberarEstados(Estado* inicio) {
    Estado* atual = inicio;
    while (atual != NULL) {
        Estado* prox = atual->Prox;
        liberarCidade(atual->capital);  
        liberarCidade(atual->cidades);  
        free(atual);
        atual = prox;
    }
}