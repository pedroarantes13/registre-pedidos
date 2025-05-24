#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"

// Imprime uma linha intermediária (visual)

void mid_line() {
    printf("-----------------------------------------------------\n");
}

// Imprime uma linha de topo/rodapé (visual)

void top_bottom() {
    printf("=====================================================\n");
}

// Registra um pedido e salva no arquivo binário

void registrar_e_salvar(
    struct dados_pedido *vetor,
    int *total_pedidos,
    int mesa,
    int pessoas,
    char item[],
    int tipo,
    int qtd_item
) {
    struct dados_pedido pedido;

    // Preenchimento da struct com os dados recebidos

    pedido.mesa = mesa;
    pedido.pessoas = pessoas;
    strncpy(pedido.item, item, sizeof(pedido.item));
    pedido.item[sizeof(pedido.item) - 1] = '\0';
    pedido.tipo = tipo;
    pedido.quantidade = qtd_item;

    // Preços fictícios

    float valor_comida = 30.0;
    float valor_bebida = 5.0;

    // Cálculo do subtotal baseado no tipo

    if (tipo == 1) {
        pedido.subtotal = qtd_item * valor_comida;
    } else if (tipo == 2) {
        pedido.subtotal = qtd_item * valor_bebida;
    } else {
        return;
    }

    // Valor individual da conta

    pedido.valor_individual = pedido.subtotal / pessoas;

    // Adiciona ao vetor
    vetor[*total_pedidos] = pedido;
    (*total_pedidos)++;

    // Salva no arquivo no modo append

    FILE *arquivo = fopen(ARQUIVO_BINARIO, "ab");
    if (arquivo == NULL) {
        printf("Erro ao salvar pedido no arquivo binario\n");
        return;
    }

    fwrite(&pedido, sizeof(struct dados_pedido), 1, arquivo);
    fclose(arquivo);
}

// Carrega os pedidos do arquivo binário para o vetor

int carregar_pedidos(struct dados_pedido vetor[], int *total_pedidos) {
    FILE *arquivo = fopen(ARQUIVO_BINARIO, "rb");
    if (arquivo == NULL) {
        *total_pedidos = 0;
        return 0;
    }

    int lidos = fread(vetor, sizeof(struct dados_pedido), 200, arquivo);
    fclose(arquivo);

    *total_pedidos = lidos;
    return lidos;
}

// Exibe um pedido individual

void exibir_pedido(struct dados_pedido p) {
    printf("Mesa %d | Pessoas: %d\n", p.mesa, p.pessoas);
    printf("Item: %s (%dx) [%s]\n", p.item, p.quantidade,
           (p.tipo == 1 ? "Comida" : "Bebida"));
    printf("Subtotal: R$%.2f\n", p.subtotal);
    mid_line();
}

// Exibe um resumo de todos os pedidos

void exibir_resumo(struct dados_pedido vetor[], int total_pedidos) {
    float total_geral = 0;
    printf("\n === RESUMO DOS PEDIDOS === \n");

    for (int i = 0; i < total_pedidos; i++) {
        exibir_pedido(vetor[i]);
        total_geral += vetor[i].subtotal;
    }

    printf("TOTAL ARRECADADO: R$%.2f\n", total_geral);
    top_bottom();
}

// Calcular: total arrecadado, total de itens vendidos e arrecadação média por mesa

void calcular_metricas_gerais(struct dados_pedido pedidos[], int total_pedidos){
    float total_arrecadado = 0;
    int total_itens = 0;
    int mesas[100] = {0};
    int total_mesas = 0;

    for (int i=0; i < total_pedidos; i++){

        total_arrecadado += pedidos[i].subtotal;
        total_itens += pedidos[i].quantidade;

        // Conta mesas únicas

        int mesa_existe = 0;

        for (int j=0; j < total_mesas; j++){
            if (mesas[j] == pedidos[i].mesa) {
                mesa_existe = 1;
                break;
            }
        }

        if (!mesa_existe) mesas[total_mesas++] = pedidos[i].mesa;
    }

    printf("\n=== RESUMO GERAL ===\n");

    top_bottom();

    printf("TOTAL ARRECADADO: R$ %10.2f\n", total_arrecadado);
    printf("MEDIA POR MESA:  R$ %10.2f\n", total_mesas > 0 ? total_arrecadado / total_mesas : 0);
    printf("ITENS VENDIDOS:  %10d unidades\n", total_itens);

    top_bottom();
}

// Calcular arrecadação de comidas x bebidas

