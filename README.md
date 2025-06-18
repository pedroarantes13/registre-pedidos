# Sistema de Gestão de Restaurante: `registre-pedidos`

## Visão Geral do Projeto

O `registre-pedidos` é um sistema de console desenvolvido em linguagem C, projetado para gerenciar os pedidos e o cardápio de um restaurante. O projeto demonstra conceitos de manipulação de arquivos binários, alocação dinâmica de memória, modularização de código e estruturação de dados para criar uma aplicação robusta e funcional.

O sistema é dividido em duas áreas principais:

* **Menu do Cliente:** Permite visualizar o cardápio por categorias, registrar novos pedidos para uma mesa, adicionar múltiplos itens a um mesmo pedido e aplicar cupons de desconto.
* **Menu do Proprietário:** Oferece funcionalidades de CRUD (Criar, Ler, Atualizar, Deletar) para gerenciar os itens do cardápio e uma função para gerar um relatório de vendas detalhado, com métricas gerais, totais por mesa, subtotais por categoria e um ranking dos itens mais vendidos.

Os dados são persistidos em dois arquivos binários:
* `cardapio.bin`: Armazena os itens do cardápio.
* `pedidos.bin`: Armazena todos os pedidos realizados.

## Estrutura dos Arquivos

O código é organizado nos seguintes diretórios e arquivos:

* **`main.c`**: Ponto de entrada do programa. Apresenta o menu inicial para selecionar o modo de operação (Cliente ou Proprietário).
* **`build.sh`**: Script de compilação que une todos os módulos para gerar o executável `registre-pedidos.exe`.
* **`restaurante/`**: Módulo com as funcionalidades do proprietário.
    * `func/func_restaurante.c` e `.h`: Funções para manipulação de dados do cardápio (CRUD), validações e lógicas de negócio.
    * `menu/menu_restaurante.c`: Funções que constroem a interface de menu interativa para o proprietário.
* **`cliente/`**: Módulo com as funcionalidades do cliente.
    * `func/funcoes.c` e `.h`: Funções para manipulação dos dados de pedidos, cupons, validações e geração de relatórios.
    * `menu/menu_cliente.c`: Funções que constroem a interface de menu para o cliente realizar pedidos.

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
* **Descrição:** Ponto de entrada do programa. Exibe um menu principal que permite ao usuário escolher entre o menu do cliente, o menu do proprietário ou finalizar a aplicação. Utiliza a função `ler_inteiro_seguro` para uma captura de opção robusta.
* **Parâmetros:** Nenhum.
* **Retorno:** `0` em caso de finalização bem-sucedida.
* **Arquivo de Origem:** `main.c`

### Módulo Restaurante - Funções de Dados (`func_restaurante.c`)

#### `int adicionar_item(Cardapio item)`
* **Descrição:** Salva uma struct do tipo `Cardapio` ao final do arquivo binário `cardapio.bin`. Abre o arquivo em modo "append binary" (`ab`) para maior eficiência.
* **Parâmetros:** `Cardapio item` - A struct com os dados do item a ser adicionado.
* **Retorno:** `0` em caso de sucesso, `1` em caso de falha.
* **Arquivo de Origem:** `func_restaurante.c`

#### `int carregar_cardapio(char *filename, Cardapio **cardapio)`
* **Descrição:** Lê todos os registros de `struct Cardapio` do arquivo binário especificado e os aloca em um vetor dinâmico na memória. A memória do vetor é aumentada conforme necessário usando `realloc`.
* **Parâmetros:**
    * `char *filename`: String com o nome do arquivo a ser lido.
    * `Cardapio **cardapio`: Ponteiro duplo para o vetor que será alocado e preenchido. É um ponteiro duplo para que o endereço do vetor possa ser modificado na função chamadora.
* **Retorno:** `0` em caso de sucesso, `1` em caso de falha na alocação de memória ou abertura do arquivo.
* **Arquivo de Origem:** `func_restaurante.c`

#### `int editar_item_cardapio(char *filename, int indice, Cardapio *novo_item)`
* **Descrição:** Altera um item específico dentro do arquivo binário. Utiliza `fseek` para posicionar o ponteiro de arquivo diretamente no registro a ser sobrescrito, evitando a reescrita completa do arquivo.
* **Parâmetros:**
    * `char *filename`: String com o nome do arquivo.
    * `int indice`: Posição (base 0) do item a ser editado.
    * `Cardapio *novo_item`: Ponteiro para a struct com os novos dados do item.
