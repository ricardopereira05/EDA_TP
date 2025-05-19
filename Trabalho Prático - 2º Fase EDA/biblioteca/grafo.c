/**
 * @file grafo.c
 * @author Ricardo (ricardopereira15jr@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-05-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#pragma region Criar Grafo
/**
 * @brief Cria as adjacências do grafo com base nos vértices (antenas) que possuem a mesma frequência.
 *
 * Esta função percorre a lista de vértices e para cada par de antenas diferentes
 * que tenham a mesma frequência, cria uma adjacência de um para o outro.
 *
 * @param lista Apontador para o início da lista ligada de vértices (antenas).
 * @return Apontador para o início da lista, com as adjacências preenchidas.
 */
Vertice* CriarGrafo(Vertice* lista) {
    if (lista == NULL) {
        // Se a lista de vértices estiver vazia, não há nada a fazer.
        return NULL;
    }
    Vertice* aux = lista;  // aux percorre cada vértice na lista.
    while (aux != NULL) {
        Vertice* comparar = lista;  // comparar percorre novamente toda a lista para comparar com 'aux'
        while (comparar != NULL) {
            // verifica se não está a comparar a antena consigo mesma e se têm a mesma frequência
            if (comparar != aux && comparar->frequencia == aux->frequencia) {
                // Cria uma adjacência de aux para comparar
                inserirAdjacencia(aux, comparar);
            }
            comparar = comparar->prox;
        }
        aux = aux->prox;
    }
    return lista;
}
#pragma endregion
#pragma region Criar Antena
/**
 * @brief Cria uma nova antena (vértice) com a frequência e as coordenadas.
 *
 * Esta função aloca memória para um novo vértice da lista de antenas, inicializando os seus
 * campos: frequência, coordenadas x e y. E deixa os apontadores de adjacências e
 * próximo a NULL.
 *
 * @param frequencia Carátere que representa a frequência da antena.
 * @param x Coordenada X da antena.
 * @param y Coordenada Y da antena.
 * @return Apontador para a nova antena criada, ou NULL em caso de falha na alocação de memória.
 */
Vertice* criarAntena(char frequencia, int x, int y) {
    Vertice* nova = (Vertice*)malloc(sizeof(Vertice));    
    // Verificar se a alocação falhou
    if (!nova) {
        printf("Erro ao alocar memória para a antena!\n");
        return NULL;
    }
    nova->frequencia = frequencia;
    nova->x = x;
    nova->y = y;
    // Apontadores da lista ligada
    nova->adjacencias = NULL; // Sem ligações ainda
    nova->prox = NULL;        // Não está ligada a nenhuma outra antena
    // Retornar o apontador para a nova antena
    return nova;
}

#pragma endregion
#pragma region Inserir Antena
/**
 * @brief Insere uma nova antena na lista ligada de antenas, ordenada por coordenadas (x, y).
 *
 * A função verifica se já existe uma antena com a mesma frequência e coordenadas. 
 * Se existir, a nova antena é descartada. Caso contrário, é inserida de forma ordenada.
 *
 * @param novo Apontador para a nova antena a ser inserida.
 * @param head Cabeça da lista ligada de antenas.
 * @param res Apontador onde guarda o resultado (1 se inserido, 0 se não foi).
 * @return Apontador para a nova cabeça da lista (pode mudar se a antena for inserida no início).
 */
