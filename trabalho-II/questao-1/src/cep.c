#include <stdio.h>
#include <stdlib.h>
#include "../includes/cep.h"
#include "../includes/cores.h"
#include "../includes/cidade.h"
#include "../includes/estado.h"
#include "../includes/pessoas.h"

Cep* buscarCep(Cep* raiz, int valor) {
    Cep* resultado = raiz;
    if (raiz != NULL && raiz->cep != valor) {
        resultado = (valor < raiz->cep) ? buscarCep(raiz->Esq, valor) : buscarCep(raiz->Dir, valor);
    }
    return resultado;
}

// Função auxiliar recursiva para buscar CEP em uma cidade
Cep* buscarCepEmCidade(Cidade* cidade, int valorCep) {
    if (cidade == NULL) return NULL;
    
    // Busca na cidade atual
    Cep* resultado = buscarCep(cidade->arv_cep, valorCep);
    if (resultado != NULL) return resultado;
    
    // Busca nas subárvores
    resultado = buscarCepEmCidade(cidade->Esq, valorCep);
    if (resultado != NULL) return resultado;
    
    return buscarCepEmCidade(cidade->Dir, valorCep);
}

// Função auxiliar recursiva para buscar CEP em um estado
Cep* buscarCepEmEstado(Estado* estado, int valorCep) {
    if (estado == NULL) return NULL;
    
    // Busca nas cidades do estado atual
    Cep* resultado = buscarCepEmCidade(estado->arv_city, valorCep);
    if (resultado != NULL) return resultado;
    
    // Busca no próximo estado
    return buscarCepEmEstado(estado->Prox, valorCep);
}