* **Retorno:** `0` em caso de sucesso, `1` em caso de falha.
* **Arquivo de Origem:** `func_restaurante.c`

#### `int remover_item_cardapio(char *filename, int indice)`
* **Descrição:** Remove um item do arquivo binário. A estratégia consiste em carregar todos os itens para a memória, apagar o arquivo original e reescrevê-lo com todos os itens, exceto aquele no índice especificado.
* **Parâmetros:**
    * `char *filename`: String com o nome do arquivo.
    * `int indice`: Posição (base 0) do item a ser removido.
* **Retorno:** `0` em caso de sucesso, `1` em caso de falha.
* **Arquivo de Origem:** `func_restaurante.c`

#### `int imprimir_cardapio(char *filename)`
* **Descrição:** Lê sequencialmente o arquivo binário do cardápio e imprime cada item em uma tabela formatada no console.
* **Parâmetros:** `char *filename` - String com o nome do arquivo a ser impresso.
* **Retorno:** `0` em caso de sucesso, `1` se o arquivo não puder ser aberto.
* **Arquivo de Origem:** `func_restaurante.c`

#### `int total_itens_cardapio(char *filename)`
* **Descrição:** Calcula o número de registros no arquivo do cardápio de forma eficiente. Posiciona o ponteiro no final do arquivo com `fseek` para obter o tamanho total em bytes com `ftell`, e então divide esse valor pelo tamanho da struct `Cardapio`.
* **Parâmetros:** `char *filename` - String com o nome do arquivo.
* **Retorno:** O número total de itens (registros) no arquivo.
* **Arquivo de Origem:** `func_restaurante.c`

#### `char* tipo_str(int tipo)`
* **Descrição:** Converte o código numérico de um tipo de item em uma string legível para exibição.
* **Parâmetros:** `int tipo` - O código do tipo (0 para "Prato", 1 para "Bebida", 2 para "Sobremesa").
* **Retorno:** Um ponteiro de `char` para a string correspondente, ou `NULL` se o tipo for inválido.
* **Arquivo de Origem:** `func_restaurante.c`

#### `int verificar_indice_cardapio(char *filename, int indice)`
* **Descrição:** Verifica se um determinado índice (base 0) é válido, ou seja, se está dentro dos limites do número de itens existentes no cardápio.
* **Parâmetros:**
    * `char *filename`: String com o nome do arquivo do cardápio.
    * `int indice`: O índice a ser validado.
* **Retorno:** `0` se o índice for válido, `1` caso contrário.
* **Arquivo de Origem:** `func_restaurante.c`

#### `int validar_tipo(int tipo)`
* **Descrição:** Verifica se o tipo de item fornecido é um dos valores válidos (0, 1 ou 2).
* **Parâmetros:** `int tipo` - O tipo a ser validado.
* **Retorno:** `0` se o tipo for válido, `1` caso contrário.
* **Arquivo de Origem:** `func_restaurante.c`

#### `int validar_valor(float valor)`
* **Descrição:** Verifica se o valor (preço) de um item é não negativo.
* **Parâmetros:** `float valor` - O valor a ser validado.
* **Retorno:** `0` se o valor for válido, `1` caso contrário.
* **Arquivo de Origem:** `func_restaurante.c`

#### `int ler_inteiro_positivo()`
* **Descrição:** Captura e valida a entrada do usuário para garantir que seja um número inteiro estritamente positivo. Lê a entrada como string com `fgets` e verifica cada caractere com `isdigit` antes de converter para inteiro com `atoi`.
* **Parâmetros:** Nenhum.
* **Retorno:** O número inteiro positivo validado.
* **Arquivo de Origem:** `func_restaurante.c`

### Módulo Restaurante - Funções de Menu (`menu_restaurante.c`)