Vertice* InsereAntena(Vertice* novo, Vertice* head, int* res) {
    *res = 0; 
    // Verificar se o novo vértice é válido
    if (!novo) return head;
    // Verificar se já existe uma antena com os mesmos dados
    Vertice* aux = head;
    while (aux != NULL) {
        if (aux->frequencia == novo->frequencia && aux->x == novo->x && aux->y == novo->y) {
            // Antena já existente, não inserir
            printf("Antena já existe nas coordenadas (%d, %d) com frequência %c!\n", novo->x, novo->y, novo->frequencia);
            free(novo); // Libertar memória alocada
            return head;
        }
        aux = aux->prox;
    }
    // Inserir no início da lista se for vazia ou se a nova antena vier antes
    if (head == NULL || head->x > novo->x || (head->x == novo->x && head->y > novo->y)) {
        novo->prox = head;
        *res = 1; 
        return novo;
    }
    // Procurar a posição certa para inserir mantendo a ordem por x, y
    Vertice* anterior = NULL;
    aux = head;
    while (aux && (aux->x < novo->x || (aux->x == novo->x && aux->y < novo->y))) {
        anterior = aux;
        aux = aux->prox;
    }
    // Inserção entre anterior e aux
    anterior->prox = novo;
    novo->prox = aux;
    *res = 1; 
    return head;
}
#pragma endregion
#pragma region Remover Antena
/**
 * @brief Remove uma antena da lista de antenas com base nas coordenadas (x, y).
 *
 * A função procura a antena com as coordenadas indicadas, remove-a da lista ligada
 * e liberta a memória associada, incluindo as suas adjacências.
 *
 * @param head Cabeça da lista de antenas.
 * @param x Coordenada x da antena a remover.
 * @param y Coordenada y da antena a remover.
 * @return Nova cabeça da lista após a remoção.
 */
Vertice* removeAntena(Vertice* head, int x, int y) {
    Vertice* atual = head;       
    Vertice* anterior = NULL;    
    while (atual) {
        if (atual->x == x && atual->y == y) {
            // Antena encontrada, se for a primeira da lista
            if (anterior == NULL) {
                head = atual->prox;
            } else {
                // Se estiver no meio ou fim da lista
                anterior->prox = atual->prox;
            }
            // Libertar as adjacências associadas à antena
            AdjD* adj = atual->adjacencias;
            while (adj) {
                AdjD* temp = adj;
                adj = adj->next;
                free(temp);
            }
            // Libertar o vértice
            free(atual);
            return head;
        }
        // Avançar para o próximo elemento
        anterior = atual;
        atual = atual->prox;
    }
    // Se chegou aqui, a antena não foi encontrada
    return head;
}
#pragma endregion
#pragma region Criar Adjacência
/**
 * @brief Cria uma nova adjacência (ligação) para um vértice (antena).
 *
 * Esta função aloca memória para uma nova estrutura de adjacência, define o destino
 * e devolve um apontador para essa nova adjacência.
 *
 * @param destino Apontador para o vértice de destino da adjacência.
 * @return Apontador para a nova adjacência criada, ou NULL se houver erro de alocação.
 */
AdjD* criarAdjacencia(Vertice* destino) {
    AdjD* nova = (AdjD*)malloc(sizeof(AdjD));
    if (!nova) return NULL;  
    nova->destino = destino;
    nova->next = NULL;
    return nova;  
}
#pragma endregion
#pragma region Inserir Adjacência
/**
 * @brief Insere uma nova adjacência (ligação) entre duas antenas (vértices).
 *
 * Esta função cria uma adjacência entre a antena de origem e a antena de destino,
 * adicionando a nova ligação na lista de adjacências da antena de origem, ou seja, partida.
 *
 * @param origem Apontador para o vértice de origem.
 * @param destino Apontador para o vértice de destino.
 */
int inserirAdjacencia(Vertice* origem, Vertice* destino) {
    // Verificar se os apontadores são válidos
    if (!origem || !destino) return 0;
    // Criar 
    AdjD* nova = criarAdjacencia(destino); 
    if (!nova) return 0; 
    if (!origem->adjacencias) {
        origem->adjacencias = nova;
    } else {
        // Se ja tiver adjacências acrescenta no fim da lista
        AdjD* aux = origem->adjacencias;
        while (aux->next) {
            aux = aux->next;
        }
        aux->next = nova;
    }
    return 1; 
}
#pragma endregion
#pragma region Remover Adjacência
/**
 * @brief Remove uma adjacência entre dois vértices.
 *
 * @param origem Apontador para o vértice de origem.
 * @param destino Apontador para o vértice de destino.
 * @param sucesso Apontador que indica se a remoção foi bem-sucedida (1) ou não (0).
 */
