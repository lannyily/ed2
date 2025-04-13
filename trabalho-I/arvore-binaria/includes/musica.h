#ifndef MUSICA_H
#define MUSICA_H

// Declarações antecipadas
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
Musica* buscarMusica(Musica* R, const char* titulo);
Musica* removerMusica(Musica *raiz, const char *titulo);
void liberarMusicas(Musica *raiz);
int musicaEmPlaylists(struct Playlist* raiz, const char* titulo);
void cadastrarMusica(struct Artista* raiz, const char* nomeArtista, const char* tituloAlbum, const char* tituloMusica, int duracao);
void removerMusicaDeAlbum(struct Artista* raiz, struct Playlist* playlists, const char* nomeArtista, const char* tituloAlbum, const char* tituloMusica);

#endif // MUSICA_H