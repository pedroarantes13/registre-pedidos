#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída     
#include <string.h> // Inclui a biblioteca de manipulação de strings
#include <stdlib.h> // Inclui a biblioteca padrão de alocação de memória e outras funções utilitárias

#include "../func/funcoes.h" // Inclui o cabeçalho de funções do cliente para acessar as funções de menu e pedidos
#include "../../restaurante/func/func_restaurante.h" // Inclui o cabeçalho do restaurante para acessar o cardápio

int menu_cliente() {

    int escolha = 0; // Variável para armazenar a escolha do usuário

    struct dados_pedido *pedidos = NULL; // Ponteiro para armazenar os pedidos feitos pelo cliente    
    int total_pedidos = 0; // Total de pedidos feitos     
    int capacidade = 0; // Capacidade do vetor de pedidos, para evitar realocações frequentes
    
    struct cupom_desconto cupons_disponiveis[MAX_CUPONS]; // Array de cupons de desconto disponíveis
    inicializar_cupons(cupons_disponiveis); // Inicializa os cupons disponíveis com códigos e porcentagens fixas
    
    // Carrega o cardápio

    Cardapio *cardapio = NULL;  // Ponteiro para armazenar o cardápio
    int contador_itens_cardapio = 0; // Contador de itens no cardápio       

    if (carregar_cardapio(STD_BIN, &cardapio) != 0) { // Tenta carregar o cardápio do arquivo   
        printf("Nao foi possivel abrir o cardapio. Caso ainda nao tenha cadastrado itens, acesse menu do proprietario para faze-lo.\n"); // Exibe mensagem de erro se não conseguir abrir o cardápio
       
        if (cardapio != NULL) { // Se o cardápio foi alocado, libera a memória        
            free(cardapio); // Libera a memória alocada para o cardápio
            cardapio = NULL; // Evita ponteiro solto       
        }

        return 1; // Retorna 1 para indicar erro ao carregar o cardápio
    }

    contador_itens_cardapio = total_itens_cardapio(STD_BIN); // Obtém o total de itens no cardápio

    
    carregar_pedidos(&pedidos, &total_pedidos, &capacidade); // Carrega os pedidos salvos        

    do { // Loop para exibir o menu até que o usuário escolha sair 

    escolha = mostrarMenu(); // Chama a função para mostrar o menu e obter a escolha do usuário

        switch (escolha) // Verifica a escolha do usuário
        {
            case 1:
                // Chama a função para mostrar os pratos principais do cardápio gerado em binário
                mostrarPratosPrincipais(cardapio, contador_itens_cardapio); 

                // Pausa a tela para que o usuário possa ver os pratos principais               
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
                // Chama a função para fazer um pedido, passando os ponteiros necessários
                fazerPedido(&pedidos, &total_pedidos, &capacidade, cardapio, contador_itens_cardapio, cupons_disponiveis, MAX_CUPONS);
                break;

            case 5:
                // Opção para sair do sistema
                printf("\nVoltando para o menu inicial...\n");
                
                break;
            default:
                // Caso o usuário escolha uma opção inválida, exibe mensagem de erro
                printf("Opcao invalida!\n");
                break;
        }
        
    } while (escolha != 5); // Continua até o usuário escolher sair (opção 5)
       
    // Libera memória alocada
    
    free(pedidos); // Libera a memória alocada para os pedidos
    if (cardapio != NULL) { // Se o cardápio foi alocado, libera a memória
    free(cardapio); // Libera a memória alocada para o cardápio
   }

    return 0; // Retorna 0 para indicar que o menu foi encerrado com sucesso
}

    // FUNÇÕES PARA MOSTRAR PRATOS PRINCIPAIS, BEBIDAS E SOBREMESAS
void mostrarPratosPrincipais(Cardapio *cardapio_ptr, int total_itens) 

