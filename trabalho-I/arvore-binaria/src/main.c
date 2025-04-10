#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"

int main() {
    Artista *raiz = NULL;
    Artista* artista = NULL;
    Album* album = NULL;

    int opcao;

    do
    {
        printf("-------------------- MENU --------------------\n");
        printf(" 1 - Cadastrar Artista\n");
        printf(" 2 - Cadastrar Albuns\n");
        printf(" 3 - Cadastrar Musicas\n");
        printf(" 4 - Mostrar todos os  artistas\n");
        printf(" 5 - Mostrar todos os artistas de um tipo\n");
        printf(" 6 - Mostrar todos os artistas de um estilo musical\n");
        printf(" 7 - Mostrar todos os artistas de um estilo musical\n     e tipo de artista\n");
        printf(" 8 - Mostrar todos os albuns de um artista\n");
        printf(" 9 - Mostrar todos os albuns de um ano e artista\n");
        printf("10 - Mostrar todas as musicas de um album e artista\n");
        printf("11 - Mostrar todos os albuns de um ano de todos os\n     artistas\n");
        printf("12 - Mostrar os dados de uma determinada Musica\n");
        printf(" 0 - SAIR\n");
        printf("----------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao) {
            case 1:{
                cadastrarArtista(&raiz, "LinkinPark", "Solo", "Rock");
                cadastrarArtista(&raiz, "Cazuza", "Banda", "MPB");
                break;
            }
            case 2:{
                cadastrarAlbum(raiz, "Cazuza", "Ideologia", "1988");
                cadastrarAlbum(raiz, "Cazuza", "Exagerado", "1985");
                cadastrarAlbum(raiz, "LinkinPark", "Numb", "2005");
                break;
            }
            case 3: {
                
                break;
            }
            case 4: {
                printf("\n=== Todos os Artistas ===\n");
                imprimirArtistas(raiz);
                break;;
            }
            case 5: {
                
                break;;
            }
            case 6: {

                break;;
            }
            case 7: {

                break;;
            }
            case 8: {
                printf("\n=== Albuns do Artista 'LinkinPark' ===\n");
                buscaArtista(raiz, "LinkinPark", &artista);
                if (artista != NULL) {
                    imprimirAlbuns(artista->albuns);
                } else {
                    printf("Artista 'LinkinPark' nao encontrado.\n");
                }
                break;;
            }
            case 9: {
                printf("\n=== Albuns do Artista 'Cazuza' no ano de 1988 ===\n");
                buscaArtista(raiz, "Cazuza", &artista);
                if (artista != NULL) {
                    imprimirAlbunsPorAno(artista->albuns, "1988");
                }
                break;;
            }
            case 10: {

                break;;
            }
            case 11: {
                printf("\n=== Albuns do ano de 2005 de todos os artistas ===\n");
                mostrarAlbunsPorAnoDeTodosArtistas(raiz, "2005");
                break;;
            }
            case 12: {

                break;;
            }
            case 0:
                exit(0);
                break;
            default:
                printf("Opcao invalida, tente novamente!\n");
                break;
            }
        
    } while (opcao != 0);

    return 0;
}