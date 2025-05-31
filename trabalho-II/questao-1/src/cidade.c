#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/cidade.h"
#include "../includes/cores.h"
#include "../includes/cep.h"
#include "../includes/estado.h"

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

void corrigirCoresCidade(Cidade *no) {
    if (cor(no->Esq) == RED && cor(no->Dir) == RED) {
        trocarCor(no->Esq);
        trocarCor(no->Dir);
        trocarCor(no);
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
            trocarCor(*Raiz);
        }
    } else {
        // Cidade já existe
        printf("Cidade ja existe!\n");
    }

    corrigirCoresCidade(*Raiz);
    // TODO: Implementar função balancear e verificar cor da raiz.

    return inseriu;
}

void rotacaoEsquerdaCidade(Cidade **Raiz) {
    // Armazena o nó à direita da raiz atual em uma variável temporária
    Cidade *temp = (*Raiz)->Dir; 

    // Move o filho esquerdo do nó à direita (temp) para o filho direito da raiz atual
    (*Raiz)->Dir = temp->Esq;

    // Se o filho esquerdo de temp não for NULL, atualiza o pai desse nó para ser a raiz atual
    if (temp->Esq != NULL) {
        temp->Esq->Pai = *Raiz;
    }

    // Atualiza o pai de temp para ser o pai da raiz atual
    temp->Pai = (*Raiz)->Pai;

    // Se a raiz atual não tiver pai (ou seja, é a raiz da árvore), temp se torna a nova raiz
    if ((*Raiz)->Pai == NULL) {
        *Raiz = temp;
    } 
    // Caso contrário, verifica se a raiz atual é o filho esquerdo ou direito de seu pai
    else if ((*Raiz) == (*Raiz)->Pai->Esq) {
        // Se for o filho esquerdo, atualiza o ponteiro esquerdo do pai para apontar para temp
        (*Raiz)->Pai->Esq = temp;
    } else {
        // Se for o filho direito, atualiza o ponteiro direito do pai para apontar para temp
        (*Raiz)->Pai->Dir = temp;
    }

    // Faz com que a raiz atual se torne o filho esquerdo de temp
    temp->Esq = *Raiz;

    // Atualiza o pai da raiz atual para ser temp
    (*Raiz)->Pai = temp;
}

void rotacaoDireita(Cidade **Raiz) {
    // Armazena o nó à esquerda da raiz atual em uma variável temporária
    Cidade *temp = (*Raiz)->Esq;

    // Move o filho direito do nó à esquerda (temp) para o filho esquerdo da raiz atual
    (*Raiz)->Esq = temp->Dir;

    // Se o filho direito de temp não for NULL, atualiza o pai desse nó para ser a raiz atual
    if (temp->Dir != NULL) {
        temp->Dir->Pai = *Raiz;
    }

    // Atualiza o pai de temp para ser o pai da raiz atual
    temp->Pai = (*Raiz)->Pai;

    // Se a raiz atual não tiver pai (ou seja, é a raiz da árvore), temp se torna a nova raiz
    if ((*Raiz)->Pai == NULL) {
        *Raiz = temp;
    }
    // Caso contrário, verifica se a raiz atual é o filho esquerdo ou direito de seu pai
    else if ((*Raiz) == (*Raiz)->Pai->Esq) {
        // Se for o filho esquerdo, atualiza o ponteiro esquerdo do pai para apontar para temp
        (*Raiz)->Pai->Esq = temp;
    } else {
        // Se for o filho direito, atualiza o ponteiro direito do pai para apontar para temp
        (*Raiz)->Pai->Dir = temp;
    }

    // Faz com que a raiz atual se torne o filho direito de temp
    temp->Dir = *Raiz;

    // Atualiza o pai da raiz atual para ser temp
    (*Raiz)->Pai = temp;
}

void cadastrarCidade(Estado** listaEstados, char* nomeEstado, char* nomeCity, int tamPopu) {
    // Busca o estado na lista de estados
    Estado* estadoAtual = buscaEstado(*listaEstados, nomeEstado);

    // Se o estado não for encontrado, exibe uma mensagem de erro
    if (estadoAtual == NULL) {
        printf("Erro: Estado \"%s\" nao encontrado!\n", nomeEstado);
        return;
    }

    // Insere a cidade no estado encontrado
    if (insereCidade(&(estadoAtual->arv_city), NULL, nomeCity, tamPopu)) {
        printf("Cidade \"%s\" cadastrada com sucesso no estado \"%s\"!\n", nomeCity, nomeEstado);
    } else {
        printf("Erro: Cidade \"%s\" ja existe no estado \"%s\"!\n", nomeCity, nomeEstado);
    }
}

void imprimirCidades(Cidade* raiz) {
    if (raiz != NULL) {
        imprimirCidades(raiz->Esq);
        printf("Cidade: %s, População: %d\n", raiz->nomeCity, raiz->tamPopu);
        imprimirCidades(raiz->Dir);
    }
}

Cidade* buscarCidade(Cidade* raiz, char* nomeCity) {
    if (raiz == NULL) {
        return 0; // Cidade não encontrada
    }

    if (strcmp(raiz->nomeCity, nomeCity) == 0) {
        return raiz; // Cidade encontrada
    }else if (strcmp(nomeCity, raiz->nomeCity) < 0) {
        return buscarCidade(raiz->Esq, nomeCity);
    } else {
        return buscarCidade(raiz->Dir, nomeCity);
    }
}