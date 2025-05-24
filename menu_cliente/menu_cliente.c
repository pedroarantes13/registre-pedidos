#include <stdio.h>
#include <string.h>

#define TAM_NOME 50
#define MAX_ITEM 50

int mostrarMenu()
{
    
    int escolha = 0;
    
        while (escolha < 1 || escolha > 4) // Validação do input do cliente.
        {
            printf("\nEscolha uma opcao do menu abaixo:\n ");
            printf("\n1 - Pratos principais\n2 - Bebidas\n3 - So nobremesas\n4 - Sair\n");
            printf("\nDigite a opcao desejada: ");
    
            if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > 4) 
            {
                printf("\nEntrada invalida. Digite um numero entre 1 e 4.\n");
                while (getchar() != '\n'); // Limpa o buffer para evitar lixo de memoria
                continue;
            }
        } 
        
    return escolha; // Retorna o valor do input.

}

struct item {
    char nome [50];
    int quantidade;
    float preco_unitario;
};

struct pedido {
    int id_pedido;
    char nome_cliente[TAM_NOME];
    struct item itens[MAX_ITEM];
    int total_itens;
    float total_pedido;
};

int main () 
{
    int escolha = 0;

    do {

    escolha = mostrarMenu(); // Atribuí a função Menu para escolha.

        switch (escolha)  /* Switch para exibir o cardapio conforme a escolha do menu */
        {
            case 1:
                printf("\nPRATOS PRINCIPAIS:\n");
                printf("\nFeijoada - R$ 38.00\n");
                printf("Estrogonofe com arroz - R$ 28.00\n");
                printf("Lasanha - R$ 32.00\n");
                break;

            case 2: 
                printf("\nBEBIDAS:\n");
                printf("Suco natural - R$ 7.00\n");
                printf("Refrigerante Guarana 2l - R$ 10.00\n");
                printf("Caipirinha - R$ 16.00\n"); 
                break;

            case 3:
                printf("\nSOBREMESAS:\n\n");
                printf("Acai - R$ 10.00\n");
                printf("Pudim - R$ 10.00\n");
                printf("Trufa - R$ 5.00\n"); 
                break;
    
            case 4: 
                printf("\nSaindo do sistema. Obrigado pela visita.\n");
                while (getchar() != '\n');
                break; 

            default:
                printf("Opcao invalida!\n");
                escolha = 0; // flag para o while a manter o loop
                break; 
        }
        
    } while (escolha != 4); 

}