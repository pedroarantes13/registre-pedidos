#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pedido {
        char prato[50];
        int quantidade_prato;
        char bebida[20];
        int quantidade_bebida;
        float subtotal;
    };

int main() {
    float valor_prato = 30, valor_bebida = 5, total = 0;
    char opcao[5];
    struct pedido pedidos[100]; // "pedidos" é um vetor que vai armazenar as structs dos pedidos (máximo de 100) 
    int num_pedidos = 0;

    while (1) { // Loop infinito para obtenção dos pedidos
        struct pedido pedido;

        printf("Nome do prato: ");
        fgets(pedido.prato, 50, stdin); // Comando da <sting.h> para ler strings
        pedido.prato[strcspn(pedido.prato, "\n")] = '\0'; // Substitui \n por \0 no final da string

        printf("Quantidade: ");
        scanf("%d", &pedido.quantidade_prato);

        getchar(); // Limpa o buffer (evita lixo de memória)

        printf("Bebida: ");
        fgets(pedido.bebida, 20, stdin);
        pedido.bebida[strcspn(pedido.bebida, "\n")] = '\0';

        printf("Quantidade: ");
        scanf("%d", &pedido.quantidade_bebida);

        getchar(); 

        pedido.subtotal = (valor_prato * pedido.quantidade_prato) + (valor_bebida * pedido.quantidade_bebida); // Calcula o total da conta (do pedido atual)
        total += pedido.subtotal; // Adiciona esse valor ao total (de todos os pedidos)

        pedidos[num_pedidos] = pedido; // Armazena esse pedido no vetor
        num_pedidos++; // Atualiza o contador de pedidos

        system("cls || clear"); // Limpa o terminal

        printf("Pedido registrado com sucesso!\n");
        printf("-----------------------------\n");
        printf("%s --- R$%.2f --- x%d\n", pedido.prato, valor_prato, pedido.quantidade_prato);
        printf("%s --- R$%.2f --- x%d\n", pedido.bebida, valor_bebida, pedido.quantidade_bebida);
        printf("Subtotal do pedido: R$%.2f\n", pedido.subtotal);
        printf("-----------------------------\n");
        printf("Total acumulado: R$%.2f\n", total);

        printf("\nDeseja fazer outro pedido? (s/n): "); 
        fgets(opcao, 5, stdin);

        if (opcao[0] == 'n' || opcao[0] == 'N') {
            break;
        } // Confere se haverá mais pedidos. Se não, encerra o loop

        system("cls || clear"); 
    }

    system("cls || clear");

    printf("\n Resumo dos pedidos:\n");
    printf("=====================================================\n");

    for(int i=0; i<num_pedidos; i++){
        printf("Pedido %d:\n", i + 1);
        printf("Prato: %s --- x%d --- R$%.2f\n", pedidos[i].prato, pedidos[i].quantidade_prato, valor_prato * pedidos[i].quantidade_prato);
        printf("Bebida: %s --- x%d --- R$%.2f\n", pedidos[i].bebida, pedidos[i].quantidade_bebida, valor_bebida * pedidos[i].quantidade_bebida);
        printf("Subtotal: R$%.2f\n", pedidos[i].subtotal);
        printf("-----------------------------------------------------\n"); // Mostra os pedidos anteriores e o subtotal de cada um
    }

    printf("TOTAL FINAL A PAGAR: R$%.2f\n", total); // Mostra o valor total
    printf("=====================================================\n");
    
    return 0;
}
