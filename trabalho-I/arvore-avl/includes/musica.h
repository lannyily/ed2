#ifndef MUSICA_H
#define MUSICA_H

struct Artista;
struct Playlist;

typedef struct Musica {
    char titulo[50];
    int quantMinutos;

    int altura;

    struct Musica *Esq;
    struct Musica *Dir;
} Musica;

void rotacaoEsqM(Musica** raiz);
void rotacaoDirM(Musica** raiz);
int maiorM(int alt1, int alt2);
int alturaNoM(Musica* no);
int fatorBalanceamentoM(Musica* raiz);
void balanceamentoM(Musica** raiz);
Musica* criarMusica(char* titulo, int quantMinutos);
int insereMusica(Musica **R, Musica *No);
void imprimirMusicas(Musica* R);
void buscarMusica(Musica* R, char* titulo, Musica** resultado);
void cadastrarMusica(struct Artista* raiz, char* nomeArtista, char* tituloAlbum, char* tituloMusica, int duracao);
void removerMusicaDeAlbum(struct Artista* raiz, struct Playlist* playlists, char* nomeArtista, char* tituloAlbum, char* tituloMusica);
int ehFilhoM(Musica* m);
Musica* souFilhoM(Musica* m);
Musica* enderecoMenorEsqM(Musica* m);
int removerMusica(Musica** raiz, char* titulo);
int musicaEmPlaylists(struct Playlist* raiz, char* titulo);
void liberarMusicas(Musica* raiz);

#endif 