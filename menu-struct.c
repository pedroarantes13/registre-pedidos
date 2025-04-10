//definição da estrutura de dados que os restaurantes precisam para cadastrar seus pratos
#include <stdio.h>

int main () {

    struct menu_restaurante
    {
        char nome[100];
        int tipo;
        float preço;
        float tempo_preparo;
    };
}