#### `void menu_adicionar_item(Cardapio *item)`
* **Descrição:** Guia o proprietário no processo de adicionar um novo item, solicitando e validando nome, tipo e valor. Utiliza funções de validação e limpa o buffer do teclado após as leituras para garantir robustez.
* **Parâmetros:** `Cardapio *item` - Ponteiro para a struct que será preenchida com os dados do novo item.
* **Retorno:** Nenhum (void).
* **Arquivo de Origem:** `menu_restaurante.c`

#### `void menu_editar_item(Cardapio *novo_item)`
* **Descrição:** Orquestra a edição de um item existente. Solicita ao usuário o índice do item, validando a entrada com `ler_inteiro_positivo`, e depois solicita e valida os novos dados antes de chamar a função `editar_item_cardapio`.
* **Parâmetros:** `Cardapio *novo_item` - Ponteiro para a struct que será preenchida com os dados atualizados.
* **Retorno:** Nenhum (void).
* **Arquivo de Origem:** `menu_restaurante.c`

#### `void menu_excluir_item()`
* **Descrição:** Conduz o usuário no processo de exclusão de um item. Solicita o índice, valida-o com `ler_inteiro_positivo` e `verificar_indice_cardapio`, e então chama a função `remover_item_cardapio`.
* **Parâmetros:** Nenhum.
* **Retorno:** Nenhum (void).
* **Arquivo de Origem:** `menu_restaurante.c`

#### `int menu_restaurante()`
* **Descrição:** É o loop principal da interface do proprietário. Exibe o menu de opções (visualizar, adicionar, editar, etc.) e gerencia a navegação, chamando as funções apropriadas com base na escolha do usuário.
* **Parâmetros:** Nenhum.
* **Retorno:** `1` quando o usuário decide finalizar a seção.
* **Arquivo de Origem:** `menu_restaurante.c`

### Módulo Cliente - Funções de Dados (`funcoes.c`)

#### `void mid_line()` e `void top_bottom()`
* **Descrição:** Funções estéticas simples que imprimem linhas de separação no console para melhorar a formatação e legibilidade da interface.
* **Parâmetros:** Nenhum.
* **Retorno:** Nenhum (void).
* **Arquivo de Origem:** `funcoes.c`

#### `void inicializar_cupons(struct cupom_desconto cupons[])`
* **Descrição:** Preenche um vetor de `struct cupom_desconto` com uma lista fixa de códigos e seus respectivos percentuais de desconto.
* **Parâmetros:** `struct cupom_desconto cupons[]` - O vetor a ser inicializado.
* **Retorno:** Nenhum (void).
* **Arquivo de Origem:** `funcoes.c`

#### `int aplicar_cupom(char codigo[], struct cupom_desconto cupons[], float *desconto)`
* **Descrição:** Verifica se um código de cupom fornecido é válido, comparando-o (ignorando maiúsculas/minúsculas com `strcasecmp`) com a lista de cupons disponíveis. Se for válido, o valor do desconto é atribuído através de um ponteiro.
* **Parâmetros:**
    * `char codigo[]`: O código digitado pelo usuário.
    * `struct cupom_desconto cupons[]`: O vetor de cupons disponíveis.
    * `float *desconto`: Ponteiro para a variável que armazenará o percentual de desconto.
* **Retorno:** `1` se o cupom for válido, `0` caso contrário.
* **Arquivo de Origem:** `funcoes.c`

#### `int ler_inteiro_seguro(const char *mensagem, int min, int max)`
* **Descrição:** Captura e valida a entrada de um número inteiro do usuário. Utiliza `fgets` para ler a linha inteira e `sscanf` para extrair o número, prevenindo erros de buffer e garantindo que a entrada esteja dentro de um intervalo `[min, max]`.
* **Parâmetros:**
    * `const char *mensagem`: Texto a ser exibido para o usuário.
    * `int min`: Valor mínimo permitido para a entrada.
    * `int max`: Valor máximo permitido para a entrada.
* **Retorno:** O número inteiro validado.
* **Arquivo de Origem:** `funcoes.c`

#### `int validar_resposta_sn(const char *mensagem)`
* **Descrição:** Valida uma resposta do tipo "sim" ou "não". Lê um caractere, converte para minúsculo e só aceita 's' ou 'n', limpando o buffer de entrada para evitar erros em leituras futuras.
* **Parâmetros:** `const char *mensagem` - Texto a ser exibido para o usuário.
* **Retorno:** `1` se a resposta for 's', `0` se for 'n'.
* **Arquivo de Origem:** `funcoes.c`

