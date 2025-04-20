#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"

Artista* criarArtista(char* nome, char* tipo, char* estiloM) {
    Artista* no = (Artista*)malloc(sizeof(Artista));

    strncpy(no->nome, nome, sizeof(no->nome) - 1);
    no->nome[sizeof(no->nome) - 1] = '\0'; // Garante que a string seja terminada corretamente
    strncpy(no->tipo, tipo, sizeof(no->tipo) - 1);
    no->tipo[sizeof(no->tipo) - 1] = '\0';
    strncpy(no->estiloMusical, estiloM, sizeof(no->estiloMusical) - 1);
    no->estiloMusical[sizeof(no->estiloMusical) - 1] = '\0';
    no->albuns = NULL;

    no->numAlbuns = 0;
    no->Esq = NULL;
    no->Dir = NULL;
    return no;
}

int insereArtista(Artista** raiz, Artista* novo) {
    if (*raiz == NULL) {
        *raiz = novo; // Insere o novo artista na posição correta
        return 1;
    }
    if (strcasecmp(novo->nome, (*raiz)->nome) < 0) {
        return insereArtista(&(*raiz)->Esq, novo); // Insere na subárvore esquerda
    } else if (strcasecmp(novo->nome, (*raiz)->nome) > 0) {
        return insereArtista(&(*raiz)->Dir, novo); // Insere na subárvore direita
    }
    return 0; // Artista já existe
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

int comparaString(const char* str1, const char* str2) {
    return strcmp(str1, str2) == 0;
}

void buscaArtista(Artista* R, const char* nome, Artista** resultado) {
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
    buscaArtista(*raiz, nome, &artista); // Resultado da busca armazenado em 'artista'

    if (artista != NULL) {
        printf("Artista \"%s\" já existe. Ignorando duplicata.\n", nome);
    } else {
        Artista* novo = criarArtista(nome, tipo, estilo);
        if (insereArtista(raiz, novo)) {
            printf("Artista \"%s\" cadastrado com sucesso.\n", nome);
        }
    }
}

void mostrarArtistasPorTipo(Artista* raiz, const char* tipo) {
    if (raiz != NULL) {
        mostrarArtistasPorTipo(raiz->Esq, tipo);
        if (strcmp(raiz->tipo, tipo) == 0) {
            printf("Artista: %s, Tipo: %s, Estilo: %s\n", raiz->nome, raiz->tipo, raiz->estiloMusical);
        }
        mostrarArtistasPorTipo(raiz->Dir, tipo);
    }
}

void mostrarArtistasPorEstilo(Artista* raiz, const char* estilo) {
    if (raiz != NULL) {
        mostrarArtistasPorEstilo(raiz->Esq, estilo);
        if (strcmp(raiz->estiloMusical, estilo) == 0) {
            printf("Artista: %s, Tipo: %s, Estilo: %s\n", raiz->nome, raiz->tipo, raiz->estiloMusical);
        }
        mostrarArtistasPorEstilo(raiz->Dir, estilo);
    }
}

void mostrarArtistasPorEstiloETipo(Artista* raiz, const char* estilo, const char* tipo) {
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
        printf("Albuns do artista %s:\n", artista->nome);
        imprimirAlbuns(artista->albuns);
    } else {
        printf("Artista %s nao encontrado.\n", nomeArtista);
    }
}

void mostrarAlbunsPorAnoDeArtista(Artista* raiz, char* nomeArtista, char* ano) {
    Artista* artista = NULL;
    buscaArtista(raiz, nomeArtista, &artista);

    if (artista != NULL) {
        printf("Albuns do artista %s no ano %s:\n", artista->nome, ano);
        imprimirAlbunsPorAno(artista->albuns, ano);
    } else {
        printf("Artista %s nao encontrado.\n", nomeArtista);
    }
}

void mostrarMusicasDeAlbum(Artista* raiz, char* nomeArtista, char* tituloAlbum) {
    Artista* artista = NULL;
    buscaArtista(raiz, nomeArtista, &artista);

    if (artista != NULL) {
        Album* album = NULL;
        buscaAlbum(artista->albuns, tituloAlbum, &album);

        if (album != NULL) {
            printf("Musicas do album %s do artista %s:\n", album->titulo, artista->nome);
            imprimirMusicas(album->musicas); 
        } else {
            printf("Album %s nao encontrado para o artista %s.\n", tituloAlbum, nomeArtista);
        }
    } else {
        printf("Artista %s nao encontrado.\n", nomeArtista);
    }
}

void mostrarAlbunsPorAnoDeTodosArtistas(Artista* raiz, const char* ano) {
    if (raiz != NULL) {
        mostrarAlbunsPorAnoDeTodosArtistas(raiz->Esq, ano);
        printf("Artista: %s\n", raiz->nome);
        imprimirAlbunsPorAno(raiz->albuns, (char*)ano);
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

