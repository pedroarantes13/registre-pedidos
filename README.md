# Sistema de Gestão de Restaurante: `registre-pedidos`

## Visão Geral do Projeto

O `registre-pedidos` é um sistema de console desenvolvido em linguagem C, projetado para gerenciar os pedidos de um restaurante. O projeto demonstra conceitos de manipulação de arquivos binários, alocação dinâmica de memória, modularização de código e estruturação de dados.

O sistema é dividido em duas áreas principais:

* **Menu do Cliente:** Permite visualizar o cardápio e registrar novos pedidos para uma mesa, incluindo a aplicação de cupons de desconto.
* **Menu do Proprietário:** Oferece funcionalidades para gerenciar o cardápio (adicionar, editar, remover itens) e gerar relatórios de vendas detalhados.

Os dados são persistidos em dois arquivos binários:
* `cardapio.bin`: Armazena os itens do cardápio.
* `pedidos.bin`: Armazena todos os pedidos realizados.

## Estrutura dos Arquivos

O código é organizado nos seguintes diretórios e arquivos:

- **`main.c`**: Ponto de entrada do programa. Apresenta o menu inicial para selecionar o modo de operação (Cliente ou Proprietário).
- **`build.sh`**: Script de compilação que une todos os módulos para gerar o executável `registre-pedidos.exe`.
- **`restaurante/`**: Módulo com as funcionalidades do proprietário.
    - `func/func_restaurante.c` e `.h`: Funções para manipulação de dados do cardápio (CRUD).
    - `menu/menu_restaurante.c`: Funções que constroem a interface de menu para o proprietário.
- **`cliente/`**: Módulo com as funcionalidades do cliente.
    - `func/funcoes.c` e `.h`: Funções para manipulação dos dados de pedidos, cupons, validações e geração de relatórios.
    - `menu/menu_cliente.c`: Funções que constroem a interface de menu para o cliente.

## Instruções de Compilação

Para compilar o projeto, utilize o script `build.sh` em um ambiente com o compilador GCC. O script compila todos os arquivos `.c` e os vincula em um único executável.

```bash
# Conceda permissão de execução ao script
chmod +x build.sh

# Execute o script para compilar
./build.sh
```

Isso irá gerar o executável `registre-pedidos.exe`.

---

## Documentação Detalhada das Funções

### Módulo Principal (`main.c`)

#### `int main()`
- **Descrição:** Ponto de entrada do programa. Exibe um menu principal que permite ao usuário escolher entre o menu do cliente, o menu do proprietário ou finalizar a aplicação.
- **Parâmetros:** Nenhum.
- **Retorno:** `0` em caso de finalização bem-sucedida.
- **Arquivo de Origem:** `main.c`

---

### Módulo Restaurante - Funções de Dados (`restaurante/func/`)

#### `int adicionar_item(Cardapio item)`
- **Descrição:** Adiciona um novo item ao final do arquivo binário `cardapio.bin`.
- **Parâmetros:**
    - `Cardapio item`: Struct contendo os dados do item a ser adicionado (nome, tipo, valor).
- **Retorno:** `0` se o item foi adicionado com sucesso; `1` se ocorreu um erro.
- **Arquivo de Origem:** `func_restaurante.c`

#### `int carregar_cardapio(char *filename, Cardapio **cardapio)`
- **Descrição:** Carrega todos os itens do arquivo de cardápio para um vetor alocado dinamicamente na memória.
- **Parâmetros:**
    - `char *filename`: Nome do arquivo binário do cardápio.
    - `Cardapio **cardapio`: Ponteiro duplo para o vetor de `Cardapio` que será alocado e preenchido.
- **Retorno:** `0` se o cardápio foi carregado com sucesso; `1` se ocorreu um erro.
- **Arquivo de Origem:** `func_restaurante.c`

