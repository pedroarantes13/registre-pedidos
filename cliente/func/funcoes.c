#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../restaurante/func/func_restaurante.h"
#include "funcoes.h"

// Imprime uma linha intermediária para separar conteúdos

void mid_line() {
    printf("----------------------------------------------------------\n");
}

// Imprime uma linha superior/inferior de destaque

void top_bottom() {
    printf("==========================================================\n");
}

/* Inicializa um vetor de cupons de desconto com valores fixos.
 Cada cupom possui um código (string) e uma porcentagem de desconto (float).

 Parâmetro:
   cupons → vetor de structs 'cupom_desconto' com espaço para até MAX_CUPONS.

 Essa função deve ser chamada uma única vez no início do programa.*/

void inicializar_cupons(struct cupom_desconto cupons[]) {
    // Define os códigos e porcentagens de desconto diretamente.

    strcpy(cupons[0].codigo, "paulo"); cupons[0].porcentagem = 0.20f;    // 20%
    strcpy(cupons[1].codigo, "daniel"); cupons[1].porcentagem = 0.30f;   // 30%
    strcpy(cupons[2].codigo, "pedro"); cupons[2].porcentagem = 0.40f;    // 40%
    strcpy(cupons[3].codigo, "lizandro"); cupons[3].porcentagem = 0.50f; // 50%
    strcpy(cupons[4].codigo, "gean"); cupons[4].porcentagem = 0.60f;     // 60%
}

/* Verifica se um cupom de desconto informado pelo usuário é válido.
 Se for, define a porcentagem de desconto correspondente.

 Parâmetros:
   codigo → string digitada pelo usuário (código do cupom).
   cupons → vetor de cupons previamente inicializado.
   desconto → ponteiro para float onde será armazenado o valor do desconto.

 Retorno:
   1 se o cupom for válido; 0 caso contrário.*/

int aplicar_cupom(char codigo[], struct cupom_desconto cupons[], float *desconto) {
    for (int i = 0; i < MAX_CUPONS; i++) {
        // Compara o código digitado com o código do cupom atual.
        // strcasecmp ignora diferença entre maiúsculas/minúsculas.

        if (strcasecmp(codigo, cupons[i].codigo) == 0) {
            *desconto = cupons[i].porcentagem; // Define o valor do desconto
            return 1;                          // Cupom válido
        }
    }
    return 0;
}

/* Função que solicita ao usuário um número inteiro dentro de um intervalo válido.
 Garante que a entrada seja numérica e que esteja entre os limites definidos.
 Utiliza fgets e sscanf para evitar problemas com lixo no buffer (como '\n').

 Parâmetros:
   mensagem → texto que será exibido ao usuário para solicitar o valor.
   min → valor mínimo permitido.
   max → valor máximo permitido.

 Retorno:
   Um número inteiro válido, dentro do intervalo [min, max]. */

int ler_inteiro_seguro(const char *mensagem, int min, int max) {
    char entrada[100]; // Buffer para armazenar a linha digitada
    int valor;         // Variável onde será armazenado o número convertido

    while (1) {
        printf("%s ", mensagem);

        // Lê uma linha completa da entrada padrão (stdin), incluindo o '\n'.
        // Isso evita que um '\n' residual atrapalhe a leitura.

        if (!fgets(entrada, sizeof(entrada), stdin)) {
            clearerr(stdin); // Limpa erros no buffer, se houver
            continue;        // Reinicia o loop caso a leitura falhe
        }

        entrada[strcspn(entrada, "\n")] = '\0'; // Substitui '\n' por '\0' na string


        // Usa sscanf para tentar extrair um número inteiro da string.
        // Se falhar (não for número), emite mensagem e repete o laço.

        if (sscanf(entrada, "%d", &valor) != 1) {
            printf("\033[1;31mErro: Digite um número válido!\033[0m\n");
            continue;
        }

        // Verifica se o valor está dentro do intervalo permitido

        if (valor < min || valor > max) {
            printf("\033[1;31mErro: Valor deve estar entre %d e %d!\033[0m\n", min, max);
            continue;
        }

        return valor;
    }
}

