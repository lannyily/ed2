#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"
#include "../includes/cidade.h"
#include "../includes/cep.h"
#include "../includes/pessoa.h"


int dataValida(char* dataN){
    int valida = 1;

    if(strlen(dataN) != 10){
        valida = 0;
    }

    if (dataN[2] != '/' || dataN[5] != '/'){
        valida = 0;
    }

    int dia, mes, ano;

    if (sscanf(dataN, "%2d/%2d/%4d", &dia, &mes, &ano) != 3){
        valida = 0;
    }

    if (dia < 1 || mes < 1 || mes > 12 || ano < 1900 || ano > 2100){
        valida = 0;
    }

    int diasMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)){
        diasMes[1] = 29;
    }

    if (dia > diasMes[mes - 1]){
        valida = 0;
    }

    return valida;
}


enum Cores corPessoa(Pessoa* pessoa){
    return pessoa != NULL ? pessoa->cor : BLACK;
}


Pessoa* rotacaoEsqPessoa(Pessoa** Raiz){
    Pessoa* aux = (*Raiz)->Dir;
    (*Raiz)->Dir = aux->Esq;
    aux->Esq = *Raiz;
    aux->cor = (*Raiz)->cor;
    (*Raiz)->cor = RED;
    return aux;
}

Pessoa* rotacaoDirPessoa(Pessoa** Raiz){
    Pessoa* aux = (*Raiz)->Esq;
    (*Raiz)->Esq = aux->Dir;
    aux->Dir = *Raiz;
    aux->cor = (*Raiz)->cor;
    (*Raiz)->cor = RED;
    return aux;
}

void trocarCorPessoa(Pessoa** Raiz){
    (*Raiz)->cor = !(*Raiz)->cor;

    if((*Raiz)->Esq != NULL){
        (*Raiz)->Esq->cor = !(*Raiz)->Esq->cor;
    }

    if((*Raiz)->Dir != NULL){
        (*Raiz)->Dir->cor = !(*Raiz)->Dir->cor;
    }

}

void buscaPessoa(Pessoa* Raiz, char* cpf, Pessoa** resultado) {
    *resultado = NULL;

    if(Raiz != NULL) {
        if(strcmp(Raiz->cpf, cpf) == 0) {
            *resultado = Raiz;
        } else if(strcmp(cpf, Raiz->cpf) < 0) {
            buscaPessoa(Raiz->Esq, cpf, resultado);
        } else {
            buscaPessoa(Raiz->Dir, cpf, resultado);
        }
    }
}

Pessoa* buscaCepEmPessoa(Pessoa* Raiz, char* cep){
    Pessoa* resultado = NULL;

    if (Raiz == NULL){
        if (strcmp(Raiz->cepCityMora, cep) == 0 || strcmp(Raiz->cepCityNatal, cep) == 0) {
            resultado = Raiz;
        }

        buscaCepEmPessoa(Raiz->Esq, cep);
        if (resultado == NULL) {
            buscaCepEmPessoa(Raiz->Dir, cep);
        }
    }

    return resultado;
}

Pessoa* criarNoPessoa(char* nome, char* cpf, char* cepCityNatal, char* cepCityMora, char* dataN){
    Pessoa* nova = (Pessoa*)malloc(sizeof(Pessoa));

    strcpy(nova->nome, nome);
    strcpy(nova->cpf, cpf);
    strcpy(nova->cepCityNatal, cepCityNatal);
    strcpy(nova->cepCityMora, cepCityMora);
    strcpy(nova->dataNascimento, dataN);
    nova->cor = RED;

    nova->Dir = NULL;
    nova->Esq = NULL;

    return nova;
}

int inserePessoa(Pessoa** Raiz, Pessoa* No){
    int inseriu = 1;

    if (*Raiz == NULL){
        *Raiz = No;
    } else {

        if (strcmp((*Raiz)->cpf, No->cpf) > 0){
            inseriu = inserePessoa(&((*Raiz)->Esq), No);
        } else if (strcmp((*Raiz)->cpf, No->cpf) < 0){
            inseriu = inserePessoa(&((*Raiz)->Dir), No);
        } else {
            inseriu = 0;
        }

        if (inseriu) {
            if(corPessoa((*Raiz)->Dir) == RED && corPessoa((*Raiz)->Esq) == BLACK){
                *Raiz = rotacaoEsqPessoa(Raiz);
            }

            if(corPessoa((*Raiz)->Esq) == RED && corPessoa((*Raiz)->Esq->Esq) == RED){
                *Raiz = rotacaoDirPessoa(Raiz);
            }

            if(corPessoa((*Raiz)->Esq) == RED && corPessoa((*Raiz)->Dir) == RED){
                trocarCorPessoa(Raiz);
            }
        }
    }

    return inseriu;

}


