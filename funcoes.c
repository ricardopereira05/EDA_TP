/**
 * @file funcoes.c
 * @author Ricardo (ricardopereira15jr@gmail.com)
 * @brief Implementação das funções para manipulação de uma lista ligada de antenas.
 * @version 0.1
 * @date 2025-03-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "funcoes.h"
 #include <stdbool.h>
 #include <stdio.h>
 #include <stdlib.h>
 

 /**
  * @brief Insere uma nova antena na lista ligada de forma ordenada e não admite repetições das coordenadas.
  * 
  * Cria uma nova antena e insere-a na lista de forma ordenada, garantindo que não existam 
  * repetições de antenas com a mesma frequência e coordenadas.
  * A inserção ocorre de forma crescente priorizando a coordenada x (as linhas) e em caso de igualdade, a coordenada y (colunas).
  * A função guarda as antenas no arquivo "antenas2.txt".
  * 
  * @param lista Ponteiro para a lista de antenas.
  * @param frequencia Caracter que representa a frequência da antena.
  * @param x Coordenada X da antena.
  * @param y Coordenada Y da antena.
  * @return Antena* Retorna a lista atualizada com a nova antena, se for inserida.
  */
 
 Antena* inserirAntena(Antena *lista, char frequencia, int x, int y) {
     // Cria memória para a nova antena
     Antena *nova = (Antena *)malloc(sizeof(Antena));
     if (!nova) {
         printf("Erro ao criar memória!\n");
         return lista;
     }
     nova->frequencia = frequencia;
     nova->x = x;
     nova->y = y;
     nova->prox = NULL;
 
     // Se a lista estiver vazia a nova antena torna-se o primeiro nó
     if (lista == NULL) {
         // Abre o arquivo para guardar a antena
         FILE *file = fopen("antenas2.txt", "a");
         if (!file) {
             printf("Erro ao abrir o ficheiro para guardar antenas!\n");
         } else {
             fprintf(file, "%c %d %d\n", frequencia, x, y);  // Guarda no arquivo
             fclose(file);
         }
         return nova;
     }
 
     // Verifica se a antena já existe na lista e não permite repetição
     Antena *aux = lista;
     while (aux != NULL) {
         if (aux->frequencia == frequencia && aux->x == x && aux->y == y) {
             printf("Antena já existe!\n");
             free(nova);
             return lista;
         }
         aux = aux->prox;
     }
 
 
     // Inserção ordenada (primeiro por x, depois por y em caso de igualdade)
     if (lista->x > nova->x || (lista->x == nova->x && lista->y > nova->y)) {  //   || (or/ou)
         nova->prox = lista;
         // Guardar a antena no arquivo
         FILE *file = fopen("antenas2.txt", "a");
         if (!file) {
             printf("Erro ao abrir o ficheiro para guardar antenas!\n");
         } else {
             fprintf(file, "%c %d %d\n", frequencia, x, y);  // Guarda no arquivo
             fclose(file);
         }
         return nova;
     }
 
     // Percorre a lista para encontrar a posição correta
     Antena *anterior = NULL;
     aux = lista;
     while (aux != NULL && (aux->x < nova->x || (aux->x == nova->x && aux->y < nova->y))) {
         anterior = aux;
         aux = aux->prox;
     }
 
     // Insere a nova antena na posição correta
     if (anterior != NULL) {
         anterior->prox = nova;
     }
     nova->prox = aux;
 
     // Guardar a antena no arquivo
     FILE *file = fopen("antenas2.txt", "a");
     if (!file) {
         printf("Erro ao abrir o ficheiro para guardar antenas!\n");
     } else {
         fprintf(file, "%c %d %d\n", frequencia, x, y);  // Guarda no arquivo
         fclose(file);
     }
 
     return lista;
 }

 


 
 /*Antena* inserirAntena(Antena *lista, char frequencia, int linha, int coluna) {
     Antena *nova = (Antena *)malloc(sizeof(Antena));
     if (!nova) {
         printf("Erro ao criar memória!\n");
         return lista;
     }
     nova->frequencia = frequencia;
     nova->x = linha;  
     nova->y = coluna;  
     nova->prox = lista;  // Insere no início da lista
 
     // Abrir o ficheiro para adicionar a nova antena
     FILE *file = fopen("antenas.txt", "a");
     if (!file) {
         printf("Erro ao abrir o ficheiro!\n");
         return lista;
     }
     fprintf(file, "%c %d %d\n", frequencia, linha, coluna);
     fclose(file);  // Fecha o ficheiro
 
     return nova;  // Retorna o primeiro nó
 }
 */
 


 

