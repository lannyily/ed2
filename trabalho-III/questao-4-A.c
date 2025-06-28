#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 121
#define FUNCIONARIOS 10000

typedef struct Funcionario{
    char matricula[7];
    char nome[50];
    char funcao[50];
    float salario;
}Funcionario;

typedef struct TabelaHash{
    Funcionario *tabela[TAM];
    int colisoes;
}TabelaHash;


int tabelaHash(char* matricula){
    char rotacionar[7];

    for(int i = 0; i < 4; i++){
        rotacionar[i] = matricula[i + 2];
    }

    rotacionar[4] = matricula[0];
    rotacionar[5] = matricula[1];
    rotacionar[6] = '\0';

    char extrair[4];
    extrair[0] = rotacionar[1];
    extrair[1] = rotacionar[3];
    extrair[2] = rotacionar[4];
    extrair[3] = '\0';

    int valor = atoi(extrair);
    int resultado = valor % TAM;
    
    return resultado;
}

void cadastrarFuncionario(TabelaHash* hash, char* matricula, char* nome, char* funcao, float salario){
    int indice = tabelaHash(matricula);

    int tentativa = 0;
    int primeiroDigito = matricula[0] - '0';

    while(hash->tabela[indice] != NULL){
        hash->colisoes++;
        tentativa++;
        indice = (indice + primeiroDigito) % TAM;
    }

    Funcionario* novo = (Funcionario*)malloc(sizeof(Funcionario));
    strcpy(novo->matricula, matricula);
    strcpy(novo->nome, nome);
    strcpy(novo->funcao, funcao);
    novo->salario = salario;

    hash->tabela[indice] = novo;
}


void mostrarTodos(TabelaHash* hash){
    for(int i = 0; i < TAM; i++){
        if (hash->tabela[i] != NULL){
            printf("Indice %d: %s | %s | %s | R$%.2f\n", i, hash->tabela[i]->matricula, hash->tabela[i]->nome, hash->tabela[i]->funcao, hash->tabela[i]->salario);
        }
    }
}


Funcionario* buscarFuncionario(TabelaHash* hash, char* matricula){
    int indice = tabelaHash(matricula);
    int primeiro_digito = matricula[0] - '0';
    int tentativas = 0;
    Funcionario* encontrou = NULL;

    while(hash->tabela[indice] != NULL && tentativas < TAM) {
        if(strcmp(hash->tabela[indice]->matricula, matricula) == 0){
            encontrou = hash->tabela[indice];
        }
            
        indice = (indice + primeiro_digito) % TAM;
        tentativas++;
    }
    return encontrou;
}