int removerAdjacencia(Vertice* origem, Vertice* destino) {
    if (!origem || !destino || !origem->adjacencias)
        return 0;
    AdjD* atual = origem->adjacencias;
    AdjD* anterior = NULL;
    while (atual) {
        if (atual->destino == destino) {
            if (anterior) {
                anterior->next = atual->next;
            } else {
                origem->adjacencias = atual->next;
            }
            free(atual);
            return 1; 
        }
        anterior = atual;
        atual = atual->next;
    }
    return 0;
}
#pragma endregion
#pragma region Efeito Existe
/**
 * @brief Verifica se uma determinada coordenada (x, y) já foi marcada como efeito nefasto.
 *
 * @param efeitos Matriz de coordenadas onde já foram identificados efeitos nefastos.
 * @param total Número total de efeitos registados.
 * @param x Coordenada x a verificar.
 * @param y Coordenada y a verificar.
 * @return 1 se já existir, 0 caso contrário.
 */
int efeitoExiste(int efeitos[][2], int total, int x, int y) {
    for (int i = 0; i < total; i++) {
        if (efeitos[i][0] == x && efeitos[i][1] == y) {
            return 1;
        }
    }
    return 0;
}
#pragma endregion
#pragma region Calcular Efeito Nefasto
/**
 * @brief Calcula e imprime na consola os efeitos nefastos provocados por interferência de antenas.
 *
 * Um efeito nefasto ocorre quando duas antenas com a mesma frequência estão separadas
 * exatamente por 2 unidades, na vertical ou horizontal. A posição intermédia é onde o
 * efeito é registado.
 *
 * @param lista Lista ligada de antenas (vértices).
 * @return Número total de efeitos nefastos identificados.
 */
int calcularEfeitosNefastos(Vertice* lista) {
    printf("\nEfeitos nefastos:\n");
    printf("Coordenadas (x, y)\n");
    printf("-------------------\n");
    int total = 0;
    int efeitos[100][2]; 
    int totalEfeitos = 0;
    // Percorrer todas as combinações de pares de antenas
    for (Vertice* a = lista; a != NULL; a = a->prox) {
        for (Vertice* b = a->prox; b != NULL; b = b->prox) {
            if (a->frequencia == b->frequencia) {
                if (a->x == b->x && abs(a->y - b->y) == 2) {
                    int meioY = (a->y + b->y) / 2;
                    if (!efeitoExiste(efeitos, totalEfeitos, a->x, meioY)) {
                        printf("Vertical: (%d, %d)\n", a->x, meioY);
                        efeitos[totalEfeitos][0] = a->x;
                        efeitos[totalEfeitos][1] = meioY;
                        totalEfeitos++;
                        total++;
                    }
                }
                // Verifica se estão alinhadas horizontalmente a 2 unidades de distância
                else if (a->y == b->y && abs(a->x - b->x) == 2) {
                    int meioX = (a->x + b->x) / 2;
                    if (!efeitoExiste(efeitos, totalEfeitos, meioX, a->y)) {
                        printf("Horizontal: (%d, %d)\n", meioX, a->y);
                        efeitos[totalEfeitos][0] = meioX;
                        efeitos[totalEfeitos][1] = a->y;
                        totalEfeitos++;
                        total++;
                    }
                }
            }
        }
    }
    if (total == 0) {
        printf("Nenhum efeito nefasto encontrado.\n");
    }
    return total;
}
#pragma endregion
#pragma region Libertar Memória
/**
 * @brief Liberta toda a memória alocada para a lista de antenas (vértices).
 *
 * Esta função percorre a lista ligada de antenas e liberta cada nó da memória.
 * Não liberta as listas de adjacências associadas a cada antena!
 *
 * @param lista Apontador para o início da lista de vértices (antenas).
 * @return Número total de vértices (antenas) libertados da memória.
 */
