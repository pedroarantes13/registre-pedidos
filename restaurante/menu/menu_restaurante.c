#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../func/func_restaurante.h"
#include "../../cliente/func/funcoes.h"


void menu_adicionar_item(Cardapio *item) {

    printf(" _______________________________________\n");
    printf("| DIGITE O NOME DO ITEM:                |\n");
    printf("| >                                     |\r| > ");

    while (getchar() != '\n' && !feof(stdin)); // limpa o buffer do teclado

    fgets(item->item, 50, stdin);
    item->item[strcspn(item->item, "\n")] = '\0'; // remove o '\n'

    // Valida se o nome contém apenas letras e espaços
    while (!validar_nome_item(item->item)) {
        printf("| NOME INVALIDO! APENAS LETRAS/ESPACOS! |\n");
        printf("| >                                     |\r| > ");
        fgets(item->item, 50, stdin);
        item->item[strcspn(item->item, "\n")] = '\0';
    }

    do
    {
        printf("|---------------------------------------|\n");
        printf("| DIGITE O TIPO: 0 = PRATO              |\n");
        printf("|                1 = BEBIDA             |\n");
        printf("|                2 = SOBREMESA          |\n");
        printf("| >                                     |\r| > ");
        scanf("%d", &item->tipo);

        while (getchar() != '\n' && !feof(stdin)); // limpa o buffer

    } while (validar_tipo(item->tipo) != 0); // Verifica se o tipo é válido

    do {
        printf("|---------------------------------------|\n");
        printf("| DIGITE O VALOR:                       |\n");
        printf("| >                                     |\r| > ");
        scanf("%f", &item->valor);
        while (getchar() != '\n' && !feof(stdin)); // limpa o buffer

    } while (validar_valor(item->valor) != 0); // Verifica se o valor é válido


    // Chamada correta com verificação feita por dentro
    if (adicionar_item(*item) == 0) {
        printf("| ITEM ADICIONADO COM SUCESSO!          |\n");
    } else {
        printf("| ERRO AO ADICIONAR ITEM!               |\n");
    }

    printf(" _______________________________________\n");
}

void menu_editar_item(Cardapio *novo_item) {
    int indice;

    do {
        printf(" ________________________________________\n");
        printf("| DIGITE O INDICE DO ITEM A SER EDITADO: |\n");
        printf("| >                                      |\r| > ");
        indice = ler_inteiro_positivo(); // Lê um inteiro positivo do usuário
        indice--; // Ajusta o índice para começar de 0

    } while (verificar_indice_cardapio(STD_BIN, indice) != 0); // Verifica se o índice é válido
    // Se o índice for inválido, solicita novamente o índice

    printf(" ________________________________________\n");
    printf("| DIGITE O NOME DO NOVO ITEM:            |\n");
    printf("| >                                      |\r| > ");

    // Implementação com validar_nome_item
    do {
        fgets(novo_item->item, 50, stdin);
        novo_item->item[strcspn(novo_item->item, "\n")] = '\0'; // remove o '\n'

        if (!validar_nome_item(novo_item->item)) {
            printf("| NOME INVALIDO! APENAS LETRAS/ESPACOS!  |\n");
            printf("| >                                      |\r| > ");
        }
    } while (!validar_nome_item(novo_item->item));

    do
    {
        printf("|----------------------------------------\n");
        printf("| DIGITE O TIPO: 0 = PRATO               |\n");
        printf("|                1 = BEBIDA              |\n");
        printf("|                2 = SOBREMESA           |\n");
        printf("| >                                      |\r| > ");
        scanf("%d", &novo_item->tipo);

        while (getchar() != '\n' && !feof(stdin)); // limpa o buffer

    } while (validar_tipo(novo_item->tipo) != 0); // Verifica se o tipo é válido

    do {
        printf("|----------------------------------------|\n");
        printf("| DIGITE O VALOR:                        |\n");
        printf("| >                                      |\r| > ");
        scanf("%f", &novo_item->valor);
        while (getchar() != '\n' && !feof(stdin)); // limpa o buffer

    } while (validar_valor(novo_item->valor) != 0); // Verifica se o valor é válido

    if (editar_item_cardapio(STD_BIN, indice, novo_item) == 0) {
        printf("| ITEM EDITADO COM SUCESSO!              |\n");
    } else {
        printf("| ERRO AO EDITAR ITEM!                   |\n");
    }

    printf(" ________________________________________\n");
}

