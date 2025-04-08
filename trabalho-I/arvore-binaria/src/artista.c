#include "../include/artista.h"
#include "../include/album.h"
#include "../include/musica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Artista* criarArtista(char* nome, char* tipo, char* estiloM) {
    Artista* no = (Artista*)malloc(sizeof(Artista));

    strncpy(no->nome, nome, sizeof(no->nome) - 1);
    no->nome[sizeof(no->nome) - 1] = '\0'; // Garante que a string seja terminada corretamente
    strncpy(no->tipo, tipo, sizeof(no->tipo) - 1);
    no->tipo[sizeof(no->tipo) - 1] = '\0';
    strncpy(no->estiloMusical, estiloM, sizeof(no->estiloMusical) - 1);
    no->estiloMusical[sizeof(no->estiloMusical) - 1] = '\0';

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

int comparaString(char* nomeBusca, char* nome){
    if (*nomeBusca != 0) {                                                    
        if (*nome == 0) return 0;                                            
        if (*nomeBusca == *nome) return comparaString(++nomeBusca, ++nome); 
        return 0;                                                            
    } else {
        return (*nome == 0); // ambas terminaram juntas? são iguais
    }
}

void buscaArtista(Artista* R, char* nome, Artista** resultado) {
    *resultado = NULL; // Inicializa o resultado como NULL

    if (R != NULL) {
        if (comparaString(R->nome, nome)) { // Compara os nomes usando comparaString
            *resultado = R; // Encontrou o artista
        } else if (strcmp(nome, R->nome) < 0) {
            buscaArtista(R->Esq, nome, resultado); // Continua na subárvore esquerda
        } else {
            buscaArtista(R->Dir, nome, resultado); // Continua na subárvore direita
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

void mostrarArtistasPorTipo(Artista* R, char* tipo) {
    if (R != NULL) {
        mostrarArtistasPorTipo(R->Esq, tipo);
        if (strcmp(R->tipo, tipo) == 0) {
            printf("Nome: %s, Tipo: %s, Estilo: %s, Albuns: %d\n", R->nome, R->tipo, R->estiloMusical, R->numAlbuns);
        }
        mostrarArtistasPorTipo(R->Dir, tipo);
    }
}

void mostrarArtistasPorEstilo(Artista* R, char* estilo) {
    if (R != NULL) {
        mostrarArtistasPorEstilo(R->Esq, estilo);
        if (strcmp(R->estiloMusical, estilo) == 0) {
            printf("Nome: %s, Tipo: %s, Estilo: %s, Albuns: %d\n", R->nome, R->tipo, R->estiloMusical, R->numAlbuns);
        }
        mostrarArtistasPorEstilo(R->Dir, estilo);
    }
}

void mostrarArtistasPorEstiloETipo(Artista* R, char* estilo, char* tipo) {
    if (R != NULL) {
        mostrarArtistasPorEstiloETipo(R->Esq, estilo, tipo);
        if (strcmp(R->estiloMusical, estilo) == 0 && strcmp(R->tipo, tipo) == 0) {
            printf("Nome: %s, Tipo: %s, Estilo: %s, Albuns: %d\n", R->nome, R->tipo, R->estiloMusical, R->numAlbuns);
        }
        mostrarArtistasPorEstiloETipo(R->Dir, estilo, tipo);
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

void mostrarAlbunsPorAnoDeTodosArtistas(Artista* R, char* ano) {
    if (R != NULL) {
        mostrarAlbunsPorAnoDeTodosArtistas(R->Esq, ano);
        printf("Albuns do artista %s no ano %s:\n", R->nome, ano);
        imprimirAlbunsPorAno(R->albuns, ano); 
        mostrarAlbunsPorAnoDeTodosArtistas(R->Dir, ano);
    }
}

void mostrarDadosDeMusica(Artista* raiz, char* tituloMusica) {
    if (raiz != NULL) {
        mostrarDadosDeMusica(raiz->Esq, tituloMusica);

        Album* albumAtual = raiz->albuns;
        while (albumAtual != NULL) {
            Musica* musica = NULL;
            buscaMusica(albumAtual->musicas, tituloMusica, &musica); 

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

