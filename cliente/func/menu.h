#pragma once // Garante que o arquivo será incluído apenas uma vez

#define MENU_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

// Chama as funcoes do necessarias

#include "funcoes.h"
#include "../../restaurante/func/func_restaurante.h"

// Mostra o menu de pratos principais
void mostrarPratosPrincipais(Cardapio *cardapio_ptr, int total_itens);

// Mostra o menu de bebidas
void mostrarBebidas(Cardapio *cardapio_ptr, int total_itens);

// Mostra o menu de sobremesas
void mostrarSobremesas(Cardapio *cardapio_ptr, int total_itens);

// Mostra o menu principal e retorna a opção escolhida
int mostrarMenu(void);

// Faz um pedido e preenche a estrutura
void fazerPedido(struct dados_pedido **pedidos_ptr,
int *total_pedidos_ptr, int *capacidade_ptr, Cardapio *cardapio_menu, int total_itens_cardapio);

// Pausa a tela até que o usuário aperte ENTER
void pausarTela(void);