/**
 * @brief Remove uma antena da lista ligada com base nas coordenadas (x, y).
 * 
 * A função percorre a lista ligada e ao encontrar a antena com as coordenadas fornecidas
 * remove e ajusta os ponteiros. Após a remoção, reescreve o arquivo "antenas2.txt" 
 * para atualizar e guardar sem a antena removida.
 * 
 * @param lista Ponteiro para a lista de antenas.
 * @param x Coordenada X da antena a ser removida.
 * @param y Coordenada Y da antena a ser removida.
 * @return Antena* Retorna a lista atualizada após a remoção da antena.
 */


Antena* removerAntena(Antena *lista, int x, int y) {
    Antena *atual = lista, *anterior = NULL;

    // Percorre a lista para encontrar a antena com as coordenadas especificadas
    while (atual) {
        if (atual->x == x && atual->y == y) {
            // Se for o primeiro nó da lista
            if (anterior == NULL) {
                lista = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            // Liberta a memória da antena removida
            free(atual);
            printf("Antena removida com sucesso!\n");

            // Atualiza ficheiro sem a removida
            FILE *file = fopen("antenas2.txt", "w");
            if (!file) {
                printf("Erro ao abrir o ficheiro para guardar antenas!\n");
                return lista;
            }

            // Percorre a lista e grava os dados atualizados no ficheiro
            Antena *aux = lista;
            while (aux) {
                fprintf(file, "%c %d %d\n", aux->frequencia, aux->x, aux->y);
                aux = aux->prox;
            }
            fclose(file);
            printf("Antena removida no ficheiro!\n");
            return lista;
        }
        anterior = atual;
        atual = atual->prox;
    }

    // Caso a antena não seja encontrada na lista
    printf("Antena não encontrada!\n");
    return lista;
}


 
 /*Antena* removerAntena(Antena *lista, int linha, int coluna) {
     Antena *atual = lista, *anterior = NULL;
     int removido = 0; // Flag para verificar se removemos a antena
 
     while (atual) {
         if (atual->x == linha && atual->y == coluna) {  
             if (anterior == NULL) {
                 lista = atual->prox;  // Remover a cabeça da lista
             } else {
                 anterior->prox = atual->prox;  // Pular o nó removido
             }
             free(atual);
             removido = 1;
             break;
         }
         anterior = atual;
         atual = atual->prox;
     }
 
     if (!removido) {
         printf("Antena não encontrada!\n");
         return lista;
     }
 
     // Criar um novo ficheiro temporário para reescrever a lista sem a antena removida
     FILE *file = fopen("antenas_temp.txt", "w");
     if (!file) {
         printf("Erro ao abrir o ficheiro!\n");
         return lista;
     }
 
     // Percorrer a lista ligada e gravar os dados no novo ficheiro
     Antena *aux = lista;
     while (aux) {
         fprintf(file, "%c %d %d\n", aux->frequencia, aux->x, aux->y);
         aux = aux->prox;
     }
     fclose(file);
 
     // Substituir o ficheiro inicial pelo novo
     remove("antenas.txt");
     rename("antenas_temp.txt", "antenas.txt");
 
     printf("Antena removida do ficheiro com sucesso!\n");
     return lista;
 }
 */ 
 
 

 
 /**
  * @brief Carrega antenas a partir de um ficheiro e as insere na lista ligada.
  * 
  * A função lê um ficheiro linha por linha, considerando cada caractere (exceto '.' e '\n')
  * como uma antena, e insere-a na lista ligada com suas respectivas coordenadas.
  * 
  * @param nomeFicheiro Nome do ficheiro contendo a matriz de antenas.
  * @return Antena* Retorna um ponteiro para a lista ligada contendo as antenas carregadas.
  */

 Antena* carregarAntenasDeFicheiro(const char *nomeFicheiro) {
     FILE *file = fopen(nomeFicheiro, "r");
     if (!file) {
         printf("Erro ao abrir o ficheiro!\n");
         return NULL;
     }
 
     Antena *lista = NULL;
     int linha = 0;
     char linhaFicheiro[256];
 
     // Lê cada linha do ficheiro e adiciona as antenas na lista
     while (fgets(linhaFicheiro, sizeof(linhaFicheiro), file)) {
         for (int coluna = 0; linhaFicheiro[coluna] != '\n' && linhaFicheiro[coluna] != '\0'; coluna++) { //  \n indica fim de linha
             if (linhaFicheiro[coluna] != '.' && linhaFicheiro[coluna] != '\n') {
                 lista = inserirAntena(lista, linhaFicheiro[coluna], linha + 1, coluna + 1); //inseri +1 pra não começar no 0 as coordenadas
             }
         }
         linha++;
     }
 
     fclose(file);
     return lista;
 }



 
 /**
  * @brief Lista todas as antenas armazenadas na lista ligada.
  * 
  * A função percorre a lista e imprime as informações de cada antena na consola.
  * 
  * @param lista Ponteiro para a lista de antenas.
  */

 void listarAntenas(Antena *lista) {
     printf("\nLista de Antenas:\n");
     printf("Frequência | Coordenadas (x, y)\n");
     printf("-------------------------------\n");
 
     while (lista) {
         printf("    %c      |    (%d, %d)\n", lista->frequencia, lista->x, lista->y);
         lista = lista->prox;
     }
 }
 


 /**
  * @brief Verifica se o efeito nefasto já está na lista de efeitos.
  * 
  * A função é utilizada para evitar a duplicação de coordenadas.
  * 
  * @param efeitos Matriz que contém as coordenadas dos efeitos nesfatos.
  * @param totalEfeitos Número total de efeitos.
  * @param x Coordenada X do efeito a verificar.
  * @param y Coordenada Y do efeito a verificar.
  * @return true Se o efeito já existe na lista.
  * @return false Se o efeito ainda não está na lista.
  */
 
 bool efeitoExiste(int efeitos[][2], int totalEfeitos, int x, int y) {
     for (int i = 0; i < totalEfeitos; i++) {
         if (efeitos[i][0] == x && efeitos[i][1] == y) {
             return true; // O efeito já existe na lista
         }
     }
     return false; // O efeito ainda não existe na lista
 }
 




 /**
  * @brief Deduz e imprime as localizações onde existe efeitos nefastos causados por antenas da mesma frequência.
  * 
  * A função verifica todas as antenas da lista e identifica pares alinhados (horizontalmente ou verticalmente)
  * que a distância tem de ser múltiplo de 2. O ponto médio entre essas antenas é considerado um ponto de efeito nefasto.
  * @param lista Ponteiro para a lista de antenas.
  */
 void deduzirEfeitosNefastos(Antena *lista) {
     printf("\nLocalizações com efeito nefasto:\n");
     printf("Coordenadas (x, y)\n");
     printf("-------------------\n");
 
     int efeitos[100][2]; //  Guarda efeitos encontrados
     int totalEfeitos = 0;
 
     // Percorre todas as antenas para identificar efeitos nefastos
     for (Antena *a1 = lista; a1 != NULL; a1 = a1->prox) {
         for (Antena *a2 = lista; a2 != NULL; a2 = a2->prox) {
             if (a1 != a2 && a1->frequencia == a2->frequencia) {
                 int dx = a2->x - a1->x;
                 int dy = a2->y - a1->y;
 
                 // Verifica se a distância é múltipla de 2
                 if ((dx == 0 && abs(dy) % 2 == 0) || (dy == 0 && abs(dx) % 2 == 0)) {
                     int meioX = a1->x + dx / 2;
                     int meioY = a1->y + dy / 2;
 
                     // Só imprime se o efeito ainda não está na lista dos efeitos nesfatos
                     if (!efeitoExiste(efeitos, totalEfeitos, meioX, meioY)) {
                         printf("     (%d, %d)\n", meioX , meioY);
                         efeitos[totalEfeitos][0] = meioX;
                         efeitos[totalEfeitos][1] = meioY;
                         totalEfeitos++;
                     }
                 }
             }
         }
     }
 
     if (totalEfeitos == 0) {
         printf("Nenhum efeito nefasto encontrado.\n");
     }
 }
 




 /**
  * @brief Liberta a memória que foi precisa pra execução
  * 
  * A função percorre a lista e remove e liberta cada nó da memória.
  * @param lista Ponteiro para a lista de antenas a ser libertada.
  */
 void libertarMemoria(Antena *lista) {
     while (lista) {
         Antena *temp = lista;
         lista = lista->prox;
         free(temp);
     }
 }
 