#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/cidade.h"
#include "../includes/cores.h"

Cidade* criarNo(char* nomeCity, int tamPopu){
    Cidade* nova = (Cidade*)malloc(sizeof(Cidade));

    strcpy(nova->nomeCity, nomeCity);
    nova->tamPopu = tamPopu;
    nova->arv_cep = NULL;
    nova->cor = RED;
    nova->Pai = NULL;
    nova->Dir = NULL;
    nova->Esq = NULL;
    return nova;
}

int cor(Cidade *no){
 if (no == NULL) {
        return BLACK; // Nós nulos são considerados pretos
    }
    return no->cor;
}
void trocarCor(Cidade *no) {
    if (no != NULL) {
        no->cor = (no->cor == RED) ? BLACK : RED;
    }
}

int balancear();

int insereCidade(Cidade** Raiz, Cidade *Pai, char* nomeCity, int tamPopu) {
    int inseriu = 0;

    if (*Raiz == NULL) {
        Cidade* nova = criarNo(nomeCity, tamPopu);
        nova->Pai = Pai;
        *Raiz = nova;

        // A raiz deve ser sempre preta
        if (Pai == NULL) {
            nova->cor = BLACK;
        }
        return 1;
    }

    // Inserção na subárvore esquerda
    if (strcmp(nomeCity, (*Raiz)->nomeCity) < 0) {
        insereCidade(&(*Raiz)->Esq, *Raiz, nomeCity, tamPopu);

        // Verificar e corrigir violações na subárvore esquerda
        if (cor((*Raiz)->Esq) == RED && cor((*Raiz)->Esq->Esq) == RED) {
            rotacaoDireita(Raiz);
            trocarCor(*Raiz);
            trocarCor((*Raiz)->Dir);
        }
    }
    // Inserção na subárvore direita
    else if (strcmp(nomeCity, (*Raiz)->nomeCity) > 0) {
        insereCidade(&(*Raiz)->Dir, *Raiz, nomeCity, tamPopu);

        // Garantir que não haja nós vermelhos na subárvore direita
        if (cor((*Raiz)->Dir) == RED) {
            rotacaoEsquerda(Raiz);
        }
    } else {
        // Cidade já existe
        printf("Cidade ja existe!\n");
    }

    // Garantir que a raiz seja preta
    if (Pai == NULL) {
        (*Raiz)->cor = BLACK;
    }

    return inseriu;
}