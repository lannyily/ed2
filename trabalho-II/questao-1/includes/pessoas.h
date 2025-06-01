#ifndef PESSOA_H
#define PESSOA_H

#include "cores.h"
#include "data.h"
#include "cidade.h"
#include "estado.h"

// Declarações antecipadas
typedef struct Cep Cep;
typedef struct Cidade Cidade;
typedef struct Estado Estado;

typedef struct Pessoa {
    int cpf;
    char nome[150];
    int cep_natal; //cidade natal
    int cep_mora; //cidade onde mora
    Data data_nascimento;
    Cor cor;
    struct Pessoa *Pai;
    struct Pessoa *Esq, *Dir;
} Pessoa;

Pessoa* criarNoPessoa(int cpf, char *nome, int cep_natal, int cep_mora, Data data_nascimento);
int corPessoa(Pessoa *no);
void trocarCorPessoa(Pessoa *no);
void rotacaoEsquerdaPessoa(Pessoa **Raiz);
void rotacaoDireitaPessoa(Pessoa **Raiz);
void balancearPessoa(Pessoa** H);
void move2EsqRED(Pessoa **raiz);
void move2DirRED(Pessoa **raiz);
Pessoa* removerNoPessoa(Pessoa *raiz, int valor) ;
Pessoa* removerMenorLLRB(Pessoa *raiz);
int inserirPessoa(Pessoa **raiz, Pessoa *pai, int cpf, char *nome, int cep_natal, int cep_mora, Data data_nascimento);
void cadastrarPessoa(Estado* estado, Pessoa** arvorePessoa, int cpf, char* nome, int cep_natal, int cep_mora, Data data_nasc);
int PessoaAssociada(Pessoa* arvorePessoa, int valorCep);
int removerPessoa(Pessoa** arvorePessoa, int cpf);
void imprimirPessoas(Pessoa* raiz);
#endif // NO_PESSOA_H