int libertarMemoria(Vertice *lista) {
    int contador = 0;
    while (lista) {
        Vertice *temp = lista;
        lista = lista->prox;
        free(temp);  // Liberta o vértice atual
        contador++;  // Conta quantos foram libertados
    }
    return contador;
}
#pragma endregion
#pragma region Listar Antenas
/**
 * @brief Lista todas as antenas da estrutura ligada de vértices.
 *
 * Esta função percorre a lista ligada de antenas (vértices) e mostra no ecrã
 * a frequência e as coordenadas (x, y) de cada uma.
 *
 * @param lista Apontador para o início da lista de vértices (antenas).
 * @return Número total de antenas listadas.
 */
int listarAntenas(Vertice *lista) {
    int contador = 0;
    printf("\nLista de Antenas:\n");
    printf("Frequência | Coordenadas (x, y)\n");
    printf("-------------------------------\n");
    while (lista) { //desde que 
        printf("    %c      |    (%d, %d)\n", lista->frequencia, lista->x, lista->y);
        lista = lista->prox;  
        contador++;        
    }
    return contador;  
}
#pragma endregion
#pragma region Carregar Antenas do Ficheiro
/**
 * @brief Carrega as antenas a partir de um ficheiro de texto.
 * 
 * Esta função lê um ficheiro "antenas.txt" interpretando cada caracter relevante
 * como uma antena com frequência e insere cada antena na estrutura de grafo como 
 * um novo vértice. 
 * 
 * Caracteres como '.' (ponto), ' ' (espaço) e '\n' são ignorados.
 * 
 * @param nomeFicheiro Nome do ficheiro de texto a ler (ex: "antenas.txt")
 * @return Apontador para a lista ligada de vértices (antenas) carregadas
 */
Vertice* carregarAntenasDeFicheiro(char *nomeFicheiro) {
    FILE *file = fopen(nomeFicheiro, "r");  
    if (!file) {
        return NULL;  
    }
    Vertice *lista = NULL;  
    int linha = 0, resultado;
    char linhaFicheiro[250]; // Buffer para guardar cada linha lida do ficheiro
    while (fgets(linhaFicheiro, sizeof(linhaFicheiro), file)) {
        for (int coluna = 0; linhaFicheiro[coluna] != '\n' && linhaFicheiro[coluna] != '\0'; coluna++) {
            // Ignora os caracteres que não representam antenas
            if (linhaFicheiro[coluna] != '.' && linhaFicheiro[coluna] != '\n' && linhaFicheiro[coluna] != ' ') {
                // Cria uma nova antena com frequência, linha e coluna (ajustadas para não começar em 0)
                Vertice *nova = criarAntena(linhaFicheiro[coluna], linha + 1, coluna + 1);
                lista = InsereAntena(nova, lista, &resultado);
            }
        }
        linha++; 
    }
    fclose(file);  
    return lista;  
}
#pragma endregion
#pragma region Guardar em ficheiro Binário
/**
 * @brief Guarda a lista de antenas num ficheiro binário.
 *
 * Esta função percorre a lista ligada de antenas e escreve cada vértice (antena)
 * no ficheiro binário "antenas.bin". 
 *
 * @param lista Apontador para o início da lista de antenas.
 * @return int Retorna 0 em caso de sucesso ou -1 em caso de erro.
 */
int guardarAntenasEmFicheiroBinario(Vertice *lista) {
    FILE *file = fopen("antenas.bin", "wb");  
    if (!file) {
        return -1;
    }
    Vertice *aux = lista; // Apontador auxiliar para percorrer a lista
    // Escreve cada vértice no ficheiro até ao fim da lista
    while (aux) {
        // fwrite escreve 1 estrutura Vertice do ponteiro aux no ficheiro
        if (fwrite(aux, sizeof(Vertice), 1, file) != 1) {
            fclose(file); 
            return -1;
        }
        aux = aux->prox; 
    }
    fclose(file); 
    return 0; 
}
#pragma endregion
#pragma region Limpar
/**
 * @brief Marca todos os vértices da lista como não visitados.
 *
 * Esta função é chamada antes de executar uma DFS para garantir
 * que o estado "visitado" de cada vértice está limpo.
 *
 * @param lista Apontador para o início da lista de vértices (antenas).
 */
