#include <stdio.h>
#include <stdlib.h>
#include "../includes/cep.h"
#include "../includes/cores.h"
#include "../includes/cidade.h"
#include "../includes/estado.h"
#include "../includes/pessoas.h"

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

void balancear(Cep** raiz, Cep* no) {
    if (no->Pai == NULL) {
        no->cor = BLACK; // Garante que a raiz seja preta
    }

    if (no == no->Pai->Esq) {
        Cep* irmao = no->Pai->Dir;

        // Caso 1: O irmão é vermelho
        if (irmao != NULL && irmao->cor == RED) {
            irmao->cor = BLACK;
            no->Pai->cor = RED;
            rotacaoEsquerdaCep(&(no->Pai)); // Rotação para priorizar o lado esquerdo
            balancear(raiz, no);
        } else if (corCep(irmao->Esq) == BLACK && corCep(irmao->Dir) == BLACK) {
            // Caso 2: Os filhos do irmão são pretos
            if (irmao != NULL) {
                irmao->cor = RED;
            }
            balancear(raiz, no->Pai);
        } else if (corCep(irmao->Dir) == BLACK) {
            // Caso 3: O filho direito do irmão é preto
            if (irmao->Esq != NULL) {
                irmao->Esq->cor = BLACK;
            }
            if (irmao != NULL) {
                irmao->cor = RED;
            }
            rotacaoDireitaCep(&irmao); // Rotação para priorizar o lado esquerdo
            balancear(raiz, no);
        } else {
            // Caso 4: O filho direito do irmão é vermelho
            if (irmao != NULL) {
                irmao->cor = no->Pai->cor;
            }
            no->Pai->cor = BLACK;
            if (irmao->Dir != NULL) {
                irmao->Dir->cor = BLACK;
            }
            rotacaoEsquerdaCep(&(no->Pai)); // Rotação para priorizar o lado esquerdo
            balancear(raiz, *raiz);
        }
    } else {
        // Simétrico para o caso em que `no` é filho direito
        Cep* irmao = no->Pai->Esq;

        // Caso 1: O irmão é vermelho
        if (irmao != NULL && irmao->cor == RED) {
            irmao->cor = BLACK;
            no->Pai->cor = RED;
            rotacaoDireitaCep(&(no->Pai)); // Rotação para priorizar o lado esquerdo
            balancear(raiz, no);
        } else if (corCep(irmao->Dir) == BLACK && corCep(irmao->Esq) == BLACK) {
            // Caso 2: Os filhos do irmão são pretos
            if (irmao != NULL) {
                irmao->cor = RED;
            }
            balancear(raiz, no->Pai);
        } else if (corCep(irmao->Esq) == BLACK) {
            // Caso 3: O filho esquerdo do irmão é preto
            if (irmao->Dir != NULL) {
                irmao->Dir->cor = BLACK;
            }
            if (irmao != NULL) {
                irmao->cor = RED;
            }
            rotacaoEsquerdaCep(&irmao); // Rotação para priorizar o lado esquerdo
            balancear(raiz, no);
        } else {
            // Caso 4: O filho esquerdo do irmão é vermelho
            if (irmao != NULL) {
                irmao->cor = no->Pai->cor;
            }
            no->Pai->cor = BLACK;
            if (irmao->Esq != NULL) {
                irmao->Esq->cor = BLACK;
            }
            rotacaoDireitaCep(&(no->Pai)); // Rotação para priorizar o lado esquerdo
            balancear(raiz, *raiz);
        }
    }
}


