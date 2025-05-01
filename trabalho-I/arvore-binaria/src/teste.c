#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"

#define NUM_ARTISTAS 100000

void testeBuscaMusicasDeArtista(Artista* raiz) {
    srand(time(NULL));

    FILE* arquivo = fopen("tempo_busca.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo de tempo.\n");
        return;
    }

    double totalTempo = 0.0;
    int artistasTestados = 30;

    
    int numero = 49985;
    char nomeArtista[100];
    sprintf(nomeArtista, "Artista_%05d", numero);

    printf("Artista escolhido para o teste: %s\n", nomeArtista);

    for (int i = 0; i < artistasTestados; i++) {
        clock_t inicio = clock();
        mostrarMusicasDoArtista(raiz, nomeArtista);
        clock_t fim = clock();

        double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        totalTempo += tempo;

        fprintf(arquivo, "Execução %02d - Artista: %s - Tempo: %.10f segundos\n", i + 1, nomeArtista, tempo);
    }

    double media = totalTempo / artistasTestados;
    fprintf(arquivo, "\nTempo médio de busca de músicas: %.10f segundos\n", media);

    fclose(arquivo);
    printf("Teste de busca finalizado. Resultados salvos em tempo_busca_artistas_fundos.txt\n");
}



void testeTemposInsercao() {
    Artista* raiz = NULL;


    int NUM_TESTES = 30;

    char tipo[] = "Solo", estilo[] = "Pop", tituloAlbum[] = "AlbumTeste", ano[] = "2024";
    double acumuladorTempo = 0.0;

    srand(time(NULL));

    FILE* arquivoMedia = fopen("media_tempo_insercao.txt", "w");
    FILE* arquivoDetalhado = fopen("tempos_individuais_insercao.txt", "w");

    if (arquivoMedia == NULL || arquivoDetalhado == NULL) {
        printf("Erro ao criar arquivos de saída.\n");
        if (arquivoMedia) fclose(arquivoMedia);
        if (arquivoDetalhado) fclose(arquivoDetalhado);
        return;
    }

    for (int t = 0; t < NUM_TESTES; t++) {
        
        Artista* artistas[NUM_ARTISTAS];

        for (int i = 0; i < NUM_ARTISTAS; i++) {
            char nomeArtista[100];
            sprintf(nomeArtista, "Artista_%05d", i + 1);
            artistas[i] = criarArtista(nomeArtista, tipo, estilo);
        }

        clock_t inicio = clock();

        for (int i = 0; i < NUM_ARTISTAS; i++) {
            int aleatorio = rand() % (NUM_ARTISTAS - i);
            Artista* escolhido = artistas[aleatorio];

            artistas[aleatorio] = artistas[NUM_ARTISTAS - 1 - i];
            artistas[NUM_ARTISTAS - 1 - i] = escolhido;

            insereArtista(&raiz, escolhido);

            Album* album = criarAlbum(tituloAlbum, ano);
            insereAlbum(&(escolhido->albuns), album);

            for (int j = 1; j <= 5; j++) {
                char tituloMusica[50];
                sprintf(tituloMusica, "Musica_%d", j);
                Musica* m = criarMusica(tituloMusica, 5);
                insereMusica(&(album->musicas), m);
            }
        }

        clock_t fim = clock();
        double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        acumuladorTempo += tempoExecucao;

        fprintf(arquivoDetalhado, "Execução %02d: Tempo = %.10f segundos\n", t + 1, tempoExecucao);
    }

    double media = acumuladorTempo / NUM_TESTES;
    fprintf(arquivoMedia, "Tempo médio de inserção em %d execuções: %.10f segundos\n", NUM_TESTES, media);

    fclose(arquivoMedia);
    fclose(arquivoDetalhado);

    printf("Teste de tempo finalizado. Resultados salvos em:\n");
    printf("- media_tempo_insercao.txt\n");
    printf("- tempos_individuais_insercao.txt\n");

    testeBuscaMusicasDeArtista(raiz);
}


