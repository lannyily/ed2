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


Pessoa* buscaPessoa(arv23Pessoa* Raiz, char* cpf){
    Pessoa* result = NULL;

    if(Raiz != NULL){
        if(strcmp(cpf, Raiz->Info1->cpf) == 0){
            result = Raiz->Info1;
        }
        else if(Raiz->Ninfos == 2 && strcmp(cpf, Raiz->Info2->cpf) == 0) {
            result = Raiz->Info2;
        } 
        else if (strcmp(cpf, Raiz->Info1->cpf) < 0) {
            result = buscaPessoa(Raiz->Esq, cpf);
        } 
        else if (Raiz->Ninfos == 1 || strcmp(cpf, Raiz->Info1->cpf) < 0) {
            result = buscaPessoa(Raiz->Cent, cpf);
        } 
        else {
            result = buscaPessoa(Raiz->Dir, cpf);
        }
    }
    return result;
    
}


int ehFolha(arv23Pessoa* pessoa){
    int folha = 0;
    if(pessoa->Esq == NULL && pessoa->Cent == NULL){
        folha = 1;
    }
    return folha;
}



void redistribuir(arv23Pessoa** Raiz, arv23Pessoa** Pai){
    if (*Raiz != NULL){

        if ((*Raiz)->Ninfos == 0) {
            if (Pai != NULL){
                if ((*Raiz) == ((*Pai)->Dir)){
                    
                    if((*Pai)->Cent->Ninfos == 2){
                        (*Raiz)->Info1 = (*Pai)->Info2;
                        (*Raiz)->Ninfos = 1;
                        (*Pai)->Info2 = (*Pai)->Cent->Info2;
                        (*Pai)->Cent->Ninfos = 1;
                        (*Pai)->Cent->Info2 = NULL;
                        (*Raiz)->Esq = (*Pai)->Cent->Dir;
                        (*Pai)->Cent->Dir = NULL;
                    } 
                    
                    else if ((*Pai)->Cent->Ninfos == 1) {
                        (*Raiz)->Info2 = (*Pai)->Info2;
                        (*Raiz)->Dir = (*Raiz)->Cent;
                        (*Raiz)->Info1 = (*Pai)->Cent->Info1;
                        (*Raiz)->Ninfos = 2;
                        (*Pai)->Ninfos = 1;
                        (*Raiz)->Cent = (*Pai)->Cent->Cent;
                        (*Raiz)->Esq = (*Pai)->Cent->Esq;
                        free((*Pai)->Cent);
                        (*Pai)->Cent = (*Raiz);
                        (*Pai)->Dir = NULL;
                    }
                } 
                
                else if ((*Raiz) == (*Pai)->Cent){

                    if ((*Pai)->Esq->Ninfos == 2) {
                        (*Raiz)->Info1 = (*Pai)->Info1;
                        (*Raiz)->Ninfos = 1;
                        (*Pai)->Info1 = (*Pai)->Esq->Info2;
                        (*Pai)->Esq->Ninfos = 1;
                        (*Raiz)->Esq = (*Pai)->Esq->Dir;
                        (*Pai)->Esq->Dir = NULL;
                    } 
                    
                    else if ((*Pai)->Esq->Ninfos == 1){

                        if ((*Pai)->Ninfos == 2) {
                            (*Raiz)->Info2 = (*Pai)->Info1;
                            (*Raiz)->Info1 = (*Pai)->Esq->Info1;
                            (*Raiz)->Ninfos = 2;
                            (*Raiz)->Dir = (*Raiz)->Cent;
                            (*Raiz)->Cent = (*Pai)->Esq->Cent;
                            (*Raiz)->Esq = (*Pai)->Esq->Esq;
                            free((*Pai)->Esq);
                            (*Pai)->Esq = (*Raiz);
                            (*Pai)->Info1 = (*Pai)->Info2;
                            (*Pai)->Ninfos = 1;
                            (*Pai)->Cent = (*Pai)->Dir;
                            (*Pai)->Dir = NULL;
                        } 
                        
                        else if ((*Pai)->Ninfos == 1) {
                            (*Raiz)->Info2 = (*Pai)->Info1;
                            (*Raiz)->Info1 = (*Pai)->Esq->Info1;
                            (*Raiz)->Ninfos = 2;
                            (*Pai)->Ninfos = 0;
                            (*Raiz)->Dir = (*Raiz)->Cent;
                            (*Raiz)->Cent = (*Pai)->Esq->Cent;
                            (*Raiz)->Esq = (*Pai)->Esq->Esq;
                            free((*Pai)->Esq);
                            (*Pai)->Esq = NULL;
                        }
                    }
                } 
                
                else if ((*Raiz) == (*Pai)->Esq) {
                    
                    if ((*Pai)->Cent->Ninfos == 2) {
                        (*Raiz)->Info1 = (*Pai)->Info1;
                        (*Raiz)->Ninfos = 1;
                        (*Pai)->Info1 = (*Pai)->Cent->Info1;
                        (*Pai)->Cent->Ninfos = 1;
                        (*Pai)->Cent->Info1 = (*Pai)->Cent->Info2;
                        (*Raiz)->Esq = (*Raiz)->Cent;
                        (*Raiz)->Cent = (*Pai)->Cent->Esq;
                        (*Pai)->Cent->Esq = (*Pai)->Cent->Cent;
                        (*Pai)->Cent->Cent = (*Pai)->Cent->Dir;
                        (*Pai)->Cent->Dir = NULL;
                    } 
                    
                    else if ((*Pai)->Cent->Ninfos == 1) {
                        
                        if ((*Pai)->Ninfos == 2) {
                            (*Raiz)->Info1 = (*Pai)->Info1;
                            (*Raiz)->Info2 = (*Pai)->Cent->Info1;
                            (*Raiz)->Ninfos = 2;
                            (*Raiz)->Esq = (*Raiz)->Cent;
                            (*Raiz)->Cent = (*Pai)->Cent->Esq;
                            (*Raiz)->Dir = (*Pai)->Cent->Cent;
                            (*Pai)->Info1 = (*Pai)->Info2;
                            (*Pai)->Ninfos = 1;
                            free((*Pai)->Cent);
                            (*Pai)->Cent = (*Pai)->Dir;
                            (*Pai)->Dir = NULL;
                        } 
                        
                        else if ((*Pai)->Ninfos == 1) {
                            (*Raiz)->Info1 = (*Pai)->Info1;
                            (*Raiz)->Esq = (*Raiz)->Cent;
                            (*Raiz)->Info2 = (*Pai)->Cent->Info1;
                            (*Raiz)->Cent = (*Pai)->Cent->Esq;
                            (*Raiz)->Dir = (*Pai)->Cent->Cent;
                            (*Pai)->Ninfos = 0;
                            (*Raiz)->Ninfos = 2;
                            free((*Pai)->Cent);
                            (*Pai)->Cent = (*Raiz);
                            (*Pai)->Esq = NULL;
                        }
                    }
                }
            } 
            else if (Pai == NULL) {
                (*Raiz) = (*Raiz)->Cent;
            }  
 
        }
    }

}


