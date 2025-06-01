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

void rotacaoDireitaCep(Cep **Raiz) {
    // Armazena o nó à esquerda da raiz atual em uma variável temporária
    Cep *temp = (*Raiz)->Esq;

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
}

int inserirCep(Cep** Raiz, Cep* Pai, int valor, Cidade* cidade) {
    int inseriu = 0;
    Cep* novo = NULL;
    if (*Raiz == NULL) {
        novo = criarNoCep(valor, cidade);
        novo->Pai = Pai;
        *Raiz = novo;
        if (Pai == NULL) {
            novo->cor = BLACK;
        }
        inseriu = 1;
    } else if (valor < (*Raiz)->cep) {
        inseriu = inserirCep(&((*Raiz)->Esq), *Raiz, valor, cidade);
        if (inseriu) {
            if (corCep((*Raiz)->Esq) == RED && corCep((*Raiz)->Esq->Esq) == RED) {
                rotacaoDireitaCep(Raiz);
                trocarCorCep(*Raiz);
            }
            if (corCep((*Raiz)->Esq) == RED && corCep((*Raiz)->Dir) == RED) {
                trocarCorCep(*Raiz);
            }
        }
    } else if (valor > (*Raiz)->cep) {
        inseriu = inserirCep(&((*Raiz)->Dir), *Raiz, valor, cidade);
        if (inseriu) {
            if (corCep((*Raiz)->Dir) == RED && corCep((*Raiz)->Dir->Dir) == RED) {
                rotacaoEsquerdaCep(Raiz);
                trocarCorCep(*Raiz);
            }
            if (corCep((*Raiz)->Esq) == RED && corCep((*Raiz)->Dir) == RED) {
                trocarCorCep(*Raiz);
            }
        }
    }
    return inseriu;
}

void cadastrarCep(Estado** listaEstados, char* nomeEstado, char* nomeCity, int valorCep) { 
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
    }else { // Insere o CEP na árvore de CEPs da cidade
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

/* int removerCepDoEstado(Estado* listaEstados, Pessoa* arvorePessoa, int valorCep, char* nomeEstado, char* nomeCity) {
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

    // Busca o CEP na árvore de CEPs da cidade usando buscarCepEmCidade
    Cep* cepAtual = buscarCepEmCidade(cidadeAtual, valorCep);

    if (cepAtual == NULL) {
        printf("Erro: CEP %d não encontrado na cidade %s!\n", valorCep, nomeCity);
        return 0;
    }

    // Remove o CEP usando buscarCepEmEstado
    return removerCep(&cidadeAtual->arv_cep, arvorePessoa, valorCep, nomeCity);
} */

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