{
    printf("\nPRATOS:\n");
    printf("----------------------------------------------------------\n"); 
    printf("| %-4s | %-30s | %-12s |\n", "ID", "Item", "Valor (R$)");
    printf("|------|--------------------------------|--------------|\n");

    int encontrado = 0; // Variável para verificar se algum prato foi encontrado
    int id_exibicao = 1; // Variável para exibir o ID dos pratos       
    for (int i = 0; i < total_itens; i++) { // Percorre todos os itens do cardápio
        if (cardapio_ptr[i].tipo == 0) {  // Verifica se o tipo do item é prato principal
            printf("| %-4d | %-30s | R$ %-9.2f |\n", // Exibe o ID, nome do item e valor formatado       
                   id_exibicao, cardapio_ptr[i].item, cardapio_ptr[i].valor); // Exibe o prato principal
            id_exibicao++; // Incrementa o ID de exibição para o próximo prato
            encontrado = 1; // Marca que pelo menos um prato foi encontrado
        }
    }
    if (!encontrado) { // Se nenhum prato foi encontrado, exibe mensagem    
        printf("|              NENHUM PRATO ENCONTRADO                                 |\n");
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
         printf("|              NENHUMA BEBIDA ENCONTRADA                               |\n");
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
         printf("|              NENHUMA SOBREMESA ENCONTRADA                              |\n");
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
    int escolha = 0; // Variável para armazenar a escolha do usuário

    while (escolha < 1 || escolha > 5) { // Loop até que o usuário escolha uma opção válida

        printf("======================================\n");
        printf("         BEM-VINDO AO SISTEMA!        \n");
        printf("======================================\n\n");

        printf("--------------------------------------\n");
        printf("| %-34s |\n", "1 - Pratos"); //
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

        printf("| %-34s |\n", "5 - Menu inicial");
        printf("--------------------------------------\n\n");

        printf("Digite a opcao desejada: ");

        if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > 5) { // Verifica se a entrada é válida
            printf("\nEntrada invalida. Digite um numero entre 1 e 5.\n"); // Exibe mensagem de erro se a entrada for inválida
            while (getchar() != '\n'); // Limpa o buffer de entrada
        }
    }

    return escolha; // Retorna a escolha do usuário
}
  // Implementação da função para obter o desconto de um cupom
float obter_desconto_cupom(const char *cupom_digitado, const struct cupom_desconto cupons[], int num_cupons) {
    for (int i = 0; i < num_cupons; i++) { // Percorre todos os cupons disponíveis
        if (strcmp(cupom_digitado, cupons[i].codigo) == 0) { // Compara o cupom digitado com o código do cupom atual        
            return cupons[i].porcentagem; // Retorna a porcentagem de desconto encontrada
        }
    }
    return 0.0; // Retorna 0.0 se o cupom não for encontrado
}
    // Função para fazer um pedido, recebe ponteiros para cada parametro necessário
