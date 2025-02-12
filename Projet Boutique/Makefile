# Nom de l'exécutable
EXEC = prog

# Fichiers source
SRCS = inspection.c boutique.c menu.c main.c

# Fichiers objets générés
OBJS = $(SRCS:.c=.o)

# Commande de compilation
CC = gcc

# Options de compilation (ajouter des warnings pour plus de sécurité)
CFLAGS = $(shell sdl2-config --cflags)

# Options d'édition de liens'
LDFLAGS = $(shell sdl2-config --libs)

# Règle principale
all: $(EXEC)

# Création de l'exécutable
$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation des fichiers .c en fichiers .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers générés
clean:
	rm -f $(OBJS) $(EXEC)

