#include "func_restaurante.h"
#include <stdio.h>
#include <stdlib.h>

// Instruções para o compilador para as funções de truncar o arquivo
// Faz a interoperabilidade entre sistemas operacionais Windows e POSIX (Linux)
// Dependendo do sistema operacional, define a função ftruncate corretamente
// Se for Windows, usa _chsize_s, caso contrário usa ftruncate
// A função remover_item_cardapio usa _chsize_s para truncar o arquivo após remover um item
#ifdef _WIN32
#include <io.h>
#define ftruncate _chsize_s
#else
#include <unistd.h>
#define ftruncate ftruncate
#endif

// Função de registrar um item no cardápio
// Salva um registro do tipo Cardapio ao final do arquivo binário padrão

int adicionar_item(Cardapio item) {

  // Abre o arquivo binário padrão para adicionar ao fim. Se não existe, cria o arquivo "cardapio.bin"
	FILE *fptr = fopen (STD_BIN, "ab");

  // Verifica se o arquivo foi acessado para escrita. Em caso de falha retorna 1
  if (fptr == NULL) {

    printf("Falha ao tentar abrir cardapio para adicionar item.\n");

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
// Retorna 1 se bem sucedido, caso contrário retorna 0

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
// Lê o arquivo binário padrão, remove o item especificado e salva as alterações
// Move os itens subsequentes para preencher o espaço vazio
int remover_item_cardapio(char *filename, int indice) {

  // Abre o arquivo binário para leitura e escrita
  FILE *fptr = fopen(filename, "r+b");

  // Verifica se o arquivo foi aberto corretamente
  if (fptr == NULL) {

    printf("Falha ao tentar abrir cardapio para remocao.\n");
    return 1;

  }

  // Move o ponteiro do arquivo para a posição do item a ser removido
  fseek(fptr, indice * sizeof(Cardapio), SEEK_SET);

  // Lê o item atual para verificar se existe
  Cardapio item_atual;
  if (fread(&item_atual, sizeof(Cardapio), 1, fptr) != 1) {

    printf("Item nao encontrado no cardapio.\n");
    fclose(fptr);
    return 1;

  }

  // Move o ponteiro do arquivo para a posição do próximo item
  fseek(fptr, (indice + 1) * sizeof(Cardapio), SEEK_SET);

  // Lê os itens subsequentes e os move para preencher o espaço vazio
  Cardapio proximo_item;
  while (fread(&proximo_item, sizeof(Cardapio), 1, fptr) == 1) {

    // Move o ponteiro de volta para a posição do item atual
    fseek(fptr, (indice * sizeof(Cardapio)), SEEK_SET);

    // Escreve o próximo item na posição do item atual
    fwrite(&proximo_item, sizeof(Cardapio), 1, fptr);

    // Move o ponteiro para a próxima posição
    indice++;
    fseek(fptr, (indice * sizeof(Cardapio)), SEEK_SET);
    
    // Incrementa o índice para continuar movendo os itens subsequentes
  }

  // Trunca o arquivo para remover os itens restantes após o último item movido
  _chsize_s(fileno(fptr), indice * sizeof(Cardapio));

  // Fecha o arquivo
  fclose(fptr);
  
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
