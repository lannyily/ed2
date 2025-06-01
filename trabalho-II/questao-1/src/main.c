#include <stdio.h>
#include <stdlib.h>
#include "../includes/cep.h"
#include "../includes/cores.h"
#include "../includes/cidade.h"
#include "../includes/estado.h"
#include "../includes/pessoas.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menuEstados(Estado** listaEstados) {
    char nome[50], capital[50];
    int populacao, numCidades;
    
    printf("\n=== Menu Estados ===\n");
    printf("1. Cadastrar Estado\n");
    printf("2. Listar Estados\n");
    printf("0. Voltar\n");
    printf("Escolha: ");
    
    int opcao;
    scanf("%d", &opcao);
    limparBuffer();
    
    switch(opcao) {
        case 1:
            printf("Nome do Estado: ");
            scanf("%[^\n]s", nome);
            limparBuffer();
            
            printf("Capital: ");
            scanf("%[^\n]s", capital);
            limparBuffer();
            
            printf("Número de Cidades: ");
            scanf("%d", &numCidades);
            
            printf("População: ");
            scanf("%d", &populacao);
            
            Estado* novoEstado = criarNoEstado(nome, capital, numCidades, populacao);
            inserirEstado(listaEstados, novoEstado);
            printf("Estado cadastrado com sucesso!\n");
            break;
            
        case 2:
            printf("\nLista de Estados:\n");
            imprimirEstados(*listaEstados);
            break;
    }
}

void menuCidades(Estado** listaEstados) {
    char nomeEstado[50], nomeCidade[50];
    int populacao;
    
    printf("\n=== Menu Cidades ===\n");
    printf("1. Cadastrar Cidade\n");
    printf("2. Listar Cidades de um Estado\n");
    printf("0. Voltar\n");
    printf("Escolha: ");
    
    int opcao;
    scanf("%d", &opcao);
    limparBuffer();
    
    switch(opcao) {
        case 1:
            printf("Nome do Estado: ");
            scanf("%[^\n]s", nomeEstado);
            limparBuffer();
            
            printf("Nome da Cidade: ");
            scanf("%[^\n]s", nomeCidade);
            limparBuffer();
            
            printf("População: ");
            scanf("%d", &populacao);
            
            cadastrarCidade(listaEstados, nomeEstado, nomeCidade, populacao);
            break;
            
        case 2:
            printf("Nome do Estado: ");
            scanf("%[^\n]s", nomeEstado);
            limparBuffer();
            
            Estado* estado = buscaEstado(*listaEstados, nomeEstado);
            if (estado != NULL) {
                printf("\nCidades do Estado %s:\n", nomeEstado);
                imprimirCidades(estado->arv_city);
            } else {
                printf("Estado não encontrado!\n");
            }
            break;
    }
}

void menuCeps(Estado** listaEstados) {
    char nomeEstado[50], nomeCidade[50];
    int cep;
    Estado* estado;
    Cidade* cidade;
    
    printf("\n=== Menu CEPs ===\n");
    printf("1. Cadastrar CEP\n");
    printf("2. Listar CEPs de uma Cidade\n");
    printf("3. Remover CEP\n");
    printf("0. Voltar\n");
    printf("Escolha: ");
    
    int opcao;
    scanf("%d", &opcao);
    limparBuffer();
    
    switch(opcao) {
        case 1:
            printf("Nome do Estado: ");
            scanf("%[^\n]s", nomeEstado);
            limparBuffer();
            
            printf("Nome da Cidade: ");
            scanf("%[^\n]s", nomeCidade);
            limparBuffer();
            
            printf("CEP: ");
            scanf("%d", &cep);
            
            cadastrarCep(listaEstados, nomeEstado, nomeCidade, cep);
            break;
            
        case 2:
            printf("Nome do Estado: ");
            scanf("%[^\n]s", nomeEstado);
            limparBuffer();
            
            printf("Nome da Cidade: ");
            scanf("%[^\n]s", nomeCidade);
            limparBuffer();
            
            estado = buscaEstado(*listaEstados, nomeEstado);
            if (estado != NULL) {
                cidade = buscaCidade(estado->arv_city, nomeCidade);
                if (cidade != NULL) {
                    printf("\nCEPs da Cidade %s:\n", nomeCidade);
                    imprimirArvoreCep(cidade->arv_cep, 0); // NOTE: Ajustar a função de impressão para imprimir todos e só dizer quem é o pai e a cor.
                } else {
                    printf("Cidade não encontrada!\n");
                }
            } else {
                printf("Estado não encontrado!\n");
            }
            break;
            
        case 3:
            printf("Nome do Estado: ");
            scanf("%[^\n]s", nomeEstado);
            limparBuffer();
            
            printf("Nome da Cidade: ");
            scanf("%[^\n]s", nomeCidade);
            limparBuffer();
            
            printf("CEP: ");
            scanf("%d", &cep);
            
            if (removerCepDoEstado(*listaEstados, NULL, cep, nomeEstado, nomeCidade)) {
                printf("CEP removido com sucesso!\n");
            } else {
                printf("Erro ao remover CEP!\n");
            }
            break;
    }
}

void menuPessoas(Estado** listaEstados, Pessoa** arvorePessoa) {
    char nome[50];
    int cpf, cepNatal, cepMora;
    Data data;
    
    printf("\n=== Menu Pessoas ===\n");
    printf("1. Cadastrar Pessoa\n");
    printf("2. Listar Pessoas\n");
    printf("3. Remover Pessoa\n");
    printf("0. Voltar\n");
    printf("Escolha: ");
    
    int opcao;
    scanf("%d", &opcao);
    limparBuffer();
    
    switch(opcao) {
        case 1:
            printf("CPF: ");
            scanf("%d", &cpf);
            limparBuffer();
            
            printf("Nome: ");
            scanf("%[^\n]s", nome);
            limparBuffer();
            
            printf("CEP Natal: ");
            scanf("%d", &cepNatal);
            
            printf("CEP Mora: ");
            scanf("%d", &cepMora);
            
            printf("Dia de Nascimento: ");
            scanf("%d", &data.dia);
            
            printf("Mês de Nascimento: ");
            scanf("%d", &data.mes);
            
            printf("Ano de Nascimento: ");
            scanf("%d", &data.ano);
            
            cadastrarPessoa(*listaEstados, arvorePessoa, cpf, nome, cepNatal, cepMora, data);
            break;
            
        case 2:
            printf("\nLista de Pessoas:\n");
            imprimirPessoas(*arvorePessoa);
            break;
            
        case 3:
            printf("CPF da pessoa a ser removida: ");
            scanf("%d", &cpf);
            
            if (removerPessoa(arvorePessoa, cpf)) {
                printf("Pessoa removida com sucesso!\n");
            } else {
                printf("Erro ao remover pessoa!\n");
            }
            break;
    }
}

int main() {
    Estado* listaEstados = NULL;
    Pessoa* arvorePessoa = NULL;
    int opcao;
    
    do {
        printf("\n=== Menu Principal ===\n");
        printf("1. Gerenciar Estados\n");
        printf("2. Gerenciar Cidades\n");
        printf("3. Gerenciar CEPs\n");
        printf("4. Gerenciar Pessoas\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                menuEstados(&listaEstados);
                break;
            case 2:
                menuCidades(&listaEstados);
                break;
            case 3:
                menuCeps(&listaEstados);
                break;
            case 4:
                menuPessoas(&listaEstados, &arvorePessoa);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    
    return 0;
}
