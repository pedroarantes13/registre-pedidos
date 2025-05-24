#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "funcoes.h"

// Imprime uma linha intermediária (visual)

void mid_line() {
    printf("-----------------------------------------------------\n");
}

// Imprime uma linha de topo/rodapé (visual)

void top_bottom() {
    printf("=====================================================\n");
}

// Sistema de cupons

void inicializar_cupons(struct cupom_desconto cupons[]){

    strcpy(cupons[0].codigo, "paulo");
    cupons[0].porcentagem = 0.20f;

    strcpy(cupons[1].codigo, "daniel");
    cupons[1].porcentagem = 0.30f;

    strcpy(cupons[2].codigo, "pedro");
    cupons[2].porcentagem = 0.40f;

    strcpy(cupons[3].codigo, "lizandro");
    cupons[3].porcentagem = 0.50f;

    strcpy(cupons[4].codigo, "gean");
    cupons[4].porcentagem = 0.60f;
}

int aplicar_cupom(char codigo[], struct cupom_desconto cupons[], float *desconto){
    for (int i=0; i < MAX_CUPONS; i++){

        if (strcasecmp(codigo, cupons[i].codigo) == 0){
            *desconto = cupons[i].porcentagem;
            return 1;
        }
    }

    return 0;
}

// Registra um pedido e salva no arquivo binário

void registrar_e_salvar(
    struct dados_pedido *vetor, 
    int *total_pedidos, 
    int mesa,                    
    int pessoas, 
    char item[], 
    int tipo, int qtd_item,
    const char *cupom,
    float desconto) 
    {

    struct dados_pedido pedido;
    
    // Preenche os dados básicos

    pedido.mesa = mesa;
    pedido.pessoas = pessoas;
    strncpy(pedido.item, item, sizeof(pedido.item));
    pedido.tipo = tipo;
    pedido.quantidade = qtd_item;
    
    // Preços fictícios (ou do cardápio)

    float valor_comida = 30.0;
    float valor_bebida = 5.0;
    
    pedido.subtotal = (tipo == 1) ? qtd_item * valor_comida : qtd_item * valor_bebida;
    pedido.valor_individual = pedido.subtotal / pessoas;
    
    // Armazena cupom (novo)

    strncpy(pedido.cupom, cupom, sizeof(pedido.cupom));
    pedido.desconto = desconto;
    
    // Adiciona ao vetor e salva

    vetor[*total_pedidos] = pedido;
    (*total_pedidos)++;
    
    FILE *arquivo = fopen(ARQUIVO_BINARIO, "ab");
    if (arquivo) {
        fwrite(&pedido, sizeof(struct dados_pedido), 1, arquivo);
        fclose(arquivo);
    }
}

// Carrega os pedidos do arquivo binário para o vetor

int carregar_pedidos(struct dados_pedido vetor[], int *total_pedidos) {
    FILE *arquivo = fopen(ARQUIVO_BINARIO, "rb");
    if (arquivo == NULL) {
        *total_pedidos = 0;
        return 0;
    }

    // Lê pedidos até encontrar EOF
    int lidos = 0;
    while (lidos < 200 && 
           fread(&vetor[lidos], sizeof(struct dados_pedido), 1, arquivo) == 1) {
        lidos++;
    }

    fclose(arquivo);
    *total_pedidos = lidos;
    return lidos;
}

// Exibe um pedido individual

void exibir_pedido(struct dados_pedido p, int eh_relatorio) {
    printf("Mesa %d | Pessoas: %d\n", p.mesa, p.pessoas);
    printf("Item: %s (%dx) [%s]\n", p.item, p.quantidade,
           (p.tipo == 1 ? "Comida" : "Bebida"));
    printf("Subtotal: R$%.2f\n", p.subtotal);

    if (strlen(p.cupom) > 0 && !eh_relatorio){
        printf("CUPOM %s APLICADO (%.0f%% OFF)\n", p.cupom, p.desconto * 100);
        printf("VALOR COM DESCONTO: R$%.2f\n", p.subtotal * (1 - p.desconto));
    }

    mid_line();
}

// Exibe um resumo de todos os pedidos

void exibir_resumo(struct dados_pedido vetor[], int total_pedidos) {
    float total_geral = 0;
    printf("\n=== RESUMO DOS PEDIDOS ===\n");
    top_bottom();

    for (int i = 0; i < total_pedidos; i++) {
        exibir_pedido(vetor[i], 1);  // 1 = modo relatório
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

    int mesas[100] = {0};
    int total_mesas = 0;

    // Identifica mesas únicas
    for (int i = 0; i < total_pedidos; i++) {
        int existe = 0;
        for (int j = 0; j < total_mesas; j++) {
            if (mesas[j] == pedidos[i].mesa) {
                existe = 1;
                break;
            }
        }
        if (!existe) mesas[total_mesas++] = pedidos[i].mesa;
    }

    // Processa cada mesa
    for (int i = 0; i < total_mesas; i++) {
        int mesa = mesas[i];
        float total_original = 0, total_final = 0;
        char cupom[20] = "";
        float desconto = 0;
        int pessoas = 0;

        printf("\nMESA %d\n", mesa);
        mid_line();

        for (int j = 0; j < total_pedidos; j++) {
            if (pedidos[j].mesa == mesa) {
                exibir_pedido(pedidos[j], 1);
                total_original += pedidos[j].subtotal;
                if (strlen(pedidos[j].cupom) > 0) {
                    strcpy(cupom, pedidos[j].cupom);
                    desconto = pedidos[j].desconto;
                }
                pessoas = pedidos[j].pessoas;
            }
        }

        total_final = total_original * (1 - desconto);

        printf("\nRESUMO FINANCEIRO:\n");
        printf("VALOR TOTAL:    R$%.2f\n", total_original);
        if (strlen(cupom) > 0) {
            printf("CUPOM %-8s   -%.0f%%\n", cupom, desconto * 100);
            printf("VALOR FINAL:    R$%.2f\n", total_final);
        }
        printf("POR PESSOA:     R$%.2f\n", total_final / pessoas);
        top_bottom();
    }

    gerar_ranking(pedidos, total_pedidos);
    calcular_subtotal_por_tipo(pedidos, total_pedidos);
}