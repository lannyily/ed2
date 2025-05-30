#ifndef CEP_H
#define CEP_H
#include "cores.h"

typedef struct Cep{
  int cep;
  Cor cor;
  struct Cep *Pai;
  struct Cep *Esq, *Dir;
}Cep;
int corCep(Cep *no);
void trocarCorCep(Cep *no);
Cep* criarNoCep(int valorCep);
int insereCep(Cep** Raiz, Cep *Pai, int valorCep);
#endif // CEP_H