#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/album.h"
#include "../Includes/artista.h" 
#include "../Includes/musica.h"

int maiorAl(int alt1, int alt2){
    
    if(alt1 > alt2){
        return alt1;
    } else {
        return alt2;
    }
}

int alturaNoAl(Album* no){
    
    if (no == NULL) {
        return -1;
    } else {
        return no->altura;
    }
}


void rotacaoEsqAl(Album** raiz){
    
    if((*raiz)->Dir != NULL){
        
        Album* aux = (*raiz)->Dir;
        (*raiz)->Dir = aux->Esq;
        aux->Esq = *raiz;


        (*raiz)->altura = maiorAl(alturaNoAl((*raiz)->Esq), alturaNoAl((*raiz)->Dir)) + 1;
        aux->altura = maiorAl(alturaNoAl(aux->Dir), (*raiz)->altura) + 1;

        (*raiz) = aux;
    }
}

void rotacaoDirAl(Album** raiz){
    
    if((*raiz)->Esq != NULL){
        
        Album* aux = (*raiz)->Esq;
        (*raiz)->Esq = aux->Dir;
        aux->Dir = *raiz;

        (*raiz)->altura = maiorAl(alturaNoAl((*raiz)->Esq), alturaNoAl((*raiz)->Dir)) + 1;
        aux->altura = maiorAl(alturaNoAl(aux->Esq), (*raiz)->altura) + 1;

        (*raiz) = aux;
    }
}

int fatorBalanceamentoAl(Album* raiz){
    
    int bl;
    if (raiz != NULL) {
        bl = alturaNoAl(raiz->Esq) - alturaNoAl(raiz->Dir);
    } else {
        bl = 0;
    }
    return bl;
}

void balanceamentoAl(Album** raiz) {
    int fb = fatorBalanceamentoAl(*raiz);
    

    if (fb == 2) {  
        
        int fbEsq = fatorBalanceamentoAl((*raiz)->Esq);
        if (fbEsq < 0) {  
            rotacaoEsqAl(&(*raiz)->Esq);  
        }
        rotacaoDirAl(raiz);
    } else if (fb == -2) {  
       
        int fbDir = fatorBalanceamentoAl((*raiz)->Dir);
        if (fbDir > 0) {  
            rotacaoDirAl(&(*raiz)->Dir);
        }
        rotacaoEsqAl(raiz);
    }
}




void buscaAlbum(Album* R,  char* nome, Album** resultado) {
    
    *resultado = NULL;

    if (R != NULL) {
        
        if (strcmp(R->titulo, nome) == 0) {
            *resultado = R;
        } else if (strcmp(nome, R->titulo) < 0) {
            buscaAlbum(R->Esq, nome, resultado);
        } else {
            buscaAlbum(R->Dir, nome, resultado);
        }
    }
    
}

Album* criarAlbum(char* titulo, char* anoLancamento){
    Album* no = (Album*)malloc(sizeof(Album));

    strcpy(no->titulo, titulo);
    strcpy(no->anoDeLancamento, anoLancamento);
    no->quantMusicas = 0;
    no->musicas = NULL;

    no->Dir = NULL;
    no->Esq = NULL;
 
    return no; 
}

int insereAlbum(Album** R, Album* No) {
    
    int inseriu = 1;
    if (*R == NULL) {
        *R = No;
        
    } else {
        
        int comparacao = strcmp(No->titulo, (*R)->titulo);

        if (comparacao < 0) {
            if(insereAlbum(&((*R)->Esq), No)){
                (*R)->altura = maiorAl(alturaNoAl((*R)->Esq), alturaNoAl((*R)->Dir)) + 1;
                balanceamentoAl(R);
            }
        } else if (comparacao > 0) {
            if (insereAlbum(&((*R)->Dir), No))
            {
                (*R)->altura = maiorAl(alturaNoAl((*R)->Esq), alturaNoAl((*R)->Dir)) + 1;
                balanceamentoAl(R);
            }
             
        }
    }

    return inseriu; 
}

void cadastrarAlbum(Artista* raiz, char* nomeA, char* titulo, char* anoLancamento) {
    Artista* artista = NULL;
    buscaArtista(raiz, nomeA, &artista);

    if (artista != NULL) {
        Album* album = NULL;
        buscaAlbum(artista->albuns, titulo, &album); 


        if (album == NULL) { 
            Album* novoAlbum = criarAlbum(titulo, anoLancamento);
            if (insereAlbum(&(artista->albuns), novoAlbum)) {
                artista->numAlbuns++; 
                printf("Album \"%s\" cadastrado para o artista \"%s\"\n", titulo, nomeA);
            }
        } else {
            printf("Album \"%s\" ja existe para o artista \"%s\"\n", titulo, nomeA);
        }
    } else {
        printf("Artista \"%s\" nao encontrado!\n", nomeA);
    }
}

void imprimirAlbuns(Album* R) {
    if (R != NULL) {
        imprimirAlbuns(R->Esq); 

        printf("Titulo: %s, Ano de Lancamento: %s, Quantidade de Musicas: %d\n", R->titulo, R->anoDeLancamento, R->quantMusicas);
        imprimirAlbuns(R->Dir); 
    }
}

void imprimirAlbunsPorAno(Album* R, char* ano) {
    if (R != NULL) {
        imprimirAlbunsPorAno(R->Esq, ano); 
        if (strcmp(R->anoDeLancamento, ano) == 0) {
            printf("Titulo: %s, Ano de Lancamento: %s, Quantidade de Musicas: %d\n", R->titulo, R->anoDeLancamento, R->quantMusicas);
        }
        imprimirAlbunsPorAno(R->Dir, ano); 
    }
}

void liberarAlbuns(Album* raiz) {
    if (raiz != NULL) {
        liberarAlbuns(raiz->Esq);
        liberarAlbuns(raiz->Dir);
        liberarMusicas(raiz->musicas); 
        free(raiz);
    }
}

