#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DISCOS 4
#define PINOS 3
#define MAX_VERTICES 81

typedef struct GrafoHanoi {
    int vertices;
    int** arestas;
    int* grau;
    int nivel[81];

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
    int** estadoTorre = malloc(sizeof(int*) * possibilidades);
    int cont = 0;

    for(int i = 0; i < PINOS; i++){
        for(int j = 0; j < PINOS; j++){
            for(int q = 0; q < PINOS; q++){
                for(int p = 0; p < PINOS; p++){
                    estadoTorre[cont] = malloc(sizeof(int) * DISCOS);
                    estadoTorre[cont][0] = i + 1;
                    estadoTorre[cont][1] = j + 1;
                    estadoTorre[cont][2] = q + 1;
                    estadoTorre[cont][3] = p + 1;

                    cont++;
                }
            }
        }
    }

    return estadoTorre;
}

int inserirAresta(GrafoHanoi* grafo, int origem, int destino, int digrafo, float peso){
    int resultado = 0;

    if(grafo != NULL){
        if((origem >= 0 && origem < grafo->vertices) && (destino >= 0 && destino < grafo->vertices)){
            grafo->arestas[origem][grafo->grau[origem]] = destino;


            if(grafo->ponderado){
                grafo->pesos[origem - 1][grafo->grau[origem - 1]] = peso;
            }

            grafo->grau[origem - 1]++;

            if(digrafo == 0){
                inserirAresta(grafo, destino, origem, 1, peso);
            }

            resultado = 1;
        }
    }

    return resultado;
}

int quantidadeMovimentos(int* estadoTorre1, int* estadoTorre2){
    int cont = 0;

    for(int i = 0; i < DISCOS; i++){
        if(estadoTorre2[i] != estadoTorre1[i]){
            cont++;
        }
    }
    return cont;
}


int qualDiscoFoiMovido(int* estadoTorre1, int* estadoTorre2){
    int posicao = -1;
    int cont = 0;

    for(int i = 0; i < DISCOS; i++){
        if(estadoTorre2[i] != estadoTorre1[i]){
            cont++;
            posicao = i;
        }
    }

    if(cont != 1){
        posicao = -1;
    }

    return posicao;
}

int discoMenorOrigem(int* estadoTorre, int posicao){
    int resultado = 1;

    for(int i = posicao + 1; i < DISCOS; i++){
        if(estadoTorre[i] == estadoTorre[posicao]){
            resultado = 0;
        }
    }
    return resultado;
}


int movimentoValido(int* estadoTorre1, int* estadoTorre2){
    int resultado = 0;

    if(quantidadeMovimentos(estadoTorre1, estadoTorre2) == 1){
        int disco = qualDiscoFoiMovido(estadoTorre1, estadoTorre2);

        if(disco != -1){
            if(discoMenorOrigem(estadoTorre1, disco) == 1){
                if(discoMenorOrigem(estadoTorre2, disco) == 1){
                    resultado = 1;
                }
            }
        }
    }

    return resultado;
}

void criarArestas(GrafoHanoi* grafo, int** estadoTorre, int possibilidades){
    for(int i = 0; i < possibilidades; i++){
        for(int j = 0; j < possibilidades; j++){
            if(movimentoValido(estadoTorre[i], estadoTorre[j]) == 1){
                inserirAresta(grafo, i + 1, j + 1, 1, 0);
            }
        }
    }
}

void criarArestasMatriz(int matriz[81][81], int** estadoTorre, int possibilidades){
    for(int i = 0; i < possibilidades; i++){
        for(int j = 0; j < possibilidades; j++){
            if(movimentoValido(estadoTorre[i], estadoTorre[j])){
                matriz[i][j] = 1; 
            }
        }
    }
}

void dijkstra(int vertices, int origem, int destino, int matrizAdj[81][81]) {
    
    int dist[MAX_VERTICES], visitado[MAX_VERTICES], anterior[MAX_VERTICES];
    
    for (int i = 0; i < vertices; i++) {
        dist[i] = 99999;
        visitado[i] = 0;
        anterior[i] = -1;
    }

    dist[origem] = 0;

    for (int i = 0; i < vertices - 1; i++) {
        int min = 99999, u = -1;

        for (int j = 0; j < vertices; j++) {
            if (!visitado[j] && dist[j] <= min) {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1) break;

        visitado[u] = 1;

        for (int v = 0; v < vertices; v++) {
            if (!visitado[v] && matrizAdj[u][v]) {
                if (dist[u] + 1 < dist[v]) {
                    dist[v] = dist[u] + 1;
                    anterior[v] = u;
                }
            }
        }
    }

    if (dist[destino] == 99999) {
        printf("Nao existe caminho entre os vartices %d e %d\n", origem, destino);
    } else {
        printf("Menor caminho do vartice %d ao %d (ordem reversa):\n", origem, destino);
        int atual = destino;
        while (atual != -1) {
            printf("V%d ", atual);
            atual = anterior[atual];
            if (atual != -1) printf("<- ");
        }
        printf("\nCusto: %d movimentos\n", dist[destino]);
    }
}



int main(){
    int possibilidades = pow(PINOS, DISCOS);
    GrafoHanoi* grafo = criarGrafo(possibilidades, PINOS, 0);
    int** estadoTorre = possibilidadeDeMovimentos(possibilidades);
    criarArestas(grafo, estadoTorre, possibilidades);

    int matrizAdj[81][81] = {0};
    criarArestasMatriz(matrizAdj, estadoTorre, possibilidades);

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
            if(configUsuario[j] != estadoTorre[i][j]) {
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
            if(destinoFinal[j] != estadoTorre[i][j]) {
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

        // Chamar Dijkstra
        dijkstra(possibilidades, indiceConfig, indiceDestino, matrizAdj);
    } else {
        printf("\nErro ao identificar configuracao inicial ou destino.\n");
    }

    return 0;
}
