#include "func_restaurante.h"
#include <stdio.h>
#include <stdlib.h>

// Função de registrar um item no cardápio
// Salva um registro do tipo Cardapio ao final do arquivo binário padrão
int adicionar_item(Cardapio item) {

  // Abre o arquivo binário padrão para adicionar ao fim. Se não existe, cria o arquivo "cardapio.bin"
	FILE *fptr = fopen (STD_BIN, "ab");

  // Verifica se o arquivo foi acessado para escrita. Em caso de falha retorna 1
  if (fptr == NULL) {

    printf("Falha ao tentar abrir cardapio para adicionar item. Caso ainda nao tenha cadastrado itens, acesse menu do proprietario para faze-lo.\n");

    return 1;

  }

  // Escreve uma item no cardaio. Em caso de falha, retorna 1
  if(fwrite(&item, sizeof(Cardapio), 1, fptr) != 1) {

    printf("Falha ao adicionar item ao cardapio,\n");

    return 1;

  }

  // Ao fim, fecha o arquivo binário
  fclose(fptr);

  // Em caso de sucesso, retorna 0
  return 0;

}

// Função para carregar todo o cardapio para a memoria em um array de itens do tipo Cardapio (passagem por referencia)
// Retorna 0 se bem sucedido, caso contrário retorna 1

int carregar_cardapio(char *filename, Cardapio **cardapio) {

  // Inicia o array de cardapio como NULL
  *cardapio = NULL;

  // Variável auxiliar para ler os itens do cardápio
  Cardapio item_atual;

  // Inicializa o contador de itens lidos
  int cont = 0;

  // Abre o arquivo binário para leitura
  FILE *fptr = fopen(filename, "rb");

  // Verifica se o arquivo foi aberto corretamente
  if (fptr == NULL) {

    printf("Falha ao tentar abrir cardapio para leitura.\n");
    return 1;

  }

  // Lê os itens do cardápio até o final do arquivo, realocando memória conforme necessário
  // A cada item lido, incrementa o contador e realoca o array de cardápio
  while (fread(&item_atual, sizeof(Cardapio), 1, fptr) == 1) {

    cont++;

    Cardapio *tmp = realloc(*cardapio, sizeof(Cardapio)*(cont));

    // Verifica se a realocação foi bem sucedida
    if (tmp == NULL) {

      printf("Falha ao realocar memoria.\n");

      fclose(fptr);

      free(*cardapio);

      return 1;

    }

    // Atualiza o ponteiro do cardápio para o novo endereço de memória
    *cardapio = tmp;

    // Armazena o item lido no array de cardápio
    // Atribui o item atual ao último índice do array
    (*cardapio)[cont-1] = item_atual;

  }

  fclose(fptr);

  return 0;
}

// Função para converter o tipo de item em uma string
char* tipo_str(int tipo) {

  switch (tipo) {

    case 0:
      return "Prato";

    case 1:
      return "Bebida";

    case 2:
      return "Sobremesa";

    default:
      return NULL;

  }

}

// Função para imprimir o cardápio na tela
// Lê o arquivo binário padrão e imprime os itens do cardápio formatados
int imprimir_cardapio(char *filename) {

  // Abre o arquivo binário para leitura
  FILE *fptr = fopen(filename, "rb");

  // Variável para armazenar o item atual lido do cardápio
  Cardapio item_atual;

  // Variável para controlar o número sequencial dos itens
  int numero_sequencial = 1;

  // Verifica se o arquivo foi aberto corretamente
  if (fptr == NULL) {

    printf("Falha ao tentar abrir cardapio para leitura.\n");

    return 1;

  }

  // Imprime o cabeçalho do cardápio
  printf("\n-------------------------- C A R D A P I O -------------------------\n");
  printf("|------|--------------------------------|-----------|--------------|\n");
  printf("| %-4s | %-30s | %-9s | %-12s |\n", "No.", "Item", "Tipo", "Valor (R$)");
  printf("|------|--------------------------------|-----------|--------------|\n");

  // Lê os itens do cardápio e imprime cada um formatado
  // Enquanto houver itens no arquivo, lê e imprime cada item
  while (fread(&item_atual, sizeof(Cardapio), 1, fptr) == 1) {

    printf("| %-4d | %-30.30s | %-9.9s | R$ %9.2f |\n",
      numero_sequencial,
      item_atual.item,
      tipo_str(item_atual.tipo),
      item_atual.valor);

    numero_sequencial++;

  }

 printf("|------|--------------------------------|-----------|--------------|\n");

  return 0;

}

