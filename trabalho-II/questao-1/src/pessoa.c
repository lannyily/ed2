#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/cidade.h"
#include "../includes/cores.h"
#include "../includes/pessoas.h"
#include "../includes/cep.h"

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
    (*Raiz)->Dir = temp->Esq;
    if (temp->Esq != NULL) {
        temp->Esq->Pai = *Raiz;
    }
    temp->Pai = (*Raiz)->Pai;
    if ((*Raiz)->Pai == NULL) {
        *Raiz = temp;
    } else if ((*Raiz) == (*Raiz)->Pai->Esq) {
        (*Raiz)->Pai->Esq = temp;
    } else {
        (*Raiz)->Pai->Dir = temp;
    }
    temp->Esq = *Raiz;
    (*Raiz)->Pai = temp;
}

void rotacaoDireitaPessoa(Pessoa **Raiz) {
    Pessoa *temp = (*Raiz)->Esq;
    (*Raiz)->Esq = temp->Dir;
    if (temp->Dir != NULL) {
        temp->Dir->Pai = *Raiz;
    }
    temp->Pai = (*Raiz)->Pai;
    if ((*Raiz)->Pai == NULL) {
        *Raiz = temp;
    } else if ((*Raiz) == (*Raiz)->Pai->Esq) {
        (*Raiz)->Pai->Esq = temp;
    } else {
        (*Raiz)->Pai->Dir = temp;
    }
    temp->Dir = *Raiz;
    (*Raiz)->Pai = temp;
}

void balancearPessoa(Pessoa** raiz, Pessoa* no) {
    if (no->Pai == NULL) {
        no->cor = BLACK; // Garante que a raiz seja preta
    }

    if (no == no->Pai->Esq) {
        Pessoa* irmao = no->Pai->Dir;

        // Caso 1: O irmão é vermelho
        if (irmao != NULL && irmao->cor == RED) {
            irmao->cor = BLACK;
            no->Pai->cor = RED;
            rotacaoEsquerdaPessoa(&(no->Pai));
            balancearPessoa(raiz, no);
        } else if (corPessoa(irmao->Esq) == BLACK && corPessoa(irmao->Dir) == BLACK) {
            // Caso 2: Os filhos do irmão são pretos
            if (irmao != NULL) {
                irmao->cor = RED;
            }
            balancearPessoa(raiz, no->Pai);
        } else if (corPessoa(irmao->Dir) == BLACK) {
            // Caso 3: O filho direito do irmão é preto
            if (irmao->Esq != NULL) {
                irmao->Esq->cor = BLACK;
            }
            if (irmao != NULL) {
                irmao->cor = RED;
            }
            rotacaoDireitaPessoa(&irmao);
            balancearPessoa(raiz, no);
        } else {
            // Caso 4: O filho direito do irmão é vermelho
            if (irmao != NULL) {
                irmao->cor = no->Pai->cor;
            }
            no->Pai->cor = BLACK;
            if (irmao->Dir != NULL) {
                irmao->Dir->cor = BLACK;
            }
            rotacaoEsquerdaPessoa(&(no->Pai));
            balancearPessoa(raiz, *raiz);
        }
    } else {
        // Simétrico para o caso em que `no` é filho direito
        Pessoa* irmao = no->Pai->Esq;

        // Caso 1: O irmão é vermelho
        if (irmao != NULL && irmao->cor == RED) {
            irmao->cor = BLACK;
            no->Pai->cor = RED;
            rotacaoDireitaPessoa(&(no->Pai));
            balancearPessoa(raiz, no);
        } else if (corPessoa(irmao->Dir) == BLACK && corPessoa(irmao->Esq) == BLACK) {
            // Caso 2: Os filhos do irmão são pretos
            if (irmao != NULL) {
                irmao->cor = RED;
            }
            balancearPessoa(raiz, no->Pai);
        } else if (corPessoa(irmao->Esq) == BLACK) {
            // Caso 3: O filho esquerdo do irmão é preto
            if (irmao->Dir != NULL) {
                irmao->Dir->cor = BLACK;
            }
            if (irmao != NULL) {
                irmao->cor = RED;
            }
            rotacaoEsquerdaPessoa(&irmao);
            balancearPessoa(raiz, no);
        } else {
            // Caso 4: O filho esquerdo do irmão é vermelho
            if (irmao != NULL) {
                irmao->cor = no->Pai->cor;
            }
            no->Pai->cor = BLACK;
            if (irmao->Esq != NULL) {
                irmao->Esq->cor = BLACK;
            }
            rotacaoDireitaPessoa(&(no->Pai));
            balancearPessoa(raiz, *raiz);
        }
    }
}

