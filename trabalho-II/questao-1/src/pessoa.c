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

int corPessoa(Pessoa *no){
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
void corrigirCoresPessoa(Pessoa *no) {
    if (cor(no->Esq) == RED && cor(no->Dir) == RED) {
        trocarCor(no->Esq);
        trocarCor(no->Dir);
        trocarCor(no);
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
            trocarCor(*Raiz);
        }
    } else {
        // CPF ja existe
        printf("Aviso: CPF %d ja existe. Insercao cancelada.\n", cpf);
    }
    corrigirCoresPessoa(*Raiz);
    // TODO: Implementar função balancear e verificar cor da raiz.

    return inseriu;
}
void rotacaoEsquerdaPessoa(Pessoa **Raiz) {
    // Armazena o nó à direita da raiz atual em uma variável temporária
    Pessoa *temp = (*Raiz)->Dir; 

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

void rotacaoDireitaPessoa(Pessoa **Raiz) {
    // Armazena o nó à esquerda da raiz atual em uma variável temporária
    Pessoa *temp = (*Raiz)->Esq;

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

void cadastrarPessoa(Cep** arvoreCep, Pessoa** arvorePessoa, int cpf, char* nome, int cep_natal, int cep_mora, Data data_nasc) {
    // Verifica se o CEP de natalidade existe
    Cep* cepNatal = buscarCep(*arvoreCep, cep_natal);
    if (cepNatal == NULL) {
        printf("Erro: CEP de natalidade \"%d\" nao encontrado!\n", cep_natal);
        return;
    }

    // Verifica se o CEP de moradia existe
    Cep* cepMora = buscarCep(*arvoreCep, cep_mora);
    if (cepMora == NULL) {
        printf("Erro: CEP de moradia \"%d\" nao encontrado!\n", cep_mora);
        return;
    }

    // Insere a pessoa na árvore de pessoas
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

