#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func_restaurante.h"
#include "funcoes.h"


 void adicionarItem(Cardapio *item) {

    printf(" __________________________________\n");
    printf("| DIGITE O NOME DO ITEM:           |\n");
    printf("| >                                |\r| > ");

    while (getchar() != '\n' && !feof(stdin)); // limpa o buffer do teclado

    fgets(item->item, 50, stdin);
    item->item[strcspn(item->item, "\n")] = '\0'; // remove o '\n'
    printf("|----------------------------------|\n");
    printf("| DIGITE O TIPO: 0 = PRATO         |\n");
    printf("|                1 = BEBIDA        |\n");
    printf("|                2 = SOBREMESA     |\n");
    printf("| >                                |\r| > ");
    scanf("%d", &item->tipo);
    
    printf("|----------------------------------|\n");
    printf("| DIGITE O VALOR:                  |\n");
    printf("| >                                |\r| > ");
    scanf("%f", &item->valor);

    while (getchar() != '\n' && !feof(stdin)); // limpa o buffer

    // Chamada correta com verificação feita por dentro
    if (adicionar_item(*item) == 0) {
        printf("| ITEM ADICIONADO COM SUCESSO!     |\n");
    } else {
        printf("| ERRO AO ADICIONAR ITEM!          |\n");
    }

    printf(" _________________________________\n");
}

 void modificar_item_cardapio(){}


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
    printf("| MODIFICAR ITEM CARD.[3]|\n");
    printf("|........................|\n");
    printf("|________________________|\n");
    printf("|   GERAR RELATORIO [4]  |\n");
    printf("|........................|\n");
    printf("|________________________|\n");
    printf("|   FINALIZAR SECAO [0]  |\n");
    printf("|........................|\n");
    

    printf("          [   ]\b\b\b");

     if (scanf("%d", &escolha) != 1) {
        printf(" __________________\n");
        printf("| ENTRADA INVÁLIDA!|\n");
        printf("| TENTE NOVAMENTE! |\n");
        printf("|------------------|\n");

        while (getchar() != '\n'); // limpa buffer
        continue;
     }


    switch (escolha)
    {
    case 1:
        
        system("cls"); // Limpa o terminal

        imprimir_cardapio(STD_BIN); //Chamo a funcao do Pedro, para mostrar o cardapio

        break;

    case 2:{

        system("cls");

        Cardapio item;

        adicionarItem(&item); //Adiciona um item no cardapio

        break;
    }
        
    case 3:

        system("cls");
    
        modificar_item_cardapio(); //Modifica algum item do cardapio

        break;

    case 4:

        system("cls");

        gerar_relatorio_final(); // Chamo a funcao do Daniel, onde vai gerar o relatorio

        break;

    case 0:

        system("cls");

        printf("  =================================\n");
        printf("  ==SECAO FINALIZADA COM SUCESSO!==\n"); //Finaliza a secao
        printf("  =================================\n\n");

        return 1;

    default:

        system("cls");
    
        printf("\n  [COMANDO INVALIDO!]\n   [TENTE NOVAMENTE]\n"); //Entra em loop ate que se digite um comando valido
    }
  }
}
 