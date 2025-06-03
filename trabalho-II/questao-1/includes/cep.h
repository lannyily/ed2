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
void buscaCep(Cep* Raiz, char* cep, Cep** resultado);
Cep* criarNoCep(char* cep);
int insereCep(Cep** Raiz, Cep* No);
void cadastrarCep(Estado* lista,  char* nomeEst, char* nomeCity, char* cep);
void imprimirCidadesCeps(Cidade* raiz);
void imprimirCeps(Cep* raiz);

#endif 