int limparVisitados(Vertice* lista) {
    if (!lista) return 0;
    while (lista) {
        lista->visitado = 0;
        lista = lista->prox;
    }
    return 1; 
}
#pragma endregion
#pragma region Profundidade
/**
 * @brief Realiza uma busca em profundidade (DFS) a partir de uma antena.
 *
 * A função visita recursivamente todas as antenas ligadas (adjacentes)
 * a partir do vértice inicial, imprimindo as coordenadas e frequência.
 *
 * @param atual Apontador para o vértice atual da DFS.
 */
int dfs(Vertice* atual) {
    if (!atual) return 0;           
    if (atual->visitado) return 1;  
    atual->visitado = 1;
    printf("(%d, %d) freq %c\n", atual->x, atual->y, atual->frequencia);
    AdjD* adj = atual->adjacencias;
    while (adj) {
        dfs(adj->destino);  //  ignoram retorno
        adj = adj->next;
    }
    return 1; 
}
#pragma endregion
#pragma region Encontrar Caminhos
/**
 * @brief Encontra e imprime todos os caminhos possíveis entre duas antenas.
 *
 * Utiliza o algoritmo DFS para explorar todos os caminhos do vértice atual
 * até ao destino. Os caminhos encontrados são apresentados através da função por "imprimirCaminho()".
 *
 * @param atual   Apontador para o vértice atual no percurso.
 * @param destino Apontador para o vértice de destino.
 * @param caminho Array de apontadores que guarda o caminho atual.
 * @param pos     Posição atual no array do caminho (uso DFS - Profundidade).
 */
int encontrarCaminhos(Vertice* atual, Vertice* destino, Vertice* caminho[], int pos) {
    if (!atual || atual->visitado) return 0; 
    atual->visitado = 1;
    caminho[pos] = atual;
    pos++;
    if (atual == destino) {
        imprimirCaminho(caminho, pos); 
    } else {
        AdjD* adj = atual->adjacencias;
        while (adj) {
            encontrarCaminhos(adj->destino, destino, caminho, pos); 
            adj = adj->next;
        }
    }
    atual->visitado = 0; 
    return 1; 
}
#pragma endregion
#pragma region Imprimir Caminho
/**
 * @brief Imprime um caminho completo entre duas antenas.
 *
 * @param caminho Array com os vértices do caminho.
 * @param tamanho Número de vértices no caminho.
 */
int imprimirCaminho(Vertice* caminho[], int tamanho) {
    if (!caminho || tamanho <= 0) return 0; 
    for (int i = 0; i < tamanho; i++) {
        if (!caminho[i]) return 0; 
        printf("(%d, %d)", caminho[i]->x, caminho[i]->y);
        if (i < tamanho - 1) printf(" -> ");
    }
    printf("\n");
    return 1; 
}
#pragma endregion
#pragma region Listar Interseções
/**
 * @brief Lista interseções entre antenas de frequências distintas.
 *
 * Percorre a lista de vértices (antenas) e identifica posições (coordenadas)
 * onde existem duas antenas com frequências diferentes na mesma
 * posição (x, y).
 *
 * @param lista Apontador para o início da lista ligada de vértices (antenas).
 * @param f1 Caractere que representa a primeira frequência a ser comparada.
 * @param f2 Caractere que representa a segunda frequência a ser comparada.
 */
int listarIntersecoes(Vertice* lista, char f1, char f2) {
    if (!lista) return 0; 
    printf("Interseções entre antenas %c e %c:\n", f1, f2);
    int encontrou = 0;
    for (Vertice* aux1 = lista; aux1 != NULL; aux1 = aux1->prox) {
        for (Vertice* aux2 = aux1->prox; aux2 != NULL; aux2 = aux2->prox) {
            if (((aux1->frequencia == f1 && aux2->frequencia == f2) ||
                 (aux1->frequencia == f2 && aux2->frequencia == f1)) &&
                aux1->x == aux2->x && aux1->y == aux2->y) {
                printf("Interseção em (%d, %d)\n", aux1->x, aux1->y);
                encontrou = 1;
            }
        }
    }
    return 1; 
}
