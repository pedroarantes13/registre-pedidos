#include <stdio.h>
#include <string.h>
#include "funcoes.h"

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
