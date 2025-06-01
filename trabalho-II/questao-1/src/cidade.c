#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/cidade.h"
#include "../includes/cores.h"
#include "../includes/cep.h"
#include "../includes/estado.h"

Cidade* buscaCidade(Cidade* raiz, char* nomeCity) {
    Cidade* resultado = NULL;
    
    if (raiz != NULL) {
        int cmp = strcmp(nomeCity, raiz->nomeCity);
        if (cmp == 0) {
            resultado = raiz;
        } else if (cmp < 0) {
            resultado = buscaCidade(raiz->Esq, nomeCity);
        } else {
            resultado = buscaCidade(raiz->Dir, nomeCity);
        }
    }
    
    return resultado;
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

void balancearCidade(Cidade** raiz, Cidade* no) {
    if (no->Pai == NULL) {
        no->cor = BLACK; // Garante que a raiz seja preta
    }

    if (no == no->Pai->Esq) {
        Cidade* irmao = no->Pai->Dir;

        // Caso 1: O irmão é vermelho
        if (irmao != NULL && irmao->cor == RED) {
            irmao->cor = BLACK;
            no->Pai->cor = RED;
            rotacaoEsquerdaCidade(&(no->Pai)); // Rotação para priorizar o lado esquerdo
            balancearCidade(raiz, no);
        } else if (corCidade(irmao->Esq) == BLACK && corCidade(irmao->Dir) == BLACK) {
            // Caso 2: Os filhos do irmão são pretos
            if (irmao != NULL) {
                irmao->cor = RED;
            }
            balancearCidade(raiz, no->Pai);
        } else if (corCidade(irmao->Dir) == BLACK) {
            // Caso 3: O filho direito do irmão é preto
            if (irmao->Esq != NULL) {
                irmao->Esq->cor = BLACK;
            }
            if (irmao != NULL) {
                irmao->cor = RED;
            }
            rotacaoDireitaCidade(&irmao); // Rotação para priorizar o lado esquerdo
            balancearCidade(raiz, no);
        } else {
            // Caso 4: O filho direito do irmão é vermelho
            if (irmao != NULL) {
                irmao->cor = no->Pai->cor;
            }
            no->Pai->cor = BLACK;
            if (irmao->Dir != NULL) {
                irmao->Dir->cor = BLACK;
            }
            rotacaoEsquerdaCidade(&(no->Pai)); // Rotação para priorizar o lado esquerdo
            balancearCidade(raiz, *raiz);
        }
    } else {
        // Simétrico para o caso em que `no` é filho direito
        Cidade* irmao = no->Pai->Esq;

        // Caso 1: O irmão é vermelho
        if (irmao != NULL && irmao->cor == RED) {
            irmao->cor = BLACK;
            no->Pai->cor = RED;
            rotacaoDireitaCidade(&(no->Pai)); // Rotação para priorizar o lado esquerdo
            balancearCidade(raiz, no);
        } else if (corCidade(irmao->Dir) == BLACK && corCidade(irmao->Esq) == BLACK) {
            // Caso 2: Os filhos do irmão são pretos
            if (irmao != NULL) {
                irmao->cor = RED;
            }
            balancearCidade(raiz, no->Pai);
        } else if (corCidade(irmao->Esq) == BLACK) {
            // Caso 3: O filho esquerdo do irmão é preto
            if (irmao->Dir != NULL) {
                irmao->Dir->cor = BLACK;
            }
            if (irmao != NULL) {
                irmao->cor = RED;
            }
            rotacaoEsquerdaCidade(&irmao); // Rotação para priorizar o lado esquerdo
            balancearCidade(raiz, no);
        } else {
            // Caso 4: O filho esquerdo do irmão é vermelho
            if (irmao != NULL) {
                irmao->cor = no->Pai->cor;
            }
            no->Pai->cor = BLACK;
            if (irmao->Esq != NULL) {
                irmao->Esq->cor = BLACK;
            }
            rotacaoDireitaCidade(&(no->Pai)); // Rotação para priorizar o lado esquerdo
            balancearCidade(raiz, *raiz);
        }
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
    } else if (strcmp(nomeCity, (*Raiz)->nomeCity) < 0) {
        inseriu = insereCidade(&((*Raiz)->Esq), *Raiz, nomeCity, tamPopu);
        if (inseriu) {
            if (corCidade((*Raiz)->Esq) == RED && corCidade((*Raiz)->Esq->Esq) == RED) {
                rotacaoDireitaCidade(Raiz);
                trocarCorCidade(*Raiz);
            }
            if (corCidade((*Raiz)->Esq) == RED && corCidade((*Raiz)->Dir) == RED) {
                trocarCorCidade(*Raiz);
            }
        }
    } else if (strcmp(nomeCity, (*Raiz)->nomeCity) > 0) {
        inseriu = insereCidade(&((*Raiz)->Dir), *Raiz, nomeCity, tamPopu);
        if (inseriu) {
            if (corCidade((*Raiz)->Dir) == RED && corCidade((*Raiz)->Dir->Dir) == RED) {
                rotacaoEsquerdaCidade(Raiz);
                trocarCorCidade(*Raiz);
            }
            if (corCidade((*Raiz)->Esq) == RED && corCidade((*Raiz)->Dir) == RED) {
                trocarCorCidade(*Raiz);
            }
        }
    }
    return inseriu;
}

void cadastrarCidade(Estado** listaEstados, char* nomeEstado, char* nomeCity, int tamPopu) {
    // Busca o estado na lista de estados
    Estado* estadoAtual = buscaEstado(*listaEstados, nomeEstado);

    // Se o estado não for encontrado, exibe uma mensagem de erro
    if (estadoAtual == NULL) {
        printf("Erro: Estado \"%s\" nao encontrado!\n", nomeEstado);
    }else{
        if (insereCidade(&(estadoAtual->arv_city), NULL, nomeCity, tamPopu)) {
            printf("Cidade \"%s\" cadastrada com sucesso no estado \"%s\"!\n", nomeCity, nomeEstado);
        } else {
            printf("Erro: Cidade \"%s\" ja existe no estado \"%s\"!\n", nomeCity, nomeEstado);
        }
    }
        
} 

void imprimirCidades(Cidade* raiz) {
    if (raiz != NULL) {
        imprimirCidades(raiz->Esq);
        printf("Cidade: %s, População: %d\n", raiz->nomeCity, raiz->tamPopu);
        imprimirCidades(raiz->Dir);
    }
}