void removerMaiorEsq(arv23Pessoa** Raiz, arv23Pessoa** maiorPai, arv23Pessoa** maiorRemove, int localInfo) {
    if(*maiorRemove != NULL) {
        if(ehFolha(*maiorRemove) == 1) {
            Pessoa* aux;
            if(localInfo == 1) {
                aux = (*Raiz)->Info1;
                if((*maiorRemove)->Ninfos == 2) {
                    printf("Removendo Info2 do no folha (CPF: %s) para substituir Info1 do no interno\n", (*maiorRemove)->Info2->cpf);
                    (*Raiz)->Info1 = (*maiorRemove)->Info2;
                    (*maiorRemove)->Info2 = aux;
                }
                else {
                    printf("Removendo Info1 do no folha (CPF: %s) para substituir Info1 do no interno\n", (*maiorRemove)->Info1->cpf);
                    (*Raiz)->Info1 = (*maiorRemove)->Info1;
                    (*maiorRemove)->Info1 = aux;
                }
            } 
            else if (localInfo == 2) {
                aux = (*Raiz)->Info2;
                if ((*maiorRemove)->Ninfos == 2) {
                    printf("Removendo Info2 do no folha (CPF: %s) para substituir Info2 do no interno\n", (*maiorRemove)->Info2->cpf);
                    (*Raiz)->Info2 = (*maiorRemove)->Info2;
                    (*maiorRemove)->Info2 = aux;
                }
                else {
                    printf("Removendo Info1 do no folha (CPF: %s) para substituir Info2 do no interno\n", (*maiorRemove)->Info1->cpf);
                    (*Raiz)->Info2 = (*maiorRemove)->Info1;
                    (*maiorRemove)->Info1 = aux;
                }
            }
            
            // Remoção do nó folha
            if((*maiorRemove)->Ninfos == 2) {
                printf("Liberando Info2 do no folha (CPF: %s)\n", (*maiorRemove)->Info2->cpf);
                free((*maiorRemove)->Info2);
                (*maiorRemove)->Info2 = NULL;
                (*maiorRemove)->Ninfos = 1;
            }
            else {
                printf("Liberando Info1 do no folha (CPF: %s)\n", (*maiorRemove)->Info1->cpf);
                free((*maiorRemove)->Info1);
                (*maiorRemove)->Info1 = NULL;
                (*maiorRemove)->Ninfos = 0;
            }
        } 
        else {
            if((*maiorRemove)->Ninfos == 2) {
                removerMaiorEsq(Raiz, maiorRemove, &((*maiorRemove)->Dir), localInfo);
            } 
            else {
                removerMaiorEsq(Raiz, maiorRemove, &((*maiorRemove)->Cent), localInfo);
            }
        }
    }
    redistribuir(maiorRemove, maiorPai);
}

