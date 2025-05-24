#include "dados_restaurante.h"
#include <stdio.h>
#include <string.h>

void escrever_dados(char nome[], int tipo, float valor, int tempo_preparo) {

	struct dados_menu {
		char nome[100];
		int tipo;
		float valor;
		int tempo_preparo;	
	};

	struct dados_menu prato;

	strcpy(prato.nome, nome);
	prato.tipo = tipo;
	prato.valor = valor;
	prato.tempo_preparo = tempo_preparo;

	FILE *output = fopen ("output", "w");

	fwrite(&prato, sizeof(struct dados_menu), 1, output);

}
