#include <stdio.h>

int avaliarsenha(int senha){ //funcao para avaliar a senha, utilizei para deixar o codigo mais limpo
    int tentativa;
    do {
        printf("Digite a senha: ");
        scanf("%d", &tentativa);

        if(tentativa != senha)
        printf("Senha incorreta. tente novamente\n");
    } while(tentativa != senha);
        
    return 1;
}

int main(){

int n1, n2;

  printf("Olá, seja bem vindo(a)\n");
  printf("Voce e:\n1 - Cliente\n2 - Funcionario\nPara a opcao desejada, digite o numero correspondente: ");
  scanf("%d", &n1);
    if (n1 == 1){
        printf("Seja bem vindo cliente!");
    } else if (n1 == 2){
            int senha = 321;
            avaliarsenha(senha); // Nesse momento chamo a funcao para avaliar a senha
            printf("1 - Visualizar cardapio\n2 - Gerar Relatorio\n");
            scanf("%d", &n2);

            if (n2 == 1){
                printf("'''Arquivo binario'''\n"); // Aqui entrara no arquivo binario do cardapio

            } else if (n2 == 2){
                int n3;
                printf("1 - Gerar relatorio\n2 - Sair\n");
                scanf("%d", &n3);

                if (n3 == 1){
                    printf("Gerarando relatorio..."); // Funcao gerar relatorio

              } else {
                printf("Funcao encerrada"); // Encerra o programa
              }
            }
         } else {
        printf("Comando invalido!\nTente novamente."); //Caso o numero digitado seja diferente de 1 e 2
    }
return 0;
}

