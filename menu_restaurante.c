#include <stdio.h>

int main(){

int n1, n2;

  printf("Olá, seja bem vindo(a)\n");
  printf("Voce e: cliente (1) funcionario (2)?\n Para a opcao, digite o numero correspondente: ");
  scanf("%d", &n1);
    if (n1 == 1){
        printf("Seja bem vindo cliente!");
    } else if (n1 == 2){
        int senha
        printf("Digite a senha: ");
        scanf("%d", &senha);
         if (senha == 321){
            printf("Visualizar cardapio (1) Gerar Relatorio (2)");
            scanf("%d", &n2);
            if (n2 == 1){
                printf("'''Arquivo binario'''"); // Aqui entrara no arquivo binario do cardapio
            } else if (n2 == 2){
                int n3;
                printf("Gerar relatorio (1) Sair (2)");
                scanf("%d", &n3);
                if (n3 == 1){
                    printf("Gerar relatorio"); // Funcao gerar relatorio
                } else if{
                    printf("Funcao encerrada"); // Encerra o programa
                }

            }
         } else if (senha != 321){
            printf("Senha incorreta");
         }
    } else if (n1 != 2 && n1 != 1){
        printf("Comando invalido");
    }
return 0;
}

