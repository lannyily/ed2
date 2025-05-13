#ifndef CIDADE_H
#define CIDADE_H

typedef struct Cidade{
    char nomeCity[50];
    int tamPopu;

    struct Cidade *Esq, *Dir;
}Cidade;

#endif 