/* Lê uma resposta simples do usuário no formato "s" (sim) ou "n" (não).
 A leitura é feita com getchar() e seguida da limpeza do buffer.
 A função é à prova de entradas inválidas e diferencia maiúsculas de minúsculas.

 Parâmetro:
   mensagem → texto que será exibido ao usuário (ex: "Deseja continuar?").

 Retorno:
   1 se a resposta for 's' ou 'S', 0 se for 'n' ou 'N'.*/

int validar_resposta_sn(const char *mensagem) {
    char resposta; // Variável para armazenar a letra digitada
    int c;         // Limpa o restante da linha do buffer

    do {
        printf("%s (s/n): ", mensagem);

        resposta = getchar(); // Lê o primeiro caractere digitado
        while ((c = getchar()) != '\n' && c != EOF);  // Limpa os caracteres restantes no buffer

        resposta = tolower(resposta); // Converte para minúsculo

        // Se for a resposta for inválida, informa ao usuário e repete o laço

        if (resposta != 's' && resposta != 'n') {
            printf("\033[1;31mOpcao invalida! Digite 's' ou 'n'.\033[0m\n");
        }

    } while (resposta != 's' && resposta != 'n');

    return (resposta == 's'); // 1 = 's' e 0 = 'n'
}

/* Verifica se uma string contém apenas letras e espaços.
 Rejeita nomes que tenham números, pontuação ou símbolos.

 Parâmetro:
   str → string a ser validada (ex: nome de um prato).

 Retorno:
   1 se a string for válida (somente letras e espaços), 0 caso contrário.*/

int validar_nome_item(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        // Verifica se o caractere é uma letra ou um espaço

        if (!isalpha(str[i]) && str[i] != ' ') return 0; // Caractere inválido -> Nome inválido
    }
    return 1; // Caracteres válidos -> Nome válido
}

/* Retorna o ponteiro para um item específico do cardápio.
 A posição informada pelo usuário é 1-based, então é ajustada para 0-based.

 Parâmetros:
   posicao → número do item no cardápio (1 a N).
   cardapio → vetor de itens previamente carregado.
   total_itens → tamanho total do vetor.

 Retorno:
   Ponteiro para o item desejado se a posição for válida.
   NULL se a posição estiver fora dos limites. */

Cardapio* buscar_item_cardapio(int posicao, Cardapio *cardapio, int total_itens) {
    // Verifica se a posição está dentro do intervalo válido do vetor.

    if (posicao < 1 || posicao > total_itens) {
        printf("\033[1;31mErro: Posicao %d invalida no cardapio!\033[0m\n", posicao);
        return NULL;
    }

    return &cardapio[posicao - 1]; // Ajusta para índice base 0 e retorna o ponteiro para o item.
}

/* Registra um novo pedido no vetor e também salva no arquivo binário.

 Função crítica do sistema: garante que os dados do pedido sejam armazenados
 corretamente em memória e também persistam no arquivo.

 Parâmetros:
   vetor → ponteiro duplo para o vetor dinâmico de pedidos.
   total_pedidos → ponteiro para o total atual de pedidos cadastrados.
   capacidade → ponteiro para a capacidade máxima alocada no vetor.
   mesa → número da mesa associada ao pedido.
   pessoas → número de pessoas na mesa (para divisão).
   posicao_item → índice escolhido do item no cardápio (1-based).
   cardapio → vetor de itens do cardápio previamente carregado.
   total_itens_cardapio → tamanho do vetor do cardápio.
   quantidade → quantidade de itens pedidos.
   cupom → código de desconto aplicado (ou string vazia se não houver).
   desconto → valor do desconto aplicado (entre 0 e 1).

 Retorno:
   Nenhum (void). Em caso de falha, imprime mensagens de erro.*/

