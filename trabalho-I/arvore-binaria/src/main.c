#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"
#include "../Includes/playlist.h"

int main() {
    Artista *raiz = NULL;
    Playlist *raizPlaylist = NULL;

    int opcao;

    do {
        printf("-------------------- MENU --------------------\n");
        printf(" 1 - Cadastrar Artista\n");
        printf(" 2 - Cadastrar Albuns\n");
        printf(" 3 - Cadastrar Musicas\n");
        printf(" 4 - Mostrar todos os artistas\n");
        printf(" 5 - Mostrar todos os artistas de um tipo\n");
        printf(" 6 - Mostrar todos os artistas de um estilo musical\n");
        printf(" 7 - Mostrar todos os artistas de um estilo musical e tipo de artista\n");
        printf(" 8 - Mostrar todos os albuns de um artista\n");
        printf(" 9 - Mostrar todos os albuns de um ano e artista\n");
        printf("10 - Mostrar todas as musicas de um album e artista\n");
        printf("11 - Mostrar todos os albuns de um ano de todos os artistas\n");
        printf("12 - Mostrar os dados de uma determinada Musica\n");
        printf("13 - Mostrar dados de uma playlist\n");
        printf("14 - Remover música de uma playlist\n");
        printf("15 - Remover uma playlist\n");
        printf("16 - Remover música de um álbum de um artista\n");
        printf(" 0 - SAIR\n");
        printf("----------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao) {
            case 1: {
                printf("\n=== Cadastrar Artista ===\n");
                char nome[100], tipo[50], estilo[50];
                printf("Digite o nome do artista: ");
                scanf(" %[^\n]", nome);
                printf("Digite o tipo do artista (Solo/Banda): ");
                scanf(" %[^\n]", tipo);
                printf("Digite o estilo musical: ");
                scanf(" %[^\n]", estilo);
                cadastrarArtista(&raiz, nome, tipo, estilo);
                break;
            }
            case 2: {
                printf("\n=== Cadastrar Album ===\n");
                char nomeArtista[100], tituloAlbum[100], ano[10];
                printf("Digite o nome do artista: ");
                scanf(" %[^\n]", nomeArtista);
                printf("Digite o título do álbum: ");
                scanf(" %[^\n]", tituloAlbum);
                printf("Digite o ano de lançamento: ");
                scanf(" %[^\n]", ano);
                cadastrarAlbum(raiz, nomeArtista, tituloAlbum, ano);
                break;
            }
            case 3: {
                printf("\n=== Cadastrar Música ===\n");
                char nomeArtista[100], tituloAlbum[100], tituloMusica[100];
                int duracao;
                printf("Digite o nome do artista: ");
                scanf(" %[^\n]", nomeArtista);
                printf("Digite o título do álbum: ");
                scanf(" %[^\n]", tituloAlbum);
                printf("Digite o título da música: ");
                scanf(" %[^\n]", tituloMusica);
                printf("Digite a duração da música (em minutos): ");
                scanf("%d", &duracao);
                cadastrarMusica(raiz, nomeArtista, tituloAlbum, tituloMusica, duracao);
                break;
            }
            case 4: {
                printf("\n=== Todos os Artistas ===\n");
                imprimirArtistas(raiz);
                break;
            }
            case 5: {
                printf("\n=== Mostrar Artistas por Tipo ===\n");
                char tipo[50];
                printf("Digite o tipo de artista (Solo/Banda): ");
                scanf(" %[^\n]", tipo);
                mostrarArtistasPorTipo(raiz, tipo);
                break;
            }
            case 6: {
                printf("\n=== Mostrar Artistas por Estilo ===\n");
                char estilo[50];
                printf("Digite o estilo musical: ");
                scanf(" %[^\n]", estilo);
                mostrarArtistasPorEstilo(raiz, estilo);
                break;
            }
            case 7: {
                printf("\n=== Mostrar Artistas por Estilo e Tipo ===\n");
                char estilo[50], tipo[50];
                printf("Digite o estilo musical: ");
                scanf(" %[^\n]", estilo);
                printf("Digite o tipo de artista (Solo/Banda): ");
                scanf(" %[^\n]", tipo);
                mostrarArtistasPorEstiloETipo(raiz, estilo, tipo);
                break;
            }
            case 8: {
                printf("\n=== Mostrar Albuns de um Artista ===\n");
                char nomeArtista[100];
                printf("Digite o nome do artista: ");
                scanf(" %[^\n]", nomeArtista);
                Artista *artista = NULL;
                buscaArtista(raiz, nomeArtista, &artista);
                if (artista != NULL) {
                    imprimirAlbuns(artista->albuns);
                } else {
                    printf("Artista \"%s\" não encontrado.\n", nomeArtista);
                }
                break;
            }
            case 9: {
                printf("\n=== Mostrar Albuns de um Ano e Artista ===\n");
                char nomeArtista[100], ano[10];
                printf("Digite o nome do artista: ");
                scanf(" %[^\n]", nomeArtista);
                printf("Digite o ano: ");
                scanf(" %[^\n]", ano);
                Artista *artista = NULL;
                buscaArtista(raiz, nomeArtista, &artista);
                if (artista != NULL) {
                    imprimirAlbunsPorAno(artista->albuns, ano);
                } else {
                    printf("Artista \"%s\" não encontrado.\n", nomeArtista);
                }
                break;
            }
            case 10: {
                printf("\n=== Mostrar Músicas de um Album e Artista ===\n");
                char nomeArtista[100], tituloAlbum[100];
                printf("Digite o nome do artista: ");
                scanf(" %[^\n]", nomeArtista);
                printf("Digite o título do álbum: ");
                scanf(" %[^\n]", tituloAlbum);
                mostrarMusicasDeAlbum(raiz, nomeArtista, tituloAlbum);
                break;
            }
            case 11: {
                printf("\n=== Mostrar Albuns de um Ano de Todos os Artistas ===\n");
                char ano[10];
                printf("Digite o ano: ");
                scanf(" %[^\n]", ano);
                mostrarAlbunsPorAnoDeTodosArtistas(raiz, ano);
                break;
            }
            case 12: {
                printf("\n=== Mostrar Dados de uma Música ===\n");
                char tituloMusica[100];
                printf("Digite o título da música: ");
                scanf(" %[^\n]", tituloMusica);
                mostrarDadosDeMusica(raiz, tituloMusica);
                break;
            }
            case 13: {
                printf("\n=== Mostrar Dados de uma Playlist ===\n");
                char nomePlaylist[100];
                printf("Digite o nome da playlist: ");
                scanf(" %[^\n]", nomePlaylist);
                Playlist *playlist = buscarPlaylist(raizPlaylist, nomePlaylist);
                if (playlist != NULL) {
                    imprimirPlaylist(playlist);
                } else {
                    printf("Playlist \"%s\" não encontrada.\n", nomePlaylist);
                }
                break;
            }
            case 14: {
                printf("\n=== Remover Música de uma Playlist ===\n");
                char nomePlaylist[100], tituloMusica[100];
                printf("Digite o nome da playlist: ");
                scanf(" %[^\n]", nomePlaylist);
                printf("Digite o título da música: ");
                scanf(" %[^\n]", tituloMusica);
                Playlist *playlist = buscarPlaylist(raizPlaylist, nomePlaylist);
                if (playlist != NULL) {
                    playlist->musicas = removerMusica(playlist->musicas, tituloMusica);
                } else {
                    printf("Playlist \"%s\" não encontrada.\n", nomePlaylist);
                }
                break;
            }
            case 15: {
                printf("\n=== Remover uma Playlist ===\n");
                char nomePlaylist[100];
                printf("Digite o nome da playlist: ");
                scanf(" %[^\n]", nomePlaylist);
                raizPlaylist = removerPlaylist(raizPlaylist, nomePlaylist);
                break;
            }
            case 16: {
                printf("\n=== Remover Música de um Álbum de um Artista ===\n");
                char nomeArtista[100], tituloAlbum[100], tituloMusica[100];
                printf("Digite o nome do artista: ");
                scanf(" %[^\n]", nomeArtista);
                printf("Digite o título do álbum: ");
                scanf(" %[^\n]", tituloAlbum);
                printf("Digite o título da música: ");
                scanf(" %[^\n]", tituloMusica);
                removerMusicaDeAlbum(raiz, raizPlaylist, nomeArtista, tituloAlbum, tituloMusica);
                break;
            }
            case 0:
                printf("Saindo do programa...\n");
                exit(0);
                break;
            default:
                printf("Opção inválida, tente novamente!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}