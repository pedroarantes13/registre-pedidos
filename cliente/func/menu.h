#pragma once // Garante que o arquivo será incluído apenas uma vez

#define FUNCOES_H

#include <stdio.h>
#include "funcoes.h"

#define TAM_NOME 50 // Tamanho máximo para nome do cliente
#define MAX_ITEM 50 // Número máximo de itens por pedido

// Estrutura para armazenar os dados de um item
struct item {
    char nome[50];
    int quantidade;
    float preco_unitario;
};

// Estrutura para armazenar os dados de um pedido
struct pedido {
    int id_pedido;
    char nome_cliente[TAM_NOME];
    struct item itens[MAX_ITEM];
    int total_itens;
    float total_pedido;
};

// Mostra o menu de pratos principais
void mostrarPratosPrincipais(void);

// Mostra o menu de bebidas
void mostrarBebidas(void);

// Mostra o menu de sobremesas
void mostrarSobremesas(void);

// Mostra o menu principal e retorna a opção escolhida
int mostrarMenu(void);

// Faz um pedido e preenche a estrutura
void fazerPedido(struct pedido* p);

// Pausa a tela até que o usuário aperte ENTER
void pausarTela(void);