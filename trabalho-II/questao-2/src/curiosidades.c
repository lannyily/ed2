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


void buscarCidadeMaisPopulosaSemCapital(arv23cidade* raiz, Cidade** maisPopulosa, Estado* estadoAtual, Estado** estadoDaCidade) {
    if (raiz != NULL) {
        
        if (raiz->Info1 != NULL) {
            if ((estadoAtual->capital == NULL || raiz->Info1 != estadoAtual->capital) &&
                (*maisPopulosa == NULL || raiz->Info1->tamPopu > (*maisPopulosa)->tamPopu)) {
                
                *maisPopulosa = raiz->Info1;
                *estadoDaCidade = estadoAtual;
            }
        }

    
        if (raiz->Ninfos == 2 && raiz->Info2 != NULL) {
            if ((estadoAtual->capital == NULL || raiz->Info2 != estadoAtual->capital) &&
                (*maisPopulosa == NULL || raiz->Info2->tamPopu > (*maisPopulosa)->tamPopu)) {
                
                *maisPopulosa = raiz->Info2;
                *estadoDaCidade = estadoAtual;
            }
        }

        
        buscarCidadeMaisPopulosaSemCapital(raiz->Esq, maisPopulosa, estadoAtual, estadoDaCidade);
        buscarCidadeMaisPopulosaSemCapital(raiz->Cent, maisPopulosa, estadoAtual, estadoDaCidade);
        buscarCidadeMaisPopulosaSemCapital(raiz->Dir, maisPopulosa, estadoAtual, estadoDaCidade);
    }

    
}


void cidadeMaisPopulosaSemCapitalTodosEstados(Estado* listaEstados) {
    if (listaEstados == NULL) {
        printf("Lista de estados vazia.\n");
        return;
    }

    Cidade* maisPopulosa = NULL;
    Estado* estadoDaCidade = NULL;
    Estado* atual = listaEstados;

    
    while (atual != NULL) {
        
        buscarCidadeMaisPopulosaSemCapital(atual->arvCidades, &maisPopulosa, atual, &estadoDaCidade);
        atual = atual->Prox;
    }

    
    if (maisPopulosa != NULL && estadoDaCidade != NULL) {
        printf("Cidade mais populosa (sem ser capital): %s (%d habitantes)\n", 
               maisPopulosa->nomeCity, maisPopulosa->tamPopu);
        printf("Estado: %s\n", estadoDaCidade->nomeEst);
    } else {
        printf("Nenhuma cidade encontrada.\n");
    }
}


int contarPessoasForaCidadeNatal(arv23Pessoa* raiz) {
    int contador = 0;
    
    if (raiz != NULL) {
        
        if (raiz->Info1 != NULL) {
            if (strcmp(raiz->Info1->cepCityMora, raiz->Info1->cepCityNatal) != 0) {
                contador++;
            }
        }

        
        if (raiz->Ninfos == 2 && raiz->Info2 != NULL) {
            if (strcmp(raiz->Info2->cepCityMora, raiz->Info2->cepCityNatal) != 0) {
                contador++;
            }
        }

        contador += contarPessoasForaCidadeNatal(raiz->Esq);
        contador += contarPessoasForaCidadeNatal(raiz->Cent);
        contador += contarPessoasForaCidadeNatal(raiz->Dir);
    }

    return contador;
}

int pessoasForaCidadeNatal(arv23Pessoa* raiz, char* cepCidadeNatal) {
    int contador = 0;
    
    if (raiz != NULL) {
        
        if (raiz->Info1 != NULL) {
            if (strcmp(raiz->Info1->cepCityNatal, cepCidadeNatal) == 0 && 
                strcmp(raiz->Info1->cepCityMora, cepCidadeNatal) != 0) {
                contador++;
            }
        }

        
        if (raiz->Ninfos == 2 && raiz->Info2 != NULL) {
            if (strcmp(raiz->Info2->cepCityNatal, cepCidadeNatal) == 0 && 
                strcmp(raiz->Info2->cepCityMora, cepCidadeNatal) != 0) {
                contador++;
            }
        }

        
        contador += pessoasForaCidadeNatal(raiz->Esq, cepCidadeNatal);
        contador += pessoasForaCidadeNatal(raiz->Cent, cepCidadeNatal);
        contador += pessoasForaCidadeNatal(raiz->Dir, cepCidadeNatal);
    }

    return contador;
}

int contarPessoasNaoNascidasNaCidade(arv23Pessoa* raiz, char* cepCidade) {
    int contador = 0;

    if (raiz != NULL) {
       
        if (raiz->Info1 != NULL) {
            if (strcmp(raiz->Info1->cepCityMora, cepCidade) == 0 && 
                strcmp(raiz->Info1->cepCityNatal, cepCidade) != 0) {
                contador++;
            }
        }

        
        if (raiz->Ninfos == 2 && raiz->Info2 != NULL) {
            if (strcmp(raiz->Info2->cepCityMora, cepCidade) == 0 && 
                strcmp(raiz->Info2->cepCityNatal, cepCidade) != 0) {
                contador++;
            }
        }

        
        contador += contarPessoasNaoNascidasNaCidade(raiz->Esq, cepCidade);
        contador += contarPessoasNaoNascidasNaCidade(raiz->Cent, cepCidade);
        contador += contarPessoasNaoNascidasNaCidade(raiz->Dir, cepCidade);
    }


    return contador;
}