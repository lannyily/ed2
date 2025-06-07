#ifndef ESTADO_H
#define ESTADO_H
#include "cidade.h"

typedef struct Cidade Cidade;

typedef struct Estado{
    char nomeEst[50];
    char nomeCap[50];
    int quantCity;
    int tamPopu;

    Cidade *capital;
    Cidade *cidades;

    struct Estado *Ant;
    struct Estado *Prox;
}Estado;


Estado* criarNoEstado(char* nomeEstado, char* nomeCapital);
void insertionSort(Estado** listaEstados);
void inserirEstadosOrdenado(Estado** lista, char* nomeEstado, char* nomeCapital);
void buscaEstado(Estado* lista, char* nomeEstado, Estado** resultado);
void imprimirEstados(Estado* lista);

#endif 