void registrar_e_salvar(
    struct dados_pedido **vetor,       // ponteiro duplo
    int *total_pedidos,
    int *capacidade,
    int mesa,
    int pessoas,
    int posicao_item,
    Cardapio *cardapio,
    int total_itens_cardapio,
    int quantidade,
    const char *cupom,
    float desconto) {
    
    // Valida se o cardápio existe e se a posição do item é válida.
    if (!cardapio || posicao_item < 1 || posicao_item > total_itens_cardapio) {
        printf("\033[1;31mErro: Item invalido ou cardapio nao carregado!\033[0m\n");
        return;
    }

    // Verifica se o vetor de pedidos precisa ser realocado.
    if (*total_pedidos >= *capacidade) {
        *capacidade = (*capacidade == 0) ? 10 : (*capacidade * 2); // Dobra a capacidade ou inicia com 10 se estiver vazia.

        // Tenta realocar o vetor para comportar mais pedidos.
        struct dados_pedido *temp = realloc(*vetor, (*capacidade) * sizeof(struct dados_pedido));

        if (!temp) {
            printf("\033[1;31mErro ao realocar memoria para pedidos!\033[0m\n");
            return;
        }
        *vetor = temp; // Atualiza o ponteiro externo com o novo bloco realocado.
    }

    Cardapio *item = &cardapio[posicao_item - 1]; // Obtém o ponteiro para o item do cardápio, ajustando para índice 0.

    // Preenche a estrutura do pedido com os dados fornecidos.
    struct dados_pedido pedido = {
        .mesa = mesa,
        .pessoas = pessoas,
        .tipo = item->tipo,
        .quantidade = quantidade,
        .subtotal = quantidade * item->valor,
        .valor_individual = (quantidade * item->valor) / (pessoas > 0 ? pessoas : 1),
        .desconto = desconto
    };

    // Copia o nome do item e o cupom para os campos da struct.
    strncpy(pedido.item, item->item, sizeof(pedido.item) - 1);
    strncpy(pedido.cupom, cupom, sizeof(pedido.cupom) - 1);

    // Adiciona o novo pedido no vetor de pedidos em memória.
    (*vetor)[*total_pedidos] = pedido;
    (*total_pedidos)++;

    // Abre o arquivo binário de pedidos no modo append ('ab').
    FILE *arquivo = fopen(ARQUIVO_BINARIO, "ab");
    if (arquivo) {
        // Grava o pedido no final do arquivo.
        fwrite(&pedido, sizeof(struct dados_pedido), 1, arquivo);
        fclose(arquivo);
    } else {
        printf("\033[1;31mErro ao salvar pedido no arquivo!\033[0m\n");
    }
}

/* Carrega os pedidos previamente salvos no arquivo binário para um vetor dinâmico.

 Essa função é chamada ao iniciar o programa, para recuperar os dados do dia atual.
 Utiliza realloc para aumentar o vetor dinamicamente conforme necessário.

 Parâmetros:
   vetor → ponteiro duplo que armazenará o vetor dinâmico de pedidos.
   total_pedidos → ponteiro para contador de pedidos já carregados.
   capacidade → ponteiro para o tamanho atual do vetor alocado.

 Retorno:
   1 se a leitura foi bem-sucedida; 0 se houve erro (como falha de alocação). */

int carregar_pedidos(struct dados_pedido **vetor, int *total_pedidos, int *capacidade) {
    // Abre o arquivo de pedidos no modo leitura binária.
    FILE *arquivo = fopen(ARQUIVO_BINARIO, "rb");

    if (arquivo == NULL) {
        // Se o arquivo não existe ou está vazio, retorna 0 silenciosamente.
        return 0;
    }

    struct dados_pedido temp; // Struct temporária usada para leitura de cada pedido.

    // Lê o arquivo pedido por pedido até o final.
    while (fread(&temp, sizeof(struct dados_pedido), 1, arquivo) == 1) {
        // Se o vetor estiver cheio, precisamos realocar mais espaço.
        if (*total_pedidos >= *capacidade) {
            // Dobra a capacidade ou começa com 10 se for a primeira alocação
            *capacidade = (*capacidade == 0) ? 10 : (*capacidade * 2);
            // Tenta realocar o vetor com o novo tamanho.
            struct dados_pedido *temp_ptr = realloc(*vetor, (*capacidade) * sizeof(struct dados_pedido));

            if (temp_ptr == NULL) {
                printf("Erro ao alocar memoria para carregar pedidos.\n");
                fclose(arquivo);
                return 0; // Falha na realocação → aborta o carregamento.
            }
            *vetor = temp_ptr; // Atualiza o ponteiro externo com o novo bloco realocado.
        }
        (*vetor)[(*total_pedidos)++] = temp; // Copia o pedido lido para a posição atual do vetor.
    }

    fclose(arquivo);
    return 1; // Carregamento bem-sucedido
}

/* Exibe as informações de um pedido formatadas no terminal.
 A exibição muda levemente conforme o contexto (visualização comum ou relatório).

 Parâmetros:
   p → struct 'dados_pedido' contendo os dados a serem exibidos.
   eh_relatorio → se for 1, oculta informações específicas como cupom e valor com desconto.
                  se for 0, exibe o cupom e valor final após desconto.*/

