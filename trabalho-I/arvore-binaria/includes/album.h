
typedef struct Artista Artista;

typedef struct Musica Musica;

typedef struct Album {
    char titulo[50];
    char anoDeLancamento[10];
    int quantMusicas; 
    Musica* musicas;

    struct Album* Esq;
    struct Album* Dir;
}Album;

Album* criarAlbum(char* titulo, char* anoLancamento);
int insereAlbum(Album** R, Album* No);
void cadastrarAlbum(Artista* raiz, char* nomeA, char* titulo, char* anoLancamento);
void buscaAlbum(Album* R, char* nome, Album** resultado);
void imprimirAlbuns(Album* R);
void imprimirAlbunsPorAno(Album* R, char* ano);