#### `int validar_nome_item(const char *str)`
* **Descrição:** Verifica se uma string contém apenas caracteres alfabéticos e espaços, sendo usada para validar os nomes dos itens do cardápio.
* **Parâmetros:** `const char *str` - A string a ser validada.
* **Retorno:** `1` se a string for válida, `0` caso contrário.
* **Arquivo de Origem:** `funcoes.c`

#### `Cardapio* buscar_item_cardapio(int posicao, Cardapio *cardapio, int total_itens)`
* **Descrição:** Retorna o ponteiro para um item específico do cardápio que já foi carregado na memória.
* **Parâmetros:**
    * `int posicao`: Posição do item desejado (base 1).
    * `Cardapio *cardapio`: Vetor de itens previamente carregado.
    * `int total_itens`: Tamanho total do vetor de cardápio.
* **Retorno:** Ponteiro para o item do cardápio se a posição for válida, ou `NULL` caso contrário.
* **Arquivo de Origem:** `funcoes.c`

#### `void registrar_e_salvar(...)`
* **Descrição:** Registra um novo pedido tanto no vetor dinâmico em memória quanto o persiste no arquivo binário `pedidos.bin`. Aumenta a capacidade do vetor de pedidos com `realloc` conforme necessário.
* **Parâmetros:** Múltiplos parâmetros, incluindo o ponteiro duplo `struct dados_pedido **vetor` para modificar o vetor na função chamadora, dados do pedido (mesa, pessoas, item, etc.), o cardápio e informações de desconto.
* **Retorno:** Nenhum (void).
* **Arquivo de Origem:** `funcoes.c`

#### `int carregar_pedidos(struct dados_pedido **vetor, int *total_pedidos, int *capacidade)`
* **Descrição:** Lê todos os registros de pedidos do arquivo `pedidos.bin` e os carrega em um vetor alocado dinamicamente na memória, preparando o sistema para adicionar novos pedidos ou gerar relatórios.
* **Parâmetros:**
    * `struct dados_pedido **vetor`: Ponteiro duplo que receberá o endereço do vetor de pedidos alocado.
    * `int *total_pedidos`: Ponteiro para o contador de pedidos.
    * `int *capacidade`: Ponteiro para a capacidade atual do vetor.
* **Retorno:** `1` em caso de sucesso; `0` se o arquivo não existir ou ocorrer um erro.
* **Arquivo de Origem:** `funcoes.c`

#### `void exibir_pedido(struct dados_pedido p, int eh_relatorio)`
* **Descrição:** Exibe as informações de um único pedido de forma formatada. O parâmetro `eh_relatorio` controla se detalhes como o desconto devem ser exibidos, customizando a saída para diferentes contextos.
* **Parâmetros:**
    * `struct dados_pedido p`: A struct com os dados do pedido a ser exibido.
    * `int eh_relatorio`: Flag que indica se a exibição é para o relatório final (1) ou não (0).
* **Retorno:** Nenhum (void).
* **Arquivo de Origem:** `funcoes.c`

#### `void gerar_relatorio_final()`
* **Descrição:** Orquestra a geração do relatório completo de vendas. Carrega todos os pedidos e chama funções auxiliares para calcular e exibir todas as métricas: resumo geral, detalhes por mesa, ranking de itens e subtotal por categoria. Libera a memória do vetor de pedidos ao final.
* **Parâmetros:** Nenhum.
* **Retorno:** Nenhum (void).
* **Arquivo de Origem:** `funcoes.c`

#### `void calcular_metricas_gerais(struct dados_pedido pedidos[], int total_pedidos)`
* **Descrição:** Função de análise para o relatório. Calcula o faturamento total (sem descontos), o número de mesas únicas atendidas, a média de faturamento por mesa e o total de itens vendidos.
* **Parâmetros:**
    * `struct dados_pedido pedidos[]`: Vetor com todos os pedidos.
    * `int total_pedidos`: Número de elementos no vetor.
* **Retorno:** Nenhum (void).
* **Arquivo de Origem:** `funcoes.c`