int main(){
    TabelaHash* hash = (TabelaHash*)malloc(sizeof(TabelaHash));
    hash->colisoes = 0;

    for(int i = 0; i < TAM; i++){
        hash->tabela[i] = NULL;
    }

    int opcao;

    do{
        printf("-------------------- MENU --------------------\n");
        printf(" 1 - Carregar Funcionarios\n");
        printf(" 2 - Buscar Funcionario\n");
        printf(" 3 - Mostrar todos os funcionarios\n");
        printf(" 0 - SAIR\n");
        printf("----------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao){
            case 1:{ 
                if(FUNCIONARIOS == 0){
                    printf("Atingido o limite de cadastramento de funcionarios\n");
                }
                else{
                    /*
                    char matricula[7];
                    char nome[50];
                    char funcao[50];
                    float salario;

                    do {
                        printf("Informe a matricula do funcionario (6 digitos): ");
                        scanf("%6s", matricula); 
                    } while (strlen(matricula) != 6); 

                    printf("Nome do funcionario: ");
                    scanf(" %[^\n]", nome);  // permite espaços

                    printf("Funcao: ");
                    scanf(" %[^\n]", funcao);

                    printf("Salario: ");
                    scanf("%f", &salario);

                    cadastrarFuncionario(hash, matricula, nome, funcao, salario);

                    printf("Funcionario cadastrado com sucesso!\n");

                    printf("colisoes totais: %d\n", hash->colisoes);
                    */

                    cadastrarFuncionario(hash, "332423", "Fulani", "Dev", 1.5454);
                    cadastrarFuncionario(hash, "812394", "Maria", "Analista", 3000.00);
                    cadastrarFuncionario(hash, "470183", "Joao", "Gerente", 4500.50);
                    cadastrarFuncionario(hash, "193857", "Ana", "Designer", 2750.75);
                    cadastrarFuncionario(hash, "604219", "Carlos", "Tester", 3100.00);
                    cadastrarFuncionario(hash, "708134", "Lucas", "Dev", 3200.00);
                    cadastrarFuncionario(hash, "519382", "Larissa", "DevOps", 4000.00);
                    cadastrarFuncionario(hash, "237489", "Juliana", "Scrum Master", 4200.00);
                    cadastrarFuncionario(hash, "849301", "Ricardo", "Dev", 3800.00);
                    cadastrarFuncionario(hash, "984210", "Fernanda", "PO", 4100.00);
                    cadastrarFuncionario(hash, "148273", "Bruno", "Tester", 3050.00);
                    cadastrarFuncionario(hash, "210394", "Paula", "UX", 2900.00);
                    cadastrarFuncionario(hash, "729384", "Thiago", "Dev", 3300.00);
                    cadastrarFuncionario(hash, "839102", "Roberta", "Gerente", 5100.00);
                    cadastrarFuncionario(hash, "672193", "Eduardo", "Analista", 3400.00);
                    cadastrarFuncionario(hash, "490182", "Camila", "Dev", 3250.00);
                    cadastrarFuncionario(hash, "918273", "Sandro", "Tester", 3000.00);
                    cadastrarFuncionario(hash, "203948", "Patricia", "Designer", 2800.00);
                    cadastrarFuncionario(hash, "567839", "Igor", "DevOps", 3900.00);
                    cadastrarFuncionario(hash, "302948", "Bianca", "Dev", 3500.00);
                    cadastrarFuncionario(hash, "402938", "Rodrigo", "Scrum Master", 4400.00);
                    cadastrarFuncionario(hash, "189273", "Tatiane", "PO", 4600.00);
                    cadastrarFuncionario(hash, "902384", "Marcelo", "UX", 3100.00);
                    cadastrarFuncionario(hash, "483920", "Renata", "Dev", 3700.00);
                    cadastrarFuncionario(hash, "209384", "Jorge", "Analista", 3450.00);
                    cadastrarFuncionario(hash, "394857", "Aline", "Designer", 2950.00);
                    cadastrarFuncionario(hash, "583920", "Fabio", "DevOps", 3850.00);
                    cadastrarFuncionario(hash, "120394", "Simone", "Tester", 3150.00);
                    cadastrarFuncionario(hash, "678203", "Andre", "Dev", 3600.00);
                    cadastrarFuncionario(hash, "983472", "Luciana", "Gerente", 5000.00);

                    printf("colisoes totais: %d\n", hash->colisoes);
                }
                break;
            }
            case 2:{ 
                char matricula[7];
                printf("Digite a matricula: ");
                scanf("%s", matricula);

                Funcionario* resultado = buscarFuncionario(hash, matricula);

                if(resultado != NULL){
                    printf("Funcionario encontrado: \n");
                    printf("%s | %s | %s | R$%.2f\n", resultado->matricula, resultado->nome, resultado->funcao, resultado->salario);
                } else {
                    printf("Funcionario nao encontrado!\n");
                }

                break;
            } 
            case 3:{ 
                mostrarTodos(hash);
                break;
            }
            case 0:{ 
                printf("Saindo do programa...\n");
                exit(0);
                break;
            }
            default:
                printf("Opcao invalida, tente novamente!\n");
                break;
            }
    } while (opcao != 0);
    
}