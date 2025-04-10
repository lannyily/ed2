
typedef struct Artista Artista;
typedef struct Album Album;

typedef struct Musica {
    char titulo[50];
    int quantMinutos;

    struct Musica* Esq;
    struct Musica* Dir;
}Musica;

Musica* criarMusica(char* titulo, int quantMinutos);
int insereMusica(Musica **R, Musica *No);
void CadastrarMusica(Album* raiz, char* nomeAlbum, char* titulo, int quantMinutos);
void imprimirMusicas(Musica* R);
void buscaMusica(Musica* R, char* titulo, Musica** resultado);