void calcular_subtotal_por_tipo(struct dados_pedido pedidos[], int total_pedidos){
    float total_comidas = 0, total_bebidas = 0;

    for (int i=0; i < total_pedidos; i++){
        if (pedidos[i].tipo == 1) total_comidas += pedidos[i].subtotal;
        else total_bebidas += pedidos[i].subtotal;
    }

    printf("\n=== SUBTOTAL POR CATEGORIA ===\n");

    top_bottom();

    printf("COMIDAS: R$ %8.2f\n", total_comidas);
    printf("BEBIDAS: R$ %8.2f\n", total_bebidas);
    printf("TOTAL  : R$ %8.2f\n", total_comidas + total_bebidas);

    top_bottom();
}

// Gera um ranking dos itens mais pedidos

void gerar_ranking(struct dados_pedido pedidos[], int total_pedidos){

    struct item_ranking {
        char nome[50];
        int quantidade;
        float subtotal;
    } ranking[50];

    int n_itens = 0;

    for (int i=0; i < total_pedidos; i++){
        int encontrado = 0;

        for (int j=0; j < n_itens; j++){
            if (strcmp(pedidos[i].item, ranking[j].nome) == 0){
                ranking[j].quantidade += pedidos[i].quantidade;
                ranking[j].subtotal += pedidos[i].subtotal;
                encontrado = 1;
                break;
            }
        }

        if (!encontrado && n_itens < 50){
            strcpy(ranking[n_itens].nome, pedidos[i].item);
            ranking[n_itens].quantidade = pedidos[i].quantidade;
            ranking[n_itens].subtotal = pedidos[i].subtotal;
            n_itens++;
        }
    }

    for (int i = 0; i < n_itens - 1; i++) {
        for (int j = i + 1; j < n_itens; j++) {
            if (ranking[j].quantidade > ranking[i].quantidade) {
                struct item_ranking temp = ranking[i];
                ranking[i] = ranking[j];
                ranking[j] = temp;
            }
        }
    }

    printf("\n=== TOP 5 ITENS MAIS VENDIDOS ===\n");

    top_bottom();

    for (int i=0; i < (n_itens < 5 ? n_itens : 5); i++){
        printf("%do: %-20s | %3dx | R$ %7.2f\n", i + 1, ranking[i].nome, ranking[i].quantidade, ranking[i].subtotal);
    }

    top_bottom();
}

// Gera o relatório final do dia com item mais pedido e total arrecadado por mesa

void gerar_relatorio_final() {
    struct dados_pedido pedidos[200];
    int total_pedidos = 0;

    if (!carregar_pedidos(pedidos, &total_pedidos)) {
        printf("Nenhum pedido registrado ainda.\n");
        return;
    }

    printf("\n=== RELATORIO FINAL DO DIA ===\n");

    calcular_metricas_gerais(pedidos, total_pedidos);

    // Total por mesa

    int mesas_exibidas[100] = {0};
    int n_mesas = 0;

    for (int i = 0; i < total_pedidos; i++) {
        int ja_exibida = 0;
        for (int j = 0; j < n_mesas; j++) {
            if (mesas_exibidas[j] == pedidos[i].mesa) {
                ja_exibida = 1;
                break;
            }
        }

        if (!ja_exibida) {
            int mesa_atual = pedidos[i].mesa;
            float total_mesa = 0;
            printf("\nMESA %d\n", mesa_atual);

            mid_line();

            for (int k = 0; k < total_pedidos; k++) {
                if (pedidos[k].mesa == mesa_atual) {
                    exibir_pedido(pedidos[k]);
                    total_mesa += pedidos[k].subtotal;
                }
            }

            printf("TOTAL DA MESA %d: R$%.2f\n", mesa_atual, total_mesa);
            top_bottom();
            mesas_exibidas[n_mesas++] = mesa_atual;
        }
    }

    gerar_ranking(pedidos, total_pedidos);
    calcular_subtotal_por_tipo(pedidos, total_pedidos);

    // Determinar o item mais pedido

    char nomes[50][50];
    int quantidades[50] = {0};
    int n_itens = 0;

    for (int i = 0; i < total_pedidos; i++) {
        int encontrado = 0;
        for (int j = 0; j < n_itens; j++) {
            if (strcmp(pedidos[i].item, nomes[j]) == 0) {
                quantidades[j] += pedidos[i].quantidade;
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            strcpy(nomes[n_itens], pedidos[i].item);
            quantidades[n_itens] = pedidos[i].quantidade;
            n_itens++;
        }
    }

    // Encontra o item com maior quantidade

    int max_index = 0;
    for (int i = 1; i < n_itens; i++) {
        if (quantidades[i] > quantidades[max_index]) {
            max_index = i;
        }
    }

    printf("ITEM MAIS PEDIDO: %s (%d unidades)\n", nomes[max_index], quantidades[max_index]);
    top_bottom();
}