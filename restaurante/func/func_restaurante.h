// Definições de funções e estruturas de dados para o restaurante

// Padrão de nome de arquivo binário onde serão salvos os dados de menu do restaurante
#define STD_BIN "cardapio.bin"

#pragma once

// Struct dos dados do Menu, com mudança do nome de tipo para itemMenu
typedef struct {
  char item[50];
  int tipo;
  float valor;
  int tempo_preparo;
} Cardapio;

void escrever_dados(Cardapio);

Cardapio* ler_dados(char filename[], int *num_itens);

//Pendente implementação
//    -> Utilizar a função ler_dados
//    -> Criar um contador para passar como parâmetro e criar loop de pintf's para imprimir os dados lidos
void imprimir_dados(char filename[], int *num_itens);
