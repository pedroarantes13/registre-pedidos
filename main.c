#include <stdio.h>
#include <stdlib.h>

#include "./restaurante/func/func_restaurante.h"
#include "./cliente/func/funcoes.h"

int main() {
    int opcao;

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
        
        while (getchar() != '\n' && !feof(stdin)); // limpa qualquer resíduo antes da leitura

        opcao = ler_inteiro_seguro("", 1, 3); // Valores entre 1 e 3

        switch (opcao) {
            case 1:
                system("cls");
                menu_cliente();
                break;
            case 2:
                system("cls");
                menu_restaurante();
                break;
            case 3:
                system("cls");
                printf("\n|------------------------|\n");
                printf("|    SECAO FINALIZADA    |\n");
                printf("|........................|\n");
                printf("|------------------------|\n");
                printf("|     MUITO OBRIGADO!    |\n");
                printf("|........................|\n");
                return 0;
            default:
                system("cls");
                printf("\n|------------------------|\n");
                printf("|    OPCAO INVALIDA!     |\n");
                printf("|........................|\n");
        }
    }

    return 0;
}
