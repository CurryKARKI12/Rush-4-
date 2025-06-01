# Compilateur
CC = gcc

# Détection du système d'exploitation
ifeq ($(OS),Windows_NT)
    # Flags pour Windows
    CFLAGS = -Wall -Wextra -Iinclude -D_WIN32
    EXEC = minishell.exe
    RM = del /Q
else
    # Flags pour Unix/Linux
    CFLAGS = -Wall -Wextra -Iinclude
    EXEC = minishell
    RM = rm -f
endif

# Fichiers sources et objets
SRC = src/main.c src/parse.c src/execute_system.c src/execute_exec.c src/utils.c
OBJ = $(SRC:.c=.o)

# Cible principale
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Règle générique pour les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
ifeq ($(OS),Windows_NT)
	$(RM) $(subst /,\,$(OBJ)) $(EXEC)
else
	$(RM) $(OBJ) $(EXEC)
endif

.PHONY: all clean