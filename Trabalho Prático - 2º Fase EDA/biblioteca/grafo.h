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
/**
 * @brief Estrutura que representa uma adjacência entre duas antenas (vértices).
 */
typedef struct adjacente {
    struct vertice* origem;   //Apontador para o vértice de origem
    struct vertice* destino;     // Apontador para o vértice de destino
    struct adjacente* next;      // Próxima adjacência na lista ligada
} AdjD;

/**
 * @brief Estrutura que representa uma antena (vértice).
 */
typedef struct vertice {
    char frequencia;             
    int x, y;                     
    int visitado;                
    struct vertice* prox;        // Apontador para o próximo vértice na lista ligada
    AdjD* adjacencias;           // Lista ligada de adjacências 
} Vertice;

/**
 * @brief Inicializa a lista de vértices (grafo)
 * @param lista Apontador para a lista de vértices
 * @return Apontador para o início da lista
 */
Vertice* CriarGrafo(Vertice* lista);

/**
 * @brief Cria uma nova antena (vértice)
 * @param frequencia Frequência da antena
 * @param x Coordenada X
 * @param y Coordenada Y
 * @return Apontador para a nova antena criada
 */
Vertice* criarAntena(char frequencia, int x, int y);

/**
 * @brief Insere uma antena na lista de vértices
 * @param novo Nova antena a inserir
 * @param head Cabeça da lista de vértices
 * @param res Apontador para código de resultado (0 = sucesso, 1 = já existe)
 * @return Nova cabeça da lista de vértices 
 */
Vertice* InsereAntena(Vertice* novo, Vertice* head, int* res);

/**
 * @brief Remove uma antena da lista de vértices com base nas coordenadas
 * @param head Cabeça da lista de vértices
 * @param x Coordenada X
 * @param y Coordenada Y
 * @return Nova cabeça da lista
 */
Vertice* removeAntena(Vertice* head, int x, int y);

/**
 * @brief Cria uma adjacência entre antenas
 * @param destino Apontador para o vértice de destino
 * @return Apontador para a nova adjacência
 */
AdjD* criarAdjacencia(Vertice* destino);

/**
 * @brief Remove uma adjacência entre duas antenas
 * @param origem Apontador para o vértice de origem
 * @param destino Apontador para o vértice de destino
 * @return 0 em caso de sucesso, -1 se não encontrada
 */
int removerAdjacencia(Vertice* origem, Vertice* destino);

/**
 * @brief Insere uma adjacência entre duas antenas
 * @param origem Apontador para o vértice de origem
 * @param destino Apontador para o vértice de destino
 * @return 0 em caso de sucesso, -1 se já existir
 */
int inserirAdjacencia(Vertice* origem, Vertice* destino);

/**
 * @brief Verifica se um efeito nefasto já foi registado
 * @param efeitos Matriz com pares de coordenadas de efeitos já registados
 * @param total Número total de efeitos registados
 * @param x Coordenada X a verificar
 * @param y Coordenada Y a verificar
 * @return 1 se existir, 0 caso contrário
 */
int efeitoExiste(int efeitos[][2], int total, int x, int y);

/**
 * @brief Calcula o número de efeitos nefastos
 * @param lista Lista de antenas
 * @return Número total de efeitos nefastos encontrados
 */
int calcularEfeitosNefastos(Vertice* lista);

/**
 * @brief Liberta a memória associada à lista de vértices e adjacências
 * @param lista Lista de antenas
 * @return 0 em caso de sucesso
 */
int libertarMemoria(Vertice *lista);

/**
 * @brief Lista todas as antenas 
 * @param lista Lista de antenas
 * @return 0 em caso de sucesso
 */
int listarAntenas(Vertice *lista);

/**
 * @brief Carrega antenas e ligações a partir de um ficheiro de texto
 * @param nomeFicheiro Nome do ficheiro a ler que será "antenas.txt"
 * @return Apontador para a lista carregada
 */
Vertice* carregarAntenasDeFicheiro(char *nomeFicheiro);

/**
 * @brief Guarda a estrutura do grafo num ficheiro binário
 * @param lista Lista de antenas
 * @return 0 em caso de sucesso
 */
int guardarAntenasEmFicheiroBinario(Vertice *lista);

/**
 * @brief Reinicializa o campo "visitado" de todas as antenas
 * @param lista Lista de antenas
 * @return 0 em caso de sucesso
 */
int limparVisitados(Vertice* lista);

/**
 * @brief Algoritmo DFS (Depth-First Search)  a partir de um vértice
 * @param atual Vértice inicial da pesquisa
 * @return Número de vértices visitados
 */
int dfs(Vertice* atual);

/**
 * @brief Encontra caminhos entre dois vértices e armazena em vetor
 * @param atual Vértice atual da pesquisa
 * @param destino Vértice de destino
 * @param caminho Vetor de Apontadores para armazenar o caminho
 * @param pos Posição atual no vetor caminho
 * @return Número de caminhos encontrados
 */
int encontrarCaminhos(Vertice* atual, Vertice* destino, Vertice* caminho[], int pos);

/**
 * @brief Imprime um caminho entre vértices
 * @param caminho Vetor de vértices no caminho
 * @param tamanho Tamanho do caminho
 * @return 0 em caso de sucesso
 */
int imprimirCaminho(Vertice* caminho[], int tamanho);

/**
 * @brief Lista interseções entre antenas de duas frequências diferentes
 * @param lista Lista de antenas
 * @param f1 Primeira frequência
 * @param f2 Segunda frequência
 * @return Número de interseções encontradas
 */
int listarIntersecoes(Vertice* lista, char f1, char f2);
#endif
