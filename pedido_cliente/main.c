#include <stdio.h>
#include "funcoes.h"

// EXEMPLO DE EXECUÇÃO

int main(){

    // Declara a struct "info", recebendo o retorno da função
    struct dados_pedido info = registrar_pedido(); 

    // Printar as informações do pedido
    printf("\n--- DADOS DO PEDIDO ---\n");
    printf("Prato: %s (x%d)\n", info.prato, info.qtd_prato);
    printf("Bebida: %s (x%d)\n", info.bebida, info.qtd_bebida);
    printf("Subtotal: R$%.2f\n", info.subtotal);
    
    return 0;
}