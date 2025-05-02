#include <stdio.h>
#include <string.h>
#include "funcoes.h"

// Função auxiliar para exibir linha de separação

void mid_line(){
    printf("---------------------------\n");
}

// Função auxiliar para exibir linha destacada

void top_bottom(){
    printf("===========================\n");
}

// Registra o pedido, preenchendo a struct com os dados conhecidos

struct dados_pedido registrar_pedido(int mesa, char prato[], int qtd_prato, char bebida[], int qtd_bebida){

    // Declara a struct 

    struct dados_pedido info;

    info.mesa = mesa;

    strcpy(info.prato, prato);
    info.qtd_prato = qtd_prato;

    strcpy(info.bebida, bebida);
    info.qtd_bebida = qtd_bebida;

    // Valores fictícios

    float valor_prato = 30.0;
    float valor_bebida = 5.0;

    // Cálculo do subtotal a partir da quantidade e dos valores fictícios

    info.subtotal = (info.qtd_prato * valor_prato) + (info.qtd_bebida * valor_bebida);

    return info;
}

// Exibe um pedido, formatado no terminal

void exibir_pedido(struct dados_pedido info){
    printf("Mesa: %d\n", info.mesa);
    printf("Prato: %s (x%d)\n", info.prato, info.qtd_prato);
    printf("Bebida: %s (x%d)\n", info.bebida, info.qtd_bebida);
    printf("Subtotal: R$%.2f\n", info.subtotal);
    mid_line();
}

// Exibe todos os pedidos e o total a pagar

void exibir_resumo(struct dados_pedido pedidos[], int num_pedidos){
    float total_geral = 0;

    printf("\n === RESUMO FINAL DOS PEDIDOS === \n");

    for (int i=0; i<num_pedidos; i++){
        exibir_pedido(pedidos[i]);
        total_geral += pedidos[i].subtotal;
    }

    printf("TOTAL GERAL: R$%.2f\n", total_geral);
    top_bottom();
}

// Salva os pedidos fornecidos no arquivo binário (acrescenta ao final)

void salvar_pedidos(struct dados_pedido pedidos[], int num_pedidos){
    FILE *arquivo = fopen(ARQUIVO_BINARIO, "ab");
    
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fwrite(pedidos, sizeof(struct dados_pedido), num_pedidos, arquivo);
    fclose(arquivo);
    printf("Pedidos salvos com sucesso!\n");

}

// Carrega os pedidos do arquivo binário (se existir)

int carregar_pedidos(struct dados_pedido pedidos[], int max_pedidos){
    FILE *arquivo = fopen(ARQUIVO_BINARIO, "rb");

    if (arquivo == NULL){
        printf("Arquivo de pedidos nao encontrado!\n");
        return 0;
    }

    int lidos = fread(pedidos, sizeof(struct dados_pedido), max_pedidos, arquivo);
    fclose(arquivo);
    return lidos;
}