void cadastrarPessoa(Estado* lista, Pessoa** Raiz, char* nome, char* cpf, char* cepCityNatal, char* cepCityMora, char* dataN){
    Pessoa* novaPessoa = criarNoPessoa(nome, cpf, cepCityNatal, cepCityMora, dataN);

    Cep* cepN = buscarCepEmEstado(lista, cepCityNatal);
    Cep* cepM = buscarCepEmEstado(lista, cepCityMora);

    if (cepN && cepM){
        if (inserePessoa(Raiz, novaPessoa)){
            printf("Pessoa com o CPF \"%s\" cadastrada com sucesso!\n", cpf);
        } else {
            printf("Pessoa com o CPF \"%s\" ja existe!\n", cpf);
        }
    } else {
        printf("CEP nao encontrado!\n");
    }
}


Pessoa* insereAjustaCorPessoa(Pessoa** raiz, Pessoa* no){
    int inseriu;
    inseriu = inserePessoa(raiz, no);

    if(inseriu){
        if(raiz){
            (*raiz)->cor = BLACK;
        }
        printf("CEP \"%s\" inserido com sucesso!\n", no->nome);
    }  
    return *raiz; 
}

void imprimirPessoas(Pessoa* raiz){
    
    if(raiz != NULL){
        imprimirPessoas(raiz->Esq);
        printf("%s \n     - CPF: %s\n     - CEP da cidade natal: %s\n     - CEP da cidade onde mora: %s\n     - Data de nascimento: %s\n     - Cor: %s\n", 
               raiz->nome, raiz->cpf, raiz->cepCityNatal, raiz->cepCityMora, 
               raiz->dataNascimento, raiz->cor == 0 ? "BLACK" : "RED");
        imprimirPessoas(raiz->Dir);
    }
}


Pessoa* removerPessoa(Pessoa** Raiz, char* cpf){
    if(*Raiz != NULL){
        if (strcmp(cpf, (*Raiz)->cpf) < 0){
            if((*Raiz)->Esq != NULL && (*Raiz)->Esq->cor == BLACK && (*Raiz)->Esq->Esq != NULL && (*Raiz)->Esq->Esq == BLACK){
                rotacaoDirPessoa(Raiz);
            }
            (*Raiz)->Esq = removerPessoa(&(*Raiz)->Esq, cpf);
        }
        else {
            if((*Raiz)->Esq != NULL && (*Raiz)->Esq->cor == RED){
                rotacaoDirPessoa(Raiz);
            }
            
            if(strcmp((*Raiz)->cpf, cpf) == 0 && (*Raiz)->Dir == NULL){
                free(*Raiz);
                printf("Pessoa com o cpf \"%s\" removido!\n", cpf);
                return NULL;
            }

            if ((*Raiz)->Dir != NULL && (*Raiz)->Dir->cor == BLACK && (*Raiz)->Dir->Esq != NULL && (*Raiz)->Dir->Esq->cor == BLACK){
                rotacaoEsqPessoa(&(*Raiz)->Dir);
                if ((*Raiz)->Dir != NULL && (*Raiz)->Dir->Dir != NULL && (*Raiz)->Dir->Dir->cor == RED){
                    rotacaoEsqPessoa(Raiz);
                }

            }

            if (strcmp((*Raiz)->cpf, cpf) == 0) {
                Pessoa* aux = (*Raiz)->Dir;
                
                while (aux->Esq != NULL){
                    aux = aux->Esq;
                }

                strcpy((*Raiz)->cpf, aux->cpf);
                strcpy((*Raiz)->nome, aux->nome);
                strcpy((*Raiz)->cepCityNatal, aux->cepCityNatal);
                strcpy((*Raiz)->cepCityMora, aux->cepCityMora);
                strcpy((*Raiz)->dataNascimento, aux->dataNascimento);

                (*Raiz)->Dir = removerPessoa(&(*Raiz)->Dir, (*Raiz)->cpf);
            } else {
                (*Raiz)->Dir = removerPessoa(&(*Raiz)->Dir, cpf);
            }

        }
    }

    return *Raiz;
}

void liberarPessoas(Pessoa* raiz) {
    if (raiz == NULL) return;
    liberarPessoas(raiz->Esq);
    liberarPessoas(raiz->Dir);
    free(raiz);
}