// Função para contar o total de itens no cardápio
// Lê o arquivo binário padrão e calcula o número total de itens
int total_itens_cardapio(char *filename) {

    // Abre o arquivo binário para leitura
    FILE *f = fopen(filename, "rb");
    // Verifica se o arquivo foi aberto corretamente
    if (!f) return 0;
    
    // Move o ponteiro do arquivo para o final e calcula o tamanho total em bytes
    fseek(f, 0, SEEK_END);

    // Calcula o número total de itens dividindo o tamanho total pelo tamanho de um item Cardapio
    int total = ftell(f) / sizeof(Cardapio);

    // Fecha o arquivo
    fclose(f);

    // Retorna o total de itens
    return total;
}

// Função para editar um item do cardápio
// Lê o arquivo binário padrão, modifica o item especificado e salva as alterações
int editar_item_cardapio(char *filename, int indice, Cardapio *novo_item) {

  // Abre o arquivo binário para leitura e escrita
  FILE *fptr = fopen(filename, "r+b");

  // Verifica se o arquivo foi aberto corretamente
  if (fptr == NULL) {

    printf("Falha ao tentar abrir cardapio para edicao.\n");
    return 1;

  }

  // Move o ponteiro do arquivo para a posição do item a ser editado
  fseek(fptr, indice * sizeof(Cardapio), SEEK_SET);

  // Escreve o novo item no arquivo
  if (fwrite(novo_item, sizeof(Cardapio), 1, fptr) != 1) {

    printf("Falha ao editar item no cardapio.\n");
    fclose(fptr);
    return 1;

  }

  // Fecha o arquivo
  fclose(fptr);
  return 0;
}

// Função para remover um item do cardápio
// Carrega o cardápio, remove o item especificado e salva as alterações
// Recebe o nome do arquivo binário e o índice do item a ser removido
int remover_item_cardapio(char *filename, int indice) {

  Cardapio *cardapio;

  int total = total_itens_cardapio(filename);
  
  carregar_cardapio(STD_BIN, &cardapio);

  for (int i = indice; i < total - 1; i++) {

    cardapio[i] = cardapio[i + 1];

  }

  // Abre o arquivo binário para escrita, sobrescrevendo o conteúdo (limpando)
  FILE *fptr = fopen(filename, "wb");

  // Verifica se o arquivo foi aberto corretamente para limpar o conteúdo
  if (fptr == NULL) {

    printf("Falha ao tentar abrir cardapio para remocao.\n");

    return 1;

  }
  
  // Fecha o arquivo sem fazer alterações (apenas para limpar o conteúdo)
  fclose(fptr);

  // Reabre o arquivo binário para adicionar os itens restantes
  for (int i = 0; i < total - 1; i++) {

    adicionar_item(cardapio[i]);

  }

  // Libera a memória alocada para o cardápio
  free(cardapio);

  return 0;

}


// Função para verificar se um inteiro é um índice do cardápio válido
// Retorna 0 se o índice for válido, caso contrário retorna 1
// Recebe o arquivo binário padrão, conta a quantidade de itens e verifica se o índice está dentro do intervalo
int verificar_indice_cardapio(char *filename, int indice) {

  // Conta o total de itens no cardápio
  int total_itens = total_itens_cardapio(filename);

  // Verifica se o índice está dentro do intervalo válido
  if (indice < 0 || indice >= total_itens) {
    printf("Indice invalido. Deve ser entre 1 e %d.\n", total_itens);
    return 1;
  }

  return 0;
}

int validar_tipo(int tipo) {

  // Verifica se o tipo é válido (0, 1 ou 2)
  if (tipo < 0 || tipo > 2) {
    printf("Tipo invalido. Deve ser 0 (Prato), 1 (Bebida) ou 2 (Sobremesa).\n");
    return 1;
  }

  return 0;
}

// Função para validar se o valor do item é um real positivo
int validar_valor(float valor) {

  // Verifica se o valor é positivo
  if (valor < 0) {
    printf("Valor invalido. Deve ser um numero positivo.\n");
    return 1;
  }

  return 0;
}

