#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/cidade.h"
#include "../includes/cores.h"
#include "../includes/cep.h"
#include "../includes/estado.h"

Cidade* buscaCidade(Cidade* raiz, char* nomeCity) {
    if (raiz == NULL) {
        return NULL;
    }
    
    int cmp = strcmp(nomeCity, raiz->nomeCity);
    
    if (cmp == 0) {
        return raiz;
    } else if (cmp < 0) {
        return buscaCidade(raiz->Esq, nomeCity);
    } else {
        return buscaCidade(raiz->Dir, nomeCity);
    }
}

Cidade* criarNoCidade(char* nomeCity, int tamPopu){
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

int corCidade(Cidade *no){
 if (no == NULL) {
        return BLACK; // Nós nulos são considerados pretos
    }
    return no->cor;
}
void trocarCorCidade(Cidade *no) {
    if (no != NULL) {
        no->cor = (no->cor == RED) ? BLACK : RED;
    }
}
void rotacaoEsquerdaCidade(Cidade **Raiz) {
    Cidade *temp = (*Raiz)->Dir;
    Cidade *raiz_atual = *Raiz;
    
    // Atualiza os ponteiros
    raiz_atual->Dir = temp->Esq;
    if (temp->Esq != NULL) {
        temp->Esq->Pai = raiz_atual;
    }
    
    temp->Pai = raiz_atual->Pai;
    
    if (raiz_atual->Pai == NULL) {
        *Raiz = temp;
    } else if (raiz_atual == raiz_atual->Pai->Esq) {
        raiz_atual->Pai->Esq = temp;
    } else {
        raiz_atual->Pai->Dir = temp;
    }
    
    temp->Esq = raiz_atual;
    raiz_atual->Pai = temp;
}

void rotacaoDireitaCidade(Cidade **Raiz) {
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

void move2EsqRED_Cidade(Cidade **H) {
    trocarCorCidade(*H);
    if (corCidade((*H)->Dir->Esq) == RED) {
        rotacaoDireitaCidade(&((*H)->Dir));
        rotacaoEsquerdaCidade(H);
        trocarCorCidade(*H);
    }
}

void move2DirRED_Cidade(Cidade **H) {
    trocarCorCidade(*H);
    if (corCidade((*H)->Esq->Esq) == RED) {
        rotacaoDireitaCidade(H);
        trocarCorCidade(*H);
    }
}

void balancearCidade(Cidade** raiz) {
    if (*raiz == NULL) return;

    // Se o filho direito é vermelho, faz rotação à esquerda
    if (corCidade((*raiz)->Dir) == RED) {
        rotacaoEsquerdaCidade(raiz);
    }

    // Se temos dois nós vermelhos consecutivos à esquerda, faz rotação à direita
    if (corCidade((*raiz)->Esq) == RED && corCidade((*raiz)->Esq->Esq) == RED) {
        rotacaoDireitaCidade(raiz);
    }

    // Se ambos os filhos são vermelhos, faz flip de cores
    if (corCidade((*raiz)->Esq) == RED && corCidade((*raiz)->Dir) == RED) {
        trocarCorCidade(*raiz);
    }
}

int insereCidade(Cidade** Raiz, Cidade* Pai, char* nomeCity, int tamPopu) {
    int inseriu = 0;
    Cidade* nova = NULL;
    
    if (*Raiz == NULL) {
        nova = criarNoCidade(nomeCity, tamPopu);
        nova->Pai = Pai;
        *Raiz = nova;
        if (Pai == NULL) {
            nova->cor = BLACK;
        }
        inseriu = 1;
    } else {
        int cmp = strcmp(nomeCity, (*Raiz)->nomeCity);
        
        if (cmp < 0) {
            inseriu = insereCidade(&((*Raiz)->Esq), *Raiz, nomeCity, tamPopu);
        } else if (cmp > 0) {
            inseriu = insereCidade(&((*Raiz)->Dir), *Raiz, nomeCity, tamPopu);
        }
        
        // Balanceamento após a inserção
        if (inseriu) {
            printf("Balanceando apos inserir %s\n", nomeCity);
            balancearCidade(Raiz);
            
            // Garante que a raiz seja sempre preta
            if ((*Raiz)->Pai == NULL) {
                (*Raiz)->cor = BLACK;
            }
        }
    }
    return inseriu;
}

void cadastrarCidade(Estado** listaEstados, char* nomeEstado, char* nomeCity, int tamPopu) {
    int cadastrou = 0;
    
    if (listaEstados != NULL && *listaEstados != NULL) {
        // Busca o estado na lista de estados
        Estado* estadoAtual = buscaEstado(*listaEstados, nomeEstado);

        // Se o estado for encontrado
        if (estadoAtual != NULL) {
            // Verifica se a cidade já existe
            Cidade* cidadeExistente = buscaCidade(estadoAtual->arv_city, nomeCity);
            
            // Se a cidade não existir, tenta inserir
            if (cidadeExistente == NULL) {
                if (insereCidade(&(estadoAtual->arv_city), NULL, nomeCity, tamPopu)) {
                    printf("Cidade \"%s\" cadastrada com sucesso no estado \"%s\"!\n", nomeCity, nomeEstado);
                    cadastrou = 1;
                } else {
                    printf("Erro ao cadastrar cidade \"%s\" no estado \"%s\"!\n", nomeCity, nomeEstado);
                }
            } else {
                printf("Erro: Cidade \"%s\" ja existe no estado \"%s\"!\n", nomeCity, nomeEstado);
            }
        } else {
            printf("Erro: Estado \"%s\" nao encontrado!\n", nomeEstado);
        }
    } else {
        printf("Erro: Lista de estados vazia!\n");
    }
}

void imprimirCidades(Cidade* raiz) {
    if (raiz != NULL) {
        imprimirCidades(raiz->Esq);
        printf("Cidade: %s, População: %d\n", raiz->nomeCity, raiz->tamPopu);
        imprimirCidades(raiz->Dir);
    }
}

void imprimirArvoreCidade(Cidade* raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }

    imprimirArvoreCidade(raiz->Dir, nivel + 1);

    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }

    printf("%s (%s)\n", raiz->nomeCity, (raiz->cor == RED) ? "RED" : "BLACK");

    imprimirArvoreCidade(raiz->Esq, nivel + 1);
}



