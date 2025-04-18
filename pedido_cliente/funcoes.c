#include <stdio.h>
#include <string.h>
#include "funcoes.h"

struct dados_pedido registrar_pedido(){

    // Declara a struct 
    struct dados_pedido info;

    // Valores fictícios
    float valor_prato = 30.0;
    float valor_bebida = 5.0;

    // Recolhe os informações (nome e quantidade) e armazena na struct
    printf("Prato: ");
    fgets(info.prato, 50, stdin);
    info.prato[strcspn(info.prato, "\n")] = '\0'; // Substitui "\n" por "\0"

    printf("Quantidade: ");
    scanf("%d", &info.qtd_prato);
    getchar(); // Limpa o buffer, evitando lixo de memória
    
    printf("Bebida: ");
    fgets(info.bebida, 50, stdin);
    info.bebida[strcspn(info.bebida, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &info.qtd_bebida);
    getchar();

    // Cálculo do subtotal a partir da quantidade e dos valores fictícios
    info.subtotal = (info.qtd_prato * valor_prato) + (info.qtd_bebida * valor_bebida);

    return info;
}
