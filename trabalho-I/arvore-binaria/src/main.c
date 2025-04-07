#include <stdio.h>
#include <stdlib.h>
#include "../include/artista.h"
#include "../include/album.h"
#include "artista.c"

int main() {
    Artista* raiz = NULL;
    raiz = NULL;
    
    cadastrarArtista(&raiz, "Dami Lovato", "Solo", "Pop");
    cadastrarArtista(&raiz, "Dami Lovato", "Banda", "Rock");
    cadastrarArtista(&raiz, "Cazuza", "Solo", "MPB");

    cadastrarAlbum(raiz, "Cazuza", "Ideologia", "1988");
    cadastrarAlbum(raiz, "Cazuza", "Exagerado", "1985");

    imprimirArtistas(raiz);

    return 0;
}