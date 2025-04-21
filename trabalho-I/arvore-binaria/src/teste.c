#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"


// Assuma que todas suas structs, funções como criarArtista, criarAlbum, criarMusica, 
// insereArtista, insereAlbum, insereMusica, buscarArtista, buscarAlbum, etc. já estão declaradas corretamente.

void testeTemposBusca() {
    const int NUM_TESTES = 30;
    const int NUM_ARTISTAS = 10000;
    char tipo[] = "Solo", estilo[] = "Pop", tituloAlbum[] = "AlbumTeste", ano[] = "2024";
    double acumuladorTempo = 0.0;

    srand(time(NULL));

    FILE* arquivo = fopen("media_tempo_insercao.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo media_tempo_insercao.txt\n");
        return;
    }

    for (int t = 0; t < NUM_TESTES; t++) {
        Artista* raiz = NULL;
        Artista* artistas[NUM_ARTISTAS];

        for (int i = 0; i < NUM_ARTISTAS; i++) {
            char nomeArtista[100];
            sprintf(nomeArtista, "Artista_%04d", i + 1);
            artistas[i] = criarArtista(nomeArtista, tipo, estilo);
        }

        // Inserção aleatória dos artistas
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

        //fprintf(arquivo, "Execução %d: Tempo = %.10f segundos\n", t + 1, tempoExecucao);

        liberarArvoreArtistas(raiz);
    }

    double media = acumuladorTempo / NUM_TESTES;
    fprintf(arquivo, "\nTempo médio de inserção em %d execuções: %.10f segundos\n", NUM_TESTES, media);

    fclose(arquivo);
    printf("Teste de tempo finalizado. Resultados salvos em media_tempo_insercao.txt\n");
}


void testeBuscaMusicasDeArtista(Artista* raiz) {
  srand(time(NULL));
  int numero = (rand() % 20) + 1; // de 1 a 20
  char nomeArtista[100];
  sprintf(nomeArtista, "Artista_%04d", numero);

  printf("Artista escolhido para o teste: %s\n", nomeArtista);

  FILE* arquivo = fopen("tempo_busca_artista.txt", "w");
  if (arquivo == NULL) {
      printf("Erro ao criar arquivo de tempo.\n");
      return;
  }

  clock_t inicio, fim;
  double totalTempo = 0.0;

  for (int i = 0; i < 30; i++) {
      inicio = clock();
      mostrarMusicasDoArtista(raiz, nomeArtista);
      fim = clock();

      double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
      totalTempo += tempo;

      fprintf(arquivo, "Execução %02d - Tempo: %.10f segundos\n", i + 1, tempo);
  }

  double media = totalTempo / 30.0;

  fprintf(arquivo, "\nArtista testado: %s\n", nomeArtista);
  fprintf(arquivo, "Tempo médio da busca de TODAS as músicas: %.10f segundos\n", media);

  fclose(arquivo);
  printf("Teste finalizado. Resultados salvos em tempo_busca_artista.txt\n");
}
// teste de envio