void exibir_pedido(struct dados_pedido p, int eh_relatorio) {
    // Exibe o número da mesa e a quantidade de pessoas nela.
    printf("Mesa %d | Pessoas: %d\n", p.mesa, p.pessoas);

    // Exibe o nome do item, a quantidade pedida e o tipo do item formatado como texto.
    // A função tipo_str (provavelmente definida pelo colega) converte o número para string.
    printf("Item: %s (%dx) [%s]\n", p.item, p.quantidade, tipo_str(p.tipo));

    // Exibe o subtotal bruto (antes de desconto).
    printf("Subtotal: R$%.2f\n", p.subtotal);

    // Se houver cupom e não estivermos em modo relatório, exibe desconto e valor com desconto.
    if (strlen(p.cupom) > 0 && !eh_relatorio) {
        // Mostra o código do cupom e o percentual de desconto aplicado.
        printf("CUPOM %s APLICADO (%.0f%% OFF)\n", p.cupom, p.desconto * 100);
        // Mostra o valor final com desconto aplicado.
        printf("VALOR COM DESCONTO: R$%.2f\n", p.subtotal * (1 - p.desconto));
    }
    mid_line();
}

/*
  Gera um relatório completo dos pedidos do dia, agrupando por mesa e exibindo:
  - Lista de pedidos por mesa, com subtotais.
  - Aplicação de cupons de desconto (se houver).
  - Divisão de valores por pessoa.
  - Métricas gerais (arrecadação total, itens vendidos, etc.).
  - Ranking dos itens mais vendidos.
  - Subtotais por categoria (pratos, bebidas, sobremesas).
  
  Esta função é o ponto central de consolidação dos dados, sendo chamada ao encerrar o programa.
  Ela carrega os pedidos do arquivo binário, processa os dados e exibe as informações formatadas.
  
  Fluxo:
    1. Carrega pedidos do arquivo binário para memória.
    2. Calcula métricas gerais (arrecadação, média por mesa, etc.).
    3. Agrupa pedidos por mesa, exibindo detalhes e totais por mesa.
    4. Gera o ranking de itens mais vendidos.
    5. Exibe subtotais por categoria de item.
  
  Observações:
    - Se não houver pedidos, exibe mensagem informativa.
    - Libera a memória alocada para o vetor de pedidos ao final.
 */

void gerar_relatorio_final() {
    // Inicializa variáveis para armazenar pedidos carregados do arquivo.
    struct dados_pedido *pedidos = NULL;
    int total_pedidos = 0;
    int capacidade = 0;

    // Tenta carregar pedidos do arquivo binário. Se falhar, exibe mensagem e retorna.
    if (!carregar_pedidos(&pedidos, &total_pedidos, &capacidade)) {
        printf("Nenhum pedido registrado ainda.\n");
        return;
    }

    // Exibe métricas gerais (arrecadação total, média por mesa, etc.).
    calcular_metricas_gerais(pedidos, total_pedidos);

    // Identifica todas as mesas únicas com pedidos registrados.
    int mesas[100] = {0}, total_mesas = 0;
    for (int i = 0; i < total_pedidos; i++) {
        int existe = 0;
        for (int j = 0; j < total_mesas; j++) {
            if (mesas[j] == pedidos[i].mesa) {
                existe = 1;
                break;
            }
        }
        if (!existe) mesas[total_mesas++] = pedidos[i].mesa;
    }

    // Processa cada mesa individualmente: exibe pedidos e calcula totais.
    for (int i = 0; i < total_mesas; i++) {
        int mesa = mesas[i];
        float total_original = 0, total_final = 0;
        char cupom[20] = "";
        float desconto = 0;
        int pessoas = 0;

        printf("\nMESA %d\n", mesa);
        mid_line();

        // Itera sobre todos os pedidos para encontrar os da mesa atual.
        for (int j = 0; j < total_pedidos; j++) {
            if (pedidos[j].mesa == mesa) {
                exibir_pedido(pedidos[j], 1); // Exibe detalhes do pedido (modo relatório).
                total_original += pedidos[j].subtotal;

                // Captura cupom de desconto (se aplicado a qualquer pedido da mesa).
                if (strlen(pedidos[j].cupom) > 0) {
                    strcpy(cupom, pedidos[j].cupom);
                    desconto = pedidos[j].desconto;
                }
                pessoas = pedidos[j].pessoas; // Assume que todas as pessoas da mesa são as mesmas
            }
        }

        // Calcula totais finais com desconto (se houver cupom).
        total_final = total_original * (1 - desconto);

        // Exibe resumo financeiro da mesa.
        printf("\nRESUMO FINANCEIRO:\n");
        printf("VALOR TOTAL:    R$%.2f\n", total_original);
        if (strlen(cupom) > 0) {
            printf("CUPOM %-8s   -%.0f%%\n", cupom, desconto * 100);
            printf("VALOR FINAL:    R$%.2f\n", total_final);
        }
        printf("POR PESSOA:     R$%.2f\n", total_final / pessoas);
        top_bottom();
    }

    // Gera ranking de itens mais vendidos e exibe subtotais por categoria.
    gerar_ranking(pedidos, total_pedidos);
    calcular_subtotal_por_tipo(pedidos, total_pedidos);

    free(pedidos);
}

