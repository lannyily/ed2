#include <stdio.h>
#include <stdlib.h>
#include "../include/artista.h"
#include "../include/album.h"
#include "../include/musica.h"

int main() {
    Artista *raiz;
    raiz = NULL;
    //FIX: CONSERTAR SAPORRA DE CADASTRARARTISTA.
    // Cadastrando artistas
    cadastrarArtista(&raiz, "LinkinPark", "Solo", "Rock");
    cadastrarArtista(&raiz, "Cazuza", "Banda", "MPB");

    // Cadastrando álbuns para os artistas
    cadastrarAlbum(raiz, "Cazuza", "Ideologia", "1988");
    cadastrarAlbum(raiz, "Cazuza", "Exagerado", "1985");
    cadastrarAlbum(raiz, "LinkinPark", "Numb", "2005");

    // Imprimindo todos os artistas
    printf("\n=== Todos os Artistas ===\n");
    imprimirArtistas(raiz);

    // Imprimindo todos os álbuns de um artista
    printf("\n=== Albuns do Artista 'LinkinPark' ===\n");
    Artista* artista = NULL;
    buscaArtista(raiz, "LinkinPark", &artista);
    if (artista != NULL) {
        imprimirAlbuns(artista->albuns);
    } else {
        printf("Artista 'LinkinPark' nao encontrado.\n");
    }

    // Imprimindo álbuns de um ano específico de um artista
    printf("\n=== Albuns do Artista 'Cazuza' no ano de 1988 ===\n");
    if (artista != NULL) {
        imprimirAlbunsPorAno(artista->albuns, "1988");
    }

    // Imprimindo álbuns de um ano específico de todos os artistas
    printf("\n=== Albuns do ano de 2005 de todos os artistas ===\n");
    mostrarAlbunsPorAnoDeTodosArtistas(raiz, "2005");

    // Testando busca de álbum
    printf("\n=== Testando busca de album ===\n");
    Album* album = NULL;
    buscaAlbum(artista->albuns, "Ideologia", &album);
    if (album != NULL) {
        printf("Álbum encontrado: %s, Ano: %s, Quantidade de Músicas: %d\n", 
               album->titulo, album->anoDeLancamento, album->quantMusicas);
    } else {
        printf("Album 'Ideologia' nao encontrado.\n");
    }



    printf("\nPressione Enter para sair...\n");
    getchar();

    return 0;
}