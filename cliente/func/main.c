#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"

int main() {
    struct dados_pedido pedidos[200];
    int total_pedidos = 0;

    // Carrega pedidos anteriores
    carregar_pedidos(pedidos, &total_pedidos);

    char continuar_programa;
    do {
        int mesa, pessoas;
        char continuar;

        top_bottom();

        // Dados gerais da mesa (apenas uma vez)
        printf("Numero da mesa: ");
        scanf("%d", &mesa);

        printf("Quantidade de pessoas na mesa: ");
        scanf("%d", &pessoas);

        // Limpa buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        int inicio_pedidos_mesa = total_pedidos; // Marca onde começam os pedidos desta mesa

        do {
            char item[50];
            int tipo, qtd;

            mid_line();

            printf("Item que deseja pedir: ");
            fgets(item, sizeof(item), stdin);
            item[strcspn(item, "\n")] = '\0';  // remove o \n
            
            printf("Tipo do item (1 = Comida, 2 = Bebida): ");
            scanf("%d", &tipo);

            printf("Quantidade: ");
            scanf("%d", &qtd);

            // Registra e salva o item
            registrar_e_salvar(pedidos, &total_pedidos, mesa, pessoas, item, tipo, qtd);

            // Limpa buffer antes do próximo fgets
            while ((c = getchar()) != '\n' && c != EOF);

            printf("Deseja pedir mais alguma coisa? (s/n): ");
            scanf("%c", &continuar);

            while ((c = getchar()) != '\n' && c != EOF); // limpa buffer após o %c

        } while (continuar == 's' || continuar == 'S');

        // Limpa a tela para mostrar apenas os pedidos da mesa
        system("cls || clear");

        top_bottom();

        // Mostra apenas os pedidos desta mesa
        printf("RESUMO DOS PEDIDOS DA MESA %d:\n", mesa);

        mid_line();

        float total_mesa = 0;
        for (int i = inicio_pedidos_mesa; i < total_pedidos; i++) {
            exibir_pedido(pedidos[i]);
            total_mesa += pedidos[i].subtotal;
        }
        printf("TOTAL DA MESA %d: R$%.2f | VALOR POR PESSOA: R$%.2f\n", mesa, total_mesa, total_mesa / pessoas);
        top_bottom();

        printf("Deseja registrar pedidos de outra mesa? (s/n): ");
        scanf(" %c", &continuar_programa);

        system("cls || clear");

        while ((c = getchar()) != '\n' && c != EOF); // limpa buffer

    } while (continuar_programa == 's' || continuar_programa == 'S');

    // Oferece ao usuário a opção de ver o relatório final
    char ver_relatorio;
    printf("\nDeseja visualizar o relatorio final do dia? (s/n): ");
    scanf(" %c", &ver_relatorio);

    if (ver_relatorio == 's' || ver_relatorio == 'S') {
        system("cls || clear");
        gerar_relatorio_final();
    }

    return 0;
}
