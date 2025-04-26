#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"

Artista* criarArtista(char* nome, char* tipo, char* estiloM) {
    Artista* no = (Artista*)malloc(sizeof(Artista));

    strcpy(no->nome, nome);
    strcpy(no->tipo, tipo);
    strcpy(no->estiloMusical, estiloM);
    no->albuns = NULL;

    no->numAlbuns = 0;
    no->Esq = NULL;
    no->Dir = NULL;
    return no;
}

int insereArtista(Artista** raiz, Artista* novo) {
    int inseriu = 1;

    if (*raiz == NULL) {
        *raiz = novo; 
        
    } else {
        int comparacao = strcasecmp(novo->nome, (*raiz)->nome);
        if (comparacao < 0) {
            inseriu = insereArtista(&(*raiz)->Esq, novo); 
        } else if (comparacao > 0) {
            inseriu = insereArtista(&(*raiz)->Dir, novo); 
        }
    }
    
    return inseriu; 
}

void imprimirArtistas(Artista* R) {
    if (R != NULL) {
        imprimirArtistas(R->Esq);
        printf("-------------------------------------------------------------\n");
        printf("%-15s %-10s %-15s %-5s\n", "Nome", "Tipo", "Estilo", "Albuns");
        printf("%-15s  %-10s  %-15s %-5d\n", R->nome, R->tipo, R->estiloMusical, R->numAlbuns);
        printf("-------------------------------------------------------------\n");
        imprimirArtistas(R->Dir);
    }
}

void buscaArtista(Artista* R,  char* nome, Artista** resultado) {
    *resultado = NULL;

    if (R != NULL) {
        if (strcmp(R->nome, nome) == 0) {
            *resultado = R;
        } else if (strcmp(nome, R->nome) < 0) {
            buscaArtista(R->Esq, nome, resultado);
        } else {
            buscaArtista(R->Dir, nome, resultado);
        }
    }
}

void cadastrarArtista(Artista** raiz, char* nome, char* tipo, char* estilo) {
    Artista* artista = NULL;
    buscaArtista(*raiz, nome, &artista); 

    if (artista != NULL) {
        printf("Artista \"%s\" ja existe!\n", nome);
    } else {
        Artista* novo = criarArtista(nome, tipo, estilo);
        if (insereArtista(raiz, novo)) {
            printf("Artista \"%s\" cadastrado com sucesso!\n", nome);
        }
    }
}

void mostrarArtistasPorTipo(Artista* raiz,  char* tipo) {
    if (raiz != NULL) {
        mostrarArtistasPorTipo(raiz->Esq, tipo);
        if (strcmp(raiz->tipo, tipo) == 0) {
            printf("Artista: %s, Tipo: %s, Estilo: %s\n", raiz->nome, raiz->tipo, raiz->estiloMusical);
        }
        mostrarArtistasPorTipo(raiz->Dir, tipo);
    }
}

void mostrarArtistasPorEstilo(Artista* raiz,  char* estilo) {
    if (raiz != NULL) {
        mostrarArtistasPorEstilo(raiz->Esq, estilo);
        if (strcmp(raiz->estiloMusical, estilo) == 0) {
            printf("Artista: %s, Tipo: %s, Estilo: %s\n", raiz->nome, raiz->tipo, raiz->estiloMusical);
        }
        mostrarArtistasPorEstilo(raiz->Dir, estilo);
    }
}

void mostrarArtistasPorEstiloETipo(Artista* raiz,  char* estilo,  char* tipo) {
    if (raiz != NULL) {
        mostrarArtistasPorEstiloETipo(raiz->Esq, estilo, tipo);
        if (strcmp(raiz->estiloMusical, estilo) == 0 && strcmp(raiz->tipo, tipo) == 0) {
            printf("Artista: %s, Tipo: %s, Estilo: %s\n", raiz->nome, raiz->tipo, raiz->estiloMusical);
        }
        mostrarArtistasPorEstiloETipo(raiz->Dir, estilo, tipo);
    }
}

void mostrarAlbunsDeArtista(Artista* raiz, char* nomeArtista) {
    Artista* artista = NULL;
    buscaArtista(raiz, nomeArtista, &artista);

    if (artista != NULL) {
        printf("Albuns do artista \"%s\":\n", artista->nome);
        imprimirAlbuns(artista->albuns);
    } else {
        printf("Artista \"%s\" nao encontrado!\n", nomeArtista);
    }
}

