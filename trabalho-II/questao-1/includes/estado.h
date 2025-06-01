#ifndef ESTADO_H
#define ESTADO_H

#include "cidade.h"

typedef struct Estado {
    char nomeEst[50];
    char nomeCap[50];
    int quantCity;
    int tamPopu;
    Cidade *arv_city;
    struct Estado *Ant;
    struct Estado *Prox;
} Estado;

Estado* criarNoEstado(char* nomeEstado, char* nomeCapital, int quantCity, int tamPopu);
int inserirEstado(Estado** lista, Estado* novo);
Estado* buscaEstado(Estado* lista, char* nomeEstado);

#endif 