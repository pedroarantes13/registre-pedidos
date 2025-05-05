#pragma once

#define ARQUIVO_BINARIO "pedidos.bin"

struct dados_pedido {
    int mesa;
    int pessoas;
    char prato[50];
    int qtd_prato;
    char bebida[50];
    int qtd_bebida;
    float subtotal;
};

// Nova função combinada:
void registrar_e_salvar(int mesa, int pessoas, char prato[], int qtd_prato, char bebida[], int qtd_bebida);

int carregar_pedidos(struct dados_pedido pedidos[], int max_pedidos);

void exibir_pedido(struct dados_pedido info);
void exibir_resumo(struct dados_pedido pedidos[], int num_pedidos);

void mid_line();
void top_bottom();