Cep* criarNoCep(int cep, Cidade* cidade) {
    Cep* novo = (Cep*)malloc(sizeof(Cep));

    novo->cep = cep;
    novo->cidade = cidade;
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

void rotacaoEsquerdaCep(Cep **Raiz) {
    Cep *temp = (*Raiz)->Dir;
    Cep *raiz_atual = *Raiz;
    
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

void rotacaoDireitaCep(Cep **Raiz) {
    Cep *temp = (*Raiz)->Esq;
    Cep *raiz_atual = *Raiz;
    
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

void balancearCep(Cep **raiz) {
    if (corCep((*raiz)->Dir) == RED) {
        rotacaoEsquerdaCep(raiz);
    }
    if (corCep((*raiz)->Esq) == RED && corCep((*raiz)->Esq->Esq) == RED) {
        rotacaoDireitaCep(raiz);
    }
    if (corCep((*raiz)->Esq) == RED && corCep((*raiz)->Dir) == RED) {
        trocarCorCep(*raiz);
    }
    
    // Garante que a raiz seja sempre preta
    if ((*raiz)->Pai == NULL) {
        (*raiz)->cor = BLACK;
    }
}

int inserirCep(Cep** Raiz, Cep* Pai, int valor, Cidade* cidade) {
    int inseriu = 0;
    Cep* novo = NULL;
    if (*Raiz == NULL) {
        novo = criarNoCep(valor, cidade);
        novo->Pai = Pai;
        *Raiz = novo;
        if (Pai == NULL) {
            novo->cor = BLACK;  // Raiz sempre é preta
        }
        printf("Inserindo CEP: %d\n", valor);
        inseriu = 1;
    } else {
        printf("Comparando inserção: %d com %d\n", valor, (*Raiz)->cep);
        if (valor < (*Raiz)->cep) {
            printf("Inserindo %d na subárvore esquerda de %d\n", valor, (*Raiz)->cep);
            inseriu = inserirCep(&((*Raiz)->Esq), *Raiz, valor, cidade);
            if (inseriu) {
                printf("Balanceando após inserir %d na esquerda\n", valor);
                if (corCep((*Raiz)->Esq) == RED && corCep((*Raiz)->Esq->Esq) == RED) {
                    printf("Rotação à direita em %d\n", (*Raiz)->cep);
                    rotacaoDireitaCep(Raiz);
                    trocarCorCep(*Raiz);
                }
                if (corCep((*Raiz)->Esq) == RED && corCep((*Raiz)->Dir) == RED) {
                    printf("Flip de cores em %d\n", (*Raiz)->cep);
                    trocarCorCep(*Raiz);
                }
            }
        } else if (valor > (*Raiz)->cep) {
            printf("Inserindo %d na subárvore direita de %d\n", valor, (*Raiz)->cep);
            inseriu = inserirCep(&((*Raiz)->Dir), *Raiz, valor, cidade);
            if (inseriu) {
                printf("Balanceando após inserir %d na direita\n", valor);
                if (corCep((*Raiz)->Dir) == RED && corCep((*Raiz)->Dir->Dir) == RED) {
                    printf("Rotação à esquerda em %d\n", (*Raiz)->cep);
                    rotacaoEsquerdaCep(Raiz);
                    trocarCorCep(*Raiz);
                }
                if (corCep((*Raiz)->Esq) == RED && corCep((*Raiz)->Dir) == RED) {
                    printf("Flip de cores em %d\n", (*Raiz)->cep);
                    trocarCorCep(*Raiz);
                }
            }
        } else {
            printf("CEP %d já existe!\n", valor);
        }
        
        // Garante que a raiz seja sempre preta
        if ((*Raiz)->Pai == NULL) {
            (*Raiz)->cor = BLACK;
        }
    }
    return inseriu;
}

void cadastrarCep(Estado** listaEstados, char* nomeEstado, char* nomeCity, int valorCep) { 
    printf("Tentando cadastrar CEP %d na cidade %s do estado %s\n", valorCep, nomeCity, nomeEstado);
    
    // Busca o estado na lista de estados
    Estado* estadoAtual = buscaEstado(*listaEstados, nomeEstado);

    // Verifica se o estado existe
    if (estadoAtual == NULL) {
        printf("Erro: Estado \"%s\" nao encontrado!\n", nomeEstado);
        return;
    }

    // Busca a cidade na árvore de cidades do estado
    Cidade* cidadeAtual = buscaCidade(estadoAtual->arv_city, nomeCity);

    // Verifica se a cidade existe
    if (cidadeAtual == NULL) {
        printf("Erro: Cidade \"%s\" nao encontrada no estado \"%s\"!\n", nomeCity, nomeEstado);
    } else { // Insere o CEP na árvore de CEPs da cidade
        printf("Cidade encontrada, tentando inserir CEP %d\n", valorCep);
        if (inserirCep(&cidadeAtual->arv_cep, NULL, valorCep, cidadeAtual)) {
            printf("CEP \"%d\" cadastrado com sucesso na cidade \"%s\"!\n", valorCep, nomeCity);
        } else {
            printf("Erro: CEP \"%d\" ja existe na cidade \"%s\"!\n", valorCep, nomeCity);
        }
    }
}

Cep* removerNoCep(Cep *raiz, int valor) {
    if (raiz == NULL) {
        return NULL;
    }

    // Descendo na árvore
    if (valor < raiz->cep) {
        if (raiz->Esq != NULL && corCep(raiz->Esq) == BLACK && 
            raiz->Esq->Esq != NULL && corCep(raiz->Esq->Esq) == BLACK) {
            move2EsqRED_Cep(&raiz);
        }
        raiz->Esq = removerNoCep(raiz->Esq, valor);
    } else {
        if (raiz->Esq != NULL && corCep(raiz->Esq) == RED) {
            rotacaoDireitaCep(&raiz);
        }
        if (valor == raiz->cep && raiz->Dir == NULL) {
            free(raiz);
            return NULL;
        }

        if (raiz->Dir != NULL && corCep(raiz->Dir) == BLACK && 
            raiz->Dir->Esq != NULL && corCep(raiz->Dir->Esq) == BLACK) {
            move2DirRED_Cep(&raiz);
        }

        if (valor == raiz->cep) {
            // Nó a ser removido tem dois filhos ou um filho direito
            Cep* sucessor = raiz->Dir; // Encontrar o menor na subárvore direita
            while(sucessor->Esq != NULL) {
                sucessor = sucessor->Esq;
            }
            
            raiz->cep = sucessor->cep; // Copia o CEP do sucessor
            raiz->cidade = sucessor->cidade; // Copia a referência para a cidade

            raiz->Dir = removerMenorLLRB_Cep(raiz->Dir); // Remove o sucessor da subárvore direita
        } else {
            // Continua a busca na subárvore direita
            raiz->Dir = removerNoCep(raiz->Dir, valor);
        }
    }

    // Subindo na árvore, balanceando
    balancearCep(&raiz);
    return raiz;
}

Cep* removerMenorLLRB_Cep(Cep *raiz) {
    if (raiz->Esq == NULL) {
        // Encontrou o menor nó
        // Antes de liberar H, precisamos retornar o nó direito (se existir) para o pai
        Cep* dir = raiz->Dir;
        free(raiz);
        return dir; // Retorna o filho direito, que será o novo filho esquerdo do pai
    }

    if (corCep(raiz->Esq) == BLACK && corCep(raiz->Esq->Esq) == BLACK) {
        move2EsqRED_Cep(&raiz);
    }

    raiz->Esq = removerMenorLLRB_Cep(raiz->Esq);

    // Balanceia no retorno
    balancearCep(&raiz);
    return raiz; // Retorna o nó H após balanceamento
}

int removerCepDoEstado(Estado* listaEstados, Pessoa* arvorePessoa, int valorCep, char* nomeEstado, char* nomeCity) {
    // Busca o estado na lista de estados
    Estado* estadoAtual = buscaEstado(listaEstados, nomeEstado);

    if (estadoAtual == NULL) {
        printf("Erro: Estado %s não encontrado!\n", nomeEstado);
        return 0;
    }

    // Busca a cidade na árvore de cidades do estado
    Cidade* cidadeAtual = buscaCidade(estadoAtual->arv_city, nomeCity);

    if (cidadeAtual == NULL) {
        printf("Erro: Cidade %s não encontrada no estado %s!\n", nomeCity, nomeEstado);
        return 0;
    }

    // Busca o CEP na árvore de CEPs da cidade
    Cep* cepAtual = buscarCep(cidadeAtual->arv_cep, valorCep);

    if (cepAtual == NULL) {
        printf("Erro: CEP %d não encontrado na cidade %s!\n", valorCep, nomeCity);
        return 0;
    }

    // Remove o CEP
    return removerCep(&cidadeAtual->arv_cep, arvorePessoa, valorCep);
}

void move2EsqRED_Cep(Cep **H) {
    trocarCorCep(*H);
    if (corCep((*H)->Dir->Esq) == RED) {
        rotacaoDireitaCep(&((*H)->Dir));
        rotacaoEsquerdaCep(H);
        trocarCorCep(*H);
    }
}

void move2DirRED_Cep(Cep **H) {
    trocarCorCep(*H);
    if (corCep((*H)->Esq->Esq) == RED) {
        rotacaoDireitaCep(H);
        trocarCorCep(*H);
    }
}

void imprimirArvoreCep(Cep* raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }

    printf("Imprimindo nó %d no nível %d\n", raiz->cep, nivel);
    
    imprimirArvoreCep(raiz->Dir, nivel + 1);

    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }

    printf("%d (%s)\n", raiz->cep, (raiz->cor == RED) ? "RED" : "BLACK");

    imprimirArvoreCep(raiz->Esq, nivel + 1);
}

int removerCep(Cep** arvoreCep, Pessoa* arvorePessoa, int valorCep) {
    int resultado = 0;
    
    if (PessoaAssociada(arvorePessoa, valorCep)) {
        *arvoreCep = removerNoCep(*arvoreCep, valorCep);
        
        if (*arvoreCep != NULL) {
            (*arvoreCep)->cor = BLACK;
        }
        
        printf("CEP %d removido com sucesso!\n", valorCep);
        resultado = 1;
    } else {
        printf("Erro: Existem pessoas associadas ao CEP %d!\n", valorCep);
    }
    
    return resultado;
}



