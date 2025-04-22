#ifndef MUSICA_H
#define MUSICA_H

// Declarações antecipadas
struct Artista;
struct Playlist;

typedef struct Musica {
    char titulo[50];
    int quantMinutos;
    int altura;
    struct Musica *Esq;
    struct Musica *Dir;
} Musica;

int maiorMusica(int x, int y);
int pegaAlturaMusica(Musica* raiz);
void rotacaoSimplesDireitaMusica(Musica** raiz);
void rotacaoSimplesEsquerdaMusica(Musica** raiz);
void rotacaoDuplaDireitaMusica(Musica** raiz);
void rotacaoDuplaEsquerdaMusica(Musica** raiz);
int alturaNoMusica(Musica* raiz);
int fatorBalanceamentoMusica(Musica* raiz);
Musica* criarMusica(char* titulo, int quantMinutos);
int insereMusica(Musica** R, Musica* No, const char* tituloMusica);
void imprimirMusicas(Musica* R);
void buscarMusica(Musica* R, const char* titulo, Musica** resultado);
void cadastrarMusica(struct Artista* raiz, const char* nomeArtista, const char* tituloAlbum, const char* tituloMusica, int duracao);
Musica* removerMusica(Musica *raiz, const char *titulo);
int musicaEmPlaylists(struct Playlist* raiz, const char* titulo);
void removerMusicaDeAlbum(struct Artista* raiz, struct Playlist* playlists, const char* nomeArtista, const char* tituloAlbum, const char* tituloMusica);

#endif // MUSICA_H