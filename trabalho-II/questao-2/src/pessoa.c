#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"
#include "../includes/cidade.h"
#include "../includes/cep.h"
#include "../includes/pessoa.h"

int dataValida(char* dataN){
    int valida = 1;

    if(strlen(dataN) != 10){
        valida = 0;
    }

    if (dataN[2] != '/' || dataN[5] != '/'){
        valida = 0;
    }

    int dia, mes, ano;

    if (sscanf(dataN, "%2d/%2d/%4d", &dia, &mes, &ano) != 3){
        valida = 0;
    }

    if (dia < 1 || mes < 1 || mes > 12 || ano < 1900 || ano > 2100){
        valida = 0;
    }

    int diasMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)){
        diasMes[1] = 29;
    }

    if (dia > diasMes[mes - 1]){
        valida = 0;
    }

    return valida;
}

Pessoa* criarNoPessoa(char* nome, char* cpf, char* cepCityNatal, char* cepCityMora, char* dataN){
    Pessoa* nova = (Pessoa*)malloc(sizeof(Pessoa));

    strcpy(nova->nome, nome);
    strcpy(nova->cpf, cpf);
    strcpy(nova->cepCityNatal, cepCityNatal);
    strcpy(nova->cepCityMora, cepCityMora);
    strcpy(nova->dataNascimento, dataN);

    nova->Dir = NULL;
    nova->Esq = NULL;

    return nova;
}


arv23Pessoa* criarNo23Pessoa(Pessoa* Info, arv23Pessoa* Esq, arv23Pessoa* Cen){
    arv23Pessoa* nova = (arv23Pessoa*)malloc(sizeof(arv23Pessoa));

    if(nova != NULL){
        nova->Info1 = Info;
        nova->Info2 = NULL;
        nova->Ninfos = 1;
        nova->Esq = Esq;
        nova->Dir = NULL;
        nova->Cent = Cen;
    }
    return nova;
}

void addInfoPessoa(arv23Pessoa* no, Pessoa* Info, arv23Pessoa* subArv){
    if(strcmp(Info->cpf, no->Info1->cpf) > 0){
        no->Info2 = Info;
        no->Dir = subArv;
    }

    else {
        no->Info2 = no->Info1;
        no->Info1 = Info;
        no->Dir = no->Cent;
        no->Cent = subArv;
    }
    no->Ninfos = 2;
}


arv23Pessoa* quebraNoPessoa(arv23Pessoa** no, Pessoa* pessoaInfo, Pessoa** sobe, arv23Pessoa* Dir){
    arv23Pessoa* maior;
    if(strcmp(pessoaInfo->cpf, (*no)->Info2->cpf) > 0){
        *sobe = (*no)->Info2;
        maior = criarNo23Pessoa(pessoaInfo, (*no)->Dir, Dir);
    } else if(strcmp(pessoaInfo->cpf, (*no)->Info1->cpf) > 0){
        *sobe = pessoaInfo;
        maior = criarNo23Pessoa((*no)->Info2, Dir, (*no)->Dir);
    } else {
        *sobe = (*no)->Info1;
        maior = criarNo23Pessoa((*no)->Info2, (*no)->Cent, (*no)->Dir);
        (*no)->Info1 = pessoaInfo;
        (*no)->Cent = Dir;
    }
    (*no)->Info2 = NULL;
    (*no)->Dir = NULL;
    (*no)->Ninfos = 1;

    return maior;
}


arv23Pessoa* insere23Pessoa(arv23Pessoa** Raiz, Pessoa* noPessoa, arv23Pessoa* Pai, Pessoa** sobe){
    arv23Pessoa* maiorNo;
    
    if(*Raiz == NULL){
        
        *Raiz = criarNo23Pessoa(noPessoa, NULL, NULL);
    } else {
        
        if((*Raiz)->Esq == NULL){
            
            if((*Raiz)->Ninfos == 1){
                addInfoPessoa(*Raiz, noPessoa, NULL);
            } else {
                maiorNo = quebraNoPessoa(Raiz, noPessoa, sobe, NULL);

                if(Pai == NULL){
                    *Raiz = criarNo23Pessoa(*sobe, *Raiz, maiorNo);
                    maiorNo = NULL;
                }
            }
        } else {
            
            if(strcmp(noPessoa->cpf, (*Raiz)->Info1->cpf) < 0){
                maiorNo = insere23Pessoa(&((*Raiz)->Esq), noPessoa, *Raiz, sobe);
            } else if ((*Raiz)->Ninfos == 1 || strcmp(noPessoa->cpf, (*Raiz)->Info2->cpf) < 0){
                maiorNo = insere23Pessoa(&((*Raiz)->Cent), noPessoa, *Raiz, sobe);
            } else {
                maiorNo = insere23Pessoa(&((*Raiz)->Dir), noPessoa, *Raiz, sobe);
            }

            if(maiorNo != NULL){
                if((*Raiz)->Ninfos == 1){
                    addInfoPessoa(*Raiz, *sobe, maiorNo);
                    maiorNo = NULL;
                } else {
                    maiorNo = quebraNoPessoa(Raiz, *sobe, sobe, maiorNo);
                    if(Pai == NULL){
                        *Raiz = criarNo23Pessoa(*sobe, *Raiz, maiorNo);
                        maiorNo = NULL;
                    }
                }
            }
        }
    }

    return maiorNo;
}

void imprimirPessoas23(arv23Pessoa *Raiz){

    if (Raiz != NULL) {
        imprimirPessoas23(Raiz->Esq);

        printf("\n%s\n   CPF: %s\n   Data Nascimento: %s\n   CEP Cidade Natal: %s\n   CEP Cidade Atual: %s\n",
            Raiz->Info1->nome, Raiz->Info1->cpf, Raiz->Info1->dataNascimento,
            Raiz->Info1->cepCityNatal, Raiz->Info1->cepCityMora);

        if (Raiz->Ninfos == 2) {
            imprimirPessoas23(Raiz->Cent);

            printf("\n%s\n   CPF: %s\n   Data Nascimento: %s\n   CEP Cidade Natal: %s\n   CEP Cidade Atual: %s\n",
            Raiz->Info2->nome, Raiz->Info2->cpf, Raiz->Info2->dataNascimento,
            Raiz->Info2->cepCityNatal, Raiz->Info2->cepCityMora);

            imprimirPessoas23(Raiz->Dir);
        } else {
            imprimirPessoas23(Raiz->Cent);
        }
    }
}