int inserirPessoa(Pessoa** Raiz, Pessoa* Pai, int cpf, char* nome, int cep_natal, int cep_mora, Data data_nasc) {
    int inseriu = 0;
    Pessoa* novo = NULL;
    if (*Raiz == NULL) {
        novo = criarNoPessoa(cpf, nome, cep_natal, cep_mora, data_nasc);
        novo->Pai = Pai;
        *Raiz = novo;
        if (Pai == NULL) {
            novo->cor = BLACK;
        }
        inseriu = 1;
    } else if (cpf < (*Raiz)->cpf) {
        inseriu = inserirPessoa(&((*Raiz)->Esq), *Raiz, cpf, nome, cep_natal, cep_mora, data_nasc);
        if (inseriu) {
            if (corPessoa((*Raiz)->Esq) == RED && corPessoa((*Raiz)->Esq->Esq) == RED) {
                rotacaoDireitaPessoa(Raiz);
                trocarCorPessoa(*Raiz);
            }
            if (corPessoa((*Raiz)->Esq) == RED && corPessoa((*Raiz)->Dir) == RED) {
                trocarCorPessoa(*Raiz);
            }
        }
    } else if (cpf > (*Raiz)->cpf) {
        inseriu = inserirPessoa(&((*Raiz)->Dir), *Raiz, cpf, nome, cep_natal, cep_mora, data_nasc);
        if (inseriu) {
            if (corPessoa((*Raiz)->Dir) == RED && corPessoa((*Raiz)->Dir->Dir) == RED) {
                rotacaoEsquerdaPessoa(Raiz);
                trocarCorPessoa(*Raiz);
            }
            if (corPessoa((*Raiz)->Esq) == RED && corPessoa((*Raiz)->Dir) == RED) {
                trocarCorPessoa(*Raiz);
            }
        }
    }
    return inseriu;
}

void cadastrarPessoa(Cep** arvoreCep, Pessoa** arvorePessoa, int cpf, char* nome, int cep_natal, int cep_mora, Data data_nasc) {
    int sucesso = 1;
    
    // Verifica se o CEP de natalidade existe
    Cep* cepNatal = buscarCep(*arvoreCep, cep_natal);
    if (cepNatal == NULL) {
        printf("Erro: CEP de natalidade \"%d\" nao encontrado!\n", cep_natal);
        sucesso = 0;
    }

    // Verifica se o CEP de moradia existe
    Cep* cepMora = buscarCep(*arvoreCep, cep_mora);
    if (cepMora == NULL) {
        printf("Erro: CEP de moradia \"%d\" nao encontrado!\n", cep_mora);
        sucesso = 0;
    }

    // Insere a pessoa na árvore de pessoas
    if (sucesso) {
        if (inserirPessoa(arvorePessoa, NULL, cpf, nome, cep_natal, cep_mora, data_nasc)) {
            printf("Pessoa \"%s\" cadastrada com sucesso!\n", nome);
        } else {
            printf("Erro: CPF \"%d\" ja existe!\n", cpf);
        }
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

int removerPessoa(Pessoa** arvorePessoa, int cpf) {
    int inseriu = 0;
    
    if (*arvorePessoa == NULL) {
        printf("Erro: Pessoa com CPF \"%d\" não encontrada!\n", cpf);
    } else{

        Pessoa* noAtual = *arvorePessoa;
    
        // Busca o nó com o CPF correspondente
        if (cpf < noAtual->cpf) {
            return removerPessoa(&(noAtual->Esq), cpf);
        } else if (cpf > noAtual->cpf) {
            return removerPessoa(&(noAtual->Dir), cpf);
        } else {
            // Pessoa encontrada
            Pessoa* temp;
    
            // Caso 1: Nó sem filhos
            if (noAtual->Esq == NULL && noAtual->Dir == NULL) {
                temp = noAtual;
                if (noAtual->Pai == NULL) {
                    *arvorePessoa = NULL; // Nó é a raiz
                } else if (noAtual->Pai->Esq == noAtual) {
                    noAtual->Pai->Esq = NULL; // Nó é filho esquerdo
                } else {
                    noAtual->Pai->Dir = NULL; // Nó é filho direito
                }
            }
            // Caso 2: Nó com apenas um filho
            else if (noAtual->Esq == NULL || noAtual->Dir == NULL) {
                Pessoa* filho = (noAtual->Esq != NULL) ? noAtual->Esq : noAtual->Dir;
                temp = noAtual;
    
                if (noAtual->Pai == NULL) {
                    *arvorePessoa = filho; // Nó é a raiz
                } else if (noAtual->Pai->Esq == noAtual) {
                    noAtual->Pai->Esq = filho; // Nó é filho esquerdo
                } else {
                    noAtual->Pai->Dir = filho; // Nó é filho direito
                }
                filho->Pai = noAtual->Pai;
            }
            // Caso 3: Nó com dois filhos
            else {
                Pessoa* sucessor = noAtual->Dir;
                while (sucessor->Esq != NULL) {
                    sucessor = sucessor->Esq;
                }
    
                // Substitui os dados do nó atual pelo sucessor
                noAtual->cpf = sucessor->cpf;
                strcpy(noAtual->nome, sucessor->nome);
                noAtual->cep_natal = sucessor->cep_natal;
                noAtual->cep_mora = sucessor->cep_mora;
                noAtual->data_nascimento = sucessor->data_nascimento;
    
                // Remove o sucessor
                return removerPessoa(&(noAtual->Dir), sucessor->cpf);
            }
    
            free(temp); // Libera a memória do nó removido
            printf("Pessoa com CPF \"%d\" removida com sucesso!\n", cpf);
    
            // Balanceia a árvore após a remoção
            balancearPessoa(arvorePessoa, noAtual->Pai);
    
            inseriu = 1; // Remoção bem-sucedida
        }
    }
    return inseriu; 
}



