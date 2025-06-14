#!/bin/bash
gcc \
    main.c \
    restaurante/func/func_restaurante.c \
    restaurante/menu/menu_restaurante.c \
    cliente/func/funcoes.c \
    cliente/menu/menu_cliente.c \
    -Irestaurante/func \
    -Icliente/func \
    -o registre-pedidos.exe