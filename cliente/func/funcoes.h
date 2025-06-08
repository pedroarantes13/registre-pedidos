#pragma once

#define ARQUIVO_BINARIO "pedidos.bin"
#define MAX_CUPONS 5

// ---------- ESTRUTURAS ----------

// Representa um cupom de desconto com código e porcentagem
struct cupom_desconto {
    char codigo[20];
    float porcentagem;
};

// Representa um pedido feito por uma mesa
struct dados_pedido {
    int mesa;
    int pessoas;
    char item[50];
    int tipo; // 1 = comida, 2 = bebida
    int quantidade;
    float subtotal;
    float valor_individual;
    char cupom[20];
    float desconto; // valor de 0.0 a 1.0 representando a porcentagem
};

// ---------- FUNÇÕES PRINCIPAIS DO SISTEMA ----------

// Registra um pedido no vetor e salva no arquivo binário
void registrar_e_salvar(struct dados_pedido*, int*, int, int, char[], int, int, const char*, float);

// Carrega pedidos do arquivo binário para vetor alocado dinamicamente
int carregar_pedidos(struct dados_pedido **vetor, int *total_pedidos, int *capacidade);

// Exibe visualmente um pedido formatado
void exibir_pedido(struct dados_pedido p, int eh_relatorio);

// Mostra resumo de todos os pedidos realizados
void exibir_resumo(struct dados_pedido pedidos[], int num_pedidos);

// Gera o relatório final com totais e ranking de vendas
void gerar_relatorio_final();

// Calcula dados estatísticos gerais do sistema
void calcular_metricas_gerais(struct dados_pedido pedidos[], int total_pedidos);

// Separa e exibe subtotal por tipo de item (comida/bebida)
void calcular_subtotal_por_tipo(struct dados_pedido pedidos[], int total_pedidos);

// Cria ranking dos itens mais vendidos
void gerar_ranking(struct dados_pedido pedidos[], int total_pedidos);

// ---------- CUPONS DE DESCONTO ----------

// Inicializa os cupons disponíveis
void inicializar_cupons(struct cupom_desconto cupons[]);

// Verifica validade de um cupom e retorna o desconto
int aplicar_cupom(char codigo[], struct cupom_desconto cupons[], float *desconto);

// ---------- ESTÉTICA (SAÍDA FORMATADA) ----------

// Imprime linha intermediária visual
void mid_line();

// Imprime linha superior/inferior visual
void top_bottom();

// ---------- VALIDAÇÃO DE ENTRADAS ----------

// Valida resposta do tipo 's' ou 'n'
int validar_resposta_sn(const char *mensagem);

// Lê um número inteiro validado dentro de um intervalo
int ler_inteiro_seguro(const char *mensagem, int min, int max);

// Verifica se string contém apenas letras e espaços (para nomes de itens)
int validar_nome_item(const char *str);