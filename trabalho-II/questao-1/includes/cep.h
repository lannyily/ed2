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
void balancearCep(Cep **raiz);
int inserirCep(Cep** Raiz, Cep* Pai, int valor, Cidade* cidade);
void cadastrarCep(Estado** listaEstados, char* nomeEstado, char* nomeCity, int valorCep);
Cep* buscarCepEmEstado(Estado* listaEstados, int valorCep);
Cep* buscarCepEmCidade(Cidade* cidade, int valorCep);
Cep* removerNoCep(Cep *raiz, int valor);
Cep* removerMenorLLRB_Cep(Cep *raiz);
void move2EsqRED_Cep(Cep **H);
void move2DirRED_Cep(Cep **H);
int removerCep(Cep** arvoreCep, Pessoa* arvorePessoa, int valorCep);
int removerCepDoEstado(Estado* listaEstados, Pessoa* arvorePessoa, int valorCep, char* nomeEstado, char* nomeCity);
void imprimirArvoreCep(Cep* raiz, int nivel); // FIX: CONSERTAR ESSA PORRA.
#endif