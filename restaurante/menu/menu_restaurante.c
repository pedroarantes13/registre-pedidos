#include <stdio.h>
#include "../registre-pedidos/dados_restaurante.h"
#include "../cliente/func/funcoes.h"

int main(){
  
 int escolha;

    printf("[SEJA BEM VINDO NOVAMENTE!]\n\n");

 while(1){

    printf("|¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨|\n");
    printf("| VISUALIZAR CARDAPIO [1]|\n");
    printf("|........................|\n");
    printf("|¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨|\n");
    printf("|   EDITAR CARDAPIO [2]  |\n");
    printf("|........................|\n");
    printf("|¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨|\n");
    printf("|   GERAR RELATORIO [3]  |\n");
    printf("|........................|\n");
    printf("|¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨|\n");
    printf("|   FINALIZAR SECAO [0]  |\n");
    printf("|........................|\n");
    

    printf("          [   ]\b\b\b");
    scanf("%d", &escolha);


    switch (escolha)
    {
    case 1:
        /*Conferir se o cardapio ja esta preenchido
        Se sim: mostre o cardapio e pergunta se quer editar
        Se nao, avisa que o cardapio nao esta preenchido
        E pergunta se quer preencher */    

        printf("\n==CARDAPIO=="); //Chamo a funcao do Pedro, para mostrar o cardapio

        break;

    case 2:
     

        printf("Editar cardapio"); //Aqui o usuario podera editar o cardapio

        break;

    case 3:
        gerar_relatorio_final();

    case 0:

        printf("\n==SECAO ENCERRADA=="); //Finaliza secao 
        break;  

    default:
    
        printf("\n  [COMANDO INVALIDO!]\n   [TENTE NOVAMENTE]\n"); //Entra em loop ate que se digite um comando valido
    }
  }


    
return 0;
}