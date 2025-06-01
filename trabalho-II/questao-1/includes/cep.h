#ifndef CEP_H
#define CEP_H

#include "cores.h"
#include "cidade.h"

// Declarações antecipadas
typedef struct Cidade Cidade;
typedef struct Estado Estado;
typedef struct Pessoa Pessoa;

typedef struct Cep {
    int cep;
    Cidade* cidade;
    Cor cor;
    struct Cep *Pai;
    struct Cep *Esq, *Dir;
} Cep;

Cep* buscarCep(Cep* raiz, int valor);
Cep* criarNoCep(int cep, Cidade* cidade);
int corCep(Cep *no);
void trocarCorCep(Cep *no);
void rotacaoEsquerdaCep(Cep **Raiz);
void rotacaoDireitaCep(Cep **Raiz);
void balancearCep(Cep** raiz, Cep* no);
int inserirCep(Cep** Raiz, Cep* Pai, int valor, Cidade* cidade);
void cadastrarCep(Estado** listaEstados, char* nomeEstado, char* nomeCity, int valorCep);
int removerCep(Cep** arvoreCep, Pessoa* arvorePessoa, int valorCep, char* nomeCity);
Cep* buscarCepEmEstado(Estado* listaEstados, int valorCep);
Cep* buscarCepEmCidade(Cidade* cidade, int valorCep);
#endif