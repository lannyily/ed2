#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"
#include "../includes/cidade.h"
#include "../includes/cep.h"
#include "../includes/pessoa.h"

int main(){
    Estado* listaEstados = NULL;
    arv23cep* raizCep = NULL;

    inserirEstadosOrdenado(&listaEstados, "SP", "Sao Paulo", 46289333);
    inserirEstadosOrdenado(&listaEstados, "RJ", "Rio de Janeiro", 17463349);
    inserirEstadosOrdenado(&listaEstados, "MG", "Belo Horizonte", 21168791);

    printf("Estados inseridos!\n");

    printf("Iniciar cadastro de Cidade!\n");

    Cidade* sobeCidade = NULL;

    cadastrarCidade(listaEstados, "SP", "Sao Paulo", 12300000, &sobeCidade); // Capital
    cadastrarCidade(listaEstados, "SP", "Campinas", 1214000, &sobeCidade);
    cadastrarCidade(listaEstados, "SP", "Sao Bernardo do Campo", 844483, &sobeCidade);
    cadastrarCidade(listaEstados, "SP", "Santo Andre", 721368, &sobeCidade);
    cadastrarCidade(listaEstados, "SP", "Osasco", 699944, &sobeCidade);
    
    cadastrarCidade(listaEstados, "RJ", "Rio de Janeiro", 6748000, &sobeCidade); // Capital
    cadastrarCidade(listaEstados, "RJ", "Sao Goncalo", 1084839, &sobeCidade);
    cadastrarCidade(listaEstados, "RJ", "Duque de Caxias", 924624, &sobeCidade);
    
    cadastrarCidade(listaEstados, "MG", "Belo Horizonte", 2523794, &sobeCidade); // Capital
    cadastrarCidade(listaEstados, "MG", "Uberlandia", 699097, &sobeCidade);
    cadastrarCidade(listaEstados, "MG", "Contagem", 668949, &sobeCidade);

    printf("Cidades cadastradas com sucesso!\n");

    Cep* sobeCep = NULL;

    cadastrarCep23(listaEstados, "SP", "Osasco", "23453-234", &sobeCep);


    imprimirEstadosCidadesCeps23(listaEstados);

    return 0;
}