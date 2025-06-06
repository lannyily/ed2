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

    struct Pessoa *Esq, *Dir;
}Pessoa;

typedef struct arv23Pessoa{
    Pessoa *Info1, *Info2;
    int Ninfos;

    struct arv23Pessoa *Esq, *Dir, *Cent;
}arv23Pessoa;

int dataValida(char* dataN);
Pessoa* criarNoPessoa(char* nome, char* cpf, char* cepCityNatal, char* cepCityMora, char* dataN);
arv23Pessoa* criarNo23Pessoa(Pessoa* Info, arv23Pessoa* Esq, arv23Pessoa* Cen);
void addInfoPessoa(arv23Pessoa* no, Pessoa* Info, arv23Pessoa* subArv);
arv23Pessoa* quebraNoPessoa(arv23Pessoa** no, Pessoa* pessoaInfo, Pessoa** sobe, arv23Pessoa* Dir);
arv23Pessoa* insere23Pessoa(arv23Pessoa** Raiz, Pessoa* noPessoa, arv23Pessoa* Pai, Pessoa** sobe);
void imprimirPessoas23(arv23Pessoa *Raiz);
Pessoa* buscaPessoa(arv23Pessoa* Raiz, char* cpf);
int ehFolha(arv23Pessoa* pessoa);
void redistribuir(arv23Pessoa** Raiz, arv23Pessoa** Pai);
void removerMaiorEsq(arv23Pessoa** Raiz, arv23Pessoa** maiorPai, arv23Pessoa** maiorRemove, int localInfo);
void removerPessoa23(arv23Pessoa** Raiz, arv23Pessoa** Pai, char* cpf);


#endif 