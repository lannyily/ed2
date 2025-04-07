#ifndef ARTISTA_H
#define ARTISTA_H

typedef struct Album Album;

typedef struct Artista {
    char nome[10];
    char tipo[10];
    char estiloMusical[10];
    int numAlbuns;
    Album* albuns;

    struct Artista* Esq;
    struct Artista* Dir;
}Artista;

Artista* criarArtista(char* nome, char* tipo, char* estiloM);
int insereArtista(Artista** R, Artista* No);
void imprimirArtistas(Artista* R);
int comparaString(char* nomeBusca, char* nome);
int buscaArtista(Artista* R, char* nome);
void cadastrarArtista(Artista** raiz, char* nome, char* tipo, char* estilo);

#endif