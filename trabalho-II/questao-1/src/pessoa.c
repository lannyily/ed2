#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/cidade.h"
#include "../includes/cores.h"
#include "../includes/pessoas.h"

Pessoa* criarNo(int cpf, char *nome, int cep_natal, int cep_mora, Data data_nascimento) {
    Pessoa* nova = (Pessoa*)malloc(sizeof(Pessoa));
    
    nova->cpf = cpf;
    strcpy(nova->nome, nome);
    nova->cep_natal = cep_natal;
    nova->cep_mora = cep_mora;
    nova->data_nascimento = data_nascimento;
    nova->cor = RED; // Inicialmente a cor é vermelha
    nova->Pai = NULL;
    nova->Esq = NULL;
    nova->Dir = NULL;

    return nova;
}

int cor(Pessoa *no){
 if (no == NULL) {
        return BLACK; // Nós nulos são considerados pretos
    }
    return no->cor;
}
void trocarCor(Pessoa *no) {
    if (no != NULL) {
        no->cor = (no->cor == RED) ? BLACK : RED;
    }
}


int inserirPessoa(Pessoa** Raiz, Pessoa* Pai, int cpf, char* nome, int cep_natal, int cep_mora, Data data_nasc) {
    int inseriu = 0;

    if (*Raiz == NULL) {
        Cidade* nova = criarNo(cpf, nome, cep_natal, cep_mora, data_nasc);
        nova->Pai = Pai;
        *Raiz = nova;

        // A raiz deve ser sempre preta
        if (Pai == NULL) {
            nova->cor = BLACK;
        }
        return 1;
    }
    if (cpf < (*Raiz)->cpf) {
        inserirPessoa(&(*Raiz)->Esq, *Raiz, cpf, nome, cep_natal, cep_mora, data_nasc);
                
        if (cor((*Raiz)->Esq) == RED && cor((*Raiz)->Esq->Esq) == RED) {
            rotacaoDireita(Raiz);
            trocarCor(*Raiz);
            trocarCor((*Raiz)->Dir);
        }
    } else if (cpf > (*Raiz)->cpf) {
        inserirPessoa(&(*Raiz)->Dir, *Raiz, cpf, nome, cep_natal, cep_mora, data_nasc);

        if (cor((*Raiz)->Dir) == RED) {
            rotacaoEsquerda(Raiz);
        }
    } else {
        // CPF ja existe
        printf("Aviso: CPF %d ja existe. Insercao cancelada.\n", cpf);
    }
    return inseriu;
}