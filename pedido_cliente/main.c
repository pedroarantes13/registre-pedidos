#include <stdio.h>
#include "funcoes.h"

int main() {
    // Simulando valores vindos de outra parte do sistema
    int mesa = 3;
    char prato[] = "Lasanha";
    int qtd_prato = 2;
    char bebida[] = "Suco de laranja";
    int qtd_bebida = 1;

    // Registrar o pedido
    struct dados_pedido info = registrar_pedido(mesa, prato, qtd_prato, bebida, qtd_bebida);

    // Apenas exibindo como teste
    printf("Pedido registrado com sucesso!\n");

    return 0;
}