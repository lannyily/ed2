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

void balancearCep(Cep** raiz, Cep* no) {
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
            balancearCep(raiz, no);
        } else if (corCep(irmao->Esq) == BLACK && corCep(irmao->Dir) == BLACK) {
            // Caso 2: Os filhos do irmão são pretos
            if (irmao != NULL) {
                irmao->cor = RED;
            }
            balancearCep(raiz, no->Pai);
        } else if (corCep(irmao->Dir) == BLACK) {
            // Caso 3: O filho direito do irmão é preto
            if (irmao->Esq != NULL) {
                irmao->Esq->cor = BLACK;
            }
            if (irmao != NULL) {
                irmao->cor = RED;
            }
            rotacaoDireitaCep(&irmao); // Rotação para priorizar o lado esquerdo
            balancearCep(raiz, no);
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
            balancearCep(raiz, *raiz);
        }
    } else {
        // Simétrico para o caso em que `no` é filho direito
        Cep* irmao = no->Pai->Esq;

        // Caso 1: O irmão é vermelho
        if (irmao != NULL && irmao->cor == RED) {
            irmao->cor = BLACK;
            no->Pai->cor = RED;
            rotacaoDireitaCep(&(no->Pai)); // Rotação para priorizar o lado esquerdo
            balancearCep(raiz, no);
        } else if (corCep(irmao->Dir) == BLACK && corCep(irmao->Esq) == BLACK) {
            // Caso 2: Os filhos do irmão são pretos
            if (irmao != NULL) {
                irmao->cor = RED;
            }
            balancearCep(raiz, no->Pai);
        } else if (corCep(irmao->Esq) == BLACK) {
            // Caso 3: O filho esquerdo do irmão é preto
            if (irmao->Dir != NULL) {
                irmao->Dir->cor = BLACK;
            }
            if (irmao != NULL) {
                irmao->cor = RED;
            }
            rotacaoEsquerdaCep(&irmao); // Rotação para priorizar o lado esquerdo
            balancearCep(raiz, no);
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
            balancearCep(raiz, *raiz);
        }
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

void cadastrarCep(Estado** listaEstados, char* nomeEstado, char* nomeCity, int valorCep) { // TODO: impletementar else.
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
        if (inserirCep(&cidadeAtual->arv_cep, NULL, valorCep, cidadeAtual)) {
            printf("CEP \"%d\" cadastrado com sucesso na cidade \"%s\"!\n", valorCep, nomeCity);
        } else {
            printf("Erro: CEP \"%d\" ja existe na cidade \"%s\"!\n", valorCep, nomeCity);
        }
    }
}

int removerCep(Cep** arvoreCep, Pessoa* arvorePessoa, int valorCep, char* nomeCity) {
    if (*arvoreCep == NULL) {
        printf("Erro: CEP %d não encontrado na cidade %s!\n", valorCep, nomeCity);
        return 0;
    }

    Cep* noAtual = *arvoreCep;

    if (valorCep < noAtual->cep) {
        return removerCep(&(noAtual->Esq), arvorePessoa, valorCep, nomeCity);
    } else if (valorCep > noAtual->cep) {
        return removerCep(&(noAtual->Dir), arvorePessoa, valorCep, nomeCity);
    } else {
        // Verifica se há pessoas associadas ao CEP
        if (!PessoaAssociada(arvorePessoa, valorCep)) {
            printf("Erro: Não é possível remover o CEP %d porque há pessoas associadas a ele!\n", valorCep);
            return 0;
        }

        // Caso 1: Nó sem filhos
        if (noAtual->Esq == NULL && noAtual->Dir == NULL) {
            free(noAtual);
            *arvoreCep = NULL;
        } 
        // Caso 2: Nó com um filho
        else if (noAtual->Esq == NULL || noAtual->Dir == NULL) {
            Cep* filho = (noAtual->Esq != NULL) ? noAtual->Esq : noAtual->Dir;
            filho->Pai = noAtual->Pai;
            free(noAtual);
            *arvoreCep = filho;
        } 
        // Caso 3: Nó com dois filhos
        else {
            Cep* sucessor = noAtual->Dir;
            while (sucessor->Esq != NULL) {
                sucessor = sucessor->Esq;
            }

            noAtual->cep = sucessor->cep;
            noAtual->cidade = sucessor->cidade;
            removerCep(&(noAtual->Dir), arvorePessoa, sucessor->cep, nomeCity);
        }

        // Balanceia a árvore após a remoção
        balancearCep(arvoreCep, noAtual->Pai);

        printf("CEP %d removido com sucesso da cidade %s!\n", valorCep, nomeCity);
        return 1;
    }
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

    // Busca o CEP na árvore de CEPs da cidade usando buscarCepEmCidade
    Cep* cepAtual = buscarCepEmCidade(cidadeAtual, valorCep);

    if (cepAtual == NULL) {
        printf("Erro: CEP %d não encontrado na cidade %s!\n", valorCep, nomeCity);
        return 0;
    }

    // Remove o CEP usando buscarCepEmEstado
    return removerCep(&cidadeAtual->arv_cep, arvorePessoa, valorCep, nomeCity);
}


