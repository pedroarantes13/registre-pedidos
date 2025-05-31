#pragma once
#define FUNCOES_H

#include <stdio.h>

#define TAM_NOME 50
#define MAX_ITEM 50


struct item {
    char nome[50];
    int quantidade;
    float preco_unitario;
};

struct pedido {
    int id_pedido;
    char nome_cliente[TAM_NOME];
    struct item itens[MAX_ITEM];
    int total_itens;
    float total_pedido;
};


void mostrarPratosPrincipais(void);
void mostrarBebidas(void);
void mostrarSobremesas(void);
void esperarEnter(void);


int mostrarMenu(void);


void fazerPedido(struct pedido* p);
