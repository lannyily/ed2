#ifndef CIDADE_H
#define CIDADE_H

typedef struct Estado Estado; 
typedef struct Cep Cep;
typedef struct arv23cep arv23cep;

typedef struct Cidade{
    char nomeCity[50];
    int tamPopu;
    arv23cep* arvCeps;
}Cidade;

typedef struct arv23cidade{
    Cidade *Info1, *Info2;
    int Ninfos;
    
    struct arv23cidade *Esq, *Dir, *Cent;
}arv23cidade;

Cidade* criarCidade(char* nomeCity, int tamPopu);
arv23cidade* criarNo23(Cidade* cidadeInfo, arv23cidade* Esq, arv23cidade* Cen);
void addInfo(arv23cidade** no, Cidade* cidadeInfo, arv23cidade* subArvInfo);
arv23cidade* quebraNo(arv23cidade** no, Cidade* cidadeInfo, Cidade** sobe, arv23cidade* FilhoDir);
arv23cidade* insere23Cidade(arv23cidade** Raiz, Cidade* noCidade, arv23cidade* Pai, Cidade** sobe);
void cadastrarCidade(Estado* lista, char* nomeEst, char* nomeCity, int tamPopu, Cidade** sobe);
Cidade* buscaCidade(arv23cidade* Raiz, char* nomeCity);

#endif 