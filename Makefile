# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra

# Nome do executável
TARGET = menu.exe

# Fontes
SRC = \
    cliente/func/menu.h \
    cliente/func/menu_funcoes.c \
    cliente/menu/menu_cliente.c


all: $(TARGET)


$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Limpeza dos arquivos binários
clean:
	del /Q $(TARGET)
