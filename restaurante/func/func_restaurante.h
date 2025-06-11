// Definições de funções e estruturas de dados para o restaurante

// Padrão de nome de arquivo binário onde serão salvos os dados de menu do restaurante
#define STD_BIN "cardapio.bin"

#pragma once

// Struct dos dados do Menu, com mudança do nome de tipo para itemMenu
typedef struct {
  char item[50];
  int tipo;
  float valor;
} Cardapio;

int adicionar_item(Cardapio);

int carregar_cardapio(char *filename, Cardapio **cardapio);

int imprimir_cardapio(char *filename);

char* tipo_str(int tipo);

int total_itens_cardapio(char *filename);

int editar_item_cardapio(char *filename, int indice, Cardapio *novo_item);

int remover_item_cardapio(char *filename, int indice);

int verificar_indice_cardapio(char *filename, int indice);

//Prototipos do menu restaurante

void adicionarItem(); 

int menu_restaurante();

void menu_editar_item(Cardapio *novo_item);

void menu_excluir_item();

