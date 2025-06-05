#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"
#include "../includes/cidade.h"
#include "../includes/cep.h"

Cidade* criarCidade(char* nomeCity, int tamPopu){
    Cidade* nova = (Cidade*)malloc(sizeof(Cidade));

    strcpy(nova->nomeCity, nomeCity);
    nova->tamPopu = tamPopu;

    return nova;
}

arv23cidade* criarNo23(Cidade* cidadeInfo, arv23cidade* Esq, arv23cidade* Cen){
    arv23cidade* novo = (arv23cidade*)malloc(sizeof(arv23cidade));

    if(novo != NULL){
        novo->Info1 = cidadeInfo;
        novo->Info2 = NULL;
        novo->Esq = Esq;
        novo->Dir = NULL;
        novo->Cent = Cen;
        novo->Ninfos = 1;
    }
    return novo;
}

void addInfo(arv23cidade** no, Cidade* cidadeInfo, arv23cidade* subArvInfo){
    if(strcmp(cidadeInfo->nomeCity, (*no)->Info1->nomeCity) > 0){
        (*no)->Info2 = cidadeInfo;
        (*no)->Dir = subArvInfo;
    } else {
        (*no)->Info2 = (*no)->Info1;
        (*no)->Info1 = cidadeInfo;
        (*no)->Dir = (*no)->Cent;
        (*no)->Cent = subArvInfo;
    }
    (*no)->Ninfos = 2;
}

arv23cidade* quebraNo(arv23cidade** no, Cidade* cidadeInfo, Cidade** sobe, arv23cidade* Dir){
    arv23cidade* maior;
    
    if(strcmp(cidadeInfo->nomeCity, (*no)->Info2->nomeCity) > 0){
        *sobe = (*no)->Info2;
        maior = criarNo23(cidadeInfo, (*no)->Dir, Dir);
    } else if(strcmp(cidadeInfo->nomeCity, (*no)->Info1->nomeCity) > 0){
        *sobe = cidadeInfo;
        maior = criarNo23((*no)->Info2, Dir, (*no)->Dir);
    } else {
        *sobe = (*no)->Info1;
        maior = criarNo23((*no)->Info2, (*no)->Cent, (*no)->Dir);
        (*no)->Info1 = cidadeInfo;
        (*no)->Cent = Dir;
    }
    (*no)->Info2 = NULL;
    (*no)->Dir = NULL;
    (*no)->Ninfos = 1;
    return maior;
}

arv23cidade* insere23Cidade(arv23cidade** Raiz, Cidade* noCidade, arv23cidade* Pai, Cidade** sobe){
    arv23cidade* maiorNo;

    if(*Raiz == NULL){
        *Raiz = criarNo23(noCidade, NULL, NULL);
    } else {
        if((*Raiz)->Esq == NULL){
            if((*Raiz)->Ninfos == 1){
                addInfo(Raiz, noCidade, NULL);
            } else {
                maiorNo = quebraNo(Raiz, noCidade, sobe, NULL);

                if(Pai == NULL){
                    *Raiz = criarNo23(*sobe, *Raiz, maiorNo);
                    maiorNo = NULL;
                }
            }
        } else {
            if(strcmp(noCidade->nomeCity, (*Raiz)->Info1->nomeCity) < 0){
                maiorNo = insere23Cidade(&((*Raiz)->Esq), noCidade, *Raiz, sobe);
            } else if ((*Raiz)->Ninfos == 1 || strcmp(noCidade->nomeCity, (*Raiz)->Info2->nomeCity) < 0){
                maiorNo = insere23Cidade(&((*Raiz)->Cent), noCidade, *Raiz, sobe);
            } else {
                maiorNo = insere23Cidade(&((*Raiz)->Dir), noCidade, *Raiz, sobe);
            }

            if(maiorNo != NULL){
                if((*Raiz)->Ninfos == 1){
                    addInfo(Raiz, *sobe, maiorNo);
                    maiorNo = NULL;
                } else {
                    maiorNo = quebraNo(Raiz, *sobe, sobe, maiorNo);
                    if(Pai == NULL){
                        *Raiz = criarNo23(*sobe, *Raiz, maiorNo);
                        maiorNo = NULL;
                    }
                }
            }
        }
    }

    return maiorNo;
}

void cadastrarCidade(Estado* lista, char* nomeEst, char* nomeCity, int tamPopu, Cidade** sobe) {
    Estado* estado = NULL;
    buscaEstado(lista, nomeEst, &estado);

    if(estado != NULL) {
        Cidade* nova = criarCidade(nomeCity, tamPopu);

        if(strcmp(nomeCity, estado->nomeCap) == 0) {
            estado->capital = nova;  
            printf("Cidade %s registrada como capital de %s\n", nomeCity, estado->nomeEst);
        }
        
        insere23Cidade(&(estado->arvCidades), nova, NULL, sobe);
        
        estado->quantCity++;

        
    } else {
        printf("Estado \"%s\" nao encontrado!\n", nomeEst);
    }
}

Cidade* buscaCidade(arv23cidade* Raiz, char* nomeCity){
    Cidade* encontrou = NULL;

    if (Raiz != NULL){
        if(strcmp(nomeCity, Raiz->Info1->nomeCity) == 0){
            encontrou = Raiz->Info1;
        } else if(Raiz->Ninfos == 2 && strcmp(nomeCity, Raiz->Info2->nomeCity) == 0){
            encontrou = Raiz->Info2;
        } else if(strcmp(nomeCity, Raiz->Info1->nomeCity) < 0){
            encontrou = buscaCidade(Raiz->Esq, nomeCity);
        } else if(Raiz->Ninfos == 1 || strcmp(nomeCity, Raiz->Info2->nomeCity) < 0){
            encontrou = buscaCidade(Raiz->Cent, nomeCity);
        } else {
            encontrou = buscaCidade(Raiz->Dir, nomeCity);
        }
    }

    return encontrou;
}