void removerPessoa23(arv23Pessoa** Raiz, arv23Pessoa** Pai, char* cpf) {
    if(*Raiz != NULL) {
        if(strcmp(cpf, (*Raiz)->Info1->cpf) == 0) {
            printf("Encontrado CPF %s para remocao (Info1)\n", cpf);
            
            if(ehFolha(*Raiz) == 1) {
                if ((*Raiz)->Ninfos == 2) {
                    printf("Removendo Info1 (CPF: %s) de no folha com 2 infos\n", (*Raiz)->Info1->cpf);
                    free((*Raiz)->Info1);
                    (*Raiz)->Info1 = (*Raiz)->Info2;
                    (*Raiz)->Info2 = NULL;
                    (*Raiz)->Ninfos = 1;
                } else if ((*Raiz)->Ninfos == 1) {
                    printf("Removendo Info1 (CPF: %s) de no folha com 1 info\n", (*Raiz)->Info1->cpf);
                    free((*Raiz)->Info1);
                    (*Raiz)->Info1 = NULL;
                    (*Raiz)->Ninfos = 0;
                }
            } else {
                printf("Substituindo Info1 (CPF: %s) de no interno pelo maior da esquerda\n", (*Raiz)->Info1->cpf);
                arv23Pessoa** maiorInfoRemove = &((*Raiz)->Esq);
                arv23Pessoa** maiorPai = Raiz;
                removerMaiorEsq(Raiz, maiorPai, maiorInfoRemove, 1);
            }
        } 
        else if ((*Raiz)->Ninfos == 2 && strcmp(cpf, (*Raiz)->Info2->cpf) == 0) {
            printf("Encontrado CPF %s para remocao (Info2)\n", cpf);

            if (ehFolha(*Raiz) == 1) {
                printf("Removendo Info2 (CPF: %s) de no folha\n", (*Raiz)->Info2->cpf);
                free((*Raiz)->Info2);
                (*Raiz)->Info2 = NULL;
                (*Raiz)->Ninfos = 1;
            } else {
                printf("Substituindo Info2 (CPF: %s) de no interno pelo maior do centro\n", (*Raiz)->Info2->cpf);
                arv23Pessoa** maiorInfoRemove = &((*Raiz)->Cent);
                arv23Pessoa** maiorPai = Raiz;
                removerMaiorEsq(Raiz, maiorPai, maiorInfoRemove, 2);
            }
        }  
        else if (strcmp(cpf, (*Raiz)->Info1->cpf) < 0) {
            printf("Buscando CPF %s na subárvore esquerda\n", cpf);
            removerPessoa23(&((*Raiz)->Esq), Raiz, cpf);
        } 
        else if ((*Raiz)->Ninfos == 1 || ((*Raiz)->Ninfos == 2 && strcmp(cpf, (*Raiz)->Info2->cpf) < 0)) {
            printf("Buscando CPF %s na subarvore central\n", cpf);
            removerPessoa23(&((*Raiz)->Cent), Raiz, cpf);
        } 
        else {
            printf("Buscando CPF %s na subarvore direita\n", cpf);
            removerPessoa23(&((*Raiz)->Dir), Raiz, cpf);
        }
    }
    redistribuir(Raiz, Pai);
}