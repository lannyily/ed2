#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"
#include "../includes/cidade.h"
#include "../includes/cep.h"
#include "../includes/pessoa.h"
#include "../includes/curiosidades.h"

Estado* listaEstados = NULL;
Pessoa* arvPessoas = NULL;

void menuCuriosidades(){
    int opcao;

    do {
        printf("-------------------- MENU --------------------\n");
        printf(" 1 - Estado mais populoso\n");
        printf(" 2 - Populacao da Capital de um estado\n");
        printf(" 3 - Cidade mais populosa de um estado sem ser a Capital\n");
        printf(" 4 - Quantas pessoas nao moram na cidade natal\n");
        printf(" 5 - Qual cidade natal de uma pessoa dado o CEP da cidade\n");
        printf(" 6 - Quantas pessoas nascidas em uma determinada cidade nao mora na cidade natal\n");
        printf(" 7 - Quantas pessoas que moram em uma determinada cidade nao nasceram na cidade\n");
        printf(" 0 - Voltar para o menu principal\n");
        printf("----------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao) {
            case 1: {
                Estado* estado;
                estado = estadoMaisPopuloso(listaEstados);
                printf("O Estado mais populoso eh: %s\n", estado->nomeEst);
                break;
            }
            case 2: {
                char estado[50];
                printf("Digite o nome do estado: ");
                scanf(" %[^\n]", estado);

                int populacao;
                populacao = populacaoCapital(listaEstados, estado);
                if (populacao != 0){
                    printf("Populacao da capital do estado \"%s\": %d\n", estado, populacao);
                }
                break;
            }
            case 3:
                cidadeMaisPopulosaSemCapitalTodosEstados(listaEstados);
                break;
            case 4: {
                int total = contarPessoasForaCidadeNatal(arvPessoas);
                printf("Total de pessoas que nao moram na cidade natal: %d\n", total);

                break;
            }
            case 5: { 
                char cepInformado[50];
                printf("Digite o CEP da cidade natal: ");
                scanf(" %[^\n]", cepInformado);

                Cidade* cidade = NULL;
                cidade = buscarCidadePorCep(listaEstados, cepInformado);
                if (cidade != NULL) {
                    printf("A cidade natal correspondente ao CEP eh %s\n", cidade->nomeCity);
                } else {
                    printf("Cidade correspondente ao CEP nao encontrada\n");
                }
                
                break;
            }
            case 6: { 
                char cepDesejado[20];
                printf("Digite o CEP da cidade natal: ");
                scanf(" %[^\n]", cepDesejado);

                int total = pessoasForaCidadeNatal(arvPessoas, cepDesejado);
                printf("Total de pessoas nascidas em %s que nao moram mais la: %d\n", cepDesejado, total);

                break;
            }
            case 7: { 
                char cepCidade[20];
                printf("Digite o CEP da cidade onde as pessoas moram: ");
                scanf(" %[^\n]", cepCidade);

                int total = contarPessoasNaoNascidasNaCidade(arvPessoas, cepCidade);
                printf("Total de pessoas que moram em %s mas nao nasceram nela: %d\n", cepCidade, total);
                break;
            }
            case 0:
                break;
            default:
                printf("Opcao invalida, tente novamente!\n");
                break;
        }

    } while (opcao != 0);
}