/*
 Calcula e exibe métricas agregadas sobre os pedidos do dia, incluindo:
 - Total arrecadado (soma de todos os subtotais dos pedidos).
 - Média de gasto por mesa.
 - Total de itens vendidos (soma de todas as quantidades).
 
 Parâmetros:
   pedidos → Vetor de structs 'dados_pedido' contendo todos os pedidos registrados.
   total_pedidos → Número total de pedidos no vetor.
 
 Observações:
   - Ignora descontos aplicados (trabalha com subtotais brutos).
   - Identifica mesas únicas para calcular a média corretamente.
   - Exibe os resultados formatados com separadores visuais.
 */

void calcular_metricas_gerais(struct dados_pedido pedidos[], int total_pedidos) {
    float total_arrecadado = 0; // Acumula o valor bruto de todos os pedidos
    int total_itens = 0;        // Contador de itens vendidos
    int mesas[100] = {0}, total_mesas = 0; // Armazena o número de mesas únicas; Contador de mesas distintas

    // Itera sobre todos os pedidos para calcular totais e identificar mesas.
    for (int i = 0; i < total_pedidos; i++) {
        total_arrecadado += pedidos[i].subtotal; // Soma subtotais
        total_itens += pedidos[i].quantidade;    // Soma quantidades

        // Verifica se a mesa já foi registrada no vetor 'mesas'
        int existe = 0;
        for (int j = 0; j < total_mesas; j++) {
            if (mesas[j] == pedidos[i].mesa) {
                existe = 1;
                break;
            }
        }
        // Se a mesa for nova, adiciona ao vetor.
        if (!existe) mesas[total_mesas++] = pedidos[i].mesa;
    }

    // Exibe as métricas formatadas
    printf("\n=== RESUMO GERAL ===\n");
    top_bottom();
    printf("TOTAL ARRECADADO: R$ %10.2f\n", total_arrecadado);
    printf("MEDIA POR MESA:  R$ %10.2f\n", total_mesas > 0 ? total_arrecadado / total_mesas : 0);
    printf("ITENS VENDIDOS:  %10d unidades\n", total_itens);
    top_bottom();
}

/*
 Calcula e exibe o subtotal de vendas agrupado por categoria de itens:
 - Pratos (tipo 0), Bebidas (tipo 1), Sobremesas (tipo 2).
 
 Parâmetros:
   pedidos → Vetor de structs 'dados_pedido' com todos os pedidos registrados.
   total_pedidos → Número total de pedidos no vetor.
 
 Fluxo:
   1. Percorre todos os pedidos, acumulando os subtotais por categoria.
   2. Exibe os valores formatados, com destaque para o total geral.
 
 Observações:
   - Assume que os tipos são definidos como:
     0: Pratos, 1: Bebidas, 2: Sobremesas.
   - Ignora descontos (trabalha com subtotais brutos).
   - Exibe uma tabela formatada com linhas de separação.
 */