int insereCep(Cep** Raiz, Cep *Pai, int valorCep) {
  int inseriu = 0;
    Cep* novo = NULL;
 
  if (*Raiz == NULL) {
        novo = criarNoCep(valorCep);
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
    balancear(Raiz, novo);
    return inseriu;
}

void rotacaoEsquerdaCep(Cep **Raiz) {
    // Armazena o nó à direita da raiz atual em uma variável temporária
    Cep *temp = (*Raiz)->Dir; 

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
void rotacaoDireitaCep(Cep** Raiz) {
    // Implementação da rotação à direita
}

void cadastrarCep(Estado** listaEstados, char* nomeEstado, char* nomeCity, int valorCep) {
    // Busca o estado na lista de estados
    Estado* estadoAtual = buscaEstado(*listaEstados, nomeEstado);

    // Verifica se o estado existe
    if (estadoAtual == NULL) {
        printf("Erro: Estado \"%s\" não encontrado!\n", nomeEstado);
        return;
    }

    // Busca a cidade na árvore de cidades do estado
    Cidade* cidadeAtual = buscaCidade(estadoAtual->arv_city, nomeCity);

    // Verifica se a cidade existe
    if (cidadeAtual == NULL) {
        printf("Erro: Cidade \"%s\" não encontrada no estado \"%s\"!\n", nomeCity, nomeEstado);
        return;
    }else { // Insere o CEP na árvore de CEPs da cidade
        if (insereCep(&(cidadeAtual->arv_cep), NULL, valorCep)) {
            printf("CEP \"%d\" cadastrado com sucesso na cidade \"%s\"!\n", valorCep, nomeCity);
        } else {
            printf("Erro: CEP \"%d\" já existe na cidade \"%s\"!\n", valorCep, nomeCity);
        }
    }
}

int removerCep(Cep** arvoreCep, Pessoa* arvorePessoa, int valorCep, char* nomeCity) {
    // Verifica se o CEP existe na árvore de CEPs
    Cep* cepAtual = buscarCep(*arvoreCep, valorCep);
    if (cepAtual == NULL) {
        printf("Erro: CEP \"%d\" não encontrado na cidade \"%s\"!\n", valorCep, nomeCity);
        return 0; // Falha na remoção
    }

    // Verifica se o CEP pode ser removido com base na associação de pessoas
    if (!PessoaAssociada(arvorePessoa, valorCep)) {
        printf("Erro: Não é possível remover o CEP \"%d\" porque existem pessoas associadas a ele na cidade \"%s\"!\n", valorCep, nomeCity);
        return 0; // Falha na remoção
    }

    // Realiza a remoção do nó diretamente
    Cep* temp = cepAtual;

    // Caso 1: Nó sem filhos
    if (cepAtual->Esq == NULL && cepAtual->Dir == NULL) {
        if (cepAtual->Pai == NULL) {
            *arvoreCep = NULL; // Nó é a raiz
        } else if (cepAtual->Pai->Esq == cepAtual) {
            cepAtual->Pai->Esq = NULL; // Nó é filho esquerdo
        } else {
            cepAtual->Pai->Dir = NULL; // Nó é filho direito
        }
    }
    // Caso 2: Nó com apenas um filho
    else if (cepAtual->Esq == NULL || cepAtual->Dir == NULL) {
        Cep* filho = (cepAtual->Esq != NULL) ? cepAtual->Esq : cepAtual->Dir;
        if (cepAtual->Pai == NULL) {
            *arvoreCep = filho; // Nó é a raiz
        } else if (cepAtual->Pai->Esq == cepAtual) {
            cepAtual->Pai->Esq = filho; // Nó é filho esquerdo
        } else {
            cepAtual->Pai->Dir = filho; // Nó é filho direito
        }
        filho->Pai = cepAtual->Pai;
    }
    // Caso 3: Nó com dois filhos
    else {
        Cep* sucessor = cepAtual->Dir;
        while (sucessor->Esq != NULL) {
            sucessor = sucessor->Esq;
        }

        // Substitui o valor do nó atual pelo sucessor
        cepAtual->cep = sucessor->cep;

        // Remove o sucessor
        if (sucessor->Pai->Esq == sucessor) {
            sucessor->Pai->Esq = sucessor->Dir;
        } else {
            sucessor->Pai->Dir = sucessor->Dir;
        }
        if (sucessor->Dir != NULL) {
            sucessor->Dir->Pai = sucessor->Pai;
        }
        temp = sucessor;
    }

    free(temp); 
    printf("CEP \"%d\" removido com sucesso da cidade \"%s\"!\n", valorCep, nomeCity);


   balancear(arvoreCep, cepAtual);

    return 1; // Remoção bem-sucedida
}
