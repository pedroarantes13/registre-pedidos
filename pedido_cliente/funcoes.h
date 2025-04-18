// Esse programa faz parte de uma avaliação da faculdade, que é um sistema de pedidos de restaurante. Nesse arquivo temos o protótipo da função que armazena os nomes e a quantidade dos itens do pedido e retorna os mesmos, juntamente com oo total da conta

#pragma once

struct dados_pedido {
    char prato[50];
    int qtd_prato;
    char bebida[50];
    int qtd_bebida;
    float subtotal;
};

struct dados_pedido registrar_pedido();