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
    enum Cores cor;

    struct Pessoa *Esq, *Dir;
}Pessoa;

int dataValida(char* dataN);
enum Cores corPessoa(Pessoa* pessoa);
Pessoa* rotacaoEsqPessoa(Pessoa** Raiz);
Pessoa* rotacaoDirPessoa(Pessoa** Raiz);
void trocarCorPessoa(Pessoa** Raiz);
void buscaPessoa(Pessoa* Raiz, char* cpf, Pessoa** resultado);
Pessoa* criarNoPessoa(char* nome, char* cpf, char* cepCityNatal, char* cepCityMora, char* dataN);
int inserePessoa(Pessoa** Raiz, Pessoa* No);
void cadastrarPessoa(Estado* lista, Pessoa** Raiz, char* nome, char* cpf, char* cepCityNatal, char* cepCityMora, char* dataN);
Pessoa* insereAjustaCorPessoa(Pessoa** raiz, Pessoa* no);
void imprimirPessoas(Pessoa* raiz);
Pessoa* removerPessoa(Pessoa** Raiz, char* cpf);

#endif 