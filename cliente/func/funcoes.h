// Esse programa faz parte de uma avaliação da faculdade, que é um sistema de pedidos de restaurante. Nesse arquivo temos o protótipo da função que armazena os nomes e a quantidade dos itens do pedido e retorna os mesmos, juntamente com oo total da conta

#pragma once

#define ARQUIVO_BINARIO "pedidos.bin"

struct dados_pedido {
    int mesa;
    int pessoas;
    char item[50];   // Nome do item
    int tipo;        // Comida (1) ou bebida (2)
    int quantidade;
    float subtotal;
    float valor_individual;
};

// Registra o pedido e salva no arquivo

void registrar_e_salvar(
    struct dados_pedido *vetor,
    int *total_pedidos,
    int mesa,
    int pessoas,
    char item[],
    int tipo,
    int qtd_item
);

// Lê o arquivo e preenche o vetor

int carregar_pedidos(struct dados_pedido vetor[], int *total_pedidos);

// Exibe um pedido individual

void exibir_pedido(struct dados_pedido info);

// Relatório, resumo e estatísticas

void exibir_resumo(struct dados_pedido pedidos[], int num_pedidos);

void gerar_relatorio_final();

void calcular_metricas_gerais(struct dados_pedido pedidos[], int total_pedidos);

void calcular_subtotal_por_tipo(struct dados_pedido pedidos[], int total_pedidos);

void gerar_ranking(struct dados_pedido pedidos[], int total_pedidos);

// Estética

void mid_line();

void top_bottom();
