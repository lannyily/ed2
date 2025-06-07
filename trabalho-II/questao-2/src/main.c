#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"
#include "../includes/cidade.h"
#include "../includes/cep.h"
#include "../includes/pessoa.h"

int main(){
    Estado* listaEstados = NULL;
    arv23Pessoa* RaizPessoa = NULL;
    arv23cep* RaizCep = NULL;

    int opcao;

    do {
        printf("-------------------- MENU --------------------\n");
        printf(" 1 - Cadastrar Estado\n");
        printf(" 2 - Cadastrar Cidade\n");
        printf(" 3 - Cadastrar CEP\n");
        printf(" 4 - Cadastrar Pessoa\n");
        printf(" 5 - Mostrar Estados\n");
        printf(" 6 - Mostrar Cidades\n");
        printf(" 7 - Mostrar CEPS\n");
        printf(" 8 - Mostrar Pessoas\n");
        printf(" 9 - Remover um CEP\n");
        printf("10 - Remover uma pessoa\n");
        printf("11 - Curiosidades\n");
        printf(" 0 - SAIR\n");
        printf("----------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao) {
            case 1: {
                printf("\n-------------- Cadastrar Estado --------------\n");
                /*
                char estado[50], capital[50];
                printf("Digite o nome do estado: ");
                scanf(" %[^\n]", estado);
                printf("Digite o nome da capital: ");
                scanf(" %[^\n]", capital);

                Estado* buscaEst = NULL;
                buscaEstado(listaEstados, estado, buscaEst);
                if(buscaEst != NULL){
                    inserirEstadosOrdenado(&listaEstados, estado, capital);
                    printf("Estado \"%s\" cadastrado com sucesso!\n", estado);
                } else {
                    printf("Esse estado ja existe!\n");
                }
                */

                inserirEstadosOrdenado(&listaEstados, "SP", "Sao Paulo");
                inserirEstadosOrdenado(&listaEstados, "RJ", "Rio de Janeiro");
                inserirEstadosOrdenado(&listaEstados, "MG", "Belo Horizonte");

                printf("Estados inseridos!\n");
                
                break;
            }
            case 2: {
                printf("\n-------------- Cadastrar Cidade --------------\n");
                /*
                char estado[50], cidade[50];
                int populacao;
                printf("Digite o nome do estado: ");
                scanf(" %[^\n]", estado);
                printf("Digite o nome da cidade: ");
                scanf(" %[^\n]", cidade);
                printf("Digite o tipo do artista (Solo/Banda): ");
                scanf(" %d", &populacao);
                
                Cidade* buscaCity = NULL;
                buscaCidade(listaEstados, estado, buscaCity);
                if (buscaCity != NULL){
                    Cidade* sobeCidade = NULL;
                    cadastrarCidade(listaEstados, estado, cidade, populacao, &sobeCidade);
                    printf("Cidade \"%s\" cadastrada com sucesso!\n", cidade);
                } else {
                    printf("Essa cidade ja existe!\n");
                }
                */
                Cidade* sobeCidade = NULL;

                cadastrarCidade(listaEstados, "SP", "Sao Paulo", 12300000, &sobeCidade); // Capital
                cadastrarCidade(listaEstados, "SP", "Campinas", 1214000, &sobeCidade);
                cadastrarCidade(listaEstados, "SP", "Sao Bernardo do Campo", 844483, &sobeCidade);
                
                cadastrarCidade(listaEstados, "RJ", "Rio de Janeiro", 6748000, &sobeCidade); // Capital
                cadastrarCidade(listaEstados, "RJ", "Sao Goncalo", 1084839, &sobeCidade);
                cadastrarCidade(listaEstados, "RJ", "Duque de Caxias", 924624, &sobeCidade);
                
                cadastrarCidade(listaEstados, "MG", "Belo Horizonte", 2523794, &sobeCidade); // Capital
                cadastrarCidade(listaEstados, "MG", "Uberlandia", 699097, &sobeCidade);
                cadastrarCidade(listaEstados, "MG", "Contagem", 668949, &sobeCidade);

                printf("Cidades cadastradas com sucesso!\n");

                break;
            }
            case 3: {
                printf("\n--------------- Cadastrar CEP ----------------\n");
                /*
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
                buscaC = buscaCep(RaizCep, cep->Cep);
                if(buscaC != NULL){
                    Cep* sobeCep = NULL;
                    cadastrarCep23(listaEstados, RaizCep, estado, cidade, cep, &sobeCep);
                    printf("CEP \"%s\" cadastrado com sucesso!\n", cep);
                } else {
                    printf("Esse CEP ja existe!\n");
                }
                */
                
                Cep* cep;
                cep = malloc(sizeof(Cep));
                strcpy(cep->Cep, "23453-234");  

                Cep* sobeCep = NULL;
                cadastrarCep23(listaEstados, RaizCep, "SP", "Sao Paulo", cep->Cep, &sobeCep);

                printf("CEPs cadastrados com sucesso!\n");

                break;
            }
            case 4: {
                printf("\n-------------- Cadastrar Pessoa --------------\n");
                /*
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

                encontrouCEPn = buscaCep(RaizCep, cepN);
                encontrouCEPm = buscaCep(RaizCep, cepM);

                if(encontrouCEPm != NULL && encontrouCEPn != NULL){
                    if(dataValida(data1)) {
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
                Pessoa* sobePessoa;
                Pessoa* nova = criarNoPessoa("Ana Maria", "34534534", "23453-234", "23453-234", "21/02/2004");
                
                insere23Pessoa(&RaizPessoa, nova, NULL, &sobePessoa);

                break;
            }
            case 5: {
                printf("\n------------------ Estados -------------------\n");

                imprimirEstadosCidadesCeps23(listaEstados);

                break;
            }
            case 6: {
                printf("\n------------------ Cidades -------------------\n");

                imprimirEstadosCidadesCeps23(listaEstados);

                break;
            }
            case 7: {
                printf("\n-------------------- CEPs --------------------\n");

                break;
            }
            case 8: {
                printf("\n------------------ Pessoas -------------------\n");
                imprimirPessoas23(RaizPessoa);
                break;
            }
            case 9: {
                printf("\n---------------- Remover CEP -----------------\n");

                break;
            }
            case 10: {
                printf("\n--------------- Remover Pessoa ---------------\n");
                removerPessoa23(&RaizPessoa, NULL, "34534534");

                break;
            }
            case 11: {

                break;
            }
            case 0: {
                printf("Saindo do programa...\n");

                break;
            }
            default:
                printf("Opcao invalida, tente novamente!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}