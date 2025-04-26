#ifndef MUSICA_H
#define MUSICA_H

struct Artista;
struct Playlist;

typedef struct Musica {
    char titulo[50];
    int quantMinutos;
    struct Musica *Esq;
    struct Musica *Dir;
} Musica;

Musica* criarMusica(char* titulo, int quantMinutos);
int insereMusica(Musica **R, Musica *No);
void imprimirMusicas(Musica* R);
void buscarMusica(Musica* R, char* titulo, Musica** resultado);
void cadastrarMusica(struct Artista* raiz, char* nomeArtista, char* tituloAlbum, char* tituloMusica, int duracao);
int ehFilhoM(Musica* m);
Musica* souFilhoM(Musica* m);
Musica* enderecoMenorEsqM(Musica* m);
int removerMusica(Musica** raiz, char* titulo);
int musicaEmPlaylists(struct Playlist* raiz, char* titulo);
void removerMusicaDeAlbum(struct Artista* raiz, struct Playlist* playlists, char* nomeArtista, char* tituloAlbum, char* tituloMusica);
void liberarMusicas(Musica* raiz);

#endif 