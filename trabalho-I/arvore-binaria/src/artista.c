#include "../include/artista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Artista* criarArtista(char* nome, char* tipo, char* estiloM) {
    Artista* no = (Artista*)malloc(sizeof(Artista));

    strcpy(no->nome, nome);
    strcpy(no->tipo, tipo);
    strcpy(no->estiloMusical, estiloM);
    no->numAlbuns = 0;
    no->Esq = NULL;
    no->Dir = NULL;
    return no;
}
int insereArtista(Artista** R, Artista* No) {
    if (*R == NULL) {
        *R = No;
        return 1; // Inserção bem-sucedida
    }

    if (strcmp(No->nome, (*R)->nome) < 0) {
        return insereArtista(&((*R)->Esq), No); // Insere na subárvore esquerda
    } else if (strcmp(No->nome, (*R)->nome) > 0) {
        return insereArtista(&((*R)->Dir), No); // Insere na subárvore direita
    }

    return 0; // Artista já existe
}

void imprimirArtistas(Artista* R) {
    if (R != NULL) {
        imprimirArtistas(R->Esq);
        printf("-------------------------------------------------------------\n");
        printf("%-15s %-10s %-15s %-5s\n", "Nome", "Tipo", "Estilo", "Albuns");
        printf("%-15s  %-10s  %-15s %-5d\n", R->nome, R->tipo, R->estiloMusical, R->numAlbuns);
        printf("-------------------------------------------------------------\n");
        imprimirArtistas(R->Dir);
    }
}

int comparaString(char* nomeBusca, char* nome){
    if (*nomeBusca != 0) {                                                    
        if (*nome == 0) return 0;                                            
        if (*nomeBusca == *nome) return comparaString(++nomeBusca, ++nome); 
        return 0;                                                            
    } else {
        return (*nome == 0); // ambas terminaram juntas? são iguais
    }
}

void buscaArtista(Artista* R, char* nome, Artista** resultado) {
    *resultado = NULL; // Inicializa o resultado como NULL

    if (R != NULL) {
        if (comparaString(R->nome, nome)) {
            *resultado = R; // Encontrou o artista
        } else if (strcmp(nome, R->nome) < 0) {
            buscaArtista(R->Esq, nome, resultado); // Continua na subárvore esquerda
        } else {
            buscaArtista(R->Dir, nome, resultado); // Continua na subárvore direita
        }
    }
}

void cadastrarArtista(Artista** raiz, char* nome, char* tipo, char* estilo) {
    Artista* artista = NULL;
    buscaArtista(*raiz, nome, &artista); // Resultado da busca armazenado em 'artista'

    if (artista != NULL) {
        printf("%s já existe\n", nome);
    } else {
        Artista* novo = criarArtista(nome, tipo, estilo);
        insereArtista(raiz, novo);
        printf("%s cadastrado com sucesso\n", nome);
    }
}
