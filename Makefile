# Variables
CC = gcc
CFLAGS = -Wall -Iinclude -g                # Ajout des headers depuis include/ et flag -g pour debug
LDFLAGS = -lmicrohttpd                     # Lien avec la bibliothèque

SRC = main.c src/serveur.c                 # Tous les fichiers source
OBJ = build/main.o build/serveur.o         # Tous les fichiers objets
BIN = projet                               # Nom de l'exécutable

# Règle principale
all: $(BIN)

# Création de l'exécutable
$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation des fichiers objets
build/main.o: main.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/serveur.o: src/serveur.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf build $(BIN)

# Phony targets
.PHONY: all clean
