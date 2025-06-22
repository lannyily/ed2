#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define DISCOS 4
#define PINOS 3
#define MAX_VERTICES 81
#define INFINITO 99999
#define NIL -1

typedef struct GrafoHanoi {
    int vertices;
    int** arestas;
    int* grau;

    int ponderado;
    int grauMaximo;
    float** pesos;
}GrafoHanoi;

GrafoHanoi* criarGrafo(int vertices, int grauMaximo, int ponderado){
    GrafoHanoi* grafo = (GrafoHanoi*)malloc(sizeof(GrafoHanoi));

    if(grafo != NULL){
        grafo->vertices = vertices;
        grafo->ponderado = (ponderado != 0) ? 1:0;
        grafo->grau = (int*)calloc(vertices, sizeof(int));
        grafo->arestas = (int**)malloc(vertices * sizeof(int*));

        for(int i = 0; i < vertices; i++){
            grafo->arestas[i] = (int*)malloc(grauMaximo * sizeof(int));
            for(int j = 0; j < grauMaximo; j++){
                grafo->arestas[i][j] = 0;
            }
        }

        if(grafo->ponderado == 1){
            grafo->pesos = (float**)malloc(vertices * sizeof(float*));

            for(int i = 0; i < vertices; i++){
                grafo->pesos[i] = (float*)malloc(vertices * sizeof(float));
            }
        }

    }
    return grafo;
}

int** possibilidadeDeMovimentos(int possibilidades){
    int** torre = malloc(sizeof(int*) * possibilidades);
    int cont = 0;

    for(int i = 0; i < PINOS; i++){
        for(int j = 0; j < PINOS; j++){
            for(int q = 0; q < PINOS; q++){
                for(int p = 0; p < PINOS; p++){
                    torre[cont] = malloc(sizeof(int) * DISCOS);
                    torre[cont][0] = i + 1;
                    torre[cont][1] = j + 1;
                    torre[cont][2] = q + 1;
                    torre[cont][3] = p + 1;

                    cont++;
                }
            }
        }
    }

    return torre;
}

int inserirAresta(GrafoHanoi* grafo, int origem, int destino, int digrafo, float peso){
    int resultado = 0;

    if(grafo != NULL){
        if((origem >= 0 && origem < grafo->vertices) && (destino >= 0 && destino < grafo->vertices)){
            grafo->arestas[origem][grafo->grau[origem]] = destino;

            if(grafo->ponderado){
                grafo->pesos[origem][grafo->grau[origem]] = peso;
            }

            grafo->grau[origem]++;

            if(digrafo == 0){
                inserirAresta(grafo, destino, origem, 1, peso);
            }

            resultado = 1;
        }
    }

    return resultado;
}


int quantidadeMovimentos(int* torre1, int* torre2){
    int cont = 0;

    for(int i = 0; i < DISCOS; i++){
        if(torre2[i] != torre1[i]){
            cont++;
        }
    }
    return cont;
}


int qualDiscoFoiMovido(int* torre1, int* torre2){
    int posicao = -1;
    int cont = 0;

    for(int i = 0; i < DISCOS; i++){
        if(torre2[i] != torre1[i]){
            cont++;
            posicao = i;
        }
    }

    if(cont != 1){
        posicao = -1;
    }

    return posicao;
}

int discoMenorOrigem(int* torre, int posicao){
    int resultado = 1;

    for(int i = posicao + 1; i < DISCOS; i++){
        if(torre[i] == torre[posicao]){
            resultado = 0;
        }
    }
    return resultado;
}


int movimentoValido(int* torre1, int* torre2){
    int resultado = 0;

    if(quantidadeMovimentos(torre1, torre2) == 1){
        int disco = qualDiscoFoiMovido(torre1, torre2);

        if(disco != -1){
            if(discoMenorOrigem(torre1, disco) == 1){
                if(discoMenorOrigem(torre2, disco) == 1){
                    resultado = 1;
                }
            }
        }
    }

    return resultado;
}

void criarArestas(GrafoHanoi* grafo, int** torre, int possibilidades){
    for(int i = 0; i < possibilidades; i++){
        for(int j = 0; j < possibilidades; j++){
            if(movimentoValido(torre[i], torre[j]) == 1){
                inserirAresta(grafo, i + 1, j + 1, 1, 0);
            }
        }
    }
}

void criarArestasMatriz(int matriz[MAX_VERTICES][MAX_VERTICES], int** torre, int possibilidades){
    for(int i = 0; i < possibilidades; i++){
        for(int j = 0; j < possibilidades; j++){
            if(movimentoValido(torre[i], torre[j])){
                matriz[i][j] = 1; 
            }
        }
    }
}


