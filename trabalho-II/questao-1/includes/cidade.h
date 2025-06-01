#ifndef CIDADE_H
#define CIDADE_H

#include "cores.h"
#include "cep.h"

// Declarações antecipadas
typedef struct Cep Cep;
typedef struct Estado Estado;

typedef struct Cidade {
    char nomeCity[50];
    int tamPopu;
    Cep *arv_cep;
    Cor cor;
    struct Cidade *Pai;
    struct Cidade *Esq, *Dir;
} Cidade;

Cidade* criarNoCidade(char* nomeCity, int tamPopu);
int corCidade(Cidade *no); 
void trocarCorCidade(Cidade *no);  
void balancearCidade(Cidade** raiz); 
int insereCidade(Cidade** Raiz, Cidade *Pai, char* nomeCity, int tamPopu);
void rotacaoEsquerdaCidade(Cidade **Raiz);
void rotacaoDireitaCidade(Cidade **Raiz);
Cidade* buscaCidade(Cidade* raiz, char* nomeCity);
void imprimirCidades(Cidade* raiz);
void cadastrarCidade(Estado** listaEstados, char* nomeEstado, char* nomeCity, int tamPopu);

#endif