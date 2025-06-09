#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"
#include "../includes/cidade.h"
#include "../includes/cep.h"
#include "../includes/pessoa.h"
#include "../includes/curiosidades.h"

Estado* listaEstados = NULL;
arv23Pessoa* RaizPessoa = NULL;
arv23cep* RaizCep = NULL;

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
                int total = contarPessoasForaCidadeNatal(RaizPessoa);
                printf("Total de pessoas que nao moram na cidade natal: %d\n", total);

                break;
            }
            case 5: { 
                
                break;
            }
            case 6: { 
                char cepDesejado[20];
                printf("Digite o CEP da cidade natal: ");
                scanf(" %[^\n]", cepDesejado);

                int total = pessoasForaCidadeNatal(RaizPessoa, cepDesejado);
                printf("Total de pessoas nascidas em %s que nao moram mais la: %d\n", cepDesejado, total);

                break;
            }
            case 7: { 
                char cepCidade[20];
                printf("Digite o CEP da cidade onde as pessoas moram: ");
                scanf(" %[^\n]", cepCidade);

                int total = contarPessoasNaoNascidasNaCidade(RaizPessoa, cepCidade);
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

int main(){
    
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
                    printf("Estado \"%s\" cadastrado com sucesso!\n", estado);
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
                buscaCity = buscaCidade(listaEstados->arvCidades, estado);
                if (buscaCity == NULL){
                    Cidade* sobeCidade = NULL;
                    cadastrarCidade(listaEstados, estado, cidade, populacao, &sobeCidade);
                    printf("Cidade \"%s\" cadastrada com sucesso!\n", cidade);
                } else {
                    printf("Essa cidade ja existe!\n");
                }

                /*
                Cidade* sobeCidade = NULL;

                cadastrarCidade(listaEstados, "SP", "Sao Paulo", 12300000, &sobeCidade); 
                cadastrarCidade(listaEstados, "SP", "Campinas", 1214000, &sobeCidade);
                cadastrarCidade(listaEstados, "SP", "Sao Bernardo do Campo", 844483, &sobeCidade);
                
                cadastrarCidade(listaEstados, "RJ", "Rio de Janeiro", 6748000, &sobeCidade); 
                cadastrarCidade(listaEstados, "RJ", "Sao Goncalo", 1084839, &sobeCidade);
                cadastrarCidade(listaEstados, "RJ", "Duque de Caxias", 924624, &sobeCidade);
                
                cadastrarCidade(listaEstados, "MG", "Belo Horizonte", 2523794, &sobeCidade); 
                cadastrarCidade(listaEstados, "MG", "Uberlandia", 699097, &sobeCidade);
                cadastrarCidade(listaEstados, "MG", "Contagem", 668949, &sobeCidade);
                */
                

                break;
            }
            case 3: {
                printf("\n--------------- Cadastrar CEP ----------------\n");
                
                char estado[50], cidade[50], cepCity[50];
                printf("Digite o nome do estado: ");
                scanf(" %[^\n]", estado);
                printf("Digite o nome da cidade: ");
                scanf(" %[^\n]", cidade);


                printf("Digite o CEP: ");
                scanf(" %[^\n]", cepCity);

                Cep* buscaC = NULL;
                buscaC = buscarCepEmEstado(listaEstados, cepCity);

                if(buscaC == NULL){
                    Cep* sobeCep = NULL;
                    cadastrarCep23(listaEstados, RaizCep, estado, cidade, cepCity, &sobeCep);
                    printf("CEP \"%s\" cadastrado com sucesso!\n", cepCity);
                } else {
                    printf("Esse CEP ja existe!\n");
                }
                
                /*
                Cep* cep;
                cep = malloc(sizeof(Cep));
                strcpy(cep->Cep, "23453-234");  

                Cep* sobeCep = NULL;
                cadastrarCep23(listaEstados, RaizCep, "SP", "Sao Paulo", cep->Cep, &sobeCep);
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
                /*
                Cep* encontrouCEPn = NULL;
                Cep* encontrouCEPm = NULL;

                encontrouCEPn = buscaCep(RaizCep, cepN);
                encontrouCEPm = buscaCep(RaizCep, cepM);

                if(encontrouCEPm != NULL && encontrouCEPn != NULL){
                    if(dataValida(dataN)) {
                        Pessoa* sobePessoa;
                        Pessoa* nova = criarNoPessoa(nomeP, cpf, cepN, cepM, dataN);
                        insere23Pessoa(&RaizPessoa, nova, NULL, &sobePessoa);
                        printf("Pessoa \"%s\" cadastrado com sucesso!\n", nomeP);
                    } else {
                        printf("Data de nascimento invalida!");
                    }
                } else {
                    printf("CEP nao existe!\n");
                }
                */

                if(dataValida(dataN)) {
                    Pessoa* sobePessoa;
                    Pessoa* nova = criarNoPessoa(nomeP, cpf, cepN, cepM, dataN);
                    insere23Pessoa(&RaizPessoa, nova, NULL, &sobePessoa);
                    printf("Pessoa \"%s\" cadastrado com sucesso!\n", nomeP);
                } else {
                    printf("Data de nascimento invalida!");
                }
                
                /*
                Pessoa* sobePessoa;
                Pessoa* nova = criarNoPessoa("Ana Maria", "34534534", "23453-234", "23453-234", "21/02/2004");
                
                insere23Pessoa(&RaizPessoa, nova, NULL, &sobePessoa);
                */
                break;
            }
            case 5: {
                printf("\n---------- Estados, Cidades e CEPs -----------\n");

                imprimirEstadosCidadesCeps23(listaEstados);

                break;
            }
            case 6: {
                printf("\n------------------ Pessoas -------------------\n");
                imprimirPessoas23(RaizPessoa);
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
                    city = buscaCidade(est->arvCidades, cidade);
                    if(city != NULL){
                        Pessoa* result = NULL;
                        result = buscaCepEmPessoa(RaizPessoa, cep);
                        if(result == NULL){
                            removerCep23(&city->arvCeps, NULL, cep);
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

                removerPessoa23(&RaizPessoa, NULL, cpf);

                break;
            }
            case 9: {
                menuCuriosidades();
                break;
            }
            case 0: {
                printf("Saindo do programa...\n");
                liberarEstados(listaEstados);
                
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