#### `void calcular_subtotal_por_tipo(struct dados_pedido pedidos[], int total_pedidos)`
* **Descrição:** Função de análise para o relatório. Agrupa o faturamento por categoria (pratos, bebidas, sobremesas) e exibe os subtotais para cada uma.
* **Parâmetros:**
    * `struct dados_pedido pedidos[]`: Vetor com todos os pedidos.
    * `int total_pedidos`: Número de elementos no vetor.
* **Retorno:** Nenhum (void).
* **Arquivo de Origem:** `funcoes.c`

#### `void gerar_ranking(struct dados_pedido pedidos[], int total_pedidos)`
* **Descrição:** Cria e exibe um ranking dos 5 itens mais vendidos. Consolida os pedidos para somar as quantidades de cada item e depois ordena os resultados usando o algoritmo Bubble Sort.
* **Parâmetros:**
    * `struct dados_pedido pedidos[]`: Vetor com todos os pedidos.
    * `int total_pedidos`: Número de elementos no vetor.
* **Retorno:** Nenhum (void).
* **Arquivo de Origem:** `funcoes.c`

### Módulo Cliente - Funções de Menu (`menu_cliente.c`)

#### `int menu_cliente()`
* **Descrição:** É a função principal da interface do cliente. Ela inicializa o ambiente (carrega cardápio, pedidos e cupons) e entra no loop principal do menu do cliente, de onde são chamadas as funções para ver o cardápio e fazer pedidos. Libera a memória alocada ao sair.
* **Parâmetros:** Nenhum.
* **Retorno:** `0` em caso de sucesso; `1` se houver erro ao carregar o cardápio.
* **Arquivo de Origem:** `menu_cliente.c`

#### `void fazerPedido(...)`
* **Descrição:** É a função interativa que guia o cliente na criação de um pedido. Ela solicita dados da mesa, cupom, e entra em um loop para que o cliente adicione múltiplos itens, chamando `registrar_e_salvar` para cada um.
* **Parâmetros:** Recebe ponteiros para o vetor de pedidos e seu estado (`total`, `capacidade`), o cardápio, e a lista de cupons.
* **Retorno:** Nenhum (void).
* **Arquivo de Origem:** `menu_cliente.c`

#### `void mostrarPratosPrincipais(...)`, `void mostrarBebidas(...)`, `void mostrarSobremesas(...)`
* **Descrição:** Cada uma dessas três funções é responsável por exibir uma categoria específica de itens do cardápio, filtrando o vetor principal com base no campo `tipo` de cada item e exibindo os resultados em uma tabela formatada.
* **Parâmetros:**
    * `Cardapio *cardapio_ptr`: Ponteiro para o vetor do cardápio.
    * `int total_itens`: Número total de itens no cardápio.
* **Retorno:** Nenhum (void).
* **Arquivo de Origem:** `menu_cliente.c`

#### `int mostrarMenu()`
* **Descrição:** Exibe o menu principal do cliente com as opções disponíveis (ver pratos, bebidas, sobremesas, fazer pedido, sair) e captura a escolha do usuário.
* **Parâmetros:** Nenhum.
* **Retorno:** A opção (de 1 a 5) escolhida pelo usuário.
* **Arquivo de Origem:** `menu_cliente.c`

#### `float obter_desconto_cupom(const char *cupom_digitado, const struct cupom_desconto cupons[], int num_cupons)`
* **Descrição:** Verifica se um código de cupom fornecido é válido, comparando-o com a lista de cupons disponíveis.
* **Parâmetros:**
    * `const char *cupom_digitado`: O código do cupom inserido pelo usuário.
    * `const struct cupom_desconto cupons[]`: O vetor de cupons disponíveis.
    * `int num_cupons`: O tamanho do vetor de cupons.
* **Retorno:** A porcentagem de desconto (e.g., `0.20`) se o cupom for válido, ou `0.0` caso contrário.
* **Arquivo de Origem:** `menu_cliente.c`

#### `void pausarTela()`
* **Descrição:** Pausa a execução do programa e aguarda que o usuário pressione a tecla Enter para continuar. Útil para permitir que o usuário leia as informações exibidas na tela antes que ela seja limpa.
* **Parâmetros:** Nenhum.
* **Retorno:** Nenhum (void).
* **Arquivo de Origem:** `menu_cliente.c`