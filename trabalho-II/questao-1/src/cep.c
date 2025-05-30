#include <stdio.h>
#include <stdlib.h>
#include "../includes/cep.h"
#include "../includes/cores.h"

Cep* criarNoCep(int valorCep) {
    Cep* novo = (Cep*)malloc(sizeof(Cep));

    novo->cep = valorCep;
    novo->cor = RED;
    novo->Pai = NULL;
    novo->Esq = NULL;
    novo->Dir = NULL;
    return novo;
}

int corCep(Cep *no) {
    if (no == NULL) {
        return BLACK; // Nós nulos são considerados pretos
    }
    return no->cor;
}

void trocarCorCep(Cep *no) {
    if (no != NULL) {
        no->cor = (no->cor == RED) ? BLACK : RED;
    }
}

void corrigirCores(Cep *no) {
    if (cor(no->Esq) == RED && cor(no->Dir) == RED) {
        trocarCor(no->Esq);
        trocarCor(no->Dir);
        trocarCor(no);
    }
}

int insereCep(Cep** Raiz, Cep *Pai, int valorCep) {
  int inseriu = 0;

 
  if (*Raiz == NULL) {
        Cep* novo = criarNoCep(valorCep);
        novo->Pai = Pai;
        *Raiz = novo;

        // A raiz deve ser sempre preta
        if (Pai == NULL) {
            novo->cor = BLACK;
        }
        inseriu = 1;
    }

    // Inserção na subárvore esquerda
    if (valorCep < (*Raiz)->cep) {
        insereCep(&(*Raiz)->Esq, *Raiz, valorCep);

        // Verificar e corrigir violações na subárvore esquerda
        if (corCep((*Raiz)->Esq) == RED && corCep((*Raiz)->Esq->Esq) == RED) {
            rotacaoDireitaCep(Raiz);
            trocarCorCep(*Raiz);
            trocarCorCep((*Raiz)->Dir);
        }
    }
    // Inserção na subárvore direita
    else if (valorCep > (*Raiz)->cep) {
        insereCep(&(*Raiz)->Dir, *Raiz, valorCep);

        // Garantir que não haja nós vermelhos na subárvore direita
        if (corCep((*Raiz)->Dir) == RED) {
            rotacaoEsquerdaCep(Raiz);
            trocarCorCep(*Raiz);
        }
    } else {
        // CEP já existe
        printf("CEP já existe!\n");
    }

    // Garantir que a raiz seja preta
    if (Pai == NULL) {
        (*Raiz)->cor = BLACK;
    }
    corrigirCoresCep(*Raiz);
    // TODO: Implementar função balancear e verificar cor da raiz.
    return inseriu;
}

void rotacaoEsquerdaCep(Cep** Raiz) {
    // Implementação da rotação à esquerda
}

void rotacaoDireitaCep(Cep** Raiz) {
    // Implementação da rotação à direita
}