#### `int editar_item_cardapio(char *filename, int indice, Cardapio *novo_item)`
- **Descrição:** Sobrescreve um item existente no cardápio em uma posição específica.
- **Parâmetros:**
    - `char *filename`: Nome do arquivo do cardápio.
    - `int indice`: Posição (base 0) do item a ser editado.
    - `Cardapio *novo_item`: Ponteiro para a struct com os novos dados do item.
- **Retorno:** `0` em caso de sucesso; `1` em caso de falha.
- **Arquivo de Origem:** `func_restaurante.c`

#### `int remover_item_cardapio(char *filename, int indice)`
- **Descrição:** Remove um item do cardápio. A função carrega todos os itens para a memória, apaga o arquivo original e o reescreve com todos os itens, exceto o do índice especificado.
- **Parâmetros:**
    - `char *filename`: Nome do arquivo do cardápio.
    - `int indice`: Posição (base 0) do item a ser removido.
- **Retorno:** `0` em caso de sucesso; `1` em caso de falha.
- **Arquivo de Origem:** `func_restaurante.c`

#### `int imprimir_cardapio(char *filename)`
- **Descrição:** Lê o arquivo do cardápio e exibe todos os itens de forma formatada no console.
- **Parâmetros:** `char *filename`: Nome do arquivo do cardápio.
- **Retorno:** `0` em caso de sucesso; `1` se o arquivo não puder ser aberto.
- **Arquivo de Origem:** `func_restaurante.c`

#### `int total_itens_cardapio(char *filename)`
- **Descrição:** Calcula a quantidade total de itens registrados no cardápio medindo o tamanho do arquivo.
- **Parâmetros:** `char *filename`: Nome do arquivo do cardápio.
- **Retorno:** O número total de itens no cardápio.
- **Arquivo de Origem:** `func_restaurante.c`

#### `char* tipo_str(int tipo)`
- **Descrição:** Converte o código numérico do tipo de item em uma string descritiva.
- **Parâmetros:** `int tipo`: O código do tipo (0: Prato, 1: Bebida, 2: Sobremesa).
- **Retorno:** Uma string contendo "Prato", "Bebida", "Sobremesa" ou `NULL`.
- **Arquivo de Origem:** `func_restaurante.c`

#### `int verificar_indice_cardapio(char *filename, int indice)`
- **Descrição:** Valida se um índice fornecido está dentro do intervalo de itens existentes no cardápio.
- **Parâmetros:**
    - `char *filename`: Nome do arquivo do cardápio.
    - `int indice`: Índice (base 0) a ser verificado.
- **Retorno:** `0` se válido; `1` se inválido.
- **Arquivo de Origem:** `func_restaurante.c`

#### `int validar_valor(float valor)`
- **Descrição:** Valida se um valor monetário é positivo.
- **Parâmetros:** `float valor`: O valor a ser verificado.
- **Retorno:** `0` se o valor for válido (>= 0); `1` se for inválido (< 0).
- **Arquivo de Origem:** `func_restaurante.c`

---

### Módulo Restaurante - Funções de Menu (`restaurante/menu/`)

#### `int menu_restaurante()`
- **Descrição:** Exibe o menu principal do proprietário e gerencia a navegação entre as opções: visualizar cardápio, adicionar, editar, excluir item, gerar relatório ou sair.
- **Parâmetros:** Nenhum.
- **Retorno:** `1` quando o usuário escolhe finalizar a seção.
- **Arquivo de Origem:** `menu_restaurante.c`

#### `void adicionarItem(Cardapio *item)`
- **Descrição:** Conduz o usuário através do processo de adicionar um novo item, solicitando nome, tipo e valor, validando as entradas e chamando `adicionar_item` para salvar.
- **Parâmetros:** `Cardapio *item`: Ponteiro para uma struct que será preenchida.
- **Retorno:** Nenhum.
- **Arquivo de Origem:** `menu_restaurante.c`

