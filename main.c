/**
 * @file main.c
 * @author Ricardo
 * @brief Implementação principal para gerir antenas sem menu interativo.
 * @version 0.1
 * @date 2025-03-24
 * 
 * @copyright Copyright (c) 2025
 */

 #include "funcoes.h"
 #include <stdio.h>
 #include <stdlib.h>
 
 /**
  * @brief Função principal do programa.
  * 
  * Carrega antenas de um ficheiro, insere algumas manualmente, remove uma,
  * deduz os efeitos nefastos e lista as antenas existentes.
  */
 int main() {
     
     Antena *listaAntenas = NULL;  // Ponteiro para a lista de antenas.
     


 
     
     /**
      * Carrega automaticamente antenas do ficheiro "antenas.txt".
      * Se o ficheiro não existir a lista inicialmente vai estar vazia.
      */
     listaAntenas = carregarAntenasDeFicheiro("antenas.txt");

     
 

     /**
      * Insere algumas antenas manualmente.
      */
     listaAntenas = inserirAntena(listaAntenas, 'A', 2, 3);
     listaAntenas = inserirAntena(listaAntenas, 'A', 3, 3);
     listaAntenas = inserirAntena(listaAntenas, 'A', 6, 3);
     listaAntenas = inserirAntena(listaAntenas, 'B', 4, 5);
     listaAntenas = inserirAntena(listaAntenas, 'A', 1, 6);
     listaAntenas = inserirAntena(listaAntenas, 'C', 7, 8);
     

     

     /**
      * Remove a antena com as coordenadas (2,3).
      */
     listaAntenas = removerAntena(listaAntenas, 2, 3);




     /**
      * Analisa as antenas e verifica a presença de efeitos nefastos e os locais afetados.
      */
     deduzirEfeitosNefastos(listaAntenas);
    
 

     /**
      * Lista todas as antenas.
      */
     listarAntenas(listaAntenas);

     



     /**
      * Liberta memória para evitar desperdício da mesma.
      */
     libertarMemoria(listaAntenas);
    

     return 0;
 }
 