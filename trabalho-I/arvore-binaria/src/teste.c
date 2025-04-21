#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Includes/artista.h"
#include "../Includes/album.h"
#include "../Includes/musica.h"


// Assuma que todas suas structs, funções como criarArtista, criarAlbum, criarMusica, 
// insereArtista, insereAlbum, insereMusica, buscarArtista, buscarAlbum, etc. já estão declaradas corretamente.

void testeTemposBusca(Artista** raiz) {
  char nomeArtista[100], tipo[20] = "Solo", estilo[20] = "Pop";
  char tituloAlbum[] = "AlbumTeste", ano[] = "2024";

  // Inicializar o gerador de números aleatórios
  srand(time(NULL));  // Isso vai gerar uma semente diferente a cada execução

  clock_t inicio, fim;
  double totalTempoInsercao = 0.0;

  // Abrir arquivo para salvar os resultados
  FILE* arquivo = fopen("tempo_insercao_aleatoria.txt", "w");
  if (arquivo == NULL) {
      printf("Erro ao criar arquivo tempo_insercao_aleatoria.txt\n");
      return;
  }

  // Criar um vetor para armazenar os artistas e inserir aleatoriamente
  Artista* artistas[10000];

  // Cadastrar os 20 artistas e armazená-los no vetor
  for (int i = 0; i < 10000; i++) {
      sprintf(nomeArtista, "Artista_%04d", i + 1);
      Artista* novo = criarArtista(nomeArtista, tipo, estilo);
      artistas[i] = novo;
  }

  // Inserir os artistas na árvore de forma aleatória
  for (int i = 0; i < 10000; i++) {
      int aleatorio = rand() % (10000 - i);  // Escolher aleatoriamente um índice
      Artista* artistaAleatorio = artistas[aleatorio];

      // Mover o artista escolhido para o final do vetor
      artistas[aleatorio] = artistas[9999 - i];
      artistas[9999 - i] = artistaAleatorio;

      inicio = clock();
      
      insereArtista(raiz, artistaAleatorio);

      // Salvar inserção do artista no arquivo
      // fprintf(arquivo, "Inserção do artista: %s\n", artistaAleatorio->nome);

      Album* album = criarAlbum(tituloAlbum, ano);
      insereAlbum(&(artistaAleatorio->albuns), album);

      char tituloMusica[50];
      for (int j = 1; j <= 5; j++) {
          sprintf(tituloMusica, "Musica_%d", j);
          Musica* m = criarMusica(tituloMusica, 5);
          insereMusica(&(album->musicas), m);
      }

      fim = clock();
      double tempoInsercao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
      totalTempoInsercao += tempoInsercao;

      // Salvar tempo de inserção do artista no arquivo
      // fprintf(arquivo, "Tempo de inserção: %.20f segundos\n\n", tempoInsercao);
  }

  // Calcular o tempo médio de inserção
  double tempoMedioInsercao = totalTempoInsercao / 1000.0;

  // Salvar no arquivo o tempo médio
  fprintf(arquivo, "Tempo médio de inserção (10000 repetições): %.20f segundos\n", tempoMedioInsercao);

  fclose(arquivo);

  printf("Resultado salvo em tempo_insercao_aleatoria.txt\n");
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

