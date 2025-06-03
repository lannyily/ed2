#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"
#include "../includes/cidade.h"
#include "../includes/cep.h"

enum CoresCep corCidade(Cep* cep){
    return cep != NULL ? cep->cor : BLACK;
}


Cep* rotacaoEsqCep(Cep** Raiz){
    Cep* aux = (*Raiz)->Dir;
    (*Raiz)->Dir = aux->Esq;
    aux->Esq = *Raiz;
    aux->cor = (*Raiz)->cor;
    (*Raiz)->cor = RED;
    return aux;
}

Cep* rotacaoDirCep(Cep** Raiz){
    Cep* aux = (*Raiz)->Esq;
    (*Raiz)->Esq = aux->Dir;
    aux->Dir = *Raiz;
    aux->cor = (*Raiz)->cor;
    (*Raiz)->cor = RED;
    return aux;
}

