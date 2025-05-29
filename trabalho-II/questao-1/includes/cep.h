#ifndef CEP_H
#define CEP_H
#include "cores.h"

typedef struct Cep{
  int cep;
  Cor cor;
  struct Cep *Esq, *Dir;
}Cep;

#endif // CEP_H