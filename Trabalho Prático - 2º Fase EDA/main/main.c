/**
 * @file main.c
 * @author Ricardo
 * @brief Testes básicos ao grafo
 * @version 0.1
 * @date 2025-05-14
 */

#include <stdio.h>
#include <stdlib.h>
#include "../biblioteca/grafo.h"

int main() {
    int res;
    // testes manuais
    Vertice* lista = NULL;

    // MANUALMENTE
    Vertice* a1 = criarAntena('A', 0, 0);
    Vertice* a2 = criarAntena('A', 1, 1);
    Vertice* a3 = criarAntena('A', 2, 2);

    lista = InsereAntena(a1, lista, &res);
    lista = InsereAntena(a2, lista, &res);
    lista = InsereAntena(a3, lista, &res);

    inserirAdjacencia(a1, a2);
    inserirAdjacencia(a2, a3);

    printf("Antenas inseridas manualmente:\n");
    listarAntenas(lista);
    printf("DFS a partir de a1 (lista manual):\n");
    dfs(a1);
    limparVisitados(lista);

    // CARREGAR DO FICHEIRO DE TEXTO
    Vertice* listaCarregada = carregarAntenasDeFicheiro("antenas.txt");

    listaCarregada = CriarGrafo(listaCarregada);

    printf("Antenas carregadas do ficheiro:\n");
    listarAntenas(listaCarregada);

    int efeitos = calcularEfeitosNefastos(listaCarregada);
    printf("Total de efeitos nefastos (ficheiro): %d\n", efeitos);

    printf("DFS a partir da primeira antena carregada:\n");
    dfs(listaCarregada);
    limparVisitados(listaCarregada);

    guardarAntenasEmFicheiroBinario(listaCarregada);

    listarIntersecoes(listaCarregada, 'A', '0');

    libertarMemoria(lista);
    libertarMemoria(listaCarregada);

    return 0;
}
