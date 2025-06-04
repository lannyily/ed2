#ifndef CEP_H
#define CEP_H

#include "cidade.h"

typedef struct Cidade Cidade;
typedef struct Estado Estado; 



typedef struct Cep{
    char Cep[50];

    struct Cep *Esq, *Dir;
}Cep;



#endif 