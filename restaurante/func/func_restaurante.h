// Definições de funções e estruturas de dados para o restaurante

// Padrão de nome de arquivo binário onde serão salvos os dados de menu do restaurante
#define STD_BIN "cardapio.bin"

#pragma once

//------------ ESTRUTURAS DE DADOS ------------

// Struct dos dados dos itens do cardápio
typedef struct {
  char item[50];
  int tipo;
  float valor;
} Cardapio;

// ------------ PROTÓTIPOS DAS FUNÇÕES DE DADOS E FUNCIONALIDADES DO RESTAURANTE ------------ (PEDRO)

// Adiciona um item ao cardápio
int adicionar_item(Cardapio);

// Carrega o cardápio do arquivo binário para a memória
int carregar_cardapio(char *filename, Cardapio **cardapio);

// Imprime o cardápio na tela
int imprimir_cardapio(char *filename);

// Converte o tipo de item em uma string para exibição
char* tipo_str(int tipo);

// Conta o total de itens no cardápio
int total_itens_cardapio(char *filename);

// Edita um item do cardápio no arquivo binário
int editar_item_cardapio(char *filename, int indice, Cardapio *novo_item);

// Remove um item do cardápio no arquivo binário
int remover_item_cardapio(char *filename, int indice);

// Verifica se um índice é válido para o cardápio
int verificar_indice_cardapio(char *filename, int indice);

int validar_tipo(int tipo); // Verifica se o tipo é válido (0, 1 ou 2)

int validar_valor(float valor); // Verifica se o valor é positivo

//------------- PROTÓTIPOS DAS FUNÇÕES DE MENUS E INTERAÇÕES COM O USUÁRIO ------------ (GEAN)

// Exibe o cardápio e permite ao usuário escolher um item
void menu_adicionar_item(); 

// Função principal do restaurante, exibe as opções do menu e executa as ações correspondentes
int menu_restaurante();

// Exibe o cardápio e permite ao usuário editar um item
void menu_editar_item(Cardapio *novo_item);

// Exibe o cardápio e permite ao usuário excluir um item
void menu_excluir_item();

