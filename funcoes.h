/**
 * @file funcoes.h
 * @author Ricardo (ricardopereira15jr@gmail.com)
 * @brief Declaração das funções e estrutura para manipulação de antenas.
 * @version 0.1
 * @date 2025-03-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #ifndef FUNCOES_H
 #define FUNCOES_H
 
 #include <stdio.h>
 #include <stdlib.h>
 
 /**
  * @struct Antena
  * @brief Estrutura que representa uma antena.
  * 
  * @var Antena::frequencia
  * Frequência da antena (representada como um caracter).
  * 
  * @var Antena::x
  * Coordenada X da posição da antena.
  * 
  * @var Antena::y
  * Coordenada Y da posição da antena.
  * 
  * @var Antena::prox
  * Ponteiro para a próxima antena na lista ligada.
  */
 typedef struct Antena {
     char frequencia; //Frequência da antena (exemplos utilizados:'0', 'A', 'B', 'C')
     int x,y;       // Coordenadas da antena no plano (x, y)
     struct Antena *prox; //Ponteiro para a próxima antena da lista
 } Antena;
 




 /**
  * @brief Insere uma nova antena na lista.
  * 
  * @param lista Ponteiro para a lista de antenas.
  * @param frequencia Caracter que representa a frequência da antena.
  * @param x Coordenada X da antena.
  * @param y Coordenada Y da antena.
  * @return Insere e devolve o ponteiro atualizado na  lista.
  */
 Antena* inserirAntena(Antena *lista, char frequencia, int x, int y);
 





 /**
  * @brief Remove uma antena com base nas coordenadas (x, y).
  * 
  * @param lista Ponteiro para a lista de antenas.
  * @param x Coordenada X da antena a ser removida.
  * @param y Coordenada Y da antena a ser removida.
  * @return Ponteiro atualizado para a lista de antenas.
  */
 Antena* removerAntena(Antena *lista, int x, int y);
 




 /**
  * @brief Lista todas as antenas armazenadas na lista.
  * 
  * @param lista Ponteiro para a lista de antenas.
  */
 void listarAntenas(Antena *lista);
 



 /**
  * @brief Procura e imprime os efeitos nefastos causados pelas antenas.
  * 
  * @param lista Ponteiro para a lista de antenas.
  */
 void deduzirEfeitosNefastos(Antena *lista);
 



 /**
  * @brief Liberta a memória para a lista de antenas.
  * 
  * @param lista Ponteiro para a lista de antenas.
  */
 void libertarMemoria(Antena *lista);
 



 /**
  * @brief Carrega antenas a partir do ficheiro de texto "antenas.txt".
  * 
  * @param nomeFicheiro Nome do ficheiro que contém as antenas.
  * @return Ponteiro para a lista de antenas carregadas.
  */
 Antena* carregarAntenasDeFicheiro(const char *nomeFicheiro);
 

 #endif // FUNCOES_H
 