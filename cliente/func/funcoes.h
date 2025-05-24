// Esse programa faz parte de uma avaliação da faculdade, que é um sistema de pedidos de restaurante. Nesse arquivo temos o protótipo da função que armazena os nomes e a quantidade dos itens do pedido e retorna os mesmos, juntamente com oo total da conta

#pragma once

#define ARQUIVO_BINARIO "pedidos.bin"
#define MAX_CUPONS 5

// Estrutura para os cupons de desconto

struct cupom_desconto {
    char codigo[20];
    float porcentagem;
};

// Estrutura principal para os pedidos

struct dados_pedido {
    int mesa;
    int pessoas;
    char item[50];
    int tipo;        // Comida (1) ou bebida (2)
    int quantidade;
    float subtotal;
    float valor_individual;
    char cupom[20];
    float desconto;
};

// Registra o pedido e salva no arquivo

void registrar_e_salvar(struct dados_pedido*, int*, int, int, char[], int, int, const char*, float);

// Lê o arquivo e preenche o vetor

int carregar_pedidos(struct dados_pedido vetor[], int *total_pedidos);

// Exibe um pedido individual

void exibir_pedido(struct dados_pedido p, int eh_relatorio);

// Relatório, resumo e estatísticas

void exibir_resumo(struct dados_pedido pedidos[], int num_pedidos);

void gerar_relatorio_final();

void calcular_metricas_gerais(struct dados_pedido pedidos[], int total_pedidos);

void calcular_subtotal_por_tipo(struct dados_pedido pedidos[], int total_pedidos);

void gerar_ranking(struct dados_pedido pedidos[], int total_pedidos);

// Cupons

void inicializar_cupons(struct cupom_desconto cupons[]);

int aplicar_cupom(char codigo[], struct cupom_desconto cupons[], float *desconto);

// Estética

void mid_line();

void top_bottom();
