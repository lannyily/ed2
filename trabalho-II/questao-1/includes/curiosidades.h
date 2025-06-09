#ifndef CURIOSIDADES_H
#define CURIOSIDADES_H

#include "estado.h"
#include "cidade.h"
#include "cep.h"
#include "pessoa.h"

Estado* estadoMaisPopuloso(Estado* listaEstados);
int populacaoCapital(Estado* listaEstados, char* nomeEstado);
void buscarCidadeMaisPopulosaSemCapital(Cidade* raiz, Cidade** maisPopulosa, Estado* estadoAtual, Estado** estadoDaCidade);
void cidadeMaisPopulosaSemCapitalTodosEstados(Estado* listaEstados);
int contarPessoasForaCidadeNatal(Pessoa* raiz);
Cidade* buscarCidadePorCepNaArvore(Cidade* raiz, char* cep);
Cidade* buscarCidadePorCep(Estado* listaEstados, char* cep);
int pessoasForaCidadeNatal(Pessoa* raiz, char* cepCidadeNatal);
int contarPessoasNaoNascidasNaCidade(Pessoa* raiz, char* cepCidade);

#endif 