#ifndef CIDADE_H
#define CIDADE_H
#include "cores.h"
#include "cep.h"
typedef struct Cidade{
    char nomeCity[50];
    int tamPopu;
    Cep *arv_cep;
    Cor cor;
    struct Cidade *Pai;
    struct Cidade *Esq, *Dir;
}Cidade;

Cidade* criarNo(char* nomeCity, int tamPopu);
int cor(Cidade *no); // INFO: não entendi para que serve essa função 
int trocarCor(Cidade *no);  // TODO: Implementar a função trocor
int balancear(Cidade *no); // TODO: Implementar a função balancear
int insereCidade(Cidade** Raiz, Cidade *Pai, char* nomeCity, int tamPopu);
#endif 