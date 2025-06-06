#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/estado.h"
#include "../includes/cidade.h"
#include "../includes/cep.h"

arv23cep* criarNo23Cep(Cep* cepInfo, arv23cep* Esq, arv23cep* Cen){
    arv23cep* novo = (arv23cep*)malloc(sizeof(arv23cep));

    if (novo != NULL){
        novo->Info1 = cepInfo;
        novo->Info2 = NULL;
        novo->Esq = Esq;
        novo->Dir = NULL;
        novo->Cent = Cen;
        novo->Ninfos = 1;
    }
    return novo;
}

void addInfoCep(arv23cep** no, Cep* cepInfo, arv23cep* subArvInfo){
    
    if(strcmp(cepInfo->Cep, (*no)->Info1->Cep) > 0){
        (*no)->Info2 = cepInfo;
        (*no)->Dir = subArvInfo;
    } else {
        (*no)->Info2 = (*no)->Info1;
        (*no)->Info1 = cepInfo;
        (*no)->Dir = (*no)->Cent;
        (*no)->Cent = subArvInfo;
    }
    (*no)->Ninfos = 2;
}

arv23cep* quebraNoCep(arv23cep** no, Cep* cepInfo, Cep** sobe, arv23cep* Dir){
    printf("Entrou em quebraNo\n");
    arv23cep* maior;

    if(strcmp(cepInfo->Cep, (*no)->Info2->Cep) > 0){
        *sobe = (*no)->Info2;
        maior = criarNo23Cep(cepInfo, (*no)->Dir, Dir);
    } else if (strcmp(cepInfo->Cep, (*no)->Info1->Cep) > 0){
        *sobe = cepInfo;
        maior = criarNo23Cep((*no)->Info2, Dir, (*no)->Dir);
    } else {
        *sobe = (*no)->Info1;
        maior = criarNo23Cep((*no)->Info2, (*no)->Cent, (*no)->Dir);
        (*no)->Info1 = cepInfo;
        (*no)->Cent = Dir;
    }
    (*no)->Info2 = NULL;
    (*no)->Dir = NULL;
    (*no)->Ninfos = 1;

    return maior;
}

arv23cep* insere23Cep(arv23cep** Raiz, Cep* cepInfo, arv23cep* Pai, Cep** sobe){
    arv23cep* maiorNo;

   
    if(*Raiz == NULL){
        
        *Raiz = criarNo23Cep(cepInfo, NULL, NULL);
    } else {
        
        if((*Raiz)->Esq == NULL){
            
            if((*Raiz)->Ninfos == 1){
                
                addInfoCep(Raiz, cepInfo, NULL);
            } else {
                
                maiorNo = quebraNoCep(Raiz, cepInfo, sobe, NULL);

                if(Pai == NULL){
                    *Raiz = criarNo23Cep(*sobe, *Raiz, maiorNo);
                    maiorNo = NULL;
                }
            }
        } else {
            
            if (strcmp(cepInfo->Cep, (*Raiz)->Info1->Cep) < 0){
                maiorNo = insere23Cep(&((*Raiz)->Esq), cepInfo, *Raiz, sobe);
            } 
            else if ((*Raiz)->Ninfos == 1 || strcmp(cepInfo->Cep, (*Raiz)->Info2->Cep) < 0){
                maiorNo = insere23Cep(&((*Raiz)->Cent), cepInfo, *Raiz, sobe);
            }
            else {
                maiorNo = insere23Cep(&((*Raiz)->Dir), cepInfo, *Raiz, sobe);
            }

            if (maiorNo != NULL){
                if((*Raiz)->Ninfos == 1){
                    addInfoCep(Raiz, *sobe, maiorNo);
                    maiorNo = NULL;
                } else {
                    maiorNo = quebraNoCep(Raiz, *sobe, sobe, maiorNo);

                    if(Pai == NULL){
                        *Raiz = criarNo23Cep(*sobe, *Raiz, maiorNo);
                        maiorNo = NULL;
                    }
                }
            }
        }
    }
    return maiorNo;
}


Cep* buscaCep(arv23cep* Raiz, Cep* cepNum){
    Cep* encontrou = NULL;

    if(Raiz != NULL){
        
        if(strcmp(cepNum->Cep, Raiz->Info1->Cep) == 0){
            encontrou = Raiz->Info1;
        } else if(Raiz->Ninfos == 2 && strcmp(cepNum->Cep, Raiz->Info2->Cep) == 0){
            encontrou = Raiz->Info2;
        } else if (strcmp(cepNum->Cep, Raiz->Info1->Cep) < 0){
            encontrou = buscaCep(Raiz->Esq, cepNum);
        } else if (Raiz->Ninfos == 1 || strcmp(cepNum->Cep, Raiz->Info2->Cep) < 0){
            encontrou = buscaCep(Raiz->Cent, cepNum);
        } else {
            encontrou = buscaCep(Raiz->Dir, cepNum);
        }
    }
    return encontrou;
}



