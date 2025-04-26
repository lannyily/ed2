#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/playlist.h"
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"

int maiorP(int alt1, int alt2){
    if(alt1 > alt2){
        return alt1;
    } else {
        return alt2;
    }
}

int pegaAlturaP(Playlist* raiz){
    int altura = 0;

    if (raiz != NULL){
        int alturaEsq = pegaAlturaP(raiz->esquerda);
        int alturaDir = pegaAlturaP(raiz->direita);
        if(alturaEsq > alturaDir){
            altura = alturaEsq + 1;
        } else {
            altura = alturaDir + 1;
        }
    }

    return altura;
}

int alturaNoP(Playlist* no){
    if (no == NULL) {
        return -1;
    } else {
        return no->altura;
    }
}

void rotacaoEsqP(Playlist** raiz){
    if((*raiz)->direita != NULL){
        
        Playlist* aux = (*raiz)->direita;
        (*raiz)->direita = aux->esquerda;
        aux->esquerda = *raiz;


        (*raiz)->altura = maiorP(alturaNoP((*raiz)->esquerda), alturaNoP((*raiz)->direita)) + 1;
        aux->altura = maiorP(alturaNoP(aux->direita), (*raiz)->altura) + 1;

        (*raiz) = aux;
    }
}


void rotacaoDirP(Playlist** raiz){
    if((*raiz)->esquerda != NULL){
        
        Playlist* aux = (*raiz)->esquerda;
        (*raiz)->esquerda = aux->direita;
        aux->direita = *raiz;

        (*raiz)->altura = maiorP(alturaNoP((*raiz)->esquerda), alturaNoP((*raiz)->direita)) + 1;
        aux->altura = maiorP(alturaNoP(aux->esquerda), (*raiz)->altura) + 1;

        (*raiz) = aux;
    }
}

int fatorBalanceamentoP(Playlist* raiz){
    int bl;
    if (raiz != NULL) {
        bl = alturaNoP(raiz->esquerda) - alturaNoP(raiz->direita);
    } else {
        bl = 0;
    }
    return bl;
}

void balanceamentoP(Playlist** raiz){
    int fb = fatorBalanceamentoP(*raiz);
    

    if (fb == 2) {  
        
        int fbEsq = fatorBalanceamentoP((*raiz)->esquerda);
        if (fbEsq < 0) {  
            rotacaoEsqP(&(*raiz)->esquerda);  
        }
        rotacaoDirP(raiz);
    } else if (fb == -2) {  
       
        int fbDir = fatorBalanceamentoP((*raiz)->direita);
        if (fbDir > 0) {  
            rotacaoDirP(&(*raiz)->direita);
        }
        rotacaoEsqP(raiz);
    }

}

int inserirPlaylist(Playlist **raiz, Playlist *novaPlaylist) {
    int inseriu = 1;

    if (*raiz == NULL) {
        *raiz = novaPlaylist;
        
    } else {
        int comparacao = strcmp(novaPlaylist->nome, (*raiz)->nome);

        if (comparacao < 0) {
            if(inserirPlaylist(&((*raiz)->esquerda), novaPlaylist)){
                (*raiz)->altura = maiorP(alturaNoP((*raiz)->esquerda), alturaNoP((*raiz)->direita)) + 1;
                balanceamentoP(raiz);
            }
        } else if (comparacao > 0) {
            if(inserirPlaylist(&((*raiz)->direita), novaPlaylist)){
                (*raiz)->altura = maiorP(alturaNoP((*raiz)->esquerda), alturaNoP((*raiz)->direita)) + 1;
                balanceamentoP(raiz);
            }
        }
        
    }

    return inseriu;
}

void buscarPlaylist(Playlist* raiz,  char* nome, Playlist** resultado) {
    *resultado = NULL;
    
    if (raiz != NULL){
        if (strcmp(raiz->nome, nome) == 0) {
            *resultado = raiz;
        } else if (strcmp(nome, raiz->nome) < 0) {
            buscarPlaylist(raiz->esquerda, nome, resultado);
        } else {
            buscarPlaylist(raiz->direita, nome, resultado);
        }
    }
    
}


Playlist* criarPlaylist(char *nome) {
    Playlist *nova = (Playlist *)malloc(sizeof(Playlist));
    
    strcpy(nova->nome, nome);
    nova->musicas = NULL; 
    nova->esquerda = NULL;
    nova->direita = NULL;
    
    return nova;
}




void cadastrarPlaylist(Playlist** raiz, char* nome){
    Playlist* playlist = NULL;
    buscarPlaylist(*raiz, nome, &playlist);
    if(playlist != NULL){
        printf("Playlist \"%s\" já existe!\n", nome);
    } else {
        Playlist* novaPlaylist = criarPlaylist(nome);
        if(inserirPlaylist(raiz, novaPlaylist)){
            printf("Playlist \"%s\" adicionada!\n", nome);
        }
    }
}


int ehFilho(Playlist* p) {
    return (p->esquerda == NULL && p->direita == NULL);
}


Playlist* souFilho(Playlist* p) {
    Playlist* resultado;
    if (p->esquerda != NULL && p->direita == NULL) {
        resultado = p->esquerda;
    } else if (p->direita != NULL && p->esquerda == NULL) {
        resultado = p->direita;
    } else {
        resultado = NULL;
    }
    return resultado;
}


Playlist* enderecoMenorEsq(Playlist* p) {
    Playlist* atual = p;
    while (atual != NULL && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

int removerPlaylist(Playlist** raiz, char* nome){
   
    int removeu = 1;

    if(*raiz != NULL){
        if(strcmp(nome, (*raiz)->nome) == 0){
           
            Playlist *filho, *aux;
            if(ehFilho(*raiz)){
                printf("Playlist removida!\n");
                aux = *raiz;
                *raiz = NULL;
                liberarMusicasPlaylist(aux->musicas);
                free(aux);
            } else {
                
                if((filho = souFilho(*raiz)) != NULL){
                    printf("Playlist  removida!\n");
                    aux = *raiz;
                    *raiz = filho;
                    liberarMusicasPlaylist(aux->musicas);
                    free(aux);
                } else {
                    Playlist* menor;
                    menor = enderecoMenorEsq((*raiz)->direita);
                     
                    strcpy((*raiz)->nome, menor->nome);
                    removerPlaylist(&((*raiz)->direita), menor->nome);
                }
            }
        } else {
            if(strcmp(nome, (*raiz)->nome) < 0){
                removeu = removerPlaylist(&((*raiz)->esquerda), nome);
            } else {
                removeu = removerPlaylist(&((*raiz)->direita), nome);
            }
        }

        if(*raiz != NULL){
            (*raiz)->altura = maiorP(alturaNoP((*raiz)->esquerda), alturaNoP((*raiz)->direita)) + 1;
            balanceamentoP(raiz);
        }

    } else {
        printf("Playlist \"%s\" nao encontrada!\n", nome);
        removeu = 0;
    }
    return removeu;
}

void liberarPlaylists(Playlist* raiz) {
    if (raiz != NULL) {
        liberarPlaylists(raiz->esquerda);
        liberarPlaylists(raiz->direita);
        liberarMusicasPlaylist(raiz->musicas); 
        free(raiz);
    }
}

