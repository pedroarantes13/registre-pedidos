/*Arquivo main.c contendo o menu principal, com as chamadas das funções referentes ao menu do cliente e ao menu do restaurante*/

#include <stdio.h>
#include <stdlib.h>

#include "./restaurante/func/func_restaurante.h"
#include "./cliente/func/funcoes.h"

int main() {
    int opcao; // Escolha do usuário sobre a próxima ação do programa

    printf("\n==========================\n");
    printf("   BEM-VINDO AO SISTEMA!   \n");
    printf("==========================\n\n");
    
    while (1) {
       
        printf("\n|------------------------|\n");
        printf("|   MENU DO CLIENTE [1]  |\n");
        printf("|........................|\n");
        printf("|------------------------|\n");
        printf("|  MENU PROPRIETARIO [2] |\n");
        printf("|........................|\n");
        printf("|------------------------|\n");
        printf("|   FINALIZAR SECAO [3]  |\n");
        printf("|........................|\n");
        
        opcao = ler_inteiro_seguro("Digite sua opcao ", 1, 3); // Função de validação de números inteiros (1 a 3)

        switch (opcao) {
            case 1:
                system("clear || cls");
                menu_cliente(); // Chamada para a função referente ao menu do cliente
                while (getchar() != '\n' && !feof(stdin)); // Limpa o buffer após retornar do menu
                break;
            case 2:
                system("clear || cls");
                menu_restaurante(); // Chamada para a função referente ao menu do cliente
                while (getchar() != '\n' && !feof(stdin)); // Limpa o buffer após retornar do menu
                break;
            case 3:
                // Após o usuário finalizar, encerra o programa
                system("clear || cls");
                printf("\n|------------------------|\n");
                printf("|    SECAO FINALIZADA    |\n");
                printf("|........................|\n");
                printf("|------------------------|\n");
                printf("|     MUITO OBRIGADO!    |\n");
                printf("|........................|\n");
                return 0;

                // obs.: default retirado devido à função de validação de números inteiros
        }
    }

    return 0;
}