#### `void menu_editar_item(Cardapio *novo_item)`
- **Descrição:** Solicita ao usuário o índice do item a ser editado e os novos dados, chamando `editar_item_cardapio` para efetuar a alteração.
- **Parâmetros:** `Cardapio *novo_item`: Ponteiro para uma struct que será preenchida com os dados atualizados.
- **Retorno:** Nenhum.
- **Arquivo de Origem:** `menu_restaurante.c`

#### `void menu_excluir_item()`
- **Descrição:** Solicita ao usuário o índice do item a ser removido e chama `remover_item_cardapio`.
- **Parâmetros:** Nenhum.
- **Retorno:** Nenhum.
- **Arquivo de Origem:** `menu_restaurante.c`

---

### Módulo Cliente - Funções de Dados (`cliente/func/`)

#### `void registrar_e_salvar(...)`
- **Descrição:** Função central para registrar um pedido. Ela adiciona o pedido a um vetor dinâmico na memória (realocando se necessário) e também o salva no arquivo `pedidos.bin`.
- **Parâmetros:**
    - `struct dados_pedido **vetor`: Ponteiro duplo para o vetor de pedidos.
    - `int *total_pedidos`: Ponteiro para o contador de pedidos.
    - `int *capacidade`: Ponteiro para a capacidade atual do vetor.
    - `int mesa`, `int pessoas`, `int posicao_item`, `int quantidade`: Dados do pedido.
    - `Cardapio *cardapio`: Ponteiro para o cardápio carregado.
    - `const char *cupom`: String com o código do cupom.
    - `float desconto`: Valor percentual do desconto (0.0 a 1.0).
- **Retorno:** Nenhum.
- **Arquivo de Origem:** `funcoes.c`

#### `int carregar_pedidos(...)`
- **Descrição:** Lê todos os registros de pedidos do arquivo `pedidos.bin` e os carrega em um vetor alocado dinamicamente.
- **Parâmetros:**
    - `struct dados_pedido **vetor`: Ponteiro duplo que armazenará o vetor de pedidos.
    - `int *total_pedidos`: Ponteiro para o contador de pedidos carregados.
    - `int *capacidade`: Ponteiro para a capacidade do vetor alocado.
- **Retorno:** `1` se o carregamento foi bem-sucedido; `0` caso contrário.
- **Arquivo de Origem:** `funcoes.c`

#### `void gerar_relatorio_final()`
- **Descrição:** Orquestra a geração do relatório completo de vendas. Carrega todos os pedidos, exibe métricas gerais, agrupa e detalha os pedidos por mesa, e exibe rankings de itens e subtotais por categoria.
- **Parâmetros:** Nenhum.
- **Retorno:** Nenhum.
- **Arquivo de Origem:** `funcoes.c`

#### `void calcular_metricas_gerais(...)`
- **Descrição:** Calcula e exibe estatísticas globais como total arrecadado, média por mesa e total de itens vendidos.
- **Parâmetros:**
    - `struct dados_pedido pedidos[]`: Vetor com todos os pedidos.
    - `int total_pedidos`: Tamanho do vetor.
- **Retorno:** Nenhum.
- **Arquivo de Origem:** `funcoes.c`

#### `void gerar_ranking(...)`
- **Descrição:** Consolida os dados de todos os pedidos para criar um ranking dos 5 itens mais vendidos, ordenados por quantidade.
- **Parâmetros:**
    - `struct dados_pedido pedidos[]`: Vetor com todos os pedidos.
    - `int total_pedidos`: Tamanho do vetor.
- **Retorno:** Nenhum.
- **Arquivo de Origem:** `funcoes.c`

#### `void calcular_subtotal_por_tipo(...)`
- **Descrição:** Calcula e exibe o faturamento total para cada categoria de item (Pratos, Bebidas, Sobremesas).
- **Parâmetros:**
    - `struct dados_pedido pedidos[]`: Vetor com todos os pedidos.
    - `int total_pedidos`: Tamanho do vetor.
