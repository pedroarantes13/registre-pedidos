#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../func/menu.h"
#include "../func/funcoes.h"
#include "../../restaurante/func/func_restaurante.h"

int main () 
{
    int escolha = 0;

    struct dados_pedido *pedidos = NULL;
    int total_pedidos = 0;
    int capacidade = 0;

    // Carrega o cardápio
    Cardapio *cardapio = NULL;
    int contador_itens_cardapio = 0;

   if (carregar_cardapio(STD_BIN, &cardapio) != 0) {
    printf("Erro ao carregar o cardápio.\n");
    // Libera cardapio se algo foi alocado antes do erro
    if (cardapio != NULL) {
        free(cardapio);
        cardapio = NULL;
    }
    return 1;
}

    contador_itens_cardapio = total_itens_cardapio(STD_BIN);

    // Carrega os pedidos salvos 
    carregar_pedidos(&pedidos, &total_pedidos, &capacidade);

    do {

    escolha = mostrarMenu(); // Atribuí a função Menu para escolha

        switch (escolha)  /* Switch para exibir o cardapio conforme a escolha do menu */
        {
            case 1:
                mostrarPratosPrincipais(cardapio, contador_itens_cardapio);
                pausarTela();
                break;
            case 2:
                mostrarBebidas(cardapio, contador_itens_cardapio);
                pausarTela();
                break;
            case 3:
                mostrarSobremesas(cardapio, contador_itens_cardapio);
                pausarTela();
                break;
            case 4:
                fazerPedido(&pedidos, &total_pedidos, &capacidade, cardapio, contador_itens_cardapio);
                pausarTela();
                break;

            case 5:
                printf("\nSaindo do sistema. Obrigado pela visita.\n");
                pausarTela();
                break;
            default:
                // Nunca deve entrar aqui, pois o menu valida as opções
                printf("Opcao invalida!\n");
                break;
        }
        
    } while (escolha != 5); // Continua até o usuário escolher sair (opção 5)
       
    // Libera memória alocada
    free(pedidos);
    if (cardapio != NULL) {
    free(cardapio);
   }

    return 0;
}