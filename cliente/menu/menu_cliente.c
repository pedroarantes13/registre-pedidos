#include <stdio.h>
#include <string.h>

#define TAM_NOME 50
#define MAX_ITEM 50

// Funções para mostrar os cardápios
void mostrarPratosPrincipais() {
    printf("\nPRATOS PRINCIPAIS:\n");
    printf("Feijoada - R$ 38.00\n");
    printf("Estrogonofe com arroz - R$ 28.00\n");
    printf("Lasanha - R$ 32.00\n");
}

void mostrarBebidas() {
    printf("\nBEBIDAS:\n");
    printf("Suco natural - R$ 7.00\n");
    printf("Refrigerante Guarana 2l - R$ 10.00\n");
    printf("Caipirinha - R$ 16.00\n"); 
}

void mostrarSobremesas() {
    printf("\nSOBREMESAS:\n");
    printf("Acai - R$ 10.00\n");
    printf("Pudim - R$ 10.00\n");
    printf("Trufa - R$ 5.00\n"); 
}


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
        
    return escolha; // Retorna o valor da escolha

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

// Funcao para fazer pedidos
void fazerPedido(struct pedido* p) {
    int tipo, opcao, qtd;

    printf("\nDigite o nome do cliente: ");
    getchar(); // Limpa o \n do buffer
    fgets(p->nome_cliente, TAM_NOME, stdin);
    p->nome_cliente[strcspn(p->nome_cliente, "\n")] = 0; // Remove o \n 

    printf("\nQual tipo de item deseja pedir?\n");
    printf("1 - Prato principal\n2 - Bebida\n3 - Sobremesa\n");
    scanf("%d", &tipo);

    if (tipo == 1) {
        mostrarPratosPrincipais();
    } else if (tipo == 2) {
        mostrarBebidas();
    } else if (tipo == 3) {
        mostrarSobremesas();
    } else {
        printf("Tipo invalido.\n");
        return;
    }

    printf("\nEscolha uma opcao (1 a 3): ");
    scanf("%d", &opcao);

    printf("Quantidade: ");
    scanf("%d", &qtd);

    struct item novo;

    if (tipo == 1) {
        if (opcao == 1) { strcpy(novo.nome, "Feijoada"); novo.preco_unitario = 38.0; }
        else if (opcao == 2) { strcpy(novo.nome, "Estrogonofe"); novo.preco_unitario = 28.0; }
        else if (opcao == 3) { strcpy(novo.nome, "Lasanha"); novo.preco_unitario = 32.0; }
        else { printf("Opcao invalida.\n"); return; }
    } else if (tipo == 2) {
        if (opcao == 1) { strcpy(novo.nome, "Suco natural"); novo.preco_unitario = 7.0; }
        else if (opcao == 2) { strcpy(novo.nome, "Guarana 2L"); novo.preco_unitario = 10.0; }
        else if (opcao == 3) { strcpy(novo.nome, "Caipirinha"); novo.preco_unitario = 16.0; }
        else { printf("Opcao invalida.\n"); return; }
    } else if (tipo == 3) {
        if (opcao == 1) { strcpy(novo.nome, "Acai"); novo.preco_unitario = 10.0; }
        else if (opcao == 2) { strcpy(novo.nome, "Pudim"); novo.preco_unitario = 10.0; }
        else if (opcao == 3) { strcpy(novo.nome, "Trufa"); novo.preco_unitario = 5.0; }
        else { printf("Opcao invalida.\n"); return; }
    }

    novo.quantidade = qtd;
    p->itens[0] = novo; //
    p->total_itens = 1;
    p->total_pedido = qtd * novo.preco_unitario;

    printf("\nPedido registrado com sucesso!\n");
    printf("Cliente: %s\n", p->nome_cliente);
    printf("Item: %s | Quantidade: %d | Total: R$ %.2f\n", novo.nome, qtd, p->total_pedido);
}



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
                break;
            case 2:
                mostrarBebidas();
                break;
            case 3:
                mostrarSobremesas();
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