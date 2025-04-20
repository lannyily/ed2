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
  Artista* artistas[50];

  // Cadastrar os 20 artistas e armazená-los no vetor
  for (int i = 0; i < 50; i++) {
      sprintf(nomeArtista, "Artista_%04d", i + 1);
      Artista* novo = criarArtista(nomeArtista, tipo, estilo);
      artistas[i] = novo;
  }

  // Inserir os artistas na árvore de forma aleatória
  for (int i = 0; i < 50; i++) {
      int aleatorio = rand() % (50 - i);  // Escolher aleatoriamente um índice
      Artista* artistaAleatorio = artistas[aleatorio];

      // Mover o artista escolhido para o final do vetor
      artistas[aleatorio] = artistas[49 - i];
      artistas[49 - i] = artistaAleatorio;

      inicio = clock();
      
      insereArtista(raiz, artistaAleatorio);

      // Salvar inserção do artista no arquivo
      fprintf(arquivo, "Inserção do artista: %s\n", artistaAleatorio->nome);

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
      fprintf(arquivo, "Tempo de inserção: %.50f segundos\n\n", tempoInsercao);
  }

  // Calcular o tempo médio de inserção
  double tempoMedioInsercao = totalTempoInsercao / 50.0;

  // Salvar no arquivo o tempo médio
  fprintf(arquivo, "Tempo médio de inserção (50 repetições): %.50f segundos\n", tempoMedioInsercao);

  fclose(arquivo);

  printf("Resultado salvo em tempo_insercao_aleatoria.txt\n");
}