void menu_excluir_item() {

    int indice;

    do {
        printf(" _______________________________________________\n");
        printf("| DIGITE O INDICE DO ITEM A SER EXCLUIDO:      |\n");
        printf("| >                                            |\r| > ");
        indice = ler_inteiro_positivo(); // Lê um inteiro positivo do usuário
        indice--; // Ajusta o índice para começar de 0

    } while (verificar_indice_cardapio(STD_BIN, indice) != 0); // Verifica se o índice é válido
    // Se o índice for inválido, solicita novamente o índice

    if (remover_item_cardapio(STD_BIN, indice) == 0) {
        printf("| ITEM EXCLUIDO COM SUCESSO!                |\n");
    } else {
        printf("| ERRO AO EXCLUIR ITEM!                     |\n");
    }

    printf(" _________________________________\n");

}


int menu_restaurante(){ //Funcao inicial do menu restaurante

    int escolha;

    printf("===============================\n");
    printf(" BEM-VINDO DE VOLTA AO SISTEMA!\n");
    printf("===============================\n\n");

    while(1){

        printf("|________________________|\n");
        printf("| VISUALIZAR CARDAPIO [1]|\n");
        printf("|........................|\n");
        printf("|________________________|\n");
        printf("|   ADICIONAR ITEM [2]   |\n");
        printf("|........................|\n");
        printf("|________________________|\n");
        printf("|  EDITAR ITEM CARD.[3]  |\n");
        printf("|........................|\n");
        printf("|________________________|\n");
        printf("|  EXCLUIR ITEM CARD.[4] |\n");
        printf("|........................|\n");
        printf("|________________________|\n");
        printf("|   GERAR RELATORIO [5]  |\n");
        printf("|........................|\n");
        printf("|________________________|\n");
        printf("|   FINALIZAR SECAO [0]  |\n");
        printf("|........................|\n");
        printf("          [   ]\b\b\b");

        if (scanf("%d", &escolha) != 1) {

            printf(" __________________\n");
            printf("| ENTRADA INVALIDA!|\n");
            printf("| TENTE NOVAMENTE! |\n");
            printf("|------------------|\n");

            while (getchar() != '\n'); // limpa buffer
            continue;

        }

        switch (escolha) {

            case 1:
                
                system("clear || cls"); // Limpa o terminal

                imprimir_cardapio(STD_BIN); //Chamo a funcao do Pedro, para mostrar o cardapio

                break;

            case 2:{

                system("clear || cls");

                Cardapio item;

                menu_adicionar_item(&item); //Adiciona um item no cardapio

                break;
            }
                
            case 3:{

                system("clear || cls");

                Cardapio novo_item;

                imprimir_cardapio(STD_BIN); //Mostra o cardapio para o usuario

                menu_editar_item(&novo_item); //Modifica um item do cardapio

                break;
            }

            case 4:{

                system("clear || cls");

                imprimir_cardapio(STD_BIN); //Mostra o cardapio para o usuario

                menu_excluir_item(); //Remove um item do cardapio

                break;

            }


            case 5:

                system("clear || cls");

                gerar_relatorio_final(); // Chamo a funcao do Daniel, onde vai gerar o relatorio

                break;

            case 0:

                system("clear || cls");

                printf("  =================================\n");
                printf("  ==SECAO FINALIZADA COM SUCESSO!==\n"); //Finaliza a secao
                printf("  =================================\n\n");

                return 1;

            default:

                system("clear || cls");

                printf("\n  [COMANDO INVALIDO!]\n   [TENTE NOVAMENTE]\n"); //Entra em loop ate que se digite um comando valido
        }
    }
}
 