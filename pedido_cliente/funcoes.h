// Esse programa faz parte de uma avaliação da faculdade, que é um sistema de pedidos de restaurante. Nesse arquivo temos o protótipo da função que armazena os nomes e a quantidade dos itens do pedido e retorna os mesmos, juntamente com oo total da conta

#pragma once

// Define o nome do arquivo binário usado

#define ARQUIVO_BINARIO "pedidos.bin"

// Estrutura que representa um pedido feito

struct dados_pedido {
    int mesa;
    char prato[50];
    int qtd_prato;
    char bebida[50];
    int qtd_bebida;
    float subtotal;
};

// Protótipos das funções

struct dados_pedido registrar_pedido(int mesa, char prato[], int qtd_prato, char bebida[], int qtd_bebida);

void exibir_pedido(struct dados_pedido info);

void exibir_resumo(struct dados_pedido pedidos[], int num_pedidos);

void salvar_pedidos(struct dados_pedido pedidos[], int num_pedidos);

int carregar_pedidos(struct dados_pedido pedidos[], int max_pedidos);

void mid_line();

void top_bottom();