CC = gcc
CFLAGS = -Wall -g
TARGET = menu# Nome do programa final

# Diretórios base
CLIENTE_DIR = cliente
CLIENTE_MENU_DIR = $(CLIENTE_DIR)/menu
CLIENTE_FUNC_DIR = $(CLIENTE_DIR)/func
RESTAURANTE_DIR = restaurante
RESTAURANTE_FUNC_DIR = $(RESTAURANTE_DIR)/func

# Diretórios onde o compilador deve procurar pelos arquivos .h (cabeçalhos)
INCLUDE_DIRS = -I$(CLIENTE_MENU_DIR) \
               -I$(CLIENTE_FUNC_DIR) \
               -I$(RESTAURANTE_FUNC_DIR)

# Adiciona os diretórios de inclusão aos CFLAGS
CFLAGS += $(INCLUDE_DIRS)

# Arquivos fonte (TODOS os .c do seu projeto que precisam ser compilados)
SRCS = \
    $(CLIENTE_MENU_DIR)/menu_cliente.c \
    $(CLIENTE_FUNC_DIR)/menu_funcoes.c \
    $(CLIENTE_FUNC_DIR)/funcoes.c \
    $(RESTAURANTE_FUNC_DIR)/func_restaurante.c

# Arquivos objeto (os .o que serão gerados a partir dos .c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

# Regra principal: compilar o executável
all: $(TARGET).exe

$(TARGET).exe: $(OBJS)
	@echo "Linking $(TARGET).exe..."
	$(CC) $(OBJS) -o $(TARGET).exe
	@echo "Build complete."

# Regra para compilar arquivos .c em .o
%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $<"

# Regra para limpar o projeto (remove todos os .o e o executável)
.PHONY: clean
clean:
	@echo "Cleaning up..."
	-rm $(OBJS) $(TARGET).exe 2>/dev/null || del $(subst /,\\,$(OBJS)) $(TARGET).exe 2>NUL || true
	@echo "Clean complete."