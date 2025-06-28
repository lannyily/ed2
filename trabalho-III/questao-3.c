#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define INFINITO 99999
#define NIL -1

typedef struct {
    int u, v;
    double confiabilidade; 
} Aresta;

typedef struct {
    int V, E;
    Aresta* arestas;
} Grafo;

Grafo* criarGrafo(int V, int E) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->V = V;
    grafo->E = E;
    grafo->arestas = (Aresta*)malloc(E * sizeof(Aresta));
    return grafo;
}


int bellmanFord(Grafo* grafo, int origem, double* dist, int* pred){
    int V = grafo->V;
    int E = grafo->E;

    
    for (int j = 0; j < E; j++) {
        double r = grafo->arestas[j].confiabilidade;
        if (r <= 0.0 || r > 1.0) {
            printf("Confiabilidade invalida na aresta");
            return 0;
        }
    }

    
    for (int i = 0; i < V; i++) {
        dist[i] = INFINITO;
        pred[i] = NIL;
    }
    dist[origem] = 0;

    
    for(int i = 1; i <= V - 1; i++){

        for(int j = 0; j < E; j++){

            int u = grafo->arestas[j].u;
            int v = grafo->arestas[j].v;

            double peso = -log(grafo->arestas[j].confiabilidade); 

            if(dist[u] != INFINITO && dist[u] + peso < dist[v] - 1e-9){
                dist[v] = dist[u] + peso;
                pred[v] = u;
            }
        }
    }

    for(int j = 0; j < E; j++){
        int u = grafo->arestas[j].u;
        int v = grafo->arestas[j].v;
        double peso = -log(grafo->arestas[j].confiabilidade);

        if (dist[u] != INFINITO && dist[u] + peso < dist[v] - 1e-9){
            printf("Aresta com ciclo detectado: (%d -> %d), confiabilidade: %.3f, peso: %.3f\n",u, v, grafo->arestas[j].confiabilidade, peso);
            printf("dist[%d] = %.3f, dist[%d] = %.3f\n", u, dist[u], v, dist[v]);
            printf("Grafo contem ciclo negativo!\n");
            return 0;
        }
    }

    for (int j = 0; j < E; j++) {
        int u = grafo->arestas[j].u;
        int v = grafo->arestas[j].v;
        double peso = -log(grafo->arestas[j].confiabilidade);
        if (dist[u] != INFINITO && dist[u] + peso < dist[v] - 1e-9){
            printf("Grafo contem ciclo negativo!\n");
            return 0;
        }
    }

    return 1; // Sucesso
}



void imprimirCaminho(int* pred, int destino) {
    if (pred[destino] == NIL) {
        printf("%d ", destino);
        return;
    }
    imprimirCaminho(pred, pred[destino]);
    printf("-> %d ", destino);
}

int main() {
    int V = 5, E = 6;
    Grafo* grafo = criarGrafo(V, E);

    
    grafo->arestas[0] = (Aresta){0, 1, 0.9};
    grafo->arestas[1] = (Aresta){0, 2, 0.5};
    grafo->arestas[2] = (Aresta){1, 2, 0.8};
    grafo->arestas[3] = (Aresta){1, 3, 0.6};
    grafo->arestas[4] = (Aresta){2, 3, 0.7};
    grafo->arestas[5] = (Aresta){3, 4, 0.95};

    int origem = 0;
    int destino = 4;

   
    double* dist = (double*)malloc(V * sizeof(double));
    int* pred = (int*)malloc(V * sizeof(int));

    if (bellmanFord(grafo, origem, dist, pred)) {
        printf("Caminho mais confiavel de %d para %d:\n", origem, destino);
        imprimirCaminho(pred, destino);
        printf("\nConfiabilidade total: %.6f\n", exp(-dist[destino]));
    } else {
        printf("Nao foi possivel encontrar o caminho.\n");
    }

    
    free(dist);
    free(pred);
    free(grafo->arestas);
    free(grafo);

    return 0;
}
