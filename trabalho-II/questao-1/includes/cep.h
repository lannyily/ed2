#ifndef CEP_H
#define CEP_H

typedef struct Cidade Cidade;

typedef enum CoresCep
{
    RED = 1,
    BLACK = 0
}CoresCep;

typedef struct Cep{
    int Cep;
    enum CoresCep cor;

    struct Cep *Esq, *Dir;
}Cep;

#endif 