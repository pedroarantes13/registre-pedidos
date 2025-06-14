#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../func/menu.h"
#include "funcoes.h"
#include "../../restaurante/func/func_restaurante.h"

extern char* tipo_str(int tipo);


// Funções para mostrar os cardápios
void mostrarPratosPrincipais(Cardapio *cardapio_ptr, int total_itens) 

{
    printf("\nPRATOS PRINCIPAIS:\n");
    printf("----------------------------------------------------------\n"); 
    printf("| %-4s | %-30s | %-12s |\n", "ID", "Item", "Valor (R$)");
    printf("|------|--------------------------------|--------------|\n");

    int encontrado = 0;
    int id_exibicao = 1;
    for (int i = 0; i < total_itens; i++) {
        if (cardapio_ptr[i].tipo == 0) { 
            printf("| %-4d | %-30s | R$ %-9.2f |\n",
                   id_exibicao, cardapio_ptr[i].item, cardapio_ptr[i].valor);
            id_exibicao++;
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("|                                NENHUM PRATO ENCONTRADO                                 |\n");
    }
    printf("----------------------------------------------------------\n");

}

void mostrarBebidas(Cardapio *cardapio_ptr, int total_itens) 

{
    printf("\nBEBIDAS:\n");
    printf("----------------------------------------------------------\n"); 
    printf("| %-4s | %-30s | %-12s |\n", "ID", "Item", "Valor (R$)");
    printf("|------|--------------------------------|--------------|\n");

    int encontrado = 0;
    int id_exibicao = 2;
    for (int i = 0; i < total_itens; i++) {
        if (cardapio_ptr[i].tipo == 1) { 
            printf("| %-4d | %-30s | R$ %-9.2f |\n",
                   id_exibicao, cardapio_ptr[i].item, cardapio_ptr[i].valor);
            id_exibicao++;
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("|                                NENHUMA BEBIDA ENCONTRADA                               |\n");
    }
    printf("----------------------------------------------------------\n");
}

void mostrarSobremesas(Cardapio *cardapio_ptr, int total_itens) 

{
    printf("\nSOBREMESAS:\n");
    printf("----------------------------------------------------------\n"); // 58 hífens
    printf("| %-4s | %-30s | %-12s |\n", "ID", "Item", "Valor (R$)");
    printf("|------|--------------------------------|--------------|\n");

    int encontrado = 0;
    int id_exibicao = 3;
    for (int i = 0; i < total_itens; i++) {
        if (cardapio_ptr[i].tipo == 2) { 
            printf("| %-4d | %-30s | R$ %-9.2f |\n",
                   id_exibicao, cardapio_ptr[i].item, cardapio_ptr[i].valor);
            id_exibicao++;
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("|                              NENHUMA SOBREMESA ENCONTRADA                              |\n");
    }
    printf("----------------------------------------------------------\n");
 
}

    // Função para pausar a tela até o usuário pressionar Enter
void pausarTela() {
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n');
    getchar();
}
    // Mostra o menu principal e retorna a escolha do usuário
int mostrarMenu() {
    int escolha = 0;

    while (escolha < 1 || escolha > 5) {
        printf("======================================\n");
        printf("         BEM-VINDO AO SISTEMA!        \n");
        printf("======================================\n\n");

        printf("--------------------------------------\n");
        printf("| %-34s |\n", "1 - Pratos principais"); 
        printf("|....................................|\n");
        printf("--------------------------------------\n");

        printf("| %-34s |\n", "2 - Bebidas");
        printf("|....................................|\n");
        printf("--------------------------------------\n");

        printf("| %-34s |\n", "3 - Sobremesas");
        printf("|....................................|\n");
        printf("--------------------------------------\n");

        printf("| %-34s |\n", "4 - Fazer pedido");
        printf("|....................................|\n");
        printf("--------------------------------------\n");

        printf("| %-34s |\n", "5 - Sair");
        printf("--------------------------------------\n\n");

        printf("Digite a opcao desejada: ");

        if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > 5) {
            printf("\nEntrada invalida. Digite um numero entre 1 e 5.\n");
            while (getchar() != '\n'); // Limpa buffer
        }
    }

    return escolha;
}

    // Função para fazer um pedido
void fazerPedido(struct dados_pedido **pedidos_ptr, int *total_pedidos_ptr, int *capacidade_ptr, Cardapio *cardapio_menu, int total_itens_cardapio) {
    int mesa;
    int pessoas;
    char cupom_str[20] = "";
    float desconto_val = 0.0;
    char tem_cupom = 'n';

    printf("\n--- INICIAR NOVO PEDIDO ---\n");

    printf("Digite o numero da mesa: ");
    while (scanf("%d", &mesa) != 1 || mesa <= 0) {
        printf("Numero de mesa invalido. Digite um numero positivo: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    printf("Digite o numero de pessoas na mesa: ");
    while (scanf("%d", &pessoas) != 1 || pessoas <= 0) {
        printf("Numero de pessoas invalido. Digite um numero positivo: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    printf("Possui cupom de desconto? (s/n): ");
    scanf(" %c", &tem_cupom);
    while (getchar() != '\n');

    if (tem_cupom == 's' || tem_cupom == 'S') {
        printf("Digite o cupom: ");
        fgets(cupom_str, sizeof(cupom_str), stdin);
        cupom_str[strcspn(cupom_str, "\n")] = 0;

        if (strlen(cupom_str) > 0) {
            desconto_val = 0.10; // Exemplo de desconto
            printf("Cupom '%s' aplicado! %.0f%% de desconto.\n", cupom_str, desconto_val * 100);
        } else {
            printf("Cupom vazio. Nenhum desconto aplicado.\n");
            strcpy(cupom_str, "");
            desconto_val = 0.0;
        }
    } else {
        strcpy(cupom_str, "");
        desconto_val = 0.0;
    }

    char adicionar_mais_itens = 's';
    while (adicionar_mais_itens == 's' || adicionar_mais_itens == 'S') {
        printf("\n--- Adicionar Item ---\n");

        printf("\n-------------------------- C A R D A P I O -------------------------\n");
        printf("|------|--------------------------------|-----------|--------------|\n");
        printf("| %-4s | %-30s | %-9s | %-12s |\n", "ID", "Item", "Tipo", "Valor (R$)");
        printf("|------|--------------------------------|-----------|--------------|\n");
        // 'total_itens_cardapio' é usado diretamente (passado por valor).
        for (int i = 0; i < total_itens_cardapio; i++) {
            printf("| %-4d | %-30.30s | %-9.9s | R$ %9.2f |\n",
                    i + 1,
                    cardapio_menu[i].item,
                    tipo_str(cardapio_menu[i].tipo),
                    cardapio_menu[i].valor);
        }
        printf("|------|--------------------------------|-----------|--------------|\n");

        int item_id_escolhido;
        // 'total_itens_cardapio' é usado diretamente.
        printf("Digite o ID do item que deseja adicionar (1 a %d): ", total_itens_cardapio);
        if (scanf("%d", &item_id_escolhido) != 1 || item_id_escolhido < 1 || item_id_escolhido > total_itens_cardapio) {
            printf("ID de item invalido. Tente novamente.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        int posicao_item_no_cardapio = item_id_escolhido - 1;

        int quantidade_item;
        printf("Quantidade: ");
        if (scanf("%d", &quantidade_item) != 1 || quantidade_item <= 0) {
            printf("Quantidade invalida. Tente novamente.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (cardapio_menu[posicao_item_no_cardapio].tipo == 1) {
             int idade_cliente;
             printf("Para este item, digite a idade do cliente: ");
             if (scanf("%d", &idade_cliente) != 1 || idade_cliente < 18) {
                 printf("Menor de idade nao pode comprar este item. Por favor, escolha outro.\n");
                 while (getchar() != '\n');
                 continue;
             }
             while (getchar() != '\n');
        }

        // registrar_e_salvar com 'total_itens_cardapio' como valor.
        registrar_e_salvar(
            pedidos_ptr,
            total_pedidos_ptr,
            capacidade_ptr,
            mesa,
            pessoas,
            item_id_escolhido,
            cardapio_menu,
            total_itens_cardapio,
            quantidade_item,
            cupom_str,
            desconto_val
        );

        printf("\nItem '%s' (x%d) adicionado ao pedido da mesa %d.\n",
                cardapio_menu[posicao_item_no_cardapio].item, quantidade_item, mesa);

        printf("Deseja adicionar outro item a este pedido da mesa %d? (s/n): ", mesa);
        scanf(" %c", &adicionar_mais_itens);
        while (getchar() != '\n');
    }

    printf("\n--- PEDIDO DA MESA %d CONCLUIDO ---\n", mesa);
}