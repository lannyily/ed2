#include <stdio.h>
#include <stdlib.h>
#include "../includes/cep.h"
#include "../includes/cores.h"
#include "../includes/cidade.h"
#include "../includes/estado.h"
#include "../includes/pessoas.h"

int main() {
    Estado* listaEstados = NULL;
    Pessoa* arvorePessoa = NULL;



    // Cadastro rápido de estados
    Estado* estado1 = criarNoEstado("Estado1", "Capital1", 5, 100000);
    inserirEstado(&listaEstados, estado1);

    Estado* estado2 = criarNoEstado("Estado2", "Capital2", 3, 50000);
    inserirEstado(&listaEstados, estado2);

    // Cadastro rápido de cidades
    cadastrarCidade(&listaEstados, "Estado1", "Cidade1", 20000);
    cadastrarCidade(&listaEstados, "Estado1", "Cidade4", 30000);
    cadastrarCidade(&listaEstados, "Estado1", "Cidade5", 30000);
    cadastrarCidade(&listaEstados, "Estado1", "Cidade2", 30000);
    cadastrarCidade(&listaEstados, "Estado2", "Cidade2", 15000);
    cadastrarCidade(&listaEstados, "Estado2", "Cidade3", 30000);

    // Cadastro rápido de CEPs
    cadastrarCep(&listaEstados, "Estado1", "Cidade1", 12345);
    cadastrarCep(&listaEstados, "Estado1", "Cidade4", 67890);
    cadastrarCep(&listaEstados, "Estado1", "Cidade5", 12346);
    cadastrarCep(&listaEstados, "Estado2", "Cidade2", 54321);
    cadastrarCep(&listaEstados, "Estado2", "Cidade3", 54322);



    Data data1 = {1, 1, 2000};
    cadastrarPessoa(listaEstados, &arvorePessoa, 111111111, "Pessoa1", 12345, 67890, data1);

    Data data2 = {2, 2, 1995};
    cadastrarPessoa(listaEstados, &arvorePessoa, 222222222, "Pessoa2", 54321, 12345, data2);

    Data data3 = {3, 3, 1990};
    cadastrarPessoa(listaEstados, &arvorePessoa, 333333333, "Pessoa3", 12346, 67890, data3);


    removerPessoa(&arvorePessoa, 111111111); 

    return 0;
}