void imprimirCep23(arv23cep* Raiz){
    
    if(Raiz != NULL) {
    
        imprimirCep23(Raiz->Esq);
        
        
        printf("            - CEP: %s\n", Raiz->Info1->Cep);
        
        
        if(Raiz->Ninfos == 2) {
            imprimirCep23(Raiz->Cent);

            printf("            - CEP: %s\n", Raiz->Info2->Cep);
            imprimirCep23(Raiz->Dir);
        } else {
            imprimirCep23(Raiz->Cent);
        }
    }
}

void imprimirCidades23(arv23cidade* Raiz) {
    if(Raiz != NULL) {
        imprimirCidades23(Raiz->Esq);
        
        printf("        - %s (Populacao: %d)\n", Raiz->Info1->nomeCity, Raiz->Info1->tamPopu);
        
        if (Raiz->Info1 != NULL && Raiz->Info1->arvCeps != NULL) {
            
            imprimirCep23(Raiz->Info1->arvCeps);
        } else {
            printf("            - Nenhum CEP cadastrado nesta cidade!\n");
        }
        
        
        if(Raiz->Ninfos == 2) {
            imprimirCidades23(Raiz->Cent);
            
            printf("        - %s (População: %d)\n", Raiz->Info2->nomeCity, Raiz->Info2->tamPopu);
            if (Raiz->Info2 != NULL && Raiz->Info2->arvCeps != NULL) {
                imprimirCep23(Raiz->Info2->arvCeps);
            } else {
                printf("            - Nenhum CEP cadastrado nesta cidade!\n");
            }
            
            imprimirCidades23(Raiz->Dir);
        } else {
            imprimirCidades23(Raiz->Cent);
        }
    }
}

void imprimirEstadosCidadesCeps23(Estado* listaEstados){
    Estado* atual = listaEstados;
    
    while(atual != NULL) {
        printf("\nEstado: %s\n", atual->nomeEst);
        printf("Capital: %s | Populacao: %d | Num. Cidades: %d\n", atual->nomeCap, atual->tamPopu, atual->quantCity);
        
        if(atual->arvCidades != NULL) {
            imprimirCidades23(atual->arvCidades);
        } else {
            printf("    - Nenhuma cidade cadastrada neste estado!\n");
        }
        
        atual = atual->Prox;
    }
}

void cadastrarCep23(Estado* listaEstados, arv23cep* raizCep, char* nomeEst, char*nomeCity, char* cep, Cep** sobe){
    Estado* estado = NULL;

    buscaEstado(listaEstados, nomeEst, &estado);

    if(estado != NULL){
        Cidade* cidade = NULL;
        cidade = buscaCidade(estado->arvCidades, nomeCity);

        if(cidade != NULL){
            Cep* novo = (Cep*) malloc(sizeof(Cep));
            if (novo == NULL) {
                fprintf(stderr, "Erro ao alocar memoria para cep\n");
                exit(1);
            }
            strncpy(novo->Cep, cep, sizeof(novo->Cep) - 1);


            insere23Cep(&(cidade->arvCeps), novo, NULL, sobe);
        } else {
            printf("Cidade nao encontrada!\n");
        }
    } else {
        printf("Estado nao encontrado!\n");
    }
}

