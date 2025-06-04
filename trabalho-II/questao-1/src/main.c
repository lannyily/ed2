#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"
#include "../includes/cidade.h"
#include "../includes/cep.h"
#include "../includes/pessoa.h"

int main() {
    Estado* listaEstados = NULL;
    Pessoa* arvPessoas = NULL;

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

    
    cadastrarCep(listaEstados, "SP", "Sao Paulo", "01000-000");
    cadastrarCep(listaEstados, "SP", "Campinas", "13010-000");
    cadastrarCep(listaEstados, "RJ", "Rio de Janeiro", "20010-000");
    cadastrarCep(listaEstados, "RJ", "Niteroi", "24020-000");
    cadastrarCep(listaEstados, "SP", "Santos", "11015350");

    // Impressão geral
    printf("\n=== ESTADOS E CIDADES ===\n");
    imprimirEstadosCidadesCeps(listaEstados);

    // Cadastro de pessoas com validação de data
    char* data1 = "21/02/2004";
    if(dataValida(data1)) {
        cadastrarPessoa(listaEstados, &arvPessoas, "Ana Maria", "23423435", "13010-000", "13010-000", data1);
    } else {
        printf("Data de nascimento invalida para Ana Maria: %s\n", data1);
    }

    char* data3 = "15/08/1995";
    if(dataValida(data3)) {
        cadastrarPessoa(listaEstados, &arvPessoas, "Maria Oliveira", "987654321", "01000-000", "13010-000", data3);
    } else {
        printf("Data de nascimento invalida para Maria Oliveira: %s\n", data3);
    }

    char* data5 = "29/02/2020"; // Data válida (2020 é bissexto)
    if(dataValida(data5)) {
        cadastrarPessoa(listaEstados, &arvPessoas, "Fernanda Lima", "321654987", "24020-000", "01000-000", data5);
    } else {
        printf("Data de nascimento invalida para Fernanda Lima: %s\n", data5);
    }

    printf("\n=== PESSOAS CADASTRADAS ===\n");
    imprimirPessoas(arvPessoas);

    

    return 0;
}
