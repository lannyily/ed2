#ifndef PESSOA_H
#define PESSOA_H

#include "cores.h"
#include "Data.h" 


typedef struct Pessoa {
    int cpf;
    char nome[150];
    int cep_natal; //cidade natal
    int cep_mora; //cidade onde mora
    Data data_nascimento;
    Cor cor;
    struct Pessoa *Pai;
    struct Pessoa *Esq, *Dir;
}Pessoa;
int corPessoa(Pessoa *no);
void trocarCorPessoa(Pessoa *no);
int inserePessoa(Pessoa **raiz, Pessoa *pai, int cpf, char *nome, int cep_natal, int cep_mora, Data data_nascimento);
#endif // NO_PESSOA_H