void redistribuirCep(arv23cep** Raiz, arv23cep** Pai){
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


int ehFolhaCep(arv23cep* cep){
    int folha = 0;
    if(cep->Esq == NULL && cep->Cent == NULL){
        folha = 1;
    }
    return folha;
}


void removerMaiorEsqCep(arv23cep** Raiz, arv23cep** maiorPai, arv23cep** maiorRemove, int localInfo){
    if(*maiorRemove != NULL) {
        if(ehFolhaCep(*maiorRemove) == 1) {
            Cep* aux;
            if(localInfo == 1) {
                aux = (*Raiz)->Info1;
                if((*maiorRemove)->Ninfos == 2) {
                    printf("Removendo Info2 do no folha (Cep: %s) para substituir Info1 do no interno\n", (*maiorRemove)->Info2->Cep);
                    (*Raiz)->Info1 = (*maiorRemove)->Info2;
                    (*maiorRemove)->Info2 = aux;
                }
                else {
                    printf("Removendo Info1 do no folha (Cep: %s) para substituir Info1 do no interno\n", (*maiorRemove)->Info1->Cep);
                    (*Raiz)->Info1 = (*maiorRemove)->Info1;
                    (*maiorRemove)->Info1 = aux;
                }
            } 
            else if (localInfo == 2) {
                aux = (*Raiz)->Info2;
                if ((*maiorRemove)->Ninfos == 2) {
                    printf("Removendo Info2 do no folha (Cep: %s) para substituir Info2 do no interno\n", (*maiorRemove)->Info2->Cep);
                    (*Raiz)->Info2 = (*maiorRemove)->Info2;
                    (*maiorRemove)->Info2 = aux;
                }
                else {
                    printf("Removendo Info1 do no folha (Cep: %s) para substituir Info2 do no interno\n", (*maiorRemove)->Info1->Cep);
                    (*Raiz)->Info2 = (*maiorRemove)->Info1;
                    (*maiorRemove)->Info1 = aux;
                }
            }
            
            // Remoção do nó folha
            if((*maiorRemove)->Ninfos == 2) {
                printf("Liberando Info2 do no folha (Cep: %s)\n", (*maiorRemove)->Info2->Cep);
                free((*maiorRemove)->Info2);
                (*maiorRemove)->Info2 = NULL;
                (*maiorRemove)->Ninfos = 1;
            }
            else {
                printf("Liberando Info1 do no folha (Cep: %s)\n", (*maiorRemove)->Info1->Cep);
                free((*maiorRemove)->Info1);
                (*maiorRemove)->Info1 = NULL;
                (*maiorRemove)->Ninfos = 0;
            }
        } 
        else {
            if((*maiorRemove)->Ninfos == 2) {
                removerMaiorEsqCep(Raiz, maiorRemove, &((*maiorRemove)->Dir), localInfo);
            } 
            else {
                removerMaiorEsqCep(Raiz, maiorRemove, &((*maiorRemove)->Cent), localInfo);
            }
        }
    }
    redistribuirCep(maiorRemove, maiorPai);
}


void removerCep23(arv23cep** Raiz, arv23cep** Pai, char* cep) {
    if(*Raiz != NULL) {
        if(strcmp(cep, (*Raiz)->Info1->Cep) == 0) {
            printf("Encontrado Cep %s para remocao (Info1)\n", cep);
            
            if(ehFolhaCep(*Raiz) == 1) {
                if ((*Raiz)->Ninfos == 2) {
                    printf("Removendo Info1 (Cep: %s) de no folha com 2 infos\n", (*Raiz)->Info1->Cep);
                    free((*Raiz)->Info1);
                    (*Raiz)->Info1 = (*Raiz)->Info2;
                    (*Raiz)->Info2 = NULL;
                    (*Raiz)->Ninfos = 1;
                } else if ((*Raiz)->Ninfos == 1) {
                    printf("Removendo Info1 (Cep: %s) de no folha com 1 info\n", (*Raiz)->Info1->Cep);
                    free((*Raiz)->Info1);
                    (*Raiz)->Info1 = NULL;
                    (*Raiz)->Ninfos = 0;
                }
            } else {
                printf("Substituindo Info1 (Cep: %s) de no interno pelo maior da esquerda\n", (*Raiz)->Info1->Cep);
                arv23cep** maiorInfoRemove = &((*Raiz)->Esq);
                arv23cep** maiorPai = Raiz;
                removerMaiorEsqCep(Raiz, maiorPai, maiorInfoRemove, 1);
            }
        } 
        else if ((*Raiz)->Ninfos == 2 && strcmp(cep, (*Raiz)->Info2->Cep) == 0) {
            printf("Encontrado CPF %s para remocao (Info2)\n", cep);

            if (ehFolhaCep(*Raiz) == 1){
                printf("Removendo Info2 (Cep: %s) de no folha\n", (*Raiz)->Info2->Cep);
                free((*Raiz)->Info2);
                (*Raiz)->Info2 = NULL;
                (*Raiz)->Ninfos = 1;
            } 
            
            else {
                printf("Substituindo Info2 (Cep: %s) de no interno pelo maior do centro\n", (*Raiz)->Info2->Cep);
                arv23cep** maiorInfoRemove = &((*Raiz)->Cent);
                arv23cep** maiorPai = Raiz;
                removerMaiorEsqCep(Raiz, maiorPai, maiorInfoRemove, 2);
            }
        }  
        else if (strcmp(cep, (*Raiz)->Info1->Cep) < 0) {
            printf("Buscando Cep %s na subarvore esquerda\n", cep);
            removerCep23(&((*Raiz)->Esq), Raiz, cep);
        } 
        else if ((*Raiz)->Ninfos == 1 || ((*Raiz)->Ninfos == 2 && strcmp(cep, (*Raiz)->Info2->Cep) < 0)) {
            printf("Buscando Cep %s na subarvore central\n", cep);
            removerCep23(&((*Raiz)->Cent), Raiz, cep);
        } 
        else {
            printf("Buscando Cep %s na subarvore direita\n", cep);
            removerCep23(&((*Raiz)->Dir), Raiz, cep);
        }
    }
    
    redistribuirCep(Raiz, Pai);
}