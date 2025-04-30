#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/playlist.h"
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"
#include "../includes/musicasPlaylist.h"




int maiorMP(int alt1, int alt2){
    if(alt1 > alt2){
        return alt1;
    } else {
        return alt2;
    }
}




int alturaNoMP(MusicasPlaylist* no){
    if (no == NULL) {
        return -1;
    } else {
        return no->altura;
    }
}

void rotacaoEsqMP(MusicasPlaylist** raiz){
    if((*raiz)->Dir != NULL){
        
        MusicasPlaylist* aux = (*raiz)->Dir;
        (*raiz)->Dir = aux->Esq;
        aux->Esq = *raiz;


        (*raiz)->altura = maiorMP(alturaNoMP((*raiz)->Esq), alturaNoMP((*raiz)->Dir)) + 1;
        aux->altura = maiorMP(alturaNoMP(aux->Dir), (*raiz)->altura) + 1;

        (*raiz) = aux;
    }
}

void rotacaoDirMP(MusicasPlaylist** raiz){
    if((*raiz)->Esq != NULL){
        
        MusicasPlaylist* aux = (*raiz)->Esq;
        (*raiz)->Esq = aux->Dir;
        aux->Dir = *raiz;

        (*raiz)->altura = maiorMP(alturaNoMP((*raiz)->Esq), alturaNoMP((*raiz)->Dir)) + 1;
        aux->altura = maiorP(alturaNoMP(aux->Esq), (*raiz)->altura) + 1;

        (*raiz) = aux;
    }
}

int fatorBalanceamentoMP(MusicasPlaylist* raiz){
    int bl;
    if (raiz != NULL) {
        bl = alturaNoMP(raiz->Esq) - alturaNoMP(raiz->Dir);
    } else {
        bl = 0;
    }
    return bl;
}

void balanceamentoMP(MusicasPlaylist** raiz){
    int fb = fatorBalanceamentoMP(*raiz);
    

    if (fb == 2) {  
        
        int fbEsq = fatorBalanceamentoMP((*raiz)->Esq);
        if (fbEsq < 0) {  
            rotacaoEsqMP(&(*raiz)->Esq);  
        }
        rotacaoDirMP(raiz);
    } else if (fb == -2) {  
       
        int fbDir = fatorBalanceamentoMP((*raiz)->Dir);
        if (fbDir > 0) {  
            rotacaoDirMP(&(*raiz)->Dir);
        }
        rotacaoEsqMP(raiz);
    }
}

MusicasPlaylist* criar(char* nomeA, char* tituloA, char* tituloM){
    MusicasPlaylist* no = (MusicasPlaylist*)malloc(sizeof(MusicasPlaylist));

    strcpy(no->tituloM, tituloM);
    strcpy(no->tituloA, tituloA);
    strcpy(no->nome, nomeA);

    no->Dir = NULL;
    no->Esq = NULL;
    return no;
}

void buscarMusicaPlaylist(MusicasPlaylist* raiz,  char* tituloM, MusicasPlaylist** resultado){
    *resultado = NULL;

    if (raiz != NULL){
        if(strcmp(raiz->tituloM, tituloM) == 0){
            *resultado = raiz;
        } else if (strcmp(tituloM, raiz->tituloM) < 0){
            buscarMusicaPlaylist(raiz->Esq, tituloM, resultado);
        } else {
            buscarMusicaPlaylist(raiz->Dir, tituloM, resultado);
        }
    }
}

int addMusica(MusicasPlaylist** R, MusicasPlaylist* musica){
    int inseriu = 1;

    if (*R == NULL){
        *R = musica;
        
    }

    if (strcmp(musica->tituloM, (*R)->tituloM) < 0){
        if(addMusica(&((*R)->Esq), musica)){
            (*R)->altura = maiorMP(alturaNoMP((*R)->Esq), alturaNoMP((*R)->Dir)) + 1;
            balanceamentoMP(R);
        }
    } else if (strcmp(musica->tituloM, (*R)->tituloM) > 0){
        if(addMusica(&((*R)->Dir), musica)){
            (*R)->altura = maiorMP(alturaNoMP((*R)->Esq), alturaNoMP((*R)->Dir)) + 1;
            balanceamentoMP(R);
        }
    }
    return inseriu;
}


