#ifndef CEP_H
#define CEP_H

#include "cidade.h"

typedef struct Cidade Cidade;
typedef struct Estado Estado; 



typedef struct Cep{
    char Cep[50];
    enum Cores cor;

    struct Cep *Esq, *Dir;
}Cep;

enum Cores corCep(Cep* cep);
Cep* rotacaoEsqCep(Cep** Raiz);
Cep* rotacaoDirCep(Cep** Raiz);
void trocarCorCep(Cep** Raiz);
Cep* criarNoCep(char* cep);
int insereCep(Cep** Raiz, Cep* No);
void cadastrarCep(Estado* lista,  char* nomeEst, char* nomeCity, char* cep);
Cep* insereAjustaCorCep(Cep** raiz, Cep* no);
void imprimirCidadesCeps(Cidade* raiz);
void imprimirCeps(Cep* raiz);
void buscaCep(Cep* Raiz, char* cep, Cep** resultado);
Cep* buscarCepEmCidade(Cidade* cidade, char* cep);
Cep* buscarCepEmEstado(Estado* estado, char* cep);
Cep* removerCep(Cep** Raiz, char* cep);
void liberarCep(Cep* raiz);
void liberarCidade(Cidade* raiz);
void liberarEstados(Estado* inicio);

#endif 