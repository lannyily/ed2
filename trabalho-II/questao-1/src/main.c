#include <stdio.h>
#include <stdlib.h>
#include "../includes/cep.h"
#include "../includes/cores.h"
#include "../includes/cidade.h"
#include "../includes/estado.h"
#include "../includes/pessoas.h"

int main() {
    Estado* listaEstados = NULL;
    Cep* arvoreCep = NULL;
    Pessoa* arvorePessoa = NULL;

    // Cadastro rápido de estados
    Estado* estado1 = criarNoEstado("Estado1", "Capital1", 5, 100000);
    inserirEstado(&listaEstados, estado1);

    Estado* estado2 = criarNoEstado("Estado2", "Capital2", 3, 50000);
    inserirEstado(&listaEstados, estado2);

    // Cadastro rápido de cidades
    cadastrarCidade(&listaEstados, "Estado1", "Cidade1", 20000);
    cadastrarCidade(&listaEstados, "Estado1", "Cidade2", 15000);
    cadastrarCidade(&listaEstados, "Estado2", "Cidade3", 30000);

    // Cadastro rápido de CEPs
    cadastrarCep(&listaEstados, "Estado1", "Cidade1", 12345);
    cadastrarCep(&listaEstados, "Estado1", "Cidade2", 67890);
    cadastrarCep(&listaEstados, "Estado2", "Cidade3", 54321);

    // Cadastro rápido de pessoas
    Data data1 = {1, 1, 2000};
    cadastrarPessoa(&arvoreCep, &arvorePessoa, 111111111, "Pessoa1", 12345, 67890, data1);

    Data data2 = {2, 2, 1995};
    cadastrarPessoa(&arvoreCep, &arvorePessoa, 222222222, "Pessoa2", 54321, 12345, data2);

    return 0;
}
