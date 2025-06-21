#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DISCOS 4
#define PINOS 3

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
        cont = -1;
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


int main(){
    printf("passou aqui 1\n");
    int possibilidades = pow(PINOS, DISCOS);
    printf("passou aqui 2\n");
    GrafoHanoi* grafo = criarGrafo(possibilidades, PINOS, 0);
    printf("passou aqui 3\n");
    int** estadoTorre = possibilidadeDeMovimentos(possibilidades);
    printf("passou aqui 4\n");
    criarArestas(grafo, estadoTorre, possibilidades);

    printf("Grafo (lista de adjacencia):\n");
    for(int i = 0; i < possibilidades; i++) {
        printf("V%d -> ", i);
        for(int j = 0; j < grafo->grau[i]; j++) {
            printf("%d ", grafo->arestas[i][j]);
        }
        printf("\n");
    }
    printf("passou aqui 5\n");
    for(int i = 0; i < possibilidades; i++) {
    printf("V%d: [%d %d %d %d]\n", i,
        estadoTorre[i][0],
        estadoTorre[i][1],
        estadoTorre[i][2],
        estadoTorre[i][3]);
    }

    int matrizAdj[81][81] = {0};
    criarArestasMatriz(matrizAdj, estadoTorre, possibilidades);

    printf("Matriz de Adjacencia:\n");
    for(int i = 0; i < possibilidades; i++){
        for(int j = 0; j < possibilidades; j++){
            printf("%d ", matrizAdj[i][j]);
        }
        printf("\n");
    }

    return 0;
}