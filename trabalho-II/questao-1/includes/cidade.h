#ifndef CIDADE_H
#define CIDADE_H
#include "cores.h"
#include "cep.h"
typedef struct Cidade{
    char nomeCity[50];
    int tamPopu;
    Cep *arv_cep;
    Cor cor;
    struct Cidade *Esq, *Dir;
}Cidade;

#endif 