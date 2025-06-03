#ifndef PESSOA_H
#define PESSOA_H

#include "cidade.h"

typedef struct Cep Cep;
typedef struct Cidade Cidade;
typedef struct Estado Estado;


typedef struct Pessoa{
    char nome[50];
    char cpf[20];
    char cepCityNatal[20];
    char cepCityMora[20];
    char dataNascimento[10];
    char Cep[50];
    enum Cores cor;

    struct Pessoa *Esq, *Dir;
}Pessoa;

#endif 