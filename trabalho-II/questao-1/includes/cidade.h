#ifndef CIDADE_H
#define CIDADE_H


typedef struct Estado Estado; 
typedef struct Cep Cep;

typedef enum CoresCity
{
    RED = 1,
    BLACK = 0
}CoresCity;

typedef struct Cidade{
    char nomeCity[50];
    int tamPopu;
    enum CoresCity cor; 
    Cep* ceps;

    struct Cidade *Esq, *Dir;
}Cidade;

enum CoresCity corCidade(Cidade* cidade);
Cidade* rotacaoEsqCidade(Cidade** Raiz);
Cidade* rotacaoDirCidade(Cidade** Raiz);
void trocarCorCidade(Cidade** Raiz);
void buscaCidade(Cidade* Raiz, char* nomeCity, Cidade** resultado);
Cidade* criarNoCidade(char* nomeCity, int tamPopu);
int insereCidade(Cidade** Raiz, Cidade* No);
void cadastrarCidade(Estado* lista, char* nomeEst, char* nomeCity, int tamPopu);
void imprimirCidades(Cidade* raiz);
void imprimirEstadosCidades(Estado* listaEstados);

#endif 