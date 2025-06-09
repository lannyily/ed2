#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"
#include "../includes/cidade.h"
#include "../includes/cep.h"
#include "../includes/pessoa.h"
#include "../includes/curiosidades.h"

Estado* estadoMaisPopuloso(Estado* listaEstados){
    Estado* maisPopuloso = listaEstados;
    Estado* atual = listaEstados->Prox;

    while (atual != NULL) {
        if (atual->tamPopu > maisPopuloso->tamPopu) {
            maisPopuloso = atual;
        }
        atual = atual->Prox;
    }

    return maisPopuloso;
}

int populacaoCapital(Estado* listaEstados, char* nomeEstado) {
    Estado* atual = listaEstados;
    int populacao = 0;

    while (atual != NULL) {
        if (strcmp(atual->nomeEst, nomeEstado) == 0) {
            if (atual->capital != NULL) {
                populacao = atual->capital->tamPopu;
            } else {
                printf("O estado \"%s\" nao possui capital cadastrada\n", nomeEstado);
            }
        }
        atual = atual->Prox;
    }

    
    return populacao;
}


void buscarCidadeMaisPopulosaSemCapital(Cidade* raiz, Cidade** maisPopulosa, Estado* estadoAtual, Estado** estadoDaCidade){
    if(raiz != NULL){
        if ((estadoAtual->capital == NULL || raiz != estadoAtual->capital) &&
            (*maisPopulosa == NULL || raiz->tamPopu > (*maisPopulosa)->tamPopu)) {
            
            *maisPopulosa = raiz;
            *estadoDaCidade = estadoAtual;
        }

        buscarCidadeMaisPopulosaSemCapital(raiz->Esq, maisPopulosa, estadoAtual, estadoDaCidade);
        buscarCidadeMaisPopulosaSemCapital(raiz->Dir, maisPopulosa, estadoAtual, estadoDaCidade);
    }
}

void cidadeMaisPopulosaSemCapitalTodosEstados(Estado* listaEstados){
    
    Cidade* maisPopulosa = NULL;
    Estado* estadoDaCidade = NULL;
    Estado* atual = listaEstados;

    
    while (atual != NULL) {
        buscarCidadeMaisPopulosaSemCapital(atual->cidades, &maisPopulosa, atual, &estadoDaCidade);
        atual = atual->Prox;
    }

    
    if (maisPopulosa != NULL && estadoDaCidade != NULL) {
        printf("Cidade mais populosa (sem ser capital): %s\n", maisPopulosa->nomeCity);
    } else {
        printf("Nenhuma cidade encontrada\n");
    }
}

int contarPessoasForaCidadeNatal(Pessoa* raiz){
    int contador = 0;

    if (raiz != NULL) {
        if (strcmp(raiz->cepCityMora, raiz->cepCityNatal) != 0) {
            contador = 1;
        }

        contador += contarPessoasForaCidadeNatal(raiz->Esq);
        contador += contarPessoasForaCidadeNatal(raiz->Dir);
    }

    return contador;
}


Cidade* buscarCidadePorCepNaArvore(Cidade* raiz, char* cep) {
    Cidade* encontrou = NULL;
    if (raiz != NULL) {
        
        if (buscarCepEmCidade(raiz, cep) != NULL) {
            encontrou = raiz;
        }

        
        Cidade* esq = buscarCidadePorCepNaArvore(raiz->Esq, cep);
        if (esq != NULL) {
            encontrou = esq;
        }

        
        Cidade* dir = buscarCidadePorCepNaArvore(raiz->Dir, cep);
        if (dir != NULL) {
            encontrou = dir;
        }
    }
    return encontrou;
}

Cidade* buscarCidadePorCep(Estado* listaEstados, char* cep) {
    Estado* atualEstado = listaEstados;

    while (atualEstado != NULL) {
        Cidade* resultado = buscarCidadePorCepNaArvore(atualEstado->cidades, cep);
        if (resultado != NULL) {
            return resultado;
        }
        atualEstado = atualEstado->Prox;
    }
    return NULL; 
}

int pessoasForaCidadeNatal(Pessoa* raiz, char* cepCidadeNatal) {
    
    int contador = 0;

    if (raiz != NULL){
        
        if (strcmp(raiz->cepCityNatal, cepCidadeNatal) == 0) {
            if (strcmp(raiz->cepCityMora, cepCidadeNatal) != 0) {
                contador = 1;
            }
        }

        
        contador += pessoasForaCidadeNatal(raiz->Esq, cepCidadeNatal);
        contador += pessoasForaCidadeNatal(raiz->Dir, cepCidadeNatal);
    }

    return contador;
}


int contarPessoasNaoNascidasNaCidade(Pessoa* raiz, char* cepCidade) {
    int contador = 0;
    
    if (raiz != NULL) {
        
        if (strcmp(raiz->cepCityMora, cepCidade) == 0) {
            if (strcmp(raiz->cepCityNatal, cepCidade) != 0) {
                contador = 1;
            }
        }

        contador += contarPessoasNaoNascidasNaCidade(raiz->Esq, cepCidade);
        contador += contarPessoasNaoNascidasNaCidade(raiz->Dir, cepCidade);

    }

    return contador;
}