- **Retorno:** Nenhum.
- **Arquivo de Origem:** `funcoes.c`

#### `void inicializar_cupons(struct cupom_desconto cupons[])`
- **Descrição:** Preenche um vetor de `cupom_desconto` com códigos e valores de desconto pré-definidos.
- **Parâmetros:** `struct cupom_desconto cupons[]`: Vetor a ser inicializado.
- **Retorno:** Nenhum.
- **Arquivo de Origem:** `funcoes.c`

#### `int ler_inteiro_seguro(const char *mensagem, int min, int max)`
- **Descrição:** Lê um número inteiro da entrada padrão de forma segura, garantindo que seja um valor numérico e que esteja dentro de um intervalo `[min, max]`.
- **Parâmetros:**
    - `const char *mensagem`: Mensagem a ser exibida para o usuário.
    - `int min`: Valor mínimo permitido.
    - `int max`: Valor máximo permitido.
- **Retorno:** O número inteiro validado.
- **Arquivo de Origem:** `funcoes.c`

#### `int validar_nome_item(const char *str)`
- **Descrição:** Verifica se uma string contém apenas caracteres alfabéticos e espaços.
- **Parâmetros:** `const char *str`: A string a ser validada.
- **Retorno:** `1` se a string for válida; `0` caso contrário.
- **Arquivo de Origem:** `funcoes.c`

---

### Módulo Cliente - Funções de Menu (`cliente/menu/`)

#### `int menu_cliente()`
- **Descrição:** Função principal da interface do cliente. Carrega o cardápio e os pedidos existentes, inicializa os cupons e entra em um loop que permite ao cliente visualizar o cardápio, fazer um pedido ou voltar ao menu inicial.
- **Parâmetros:** Nenhum.
- **Retorno:** `0` ao sair com sucesso; `1` se houver erro ao carregar o cardápio.
- **Arquivo de Origem:** `menu_cliente.c`

#### `void fazerPedido(...)`
- **Descrição:** Guia o cliente no processo de criação de um pedido. Solicita número da mesa, de pessoas e um cupom. Em seguida, permite adicionar múltiplos itens ao mesmo pedido, chamando `registrar_e_salvar` para cada um.
- **Parâmetros:**
    - `struct dados_pedido **pedidos_ptr`: Ponteiro duplo para o vetor de pedidos.
    - `int *total_pedidos_ptr`: Ponteiro para o contador de pedidos.
    - `int *capacidade_ptr`: Ponteiro para a capacidade do vetor.
    - `Cardapio *cardapio_menu`: O cardápio carregado.
    - `const struct cupom_desconto cupons_disponiveis[]`: Vetor de cupons.
- **Retorno:** Nenhum.
- **Arquivo de Origem:** `menu_cliente.c`

#### `void mostrarPratosPrincipais(...)`, `void mostrarBebidas(...)`, `void mostrarSobremesas(...)`
- **Descrição:** Estas três funções filtram e exibem os itens do cardápio que pertencem a uma categoria específica (Pratos, Bebidas ou Sobremesas).
- **Parâmetros:**
    - `Cardapio *cardapio_ptr`: Ponteiro para o vetor do cardápio.
    - `int total_itens`: Número total de itens no cardápio.
- **Retorno:** Nenhum.
- **Arquivo de Origem:** `menu_cliente.c`

#### `float obter_desconto_cupom(...)`
- **Descrição:** Verifica se um código de cupom fornecido é válido, comparando-o com a lista de cupons disponíveis.
- **Parâmetros:**
    - `const char *cupom_digitado`: O código do cupom inserido pelo usuário.
    - `const struct cupom_desconto cupons[]`: O vetor de cupons disponíveis.
    - `int num_cupons`: O tamanho do vetor de cupons.
- **Retorno:** A porcentagem de desconto (e.g., `0.20` para 20%) se o cupom for válido, ou `0.0` caso contrário.
- **Arquivo de Origem:** `menu_cliente.c`