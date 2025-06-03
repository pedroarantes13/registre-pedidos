#include <stdio.h>
#include <string.h>
#include "../func/menu.h"

int main () 
{
    int escolha = 0;

    do {

    escolha = mostrarMenu(); // Atribuí a função Menu para escolha.
    struct pedido p;

        switch (escolha)  /* Switch para exibir o cardapio conforme a escolha do menu */
        {
            case 1:
                mostrarPratosPrincipais();
                pausarTela();
                break;
            case 2:
                mostrarBebidas();
                pausarTela();
                break;
            case 3:
                mostrarSobremesas();
                pausarTela();
                break;
            case 4:
                fazerPedido(&p);
                break;
            case 5:
                printf("\nSaindo do sistema. Obrigado pela visita.\n");
                break;
            default:
                // Nunca deve entrar aqui, pois o menu valida as opções
                printf("Opcao invalida!\n");
                break;
        }
        
    } while (escolha != 5); 

}