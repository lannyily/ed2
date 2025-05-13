#ifndef ESTADO_H
#define ESTADO_H

typedef struct Estado{
    char nomeEst[50];
    char nomeCap[50];
    int quantCity;
    int tamPopu;

    struct Estado *Ant;
    struct Estado *Prox;
}Estado;

Estado* criarNo(char* nomeEstado, char* nomeCapital, int quantCity, int tamPopu);
void inserirEstadosOrdenado(Estado** lista, char* nomeEstado, char* nomeCapital, int quantCity, int tamPopu);

#endif 