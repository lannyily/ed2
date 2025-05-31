#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"

Estado* criarNo(char* nomeEstado, char* nomeCapital, int quantCity, int tamPopu){
    Estado* novo = (Estado*)malloc(sizeof(Estado));

    strcpy(novo->nomeEst, nomeEstado);
    strcpy(novo->nomeCap, nomeCapital);
    novo->quantCity = quantCity;
    novo->tamPopu = tamPopu;

    novo->Ant = NULL;
    novo->Prox = NULL;

    return novo;
}

int inserirEstado(Estado** lista, Estado* novo) {
    int inseriu = 0;
    
    Estado* atual = *lista;
    Estado* anterior = NULL;

    // Percorre a lista para encontrar a posição correta e verificar duplicatas
    while (atual != NULL) {
        // Verifica se já existe um estado com o mesmo nome
        if (strcmp(novo->nomeEst, atual->nomeEst) == 0) {
            return inseriu; // Estado já existe
        }

        // Se o nome do novo estado for maior, continua percorrendo
        if (strcmp(novo->nomeEst, atual->nomeEst) > 0) {
            anterior = atual;
            atual = atual->Prox;
        } else {
            break; // Encontrou a posição correta para inserção
        }
    }

    // Insere o novo estado na posição correta
    if (anterior == NULL) {
        // Insere no início da lista
        novo->Prox = *lista;
        if (*lista != NULL) {
            (*lista)->Ant = novo;
        }
        *lista = novo;
    } else {
        // Insere entre anterior e atual
        novo->Prox = atual;
        novo->Ant = anterior;
        anterior->Prox = novo;
        if (atual != NULL) {
            atual->Ant = novo;
        }
        inseriu = 1;
    }

    return inseriu; // Inserção bem-sucedida
}
Estado* buscaEstado(Estado* lista, char* nomeEstado) {
    Estado* atual = lista;

    // Percorre a lista de estados
    while (atual != NULL) {
        // Verifica se o nome do estado atual corresponde ao nome buscado
        if (strcmp(atual->nomeEst, nomeEstado) == 0) {
            return atual; // Estado encontrado
        }
        atual = atual->Prox; // Avança para o próximo estado
    }

    // Retorna NULL se o estado não for encontrado
    return 0;
}


void cadastrarEstado(Estado** lista, char* nomeEstado, char* nomeCapital, int quantCity, int tamPopu) {
    // Cria o novo estado
    Estado* novo = criarNo(nomeEstado, nomeCapital, quantCity, tamPopu);

    // Tenta inserir o estado na lista
    if (inserirEstado(lista, novo)) {
        printf("Estado \"%s\" cadastrado com sucesso!\n", nomeEstado);
    } else {
        printf("Erro: Estado com o nome \"%s\" ja existe na lista.\n", nomeEstado);
    }
}
