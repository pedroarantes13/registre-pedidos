#include <stdio.h>
#include <string.h>
#include "funcoes.h"

// Imprime uma linha intermediária (visual)
void mid_line(){
    printf("-----------------------------------\n");
}

// Imprime uma linha de topo/rodapé (visual)
void top_bottom(){
    printf("===================================\n");
}

// Essa função registra um novo pedido E já salva diretamente no arquivo binário
void registrar_e_salvar(int mesa, int pessoas, char prato[], int qtd_prato, char bebida[], int qtd_bebida){
    struct dados_pedido info;  // Cria uma nova struct para armazenar os dados do pedido

    // Preenchendo os dados básicos do pedido
    info.mesa = mesa;
    info.pessoas = pessoas;

    // Copiando os nomes dos itens (strings)
    strcpy(info.prato, prato);
    info.qtd_prato = qtd_prato;

    strcpy(info.bebida, bebida);
    info.qtd_bebida = qtd_bebida;

    // Preços fictícios dos itens
    float valor_prato = 30.0;
    float valor_bebida = 5.0;

    // Calcula o valor total e depois divide igualmente entre as pessoas
    float total = (qtd_prato * valor_prato) + (qtd_bebida * valor_bebida);
    info.subtotal = total / pessoas;  // Armazena quanto cada pessoa vai pagar

    // Abre o arquivo binário em modo append (adicionar no fim)
    FILE *arquivo = fopen(ARQUIVO_BINARIO, "ab");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return;  // Sai da função em caso de erro
    }

    // Escreve 1 struct no arquivo
    fwrite(&info, sizeof(struct dados_pedido), 1, arquivo);

    fclose(arquivo);  // Fecha o arquivo
    printf("Pedido da mesa %d salvo com sucesso!\n", mesa);
}

// Lê os pedidos anteriores do arquivo binário e preenche o vetor 'pedidos'
// Retorna quantos foram lidos com sucesso
int carregar_pedidos(struct dados_pedido pedidos[], int max_pedidos){
    FILE *arquivo = fopen(ARQUIVO_BINARIO, "rb");

    if (arquivo == NULL){
        printf("Arquivo de pedidos nao encontrado!\n");
        return 0;  // Nenhum pedido carregado
    }

    // Lê até max_pedidos registros do arquivo
    int lidos = fread(pedidos, sizeof(struct dados_pedido), max_pedidos, arquivo);
    fclose(arquivo);
    return lidos;  // Retorna o total de pedidos lidos
}

// Exibe os dados de um pedido na tela, formatado
void exibir_pedido(struct dados_pedido info){
    printf("Mesa: %d\n", info.mesa);
    printf("Pessoas na mesa: %d\n", info.pessoas);
    printf("Prato: %s (x%d)\n", info.prato, info.qtd_prato);
    printf("Bebida: %s (x%d)\n", info.bebida, info.qtd_bebida);
    printf("Subtotal (por pessoa): R$%.2f\n", info.subtotal);
    mid_line();
}

// Mostra um resumo de todos os pedidos e o total geral
void exibir_resumo(struct dados_pedido pedidos[], int num_pedidos){
    float total_geral = 0;

    printf("\n === RESUMO FINAL DOS PEDIDOS === \n");

    for (int i=0; i<num_pedidos; i++){
        exibir_pedido(pedidos[i]);
        total_geral += pedidos[i].subtotal * pedidos[i].pessoas;  // Reconstrói o total original
    }

    printf("TOTAL GERAL: R$%.2f\n", total_geral);
    top_bottom();
}
