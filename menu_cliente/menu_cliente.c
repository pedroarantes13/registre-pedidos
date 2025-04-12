#include <stdio.h>
int main () 
{
    int escolha = 0;
    // Variaveis de opcoes para o Menu
    int Pratos_principais = 1, Bebidas = 2, Sobremesas = 3, Sair = 4;
    
    while (escolha < 1 || escolha > 4)
    /* Implementacao de um sistema para validar o input do cliente*/
    {
        printf("\nEscolha uma opcao do menu abaixo:\n ");
        printf("\n1 - Pratos principais\n2 - Bebidas\n3 - Sobremesas\n4 - Sair\n");
        printf("\nSua escolha: ");
    
    if (scanf("%d", &escolha) != 1) {
        printf("\nPor favor, digite uma opcao valida.\n");
        while (getchar() != '\n'); // Limpa o buffer para evitar lixo de memoria
        continue; }
        
    switch (escolha)  /* Switch para exibir o cardapio conforme a escolha do menu */
    {
    case 1:
        printf("PRATOS PRINCIPAIS:\n");
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
        printf("\nSOBREMESAS:\n");
        printf("Acai - R$ 10.00\n");
        printf("Pudim - R$ 10.00\n");
        printf("Trufa - R$ 5.00\n"); 
        break;
    
    case 4: 
        printf("\nPressione Enter para sair. ");
        while (getchar() != '\n');
        getchar (); break; /*Esse seria o menu principal para
        login do restaurante ou cliente, ainda nao foi desenvolvido.*/
        
    default:
        printf("Opcao invalida!\n");
        escolha = 0; // Forca o while a manter o loop
        break; 
    }
    
    } 

}