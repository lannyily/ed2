#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/album.h"
#include "../Includes/artista.h" 
#include "../Includes/musica.h"


int maiorAlbum(int x, int y) {
    if (x > y){
        return x;
    } else {
        return y;
    }
}

int pegaAlturaAlbum(Album* raiz){
    int altura = 0;
    if(raiz != NULL){
        int alturaEsq = pegaAlturaAlbum(raiz->Esq);
        int alturaDir = pegaAlturaAlbum(raiz->Dir);

        if(alturaEsq > alturaDir){
            altura = alturaEsq + 1;
        } else {
            altura = alturaDir + 1;
        }
    }
    return altura;
}

void rotacaoSimplesDireitaAlbum(Album** raiz){
    if((*raiz)->Esq != NULL){
        Album* aux = (*raiz)->Esq;
        (*raiz)->Esq = aux->Dir;
        aux->Dir = *raiz;
        (*raiz)->altura = maiorAlbum(pegaAlturaAlbum((*raiz)->Esq), pegaAlturaAlbum((*raiz)->Dir)) + 1;
        aux->altura = maiorAlbum(pegaAlturaAlbum(aux->Esq), (*raiz)->altura) + 1;
        (*raiz) = aux;
    }
}

void rotacaoSimplesEsquerdaAlbum(Album** raiz){
    if((*raiz)->Dir != NULL){
        Album* aux = (*raiz)->Dir;
        (*raiz)->Dir = aux->Esq;
        aux->Esq = *raiz;
        (*raiz)->altura = maiorAlbum(pegaAlturaAlbum((*raiz)->Esq), pegaAlturaAlbum((*raiz)->Dir)) + 1;
        aux->altura = maiorAlbum(pegaAlturaAlbum(aux->Dir), (*raiz)->altura) + 1;
        (*raiz) = aux;
    }
}

void rotacaoDuplaDireitaAlbum(Album** raiz){
    rotacaoSimplesEsquerdaAlbum(&(*raiz)->Esq);
    rotacaoSimplesDireitaAlbum(&(*raiz));
}

void rotacaoDuplaEsquerdaAlbum(Album** raiz){
    rotacaoSimplesDireitaAlbum(&(*raiz)->Dir);
    rotacaoSimplesEsquerdaAlbum(&(*raiz));
}

int alturaNoAlbum(Album* raiz){
    return raiz == NULL ? -1 : raiz->altura;
}

int fatorBalanceamentoAlbum(Album* raiz){
    int bl;
    bl = raiz != NULL ? abs(alturaNoAlbum(raiz->Esq) - alturaNoAlbum(raiz->Dir)) : 0;
    return bl;
}

void buscaAlbum(Album* R, const char* nome, Album** resultado) {
    
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

int insereAlbum(Album** R, Album* No, char* titulo) {
    int inseriu = 0;
    if (*R == NULL) {
        *R = No;
        inseriu = 1; // Inserção bem-sucedida
    } else {
        int comparacao = strcmp(No->titulo, (*R)->titulo);

        if (comparacao < 0) {
            if (inseriu = insereAlbum(&(*R)->Esq, No, titulo) == 1){ // Insere na subárvore esquerda
                if(fatorBalanceamentoAlbum(*R) >= 2){
                    if(strcmp((*R)->Esq->titulo, titulo) == 1){
                        rotacaoSimplesDireitaAlbum(&(*R));
                    }else {
                        rotacaoDuplaDireitaAlbum(&(*R));
                    }
                }
            } // Insere na subárvore esquerda
        } else if (comparacao > 0) {
            if (inseriu = insereAlbum(&(*R)->Dir, No, titulo) == 1){ // Insere na subárvore direita
                if(fatorBalanceamentoAlbum(*R) >= 2){
                    if(strcmp((*R)->Dir->titulo, titulo) == -1){
                        rotacaoSimplesEsquerdaAlbum(&(*R));
                    }else {
                        rotacaoDuplaEsquerdaAlbum(&(*R));
                    }
                }
            }  // Insere na subárvore direita
        }
        (*R)->altura = pegaAlturaAlbum((*R));
    }

    return inseriu; // Álbum já existe
}

void cadastrarAlbum(Artista* raiz, char* nomeA, char* titulo, char* anoLancamento) {
    Artista* artista = NULL;
    buscaArtista(raiz, nomeA, &artista); // Resultado da busca armazenado em 'artista'

    if (artista != NULL) {
        Album* album = NULL;
        buscaAlbum(artista->albuns, titulo, &album); // Resultado da busca armazenado em 'album'

        if (album == NULL) { // Se o álbum não foi encontrado
            Album* novoAlbum = criarAlbum(titulo, anoLancamento);
            if (insereAlbum(&(artista->albuns), novoAlbum, titulo)) {
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
        imprimirAlbuns(R->Esq); // Percorre a subárvore esquerda
        printf("Titulo: %s, Ano de Lancamento: %s, Quantidade de Musicas: %d\n", 
               R->titulo, R->anoDeLancamento, R->quantMusicas);
        imprimirAlbuns(R->Dir); // Percorre a subárvore direita
    }
}

void imprimirAlbunsPorAno(Album* R, char* ano) {
    if (R != NULL) {
        imprimirAlbunsPorAno(R->Esq, ano); // Percorre a subárvore esquerda
        if (strcmp(R->anoDeLancamento, ano) == 0) {
            printf("Titulo: %s, Ano de Lancamento: %s, Quantidade de Musicas: %d\n", 
                   R->titulo, R->anoDeLancamento, R->quantMusicas);
        }
        imprimirAlbunsPorAno(R->Dir, ano); // Percorre a subárvore direita
    }
}


void liberarAlbuns(Album* raiz) {
    if (raiz == NULL) return;
    liberarAlbuns(raiz->Esq);
    liberarAlbuns(raiz->Dir);
    free(raiz);
}