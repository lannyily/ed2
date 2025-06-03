#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/album.h"
#include "../Includes/artista.h" 
#include "../Includes/musica.h"

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
            inseriu = insereAlbum(&((*R)->Esq), No); 
        } else if (comparacao > 0) {
            inseriu = insereAlbum(&((*R)->Dir), No); 
        } else {
            inseriu = 0;
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

