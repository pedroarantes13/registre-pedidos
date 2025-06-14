#pragma pack(1)

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
    int total_itens_cardapio = 0;

    if (carregar_cardapio(STD_BIN, &cardapio, &total_itens_cardapio) != 0) {
    printf("Erro ao carregar o cardápio.\n");
    return 1;
    }

    if (cardapio == NULL && total_itens_cardapio == 0) {
    printf("Cardápio está vazio ou houve um problema na alocacao/leitura.\n");

    // Carrega os pedidos salvos 
    carregar_pedidos(&pedidos, &total_pedidos, &capacidade);}

    do {

    escolha = mostrarMenu(); // Atribuí a função Menu para escolha

        switch (escolha)  /* Switch para exibir o cardapio conforme a escolha do menu */
        {
            case 1:
                mostrarPratosPrincipais(cardapio, total_itens_cardapio);
                pausarTela();
                break;
            case 2:
                mostrarBebidas(cardapio, total_itens_cardapio);
                pausarTela();
                break;
            case 3:
                mostrarSobremesas(cardapio, total_itens_cardapio);
                pausarTela();
                break;
            case 4:
                fazerPedido(&pedidos, &total_pedidos, &capacidade, cardapio, total_itens_cardapio);
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
    free(cardapio);

    return 0;

}

#pragma pack()