int bellmanFord(GrafoHanoi* grafo, int origem, int* dist, int* pred) {
    int V = grafo->vertices;

    for (int i = 0; i < V; i++) {
        dist[i] = INFINITO;
        pred[i] = NIL;
    }
    dist[origem] = 0;

    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (int j = 0; j < grafo->grau[u]; j++) {
                int v = grafo->arestas[u][j];
                float peso = 1.0; // cada movimento tem peso 1

                if (dist[u] != INFINITO && dist[v] > dist[u] + peso) {
                    dist[v] = dist[u] + peso;
                    pred[v] = u;
                }
            }
        }
    }

    // Verifica ciclos negativos
    for (int u = 0; u < V; u++) {
        for (int j = 0; j < grafo->grau[u]; j++) {
            int v = grafo->arestas[u][j];
            float peso = 1.0;
            if (dist[u] != INFINITO && dist[v] > dist[u] + peso) {
                return 0; // ciclo negativo detectado
            }
        }
    }

    return 1;
}

void imprimirCaminho(int origem, int destino, int* pred) {
    if (origem == destino) {
        printf("V%d ", origem);
    } else if (pred[destino] == NIL) {
        printf("Sem caminho de V%d a V%d\n", origem, destino);
    } else {
        imprimirCaminho(origem, pred[destino], pred);
        printf("-> V%d ", destino);
    }
}


int main() {
    int possibilidades = MAX_VERTICES;
    GrafoHanoi* grafo = criarGrafo(possibilidades, PINOS, 0);
    int** torre = possibilidadeDeMovimentos(possibilidades);
    criarArestas(grafo, torre, possibilidades);

    int matrizAdj[MAX_VERTICES][MAX_VERTICES] = {0};
    criarArestasMatriz(matrizAdj, torre, possibilidades);

    // Entrada do usuário
    int configUsuario[DISCOS];
    printf("Digite a configuracao dos %d discos (valores de 1 a 3 para cada pino):\n", DISCOS);
    for(int i = 0; i < DISCOS; i++) {
        do {
            printf("Disco %d esta em qual pino? ", i + 1);
            scanf("%d", &configUsuario[i]);
            if (configUsuario[i] < 1 || configUsuario[i] > 3) {
                printf("Valor invalido! Insira 1, 2 ou 3.\n");
            }
        } while(configUsuario[i] < 1 || configUsuario[i] > 3);
    }

    // Buscar índice da configuração digitada
    int indiceConfig = -1;
    for(int i = 0; i < possibilidades; i++) {
        int igual = 1;
        for(int j = 0; j < DISCOS; j++) {
            if(configUsuario[j] != torre[i][j]) {
                igual = 0;
                break;
            }
        }
        if (igual) {
            indiceConfig = i;
            break;
        }
    }

    // Definir destino final padrão: todos os discos no pino 3
    int destinoFinal[DISCOS] = {3, 3, 3, 3};
    int indiceDestino = -1;
    for(int i = 0; i < possibilidades; i++) {
        int igual = 1;
        for(int j = 0; j < DISCOS; j++) {
            if(destinoFinal[j] != torre[i][j]) {
                igual = 0;
                break;
            }
        }
        if (igual) {
            indiceDestino = i;
            break;
        }
    }

    if(indiceConfig != -1 && indiceDestino != -1) {
        printf("\nConfiguracao inicial corresponde ao vertice V%d\n", indiceConfig);
        printf("Destino final (todos os discos no pino 3) e o vertice V%d\n", indiceDestino);

        clock_t inicio = clock();
        
        int dist[MAX_VERTICES];
        int pred[MAX_VERTICES];

        if (bellmanFord(grafo, indiceConfig, dist, pred)) {
            printf("\nCaminho mais curto de V%d ate V%d:\n", indiceConfig, indiceDestino);
            imprimirCaminho(indiceConfig, indiceDestino, pred);
            printf("\nDistancia total: %d\n", dist[indiceDestino]);
        } else {
            printf("\nExiste ciclo negativo no grafo.\n");
        }

                
        clock_t fim = clock();

        double tempo_ms = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
        printf("\nTempo gasto: %.3f milissegundos\n", tempo_ms);
    } else {
        printf("\nErro ao identificar configuracao inicial ou destino.\n");
    }

    // Liberar memória
    for(int i = 0; i < possibilidades; i++) {
        free(torre[i]);
    }
    free(torre);
    
    return 0;
}
