#include <stdio.h>
#include "funcoes.h"

int main() {

    // Vetor que armazena todos os pedidos (anteriores e novos)

    struct dados_pedido pedidos[200];
    int total_pedidos = 0;

    // Tenta carregar pedidos anteriores já salvos

    int pedidos_anteriores = carregar_pedidos(pedidos, 200);
    total_pedidos += pedidos_anteriores;

    if (pedidos_anteriores > 0){
        printf("Pedidos anteriores carregados:\n");
        exibir_resumo(pedidos, pedidos_anteriores); // Exibe os pedidos antigos
    } else {
        printf("Nenhum pedido anterior encontrado!\n");
    }

    // Criando dois novos pedidos simulados

    struct dados_pedido novo1 = registrar_pedido(5, "Pizza", 1, "Vinho", 2);
    struct dados_pedido novo2 = registrar_pedido(3, "Rosca", 2, "Cafe", 3);

    // Armazena no vetor principal

    pedidos[total_pedidos++] = novo1;
    pedidos[total_pedidos++] = novo2;

    // Exibe o mesmo resumo com os pedidos antigos e novos

    printf("Resumo apos novos pedidos:\n");
    exibir_resumo(pedidos, total_pedidos);

    // Cria um vetor só para os novos pedidos

    struct dados_pedido novos_pedidos[2] = {novo1, novo2};
    salvar_pedidos(novos_pedidos, 2); // Salva apenas os novos

    return 0;
}