void fazerPedido(struct dados_pedido **pedidos_ptr, int *total_pedidos_ptr, int *capacidade_ptr, Cardapio *cardapio_menu, int total_itens_cardapio,
                 const struct cupom_desconto cupons_disponiveis[], int num_cupons) {
    int mesa; // Variável para armazenar o número da mesa
    int pessoas; // Variável para armazenar o número de pessoas na mesa
    char cupom_str[20] = ""; // String para armazenar o cupom de desconto
    float desconto_val = 0.0; // Variável para armazenar o valor do desconto
    char tem_cupom = 'n'; // Variável para verificar se o cliente tem cupom de desconto

    printf("\n--- INICIAR NOVO PEDIDO ---\n");

    printf("Digite o numero da mesa: ");
    while (scanf("%d", &mesa) != 1 || mesa <= 0) { // Verifica se a entrada é válida
        printf("Numero de mesa invalido. Digite um numero positivo: "); //
        while (getchar() != '\n'); // Limpa o buffer de entrada
    }
    while (getchar() != '\n'); // Limpa o buffer de entrada depois de sair do loop

    printf("Digite o numero de pessoas na mesa: "); 
    while (scanf("%d", &pessoas) != 1 || pessoas <= 0) { // Verifica se a entrada é válida
        printf("Numero de pessoas invalido. Digite um numero positivo: ");
        while (getchar() != '\n'); // Limpa o buffer de entrada
    }
    while (getchar() != '\n'); // Limpa o buffer de entrada depois de sair do loop

    printf("Possui cupom de desconto? (s/n): "); // Pergunta se o cliente tem cupom de desconto
    scanf(" %c", &tem_cupom); // Lê a resposta do cliente
    while (getchar() != '\n'); // Limpa o buffer de entrada

    if (tem_cupom == 's' || tem_cupom == 'S') {
        printf("Digite o cupom: "); // Solicita ao cliente que digite o cupom de desconto
        fgets(cupom_str, sizeof(cupom_str), stdin);
        cupom_str[strcspn(cupom_str, "\n")] = 0; // Remove a quebra de linha.

        if (strlen(cupom_str) > 0) { // Se o usuário digitou algo
            desconto_val = obter_desconto_cupom(cupom_str, cupons_disponiveis, num_cupons);

            if (desconto_val > 0.0) { // Se a função retornou um desconto válido.
                printf("Cupom '%s' aplicado! %.0f%% de desconto.\n", cupom_str, desconto_val * 100);
            } else { // Se o cupom é inválido.
                printf("Cupom '%s' invalido ou expirado. Nenhum desconto aplicado.\n", cupom_str);
                strcpy(cupom_str, ""); // Limpa o cupom_str para não persistir um inválido.
                desconto_val = 0.0;    // Garante que o desconto seja 0.
            }
        } else { // Se o usuário disse 's' mas não digitou nada.
            printf("Cupom vazio. Nenhum desconto aplicado.\n");
            strcpy(cupom_str, "");
            desconto_val = 0.0;
        }
    } else { // Se o cliente não possui cupom.
        strcpy(cupom_str, "");
        desconto_val = 0.0;
    }

    char adicionar_mais_itens = 's'; // Variável para controlar se o cliente deseja adicionar mais itens ao pedido
    while (adicionar_mais_itens == 's' || adicionar_mais_itens == 'S') { // Loop para adicionar itens ao pedido até que o cliente decida parar    
        printf("\n--- Adicionar Item ---\n");

        printf("\n-------------------------- C A R D A P I O -------------------------\n");
        printf("|------|--------------------------------|-----------|--------------|\n");
        printf("| %-4s | %-30s | %-9s | %-12s |\n", "ID", "Item", "Tipo", "Valor (R$)"); // Exibe o cabeçalho da tabela do cardápio
        printf("|------|--------------------------------|-----------|--------------|\n");
        
        for (int i = 0; i < total_itens_cardapio; i++) { // Percorre todos os itens do cardápio
            printf("| %-4d | %-30.30s | %-9.9s | R$ %9.2f |\n", // Exibe o ID, nome do item, tipo e valor formatado
                    i + 1, // 'i + 1' para exibir IDs começando de 1
                    cardapio_menu[i].item, // Nome do item      
                    tipo_str(cardapio_menu[i].tipo), // Converte o tipo do item para string
                    cardapio_menu[i].valor); // Valor do item formatado com 2 casas decimais
        }
        printf("|------|--------------------------------|-----------|--------------|\n");

        int item_id_escolhido; // Variável para armazenar o ID do item escolhido pelo cliente

        printf("Digite o ID do item que deseja adicionar (1 a %d): ", total_itens_cardapio); // Solicita ao cliente o ID do item que deseja adicionar ao pedido
        if (scanf("%d", &item_id_escolhido) != 1 || item_id_escolhido < 1 || item_id_escolhido > total_itens_cardapio) { // Verifica se a entrada é válida
            printf("ID de item invalido. Tente novamente.\n");
            while (getchar() != '\n');
            continue; // Se a entrada for inválida, exibe mensagem de erro e continua o loop
        }
        while (getchar() != '\n');

        int posicao_item_no_cardapio = item_id_escolhido - 1; // Converte o ID do item para a posição no vetor (começa em 0)    

        int quantidade_item; // Variável para armazenar a quantidade do item escolhido pelo cliente        
        printf("Quantidade: ");
        if (scanf("%d", &quantidade_item) != 1 || quantidade_item <= 0) { // Verifica se a entrada é válida      
            printf("Quantidade invalida. Tente novamente.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        // Chama a função para registrar e salvar o pedido, passando os ponteiros necessários
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

        // Exibe mensagem de confirmação do item adicionado ao pedido
        printf("\nItem '%s' (x%d) adicionado ao pedido da mesa %d.\n",
        cardapio_menu[posicao_item_no_cardapio].item, quantidade_item, mesa);   
        
        // Pergunta se o cliente deseja adicionar mais itens ao pedido
        printf("Deseja adicionar outro item a este pedido da mesa %d? (s/n): ", mesa);
        scanf(" %c", &adicionar_mais_itens); // Lê a resposta do cliente
        while (getchar() != '\n');
    }

    printf("\n--- PEDIDO DA MESA %d CONCLUIDO ---\n", mesa); // Exibe mensagem de conclusão do pedido da mesa        
}