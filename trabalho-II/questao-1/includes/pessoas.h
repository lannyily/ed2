#ifndef PESSOA_H
#define PESSOA_H

#include "cores.h"
#include "Data.h" 


typedef struct Pessoa {
    long cpf;
    char nome[150];
    int cep_natal; //cidade natal
    int cep_mora; //cidade onde mora
    Data data_nascimento;
    Cor cor;
    struct Pessoa *pai;
    struct Pessoa *esquerda;
    struct Pessoa *direita;
}Pessoa;

#endif // NO_PESSOA_H