void cadastrarMusicasPlaylist(Playlist* raiz, char* nomePlaylist, char* nomeA, char* tituloA, char* tituloM){
    Playlist* encontrarNome = NULL;
    buscarPlaylist(raiz, nomePlaylist, &encontrarNome);

    if(encontrarNome != NULL){
        MusicasPlaylist* buscaTitulo = NULL;
        buscarMusicaPlaylist(raiz->musicas, tituloM, &buscaTitulo);

        if (buscaTitulo != NULL){
            printf("Musica \"%s\" ja esta nessa playlist!\n", tituloM);
        } else {
            MusicasPlaylist* novaMusica = criar(nomeA, tituloA, tituloM);
            if(addMusica(&(encontrarNome->musicas), novaMusica)){
                printf("Musica \"%s\" adicionada a playlist \"%s\"!\n", tituloM, nomePlaylist);
            }
        }
    } else {
        printf("Playlist \"%s\" nao encontrada\n", nomePlaylist);
    }
    
}

int ehFilhoMP(MusicasPlaylist* mp) {
    return (mp->Esq == NULL && mp->Dir == NULL);
}


MusicasPlaylist* souFilhoMP(MusicasPlaylist* mp) {
    MusicasPlaylist* resultado;
    if (mp->Esq != NULL && mp->Dir == NULL) {
        resultado = mp->Esq;
    } else if (mp->Dir != NULL && mp->Esq == NULL) {
        resultado = mp->Dir;
    } else {
        resultado = NULL;
    }
    return resultado;
}


MusicasPlaylist* enderecoMenorEsqMP(MusicasPlaylist* mp) {
    MusicasPlaylist* atual = mp;
    while (atual != NULL && atual->Esq != NULL) {
        atual = atual->Esq;
    }
    return atual;
}

int removerMusicaPlaylist(MusicasPlaylist** raiz, char* tituloM){
    int removeu = 1;

    if(*raiz != NULL){
        if(strcmp(tituloM, (*raiz)->tituloM) == 0){
           
            MusicasPlaylist *filho, *aux;

            if(ehFilhoMP(*raiz)){
                printf("Musica removida da Playlist!\n");
                aux = *raiz;
                *raiz = NULL;
                free(aux);
            } else {
                
                if((filho = souFilhoMP(*raiz)) != NULL){
                    printf("Musica removida da Playlist!\n");
                    aux = *raiz;
                    *raiz = filho;
                    free(aux);
                } else {
                    MusicasPlaylist* menor;
                    menor = enderecoMenorEsqMP((*raiz)->Dir);
                     
                    strcpy((*raiz)->tituloM, menor->tituloM);
                    removerMusicaPlaylist(&((*raiz)->Dir), menor->tituloM);

                }
            }
        } else {
            if(strcmp(tituloM, (*raiz)->tituloM) < 0){
                removeu = removerMusicaPlaylist(&((*raiz)->Esq), tituloM);
            } else {
                removeu = removerMusicaPlaylist(&((*raiz)->Dir), tituloM);
            }
        }
        
        if (*raiz != NULL) {
            (*raiz)->altura = maiorMP(alturaNoMP((*raiz)->Esq), alturaNoMP((*raiz)->Dir)) + 1;
            balanceamentoMP(raiz);
        }

    } else {
        printf("Musica \"%s\" nao encontrada!\n", tituloM);
        removeu = 0;
    }
    return removeu;
}

void imprimirMusicasPlaylist(MusicasPlaylist* R){
    
    if(R != NULL){
        
        imprimirMusicasPlaylist(R->Esq);

        printf("Musica: %s, Album: %s, Artista: %s\n", R->tituloM, R->tituloA, R->nome);
        imprimirMusicasPlaylist(R->Dir);
    }
   
}

void liberarMusicasPlaylist(MusicasPlaylist* raiz) {
    if (raiz != NULL) {
        liberarMusicasPlaylist(raiz->Esq);
        liberarMusicasPlaylist(raiz->Dir);
        free(raiz);
    }
}