void mostrarAlbunsPorAnoDeArtista(Artista* raiz, char* nomeArtista, char* ano) {
    Artista* artista = NULL;
    buscaArtista(raiz, nomeArtista, &artista);

    if (artista != NULL) {
        printf("Albuns do artista \"%s\" no ano \"%s\":\n", artista->nome, ano);
        imprimirAlbunsPorAno(artista->albuns, ano);
    } else {
        printf("Artista \"%s\" nao encontrado!\n", nomeArtista);
    }
}

void mostrarMusicasDeAlbum(Artista* raiz, char* nomeArtista, char* tituloAlbum) {
    Artista* artista = NULL;
    buscaArtista(raiz, nomeArtista, &artista);

    if (artista != NULL) {
        Album* album = NULL;
        buscaAlbum(artista->albuns, tituloAlbum, &album);

        if (album != NULL) {
            printf("Musicas do album \"%s\" do artista \"%s\":\n", album->titulo, artista->nome);
            imprimirMusicas(album->musicas); 
        } else {
            printf("Album \"%s\" nao encontrado para o artista \"%s\"!\n", tituloAlbum, nomeArtista);
        }
    } else {
        printf("Artista \"%s\" nao encontrado.\n", nomeArtista);
    }
}

int temAlbumDoAno(Album* raiz,  char* ano) {
    return raiz != NULL && (
        strcmp(raiz->anoDeLancamento, ano) == 0 ||
        temAlbumDoAno(raiz->Esq, ano) ||
        temAlbumDoAno(raiz->Dir, ano)
    );
}

void mostrarAlbunsPorAnoDeTodosArtistas(Artista* raiz,  char* ano) {
    if (raiz != NULL) {
        mostrarAlbunsPorAnoDeTodosArtistas(raiz->Esq, ano);

        if (temAlbumDoAno(raiz->albuns, ano)) {
            printf("Artista: \"%s\"\n", raiz->nome);
            imprimirAlbunsPorAno(raiz->albuns, (char*)ano);
        }

        mostrarAlbunsPorAnoDeTodosArtistas(raiz->Dir, ano);
    }
}

void mostrarDadosDeMusica(Artista* raiz, char* tituloMusica) {
    if (raiz != NULL) {
        mostrarDadosDeMusica(raiz->Esq, tituloMusica);

        Album* albumAtual = raiz->albuns;
        while (albumAtual != NULL) {
            Musica* musica = NULL;
            buscarMusica(albumAtual->musicas, tituloMusica, &musica); 

            if (musica != NULL) {
                printf("Musica: %s\n", musica->titulo);
                printf("Artista: %s\n", raiz->nome);
                printf("Album: %s\n", albumAtual->titulo);
                printf("Ano de Lançamento: %s\n", albumAtual->anoDeLancamento);
                return;
            }

            albumAtual = albumAtual->Dir;
        }

        mostrarDadosDeMusica(raiz->Dir, tituloMusica);
    }
}

void mostrarMusicas(Musica* raiz) {
    if (raiz == NULL) return;

    mostrarMusicas(raiz->Esq);
    printf("    Música: %s (%d min)\n", raiz->titulo, raiz->quantMinutos);
    mostrarMusicas(raiz->Dir);
}

void mostrarAlbuns(Album* raiz) {
    if (raiz == NULL) return;

    mostrarAlbuns(raiz->Esq);
    printf("  Álbum: %s (%s)\n", raiz->titulo, raiz->anoDeLancamento);
    mostrarMusicas(raiz->musicas);
    mostrarAlbuns(raiz->Dir);
}


void mostrarMusicasDoArtista(Artista* raiz,  char* nomeArtista) {
    if (raiz != NULL) {
        int cmp = strcmp(nomeArtista, raiz->nome);
        if (cmp < 0) {
            mostrarMusicasDoArtista(raiz->Esq, nomeArtista);
        } else if (cmp > 0) {
            mostrarMusicasDoArtista(raiz->Dir, nomeArtista);
        } else {
            
            printf("Musicas do artista: %s\n", raiz->nome);
            mostrarAlbuns(raiz->albuns);
        }
        
    } else{
        printf("Artista \"%s\" nao encontrado.\n", nomeArtista);
    }
    
}


void liberarArtistas(Artista* raiz) {
    if (raiz != NULL) {
        liberarArtistas(raiz->Esq);
        liberarArtistas(raiz->Dir);
        liberarAlbuns(raiz->albuns); 
        free(raiz);
    }
}
