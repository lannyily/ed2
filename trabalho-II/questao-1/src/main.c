#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"
#include "../includes/cidade.h"

int main() {
    Estado* listaEstados = NULL;
    Cidade* ArvVPCidade = NULL;

    // Inserção de estados
    inserirEstadosOrdenado(&listaEstados, "SP", "Sao Paulo", 46289333);
    inserirEstadosOrdenado(&listaEstados, "RJ", "Rio de Janeiro", 17463349);
    inserirEstadosOrdenado(&listaEstados, "MG", "Belo Horizonte", 21168791);

    printf("Estados inseridos!\n");

    imprimirEstados(listaEstados);

    printf("Iniciar cadastro de Cidade!\n");

    // Cadastro de cidades em SP
    cadastrarCidade(listaEstados, "SP", "Campinas", 1214000);
    cadastrarCidade(listaEstados, "SP", "Sao Paulo", 12300000);
    cadastrarCidade(listaEstados, "SP", "Santos", 433656);
    cadastrarCidade(listaEstados, "SP", "Sorocaba", 695328);

    // Cadastro de cidades em RJ
    cadastrarCidade(listaEstados, "RJ", "Niteroi", 515000);
    cadastrarCidade(listaEstados, "RJ", "Duque de Caxias", 924000);
    cadastrarCidade(listaEstados, "RJ", "Petropolis", 307000);

    // Cadastro de cidades em MG
    cadastrarCidade(listaEstados, "MG", "Contagem", 672000);
    cadastrarCidade(listaEstados, "MG", "Uberlandia", 699000);
    cadastrarCidade(listaEstados, "MG", "Juiz de Fora", 573000);

    printf("Cidades inseridos!\n");

    // Impressão geral
    //printf("\n=== ESTADOS E CIDADES ===\n");
    imprimirEstadosCidades(listaEstados);

    return 0;
}
