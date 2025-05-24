#include <stdio.h>

int main(){
  
 int escolha;

    printf("[SEJA BEM VINDO NOVAMENTE!]\n\n");

 while(1){

    printf("|¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨|\n");
    printf("| VISUALIZAR CARDAPIO [1]|\n");
    printf("|........................|\n");
    printf("|¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨|\n");
    printf("|   GERAR RELATORIO [2]  |\n");
    printf("|........................|\n");
    printf("|¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨|\n");
    printf("|   FINALIZAR SECAO [0]  |\n");
    printf("|........................|\n");
    

    printf("          [   ]\b\b\b");
    scanf("%d", &escolha);


    switch (escolha)
    {
    case 1:
        printf("\n==CARDAPIO=="); //Chamo a funcao do Pedro
        return 0;
    case 2:
        printf("\n==RELATORIO=="); //Chamo a funcao do Daniel    
        return 0;
    case 0:
        printf("\n==SECAO ENCERRADA=="); //Finaliza secao 
        return 0;   
    default:
        printf("\n  [COMANDO INVALIDO!]\n   [TENTE NOVAMENTE]\n"); //Entra em loop ate que se digite um comando valido
    }
  }


    
return 0;
}