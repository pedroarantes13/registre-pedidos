#include <stdio.h>
#include "funcoes.h"  // Inclui os protótipos e a definição da struct

int main() {
    struct dados_pedido pedidos[200];  // Vetor para armazenar os pedidos carregados
    int total_pedidos = 0;             // Contador de pedidos totais

    // Tenta carregar os pedidos salvos no arquivo binário
    int pedidos_anteriores = carregar_pedidos(pedidos, 200);
    total_pedidos += pedidos_anteriores;  // Atualiza o total com o que foi lido

    // Se houver pedidos anteriores, exibe eles
    if (pedidos_anteriores > 0){
        printf("Pedidos anteriores carregados:\n");
        exibir_resumo(pedidos, pedidos_anteriores);
    } else {
        printf("Nenhum pedido anterior encontrado!\n");
    }

    // Adiciona dois novos pedidos (cada um já será salvo no arquivo binário)
    registrar_e_salvar(4, 1, "Strogonoff", 2, "Coca", 1);  
    registrar_e_salvar(5, 2, "Scargot", 5, "Tang", 2);       

    // Após registrar os novos, recarrega todos os pedidos (antigos + novos)
    total_pedidos = carregar_pedidos(pedidos, 200);  // Sobrescreve o vetor

    // Exibe o resumo geral com todos os pedidos
    printf("Resumo apos novos pedidos:\n");
    exibir_resumo(pedidos, total_pedidos);

    return 0;
}