void calcular_subtotal_por_tipo(struct dados_pedido pedidos[], int total_pedidos) {
    float total_pratos = 0, total_bebidas = 0, total_sobremesas = 0; // Acumulam itens separados por tipo

    // Classifica cada pedido por tipo e soma ao respectivo subtotal.
    for (int i = 0; i < total_pedidos; i++) {
        switch(pedidos[i].tipo) {
            case 0: total_pratos += pedidos[i].subtotal; break;
            case 1: total_bebidas += pedidos[i].subtotal; break;
            case 2: total_sobremesas += pedidos[i].subtotal; break;
            // Tipos inválidos são ignorados silenciosamente.
        }
    }

    // Exibe os resultados formatados.
    printf("\n=== SUBTOTAL POR CATEGORIA ===\n");
    top_bottom();
    printf("PRATOS:     R$ %8.2f\n", total_pratos);
    printf("BEBIDAS:    R$ %8.2f\n", total_bebidas);
    printf("SOBREMESAS: R$ %8.2f\n", total_sobremesas);
    printf("TOTAL:      R$ %8.2f\n", total_pratos + total_bebidas + total_sobremesas);
    top_bottom();
}

/*
 Gera um ranking dos itens mais vendidos, ordenados por quantidade total.
 - Agrupa pedidos repetidos pelo nome do item.
 - Calcula a quantidade total vendida e o subtotal acumulado por item.
 - Ordena os itens em ordem decrescente de quantidade.
 - Exibe o Top 5 (ou menos, se houver menos itens).
 
 Parâmetros:
   pedidos → Vetor de structs 'dados_pedido' com todos os pedidos registrados.
   total_pedidos → Número total de pedidos no vetor.
 
 Estruturas internas:
   - Usa um vetor auxiliar 'ranking' do tipo 'item_ranking' para armazenar:
       nome: Nome do item (copiado de 'pedidos[i].item').
       quantidade: Soma das quantidades vendidas.
       subtotal: Soma dos subtotais (preço × quantidade).
 
 Observações:
   - Limita o ranking a 50 itens distintos (tamanho do vetor 'ranking').
   - Itens com nomes idênticos são agrupados (case-sensitive).
   - Se houver empate em quantidade, a ordem de exibição é indefinida.
 */

void gerar_ranking(struct dados_pedido pedidos[], int total_pedidos) {
    struct item_ranking {
        char nome[50];   // Nome do item (copiado do pedido)
        int quantidade;  // Quantidade total vendida
        float subtotal;  // Soma dos subtotais
    } ranking[50];       // Vetor auxiliar com capacidade para 50 itens distintos

    int n_itens = 0; // Contador de itens únicos já registrados no ranking.

    // Passo 1: Consolidar itens repetidos (agrupar por nome).
    for (int i = 0; i < total_pedidos; i++) {
        int encontrado = 0;

        // Verifica se o item já foi registrado no vetor 'ranking'.
        for (int j = 0; j < n_itens; j++) {
            if (strcmp(pedidos[i].item, ranking[j].nome) == 0) {

                // Item encontrado: acumula quantidade e subtotal.
                ranking[j].quantidade += pedidos[i].quantidade;
                ranking[j].subtotal += pedidos[i].subtotal;
                encontrado = 1;
                break;
            }
        }

        // Se o item é novo e há espaço no vetor, adiciona ao ranking.
        if (!encontrado && n_itens < 50) {
            strcpy(ranking[n_itens].nome, pedidos[i].item);
            ranking[n_itens].quantidade = pedidos[i].quantidade;
            ranking[n_itens].subtotal = pedidos[i].subtotal;
            n_itens++;
        }
    }

    // Passo 2: Ordenar itens por quantidade (decrescente) - algoritmo Bubble Sort simplificado.
    for (int i = 0; i < n_itens - 1; i++) {
        for (int j = i + 1; j < n_itens; j++) {
            if (ranking[j].quantidade > ranking[i].quantidade) {
                struct item_ranking temp = ranking[i];
                ranking[i] = ranking[j];
                ranking[j] = temp;
            }
        }
    }

    // Passo 3: Exibir o Top 5 itens (ou menos, se não houver 5 itens distintos).
    printf("\n=== TOP 5 ITENS MAIS VENDIDOS ===\n");
    top_bottom();
    for (int i = 0; i < (n_itens < 5 ? n_itens : 5); i++) {
        printf("%do: %-20s | %3dx | R$ %7.2f\n", i + 1, ranking[i].nome,
               ranking[i].quantidade, ranking[i].subtotal);
    }
    top_bottom();
}