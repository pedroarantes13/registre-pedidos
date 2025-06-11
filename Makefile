CC = gcc
CFLAGS = -Wall -g
TARGET = programa

SRCS = \
	cliente/menu/menu_cliente.c \
	cliente/func/menu_funcoes.c \
	cliente/func/funcoes.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET).exe $(CFLAGS) # Adicionado .exe aqui

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@echo Cleaning up...
	-del $(subst /,\\,$(OBJS)) 2>NUL # Usa del para .o, e converte barras
	-del $(TARGET).exe 2>NUL       # Usa del para o executável .exe
	@echo Done.CC = gcc
CFLAGS = -Wall -g
TARGET = programa

SRCS = \
	cliente/menu/menu_cliente.c \
	cliente/func/menu_funcoes.c \
	cliente/func/funcoes.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET).exe $(CFLAGS) # Adicionado .exe aqui

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@echo Cleaning up...
	-del $(subst /,\\,$(OBJS)) 2>NUL # Usa del para .o, e converte barras
	-del $(TARGET).exe 2>NUL       # Usa del para o executável .exe
	@echo Done.