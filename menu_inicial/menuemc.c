#include <stdio.h>

#define SENHA_CORRETA 1234  

void menu_cliente() {
    int x;
    int opcao_valida = 0;

    do{

        printf("\nBem vindo ao menu do cliente\n\n");
        printf("1. Acessar pedidos\n");
        printf("2. Retornar ao menu principal.\n");

        printf("\nDigite sua opcao: ");
        scanf("%d", &x);

        switch(x){
            case 1:
                printf("\nPedidos\n");
                opcao_valida = 1;
                break;
            case 2:
                main();
                opcao_valida = 1;
                break;
            default:
                printf("Opcao invalida. Tente novamente\n\n");
                opcao_valida = 0;

        }


    } while(!opcao_valida);


}

void menu_proprietario() {
    int senha_digitada;
    int tentativas = 0;
    int acesso_liberado = 0;

    printf("\nBem-vindo ao menu do proprietario\n");

    while (tentativas < 3) {
       
        printf("\nDigite sua senha:  ");
        scanf("%d", &senha_digitada);

        if (senha_digitada == SENHA_CORRETA) {
            
            printf("Acesso concedido!\n");
            acesso_liberado = 1;
            break; 
       
        } else {
            
            printf("\nSenha incorreta! Tente novamente.\n");
            tentativas++;
        }
    }

    if (!acesso_liberado) {
        
        printf("\nNumero maximo de tentativas atingido. Acesso bloqueado.\n");
        main();
   
    } else {
      
        printf("\nMenu do proprietario:\n\n");
       
        printf("1. Ver relatorios\n");
        printf("2. Gerenciar cardapio\n");
        printf("3. Configuracoes do sistema\n");
        
    }
}

void sair() {
    printf("\nVoce saiu.\n");
}

int main() {
    int x;
    int opcao_valida = 0;

    do {
        printf("\nBem vindo ao menu principal.\n\n");
        printf("1. Menu cliente.\n");
        printf("2. Menu proprietario.\n");
        printf("3. Sair\n\n");
        printf("Digite sua opcao: ");
        scanf("%d", &x);

        switch (x) {
            case 1:
                menu_cliente();
                opcao_valida = 1;
                break;
            case 2:
                menu_proprietario();
                opcao_valida = 1;
                break;
            case 3:
                sair();
                opcao_valida = 1;
                break;
            default:
                printf("\nOpcao invalida. Escolha novamente.\n");
                opcao_valida = 0;
        }

    } while (!opcao_valida); 

    return 0;
}
