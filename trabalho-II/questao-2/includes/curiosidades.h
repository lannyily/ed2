#ifndef CURIOSIDADES_H
#define CURIOSIDADES_H

#include "estado.h"
#include "cidade.h"
#include "cep.h"
#include "pessoa.h"

Estado* estadoMaisPopuloso(Estado* listaEstados);
int populacaoCapital(Estado* listaEstados, char* nomeEstado);
void buscarCidadeMaisPopulosaSemCapital(arv23cidade* raiz, Cidade** maisPopulosa, Estado* estadoAtual, Estado** estadoDaCidade);
void cidadeMaisPopulosaSemCapitalTodosEstados(Estado* listaEstados);
int contarPessoasForaCidadeNatal(arv23Pessoa* raiz);
int pessoasForaCidadeNatal(arv23Pessoa* raiz, char* cepCidadeNatal);
int contarPessoasNaoNascidasNaCidade(arv23Pessoa* raiz, char* cepCidade);

#endif 