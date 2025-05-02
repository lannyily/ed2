#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"
#include "../Includes/playlist.h"
#include "../Includes/teste.h"
#include "../includes/musicasPlaylist.h"

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
        printf("13 - Criar uma playlist\n");
        printf("14 - Inserir musicas em uma playlist\n");
        printf("15 - Mostrar dados de uma playlist\n");
        printf("16 - Remover musica de uma playlist\n");
        printf("17 - Remover uma playlist\n");
        printf("18 - Remover musica de um album de um artista\n");
        printf("19 - Teste de Tempo\n");
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
                /*
                cadastrarArtista(&raiz, "Legiao Urbana", "Banda", "Rock");
                cadastrarArtista(&raiz, "Anitta", "Solo", "Pop");
                cadastrarArtista(&raiz, "Chico Buarque", "Solo", "MPB");
                cadastrarArtista(&raiz, "Os Baroes da Pisadinha", "Banda", "Forro");
                cadastrarArtista(&raiz, "Ludmilla", "Solo", "Funk");
                cadastrarArtista(&raiz, "Skank", "Banda", "Pop Rock");
                cadastrarArtista(&raiz, "Ivete Sangalo", "Solo", "Axe");
                cadastrarArtista(&raiz, "Tribalistas", "Banda", "MPB");
                cadastrarArtista(&raiz, "Marilia Mendonca", "Solo", "Sertanejo");
                cadastrarArtista(&raiz, "Mamonas Assassinas", "Banda", "Rock Comico");
                */
                break;
            }
            case 2: {
                printf("\n=== Cadastrar Album ===\n");
                
                char nomeArtista[100], tituloAlbum[100], ano[10];
                printf("Digite o nome do artista: ");
                scanf(" %[^\n]", nomeArtista);
                printf("Digite o titulo do álbum: ");
                scanf(" %[^\n]", tituloAlbum);
                printf("Digite o ano de lancamento: ");
                scanf(" %[^\n]", ano);
                cadastrarAlbum(raiz, nomeArtista, tituloAlbum, ano);
                /*
                cadastrarAlbum(raiz, "Legiao Urbana", "Dois", "1986");
                cadastrarAlbum(raiz, "Anitta", "Kisses", "2019");
                cadastrarAlbum(raiz, "Chico Buarque", "Construcao", "1971");
                cadastrarAlbum(raiz, "Os Baroes da Pisadinha", "Conquistas", "2020");
                cadastrarAlbum(raiz, "Ludmilla", "Numanice #2", "2022");
                cadastrarAlbum(raiz, "Skank", "Calango", "1994");
                cadastrarAlbum(raiz, "Ivete Sangalo", "Festa", "2001");
                cadastrarAlbum(raiz, "Tribalistas", "Tribalistas", "2002");
                cadastrarAlbum(raiz, "Marilia Mendonca", "Todos os Cantos", "2019");
                cadastrarAlbum(raiz, "Mamonas Assassinas", "Mamonas Assassinas", "1995");
                */
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
                /*
                cadastrarMusica(raiz, "Legiao Urbana", "Dois", "Tempo Perdido", 5);
                cadastrarMusica(raiz, "Anitta", "Kisses", "Poquito", 3);
                cadastrarMusica(raiz, "Anitta", "Kisses", "teste", 3);
                cadastrarMusica(raiz, "Chico Buarque", "Construcao", "Construcao", 6);
                cadastrarMusica(raiz, "Os Baroes da Pisadinha", "Conquistas", "Basta Voce Me Ligar", 3);
                cadastrarMusica(raiz, "Ludmilla", "Numanice #2", "Maldivas", 4);
                cadastrarMusica(raiz, "Skank", "Calango", "Te Ver", 3);
                cadastrarMusica(raiz, "Ivete Sangalo", "Festa", "Festa", 4);
                cadastrarMusica(raiz, "Tribalistas", "Tribalistas", "Velha Infancia", 5);
                cadastrarMusica(raiz, "Marilia Mendonca", "Todos os Cantos", "Supera", 4);
                cadastrarMusica(raiz, "Mamonas Assassinas", "Mamonas Assassinas", "Pelados em Santos", 3);
                */
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
                    printf("Artista \"%s\" nao encontrado.\n", nomeArtista);
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
                    printf("Artista \"%s\" nao encontrado.\n", nomeArtista);
                }
                break;
            }
            case 10: {
                printf("\n=== Mostrar Musicas de um Album e Artista ===\n");
                char nomeArtista[100], tituloAlbum[100];
                printf("Digite o nome do artista: ");
                scanf(" %[^\n]", nomeArtista);
                printf("Digite o titulo do album: ");
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
                printf("\n=== Mostrar Dados de uma Musica ===\n");
                char tituloMusica[100];
                printf("Digite o titulo da musica: ");
                scanf(" %[^\n]", tituloMusica);
                mostrarDadosDeMusica(raiz, tituloMusica);
                break;
            }
            case 13: {
                
                printf("\n=== Criar Playlist ===\n");
                char playlistNome[100];
                printf("Digite o nome da playlist: ");
                scanf(" %[^\n]", playlistNome);
                cadastrarPlaylist(&raizPlaylist, playlistNome);
                
                /*
                cadastrarPlaylist(&raizPlaylist, "rock");
                cadastrarPlaylist(&raizPlaylist, "pop");
                cadastrarPlaylist(&raizPlaylist, "mpb");
                cadastrarPlaylist(&raizPlaylist, "sertanejo");
                cadastrarPlaylist(&raizPlaylist, "engracadas");
                */
                break;
            }
            case 14: {
                
                printf("\n=== Inserir musica em uma Playlist ===\n");
                char playlist[100];
                printf("Digite o nome da playlist: ");
                scanf(" %[^\n]", playlist);
            
                char nomeArtista[100], tituloAlbum[100], tituloMusica[100];

                printf("Digite o nome do artista: ");
                scanf(" %[^\n]", nomeArtista);
                printf("Digite o título do álbum: ");
                scanf(" %[^\n]", tituloAlbum);
                printf("Digite o título da musica: ");
                scanf(" %[^\n]", tituloMusica);

                Artista* encontrarArtista;
                buscaArtista(raiz, nomeArtista, &encontrarArtista);

                if (encontrarArtista != NULL){
                    Album* encontrarAlbum;
                    buscaAlbum(encontrarArtista->albuns, tituloAlbum, &encontrarAlbum);
                    if (encontrarAlbum != NULL){
                        Musica* encontrarMusica;
                        buscarMusica(encontrarAlbum->musicas, tituloMusica, &encontrarMusica);
                        if (encontrarMusica != NULL){
                            cadastrarMusicasPlaylist(raizPlaylist, playlist, encontrarArtista->nome, encontrarAlbum->titulo, encontrarMusica->titulo);
                        }
                    }
                } else {
                    printf("Artista \"%s\" com o album \"%s\" com a musica \"%s\" nao encontrada\n", nomeArtista, tituloAlbum, tituloMusica);
                }
                
                /*
                cadastrarMusicasPlaylist(raizPlaylist, "rock", "Legiao Urbana", "Dois", "Tempo Perdido");
                cadastrarMusicasPlaylist(raizPlaylist, "rock", "Skank", "Calango", "Te Ver");
                cadastrarMusicasPlaylist(raizPlaylist, "rock", "Mamonas Assassinas", "Mamonas Assassinas", "Pelados em Santos");
                cadastrarMusicasPlaylist(raizPlaylist, "pop", "Anitta", "Kisses", "Poquito");
                cadastrarMusicasPlaylist(raizPlaylist, "pop", "Ludmilla", "Numanice #2", "Maldivas");
                cadastrarMusicasPlaylist(raizPlaylist, "mpb", "Chico Buarque", "Construcao", "Construcao");
                cadastrarMusicasPlaylist(raizPlaylist, "mpb", "Tribalistas", "Tribalistas", "Velha Infancia");
                cadastrarMusicasPlaylist(raizPlaylist, "sertanejo", "Marilia Mendonca", "Todos os Cantos", "Supera");
                cadastrarMusicasPlaylist(raizPlaylist, "sertanejo", "Os Baroes da Pisadinha", "Conquistas", "Basta Voce Me Ligar");
                cadastrarMusicasPlaylist(raizPlaylist, "engracadas", "Mamonas Assassinas", "Mamonas Assassinas", "Pelados em Santos");
                */
                break;
            }
            case 15: {
                printf("\n=== Mostrar Dados de uma Playlist ===\n");
                char nomePlaylist[100];
                printf("Digite o nome da playlist: ");
                scanf(" %[^\n]", nomePlaylist);
                Playlist *playlist;
                buscarPlaylist(raizPlaylist, nomePlaylist, &playlist);
                if (playlist != NULL) {
                    imprimirMusicasPlaylist(playlist->musicas);
                    
                } else {
                    printf("Playlist \"%s\" nao encontrada.\n", nomePlaylist);
                }
                break;
            }
            case 16: {
                printf("\n=== Remover Musica de uma Playlist ===\n");
                char nomePlaylist[100], tituloMusica[100];
                printf("Digite o nome da playlist: ");
                scanf(" %[^\n]", nomePlaylist);
                printf("Digite o titulo da musica: ");
                scanf(" %[^\n]", tituloMusica);
                Playlist *playlist;
                buscarPlaylist(raizPlaylist, nomePlaylist, &playlist);
                if (playlist != NULL) {
                    removerMusicaPlaylist(&playlist->musicas, tituloMusica);
                } else {
                    printf("Playlist \"%s\" nao encontrada.\n", nomePlaylist);
                }
                break;
            }
            case 17: {
                printf("\n=== Remover uma Playlist ===\n");
                char nomePlaylist[100];
                printf("Digite o nome da playlist: ");
                scanf(" %[^\n]", nomePlaylist);
                removerPlaylist(&raizPlaylist, nomePlaylist);

                break;
            }
            case 18: {
                printf("\n=== Remover Musica de um Album de um Artista ===\n");
                char nomeArtista[100], tituloAlbum[100], tituloMusica[100];
                printf("Digite o nome do artista: ");
                scanf(" %[^\n]", nomeArtista);
                printf("Digite o titulo do album: ");
                scanf(" %[^\n]", tituloAlbum);
                printf("Digite o titulo da musica: ");
                scanf(" %[^\n]", tituloMusica);
                removerMusicaDeAlbum(raiz, raizPlaylist, nomeArtista, tituloAlbum, tituloMusica);
                break;
            }

            case 19:{
                printf("\n=== Teste de Tempos de Busca ===\n");
                testeTemposInsercao();
                
                break;
            }
            case 0:
                printf("Saindo do programa...\n");
                liberarArtistas(raiz);
                liberarPlaylists(raizPlaylist);

                exit(0);
                break;
            default:
                printf("Opcao invalida, tente novamente!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}