int main() {
    

    int opcao;

    do {
        printf("-------------------- MENU --------------------\n");
        printf(" 1 - Cadastrar Estado\n");
        printf(" 2 - Cadastrar Cidade\n");
        printf(" 3 - Cadastrar CEP\n");
        printf(" 4 - Cadastrar Pessoa\n");
        printf(" 5 - Mostrar Estados, Cidades e CEPs\n");
        printf(" 6 - Mostrar Pessoas\n");
        printf(" 7 - Remover um CEP\n");
        printf(" 8 - Remover uma pessoa\n");
        printf(" 9 - Curiosidades\n");
        printf(" 0 - SAIR\n");
        printf("----------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao) {
            case 1: {
                printf("\n-------------- Cadastrar Estado --------------\n");
                
                char estado[50], capital[50];
                printf("Digite o nome do estado: ");
                scanf(" %[^\n]", estado);
                printf("Digite o nome da capital: ");
                scanf(" %[^\n]", capital);

                Estado* buscaEst = NULL;
                buscaEstado(listaEstados, estado, &buscaEst);
                if(buscaEst == NULL){
                    inserirEstadosOrdenado(&listaEstados, estado, capital);
                } else {
                    printf("Esse estado ja existe!\n");
                }
                
                /*
                inserirEstadosOrdenado(&listaEstados, "SP", "Sao Paulo");
                inserirEstadosOrdenado(&listaEstados, "RJ", "Rio de Janeiro");
                inserirEstadosOrdenado(&listaEstados, "MG", "Belo Horizonte");
                */
                
                break;
            }
            case 2: {
                printf("\n-------------- Cadastrar Cidade --------------\n");
                
                char estado[50], cidade[50];
                int populacao;
                printf("Digite o nome do estado: ");
                scanf(" %[^\n]", estado);
                printf("Digite o nome da cidade: ");
                scanf(" %[^\n]", cidade);
                printf("Digite o tamanho da populacao: ");
                scanf(" %d", &populacao);
                
                Cidade* buscaCity = NULL;
                buscaCidade(listaEstados->cidades, cidade, &buscaCity);
                if (buscaCity == NULL){
                    cadastrarCidade(listaEstados, estado, cidade, populacao);
                    
                } else {
                    printf("Essa cidade ja existe!\n");
                }
                

                
                /*
                cadastrarCidade(listaEstados, "SP", "Campinas", 1214000);
                cadastrarCidade(listaEstados, "SP", "Sao Paulo", 12300000);
                cadastrarCidade(listaEstados, "SP", "Santos", 433656);
                cadastrarCidade(listaEstados, "SP", "Sorocaba", 695328);

                cadastrarCidade(listaEstados, "RJ", "Niteroi", 515000);
                cadastrarCidade(listaEstados, "RJ", "Duque de Caxias", 924000);
                cadastrarCidade(listaEstados, "RJ", "Petropolis", 307000);

                cadastrarCidade(listaEstados, "MG", "Contagem", 672000);
                cadastrarCidade(listaEstados, "MG", "Uberlandia", 699000);
                cadastrarCidade(listaEstados, "MG", "Juiz de Fora", 573000);
                */
                

                break;
            }
            case 3: {
                printf("\n--------------- Cadastrar CEP ----------------\n");
                
                char estado[50], cidade[50];
                printf("Digite o nome do estado: ");
                scanf(" %[^\n]", estado);
                printf("Digite o nome da cidade: ");
                scanf(" %[^\n]", cidade);

                Cep* cep;
                cep = malloc(sizeof(Cep));

                printf("Digite o CEP: ");
                scanf(" %[^\n]", cep->Cep);

                Cep* buscaC = NULL;
                buscaC = buscarCepEmEstado(listaEstados, cep->Cep);

                if(buscaC == NULL){
                    Cep* sobeCep = NULL;
                    cadastrarCep(listaEstados, estado, cidade, cep->Cep);
                    printf("CEP \"%s\" cadastrado com sucesso!\n", cep);
                } else {
                    printf("Esse CEP ja existe!\n");
                }
                
                /*
                cadastrarCep(listaEstados, "SP", "Sao Paulo", "01000-000");
                cadastrarCep(listaEstados, "SP", "Campinas", "13010-000");
                cadastrarCep(listaEstados, "RJ", "Niteroi", "24020-000");
                cadastrarCep(listaEstados, "SP", "Santos", "11015350");
                */

                break;
            }
            case 4: {
                printf("\n-------------- Cadastrar Pessoa --------------\n");
                
                char nomeP[50], cpf[50], cepN[50], cepM[50], dataN[50];
                printf("Digite o nome: ");
                scanf(" %[^\n]", nomeP);
                printf("Digite o cpf: ");
                scanf(" %[^\n]", cpf);
                printf("Digite o cep de onde nasceu: ");
                scanf(" %[^\n]", cepN);
                printf("Digite o cep de onde mora: ");
                scanf(" %[^\n]", cepM);
                printf("Digite a data de nascimento (ex: 21/02/2004): ");
                scanf(" %[^\n]", dataN);

                Cep* encontrouCEPn = NULL;
                Cep* encontrouCEPm = NULL;

                encontrouCEPn = buscarCepEmEstado(listaEstados, cepN);
                encontrouCEPm = buscarCepEmEstado(listaEstados, cepM);

                if(encontrouCEPm != NULL && encontrouCEPn != NULL){
                    if(dataValida(dataN)) {
                        cadastrarPessoa(listaEstados, &arvPessoas, nomeP, cpf, cepN, cepM, dataN);
                        printf("Pessoa \"%s\" cadastrado com sucesso!\n", nomeP);
                    } else {
                        printf("Data de nascimento invalida!");
                    }
                } else {
                    printf("CEP nao existe!\n");
                }
                
                
                /*
                char* data1 = "21/02/2004";
                if(dataValida(data1)) {
                    cadastrarPessoa(listaEstados, &arvPessoas, "Ana Maria", "23423435", "13010-000", "13010-000", data1);
                } else {
                    printf("Data de nascimento invalida!\n");
                }

                char* data3 = "15/08/1995";
                if(dataValida(data3)) {
                    cadastrarPessoa(listaEstados, &arvPessoas, "Maria Oliveira", "987654321", "01000-000", "13010-000", data3);
                } else {
                    printf("Data de nascimento invalida!\n");
                }

                char* data5 = "29/02/2020"; 
                if(dataValida(data5)) {
                    cadastrarPessoa(listaEstados, &arvPessoas, "Fernanda Lima", "321654987", "24020-000", "01000-000", data5);
                } else {
                    printf("Data de nascimento invalida!\n");
                }
                */
                break;
            }
            case 5: {
                printf("\n---------- Estados, Cidades e CEPs -----------\n");
                imprimirEstadosCidadesCeps(listaEstados);
                break;
            }
            case 6: {
                printf("\n------------------ Pessoas -------------------\n");
                imprimirPessoas(arvPessoas);
                break;
            }
            case 7: {
                printf("\n---------------- Remover CEP -----------------\n");

                char estado[50], cidade[50], cep[50];
                printf("Digite o estado: ");
                scanf(" %[^\n]", estado);
                printf("Digite a cidade: ");
                scanf(" %[^\n]", cidade);
                printf("Digite o CEP a ser removido: ");
                scanf(" %[^\n]", cep);

                Estado* est;
                buscaEstado(listaEstados, estado, &est);
                if(est != NULL){
                    Cidade* city;
                    buscaCidade(est->cidades, cidade, &city);
                    if(city != NULL){
                        Pessoa* result = NULL;
                        result = buscaCepEmPessoa(arvPessoas, cep);
                        if(result == NULL){
                            removerCep(&city->ceps, cep);
                        }
                        
                    } else {
                        printf("Cidade \"%s\" nao existe!\n", cidade);
                    }
                } else {
                    printf("Estado \"%s\" nao existe!\n", estado);
                }

                
                break;
            }
            case 8: {
                printf("\n--------------- Remover Pessoa ---------------\n");
                
                char cpf[50];
                printf("Digite o cpf: ");
                scanf(" %[^\n]", cpf);

                removerPessoa(&arvPessoas, cpf);
                
                //removerPessoa(&arvPessoas, "987654321");

                break;
            }
            case 9: {
                menuCuriosidades();
                break;
            }
            case 0: {
                printf("Saindo do programa...\n");
                liberarEstados(listaEstados);
                liberarPessoas(arvPessoas);
                exit(0);

                break;
            }
            default:
                printf("Opcao invalida, tente novamente!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
