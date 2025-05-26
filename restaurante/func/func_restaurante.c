#include "func_restaurante.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Imprime uma linha intermediária (visual)

void mid_line() {
    printf("-----------------------------------------------------\n");
}

// Imprime uma linha de topo/rodapé (visual)

void top_bottom() {
    printf("=====================================================\n");
}

// Função de registrar um item no cardápio
//    -> Salva um registro do tipo Cardapio ao final do arquivo binário padrão
//    -> (Pendente) Restaurates podem ter mais de um cardápio para diferentes dias/horários
//    -> (Pendente) Permite escolher em qual cardápio será feito o registro (arquivos binários)

void escrever_dados(Cardapio item) {

	FILE *fptr = fopen (STD_BIN, "ab");

  if (fptr == NULL){

    printf("Falha ao tentar acessar arquivo de dados\n");

  } else {

    fwrite(&item, sizeof(Cardapio), 1, fptr);
    fclose(fptr);

  }

}

// Função para carregar todos os itens de um arquivo binário (filename) para a memória

Cardapio* ler_dados(char filename[50], int *num_itens) {

  Cardapio *cardapio = calloc(1,sizeof(Cardapio));

  Cardapio item_atual;

  int cont = 0;

  *num_itens = 0;

  FILE *fptr = fopen(filename, "rb");

  if (fptr == NULL) {

    printf("Falha ao tentar acessar arquivo de dados\n");
    free(cardapio);
    return NULL;

  }

  while (fread(&item_atual, sizeof(Cardapio), 1, fptr) == 1) {

    strcpy(cardapio[cont].item, item_atual.item);
    cardapio[cont].tipo = item_atual.tipo;
    cardapio[cont].valor = item_atual.valor;
    cardapio[cont].tempo_preparo = item_atual.tempo_preparo;

    cont++;

    Cardapio *tmp = realloc(cardapio, sizeof(Cardapio)*(cont + 1));

    if (tmp == NULL) {

      printf("Falha ao realocar memoria\n");
      fclose(fptr);
      *num_itens = cont;

      return cardapio;

    }

    cardapio = tmp;

  }

  fclose(fptr);
  *num_itens = cont;
  return cardapio;

}

