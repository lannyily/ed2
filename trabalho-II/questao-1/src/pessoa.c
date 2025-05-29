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
    nova->pai = NULL;
    nova->esq = NULL;
    nova->dir = NULL;

    return nova;
}

int inserirPessoa(Pessoa** Raiz, Pessoa* pai, long cpf, char* nome, int cep_natal, int cep_mora, Data data_nasc) {
    Pessoa* atual = *Raiz;
    int inseriu = 0;

    if (atual == NULL) {
        Pessoa* nova = criar_no_pessoa(cpf, nome, cep_natal, cep_mora, data_nasc);
        *Raiz = nova;
        if (pai == NULL) {
            nova->cor = BLACK; 
        inseriu = 1;
    }

    if (cpf < atual->cpf) {
        inserirPessoa(&(atual->esq), atual, cpf, nome, cep_natal, cep_mora, data_nasc);
    } else if (cpf > atual->cpf) {
        inserirPessoa(&(atual->dir), atual, cpf, nome, cep_natal, cep_mora, data_nasc);
    } else {
        // CPF ja existe
        printf("Aviso: CPF %d ja existe. Insercao cancelada.\n", cpf);
    }
    return inseriu;
}