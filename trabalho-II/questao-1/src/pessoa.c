#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/cidade.h"
#include "../includes/cores.h"
#include "../includes/pessoas.h"
#include "../includes/cep.h"
#include "../includes/estado.h"

Pessoa* criarNoPessoa(int cpf, char *nome, int cep_natal, int cep_mora, Data data_nascimento) {
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

int corPessoa(Pessoa *no) {
    if (no == NULL) {
        return BLACK; // Nós nulos são considerados pretos
    }
    return no->cor;
}

void trocarCorPessoa(Pessoa *no) {
    if (no != NULL) {
        no->cor = (no->cor == RED) ? BLACK : RED;
    }
}

void rotacaoEsquerdaPessoa(Pessoa **Raiz) {
    Pessoa *temp = (*Raiz)->Dir;
    Pessoa *raiz_atual = *Raiz;
    
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

void rotacaoDireitaPessoa(Pessoa **Raiz) {
    Pessoa *temp = (*Raiz)->Esq;
    Pessoa *raiz_atual = *Raiz;
    
    // Atualiza os ponteiros
    raiz_atual->Esq = temp->Dir;
    if (temp->Dir != NULL) {
        temp->Dir->Pai = raiz_atual;
    }
    
    temp->Pai = raiz_atual->Pai;
    
    if (raiz_atual->Pai == NULL) {
        *Raiz = temp;
    } else if (raiz_atual == raiz_atual->Pai->Esq) {
        raiz_atual->Pai->Esq = temp;
    } else {
        raiz_atual->Pai->Dir = temp;
    }
    
    temp->Dir = raiz_atual;
    raiz_atual->Pai = temp;
}


int inserirPessoa(Pessoa** Raiz, Pessoa* Pai, int cpf, char* nome, int cep_natal, int cep_mora, Data data_nasc) {
    int inseriu = 0;
    
    if (*Raiz == NULL) {
        // Cria novo nó
        *Raiz = criarNoPessoa(cpf, nome, cep_natal, cep_mora, data_nasc);
        (*Raiz)->Pai = Pai;
        inseriu = 1;
    } else if (cpf < (*Raiz)->cpf) {
        // Insere na subárvore esquerda
        inseriu = inserirPessoa(&((*Raiz)->Esq), *Raiz, cpf, nome, cep_natal, cep_mora, data_nasc);
    } else if (cpf > (*Raiz)->cpf) {
        // Insere na subárvore direita
        inseriu = inserirPessoa(&((*Raiz)->Dir), *Raiz, cpf, nome, cep_natal, cep_mora, data_nasc);
    }
    
    // Balanceia a árvore após a inserção
    if (inseriu) {
        balancearPessoa(Raiz);
    }

    return inseriu;
}

void cadastrarPessoa(Estado* listaEstados, Pessoa** arvorePessoa, int cpf, char* nome, int cep_natal, int cep_mora, Data data_nasc) {
    // Verifica se o CEP de natalidade existe em qualquer estado
    Cep* cepNatal = buscarCepEmEstado(listaEstados, cep_natal);
    if (cepNatal == NULL) {
        printf("Erro: CEP de natalidade \"%d\" nao encontrado!\n", cep_natal);
        return;
    }

    // Verifica se o CEP de moradia existe em qualquer estado
    Cep* cepMora = buscarCepEmEstado(listaEstados, cep_mora);
    if (cepMora == NULL) {
        printf("Erro: CEP de moradia \"%d\" nao encontrado!\n", cep_mora);
        return;
    }

    // Se ambos os CEPs foram encontrados, insere a pessoa
    if (inserirPessoa(arvorePessoa, NULL, cpf, nome, cep_natal, cep_mora, data_nasc)) {
        printf("Pessoa \"%s\" cadastrada com sucesso!\n", nome);
    } else {
        printf("Erro: CPF \"%d\" ja existe!\n", cpf);
    }
}

int PessoaAssociada(Pessoa* arvorePessoa, int valorCep) {
    if (arvorePessoa == NULL) {
        return 1; // Não há pessoas associadas ao CEP
    }

    int count = 0;

    // Verifica se a pessoa está associada ao CEP de natalidade ou moradia
    if (arvorePessoa->cep_natal == valorCep || arvorePessoa->cep_mora == valorCep) {
        count++;
    }

    // Soma as associações nas subárvores esquerda e direita
    count += PessoaAssociada(arvorePessoa->Esq, valorCep);
    count += PessoaAssociada(arvorePessoa->Dir, valorCep);

    // Retorna 0 se houver mais de uma pessoa associada, caso contrário retorna 1
    return (count <= 1) ? 1 : 0;
}

void move2EsqRED(Pessoa **raiz) {
    trocarCorPessoa(*raiz);
    trocarCorPessoa((*raiz)->Esq);
    if (corPessoa((*raiz)->Dir->Esq) == RED) {
        rotacaoDireitaPessoa(&((*raiz)->Dir));
        rotacaoEsquerdaPessoa(raiz);
        trocarCorPessoa(*raiz);
    }
}

void move2DirRED(Pessoa **raiz) {
    trocarCorPessoa(*raiz);
    trocarCorPessoa((*raiz)->Dir);
    if (corPessoa((*raiz)->Esq->Esq) == RED) {
        rotacaoDireitaPessoa(raiz);
        trocarCorPessoa(*raiz);
    }
}

int removerPessoa(Pessoa** arvorePessoa, int cpf) {
    int removeu = 0;
    
    if (*arvorePessoa == NULL) {
        printf("Erro: Pessoa com CPF \"%d\" nao encontrada!\n", cpf);
    } else {
        *arvorePessoa = removerNoPessoa(*arvorePessoa, cpf);

        // Garante que a raiz final seja preta, se a árvore não estiver vazia
        if (*arvorePessoa != NULL) {
            (*arvorePessoa)->cor = BLACK;
            removeu = 1;
            printf("Pessoa com CPF \"%d\" removida com sucesso!\n", cpf);
        }
    }
    return removeu;
}

// Função de balanceamento para árvore LLRB
void balancearPessoa(Pessoa **raiz) {
    if (corPessoa((*raiz)->Dir) == RED) {
        rotacaoEsquerdaPessoa(raiz);
    }
    if (corPessoa((*raiz)->Esq) == RED && corPessoa((*raiz)->Esq->Esq) == RED) {
        rotacaoDireitaPessoa(raiz);
    }
    if (corPessoa((*raiz)->Esq) == RED && corPessoa((*raiz)->Dir) == RED) {
        trocarCorPessoa(*raiz);
    }
}

// Função auxiliar recursiva para remover um nó na árvore LLRB
Pessoa* removerNoPessoa(Pessoa *raiz, int valor) {
    if (raiz == NULL) {
        return NULL;
    }

    // Descendo na árvore
    if (valor < raiz->cpf) {
        if (raiz->Esq != NULL && corPessoa(raiz->Esq) == BLACK && 
            raiz->Esq->Esq != NULL && corPessoa(raiz->Esq->Esq) == BLACK) {
            move2EsqRED(&raiz);
        }
        raiz->Esq = removerNoPessoa(raiz->Esq, valor);
    } else {
        if (raiz->Esq != NULL && corPessoa(raiz->Esq) == RED) {
            rotacaoDireitaPessoa(&raiz);
        }
        if (valor == raiz->cpf && raiz->Dir == NULL) {
            free(raiz);
            return NULL;
        }

        if (raiz->Dir != NULL && corPessoa(raiz->Dir) == BLACK && 
            raiz->Dir->Esq != NULL && corPessoa(raiz->Dir->Esq) == BLACK) {
            move2DirRED(&raiz);
        }

        if (valor == raiz->cpf) {
            // Nó a ser removido tem dois filhos ou um filho direito
            Pessoa* sucessor = raiz->Dir; // Encontrar o menor na subárvore direita
            while(sucessor->Esq != NULL) {
                sucessor = sucessor->Esq;
            }
            
            raiz->cpf = sucessor->cpf; // Copia os dados do sucessor
            strcpy(raiz->nome, sucessor->nome); // Copia outros dados conforme necessário
            raiz->cep_natal = sucessor->cep_natal;
            raiz->cep_mora = sucessor->cep_mora;
            raiz->data_nascimento = sucessor->data_nascimento; // Copia dados de data

            raiz->Dir = removerMenorLLRB(raiz->Dir); // Remove o sucessor da subárvore direita
        } else {
            // Continua a busca na subárvore direita
            raiz->Dir = removerNoPessoa(raiz->Dir, valor);
        }
    }

    // Subindo na árvore, balanceando
    balancearPessoa(&raiz);
    return raiz;
}

// Função auxiliar para remover o menor nó ( leftmost ) de uma subárvore
Pessoa* removerMenorLLRB(Pessoa *raiz) {
    if (raiz->Esq == NULL) {
        // Encontrou o menor nó
        // Antes de liberar H, precisamos retornar o nó direito (se existir) para o pai
        Pessoa* dir = raiz->Dir;
        free(raiz);
        return dir; // Retorna o filho direito, que será o novo filho esquerdo do pai
    }

    if (corPessoa(raiz->Esq) == BLACK && corPessoa(raiz->Esq->Esq) == BLACK) {
        move2EsqRED(&raiz);
    }

    raiz->Esq = removerMenorLLRB(raiz->Esq);

    // Balanceia no retorno
    balancearPessoa(&raiz);
    return raiz; // Retorna o nó H após balanceamento
}

void imprimirArvorePessoa(Pessoa* raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }

    imprimirArvorePessoa(raiz->Dir, nivel + 1);

    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }

    printf("%d (%s)\n", raiz->cpf, (raiz->cor == RED) ? "RED" : "BLACK");

    imprimirArvorePessoa(raiz->Esq, nivel + 1);
}

void imprimirPessoas(Pessoa* raiz) {
    if (raiz != NULL) {
        imprimirPessoas(raiz->Esq);
        printf("CPF: %d\n", raiz->cpf);
        printf("Nome: %s\n", raiz->nome);
        printf("CEP Natal: %d\n", raiz->cep_natal);
        printf("CEP Mora: %d\n", raiz->cep_mora);
        printf("Data de Nascimento: %d/%d/%d\n", 
               raiz->data_nascimento.dia,
               raiz->data_nascimento.mes,
               raiz->data_nascimento.ano);
        printf("-------------------\n");
        imprimirPessoas(raiz->Dir);
    }
}



