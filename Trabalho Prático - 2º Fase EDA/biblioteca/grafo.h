/**
 * @file grafo.h
 * @author Ricardo (ricardopereira15jr@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-05-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef GRAFO_H
#define GRAFO_H

typedef struct adjacente {
    struct vertice* origem;   //Apotador para o vértice de origem
    struct vertice* destino;     // Apontador para o vértice de destino
    struct adjacente* next;      // Próxima adjacência na lista ligada
} AdjD;

typedef struct vertice {
    char frequencia;             
    int x, y;                     
    int visitado;                
    struct vertice* prox;        // Apontador para o próximo vértice na lista ligada
    AdjD* adjacencias;           // Lista ligada de adjacências 
} Vertice;

Vertice* CriarGrafo(Vertice* lista);
Vertice* criarAntena(char frequencia, int x, int y);
Vertice* InsereAntena(Vertice* novo, Vertice* head, int* res);
Vertice* removeAntena(Vertice* head, int x, int y);
AdjD* criarAdjacencia(Vertice* destino);
int removerAdjacencia(Vertice* origem, Vertice* destino);
int inserirAdjacencia(Vertice* origem, Vertice* destino);
int efeitoExiste(int efeitos[][2], int total, int x, int y);
int calcularEfeitosNefastos(Vertice* lista);
int libertarMemoria(Vertice *lista);
int listarAntenas(Vertice *lista);
Vertice* carregarAntenasDeFicheiro(char *nomeFicheiro);
int guardarAntenasEmFicheiroBinario(Vertice *lista);
int limparVisitados(Vertice* lista) ;
int dfs(Vertice* atual);
int encontrarCaminhos(Vertice* atual, Vertice* destino, Vertice* caminho[], int pos) ;
int imprimirCaminho(Vertice* caminho[], int tamanho);
int listarIntersecoes(Vertice* lista, char f1, char f2);
#endif
