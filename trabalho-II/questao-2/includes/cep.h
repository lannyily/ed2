#ifndef CEP_H
#define CEP_H

#include "cidade.h"

typedef struct Cidade Cidade;
typedef struct Estado Estado; 

typedef struct Cep{
    char Cep[50];
}Cep;

typedef struct arv23cep{
    Cep *Info1, *Info2;
    int Ninfos;
    
    struct arv23cep *Esq, *Dir, *Cent;
}arv23cep;

arv23cep* criarNo23Cep(Cep* cepInfo, arv23cep* Esq, arv23cep* Cen);
void addInfoCep(arv23cep** no, Cep* cepInfo, arv23cep* subArvInfo);
arv23cep* quebraNoCep(arv23cep** no, Cep* cepInfo, Cep** sobe, arv23cep* Dir);
arv23cep* insere23Cep(arv23cep** Raiz, Cep* cepInfo, arv23cep* Pai, Cep** sobe);
Cep* buscaCep(arv23cep* Raiz, char* cepNum);
void imprimirCep23(arv23cep* Raiz);
void imprimirCidades23(arv23cidade* Raiz);
void imprimirEstadosCidadesCeps23(Estado* listaEstados);
void cadastrarCep23(Estado* listaEstados, arv23cep* raizCep, char* nomeEst, char*nomeCity, char* cep, Cep** sobe);
void redistribuirCep(arv23cep** Raiz, arv23cep** Pai);
int ehFolhaCep(arv23cep* cep);
void removerMaiorEsqCep(arv23cep** Raiz, arv23cep** maiorPai, arv23cep** maiorRemove, int localInfo);
void removerCep23(arv23cep** Raiz, arv23cep** Pai, char* cep);
Cep* buscarCepEmCidade(arv23cidade* arvCidades, char* cep);
Cep* buscarCepEmEstado(Estado* estado, char* cep);
void liberarCep(arv23cep* raiz);
void liberarCidade(arv23cidade* raiz);
void liberarEstados(Estado* inicio);

#endif 