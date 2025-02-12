#include "boutique.h"
#ifndef INSPECTION_H
#define INSPECTION_H

typedef struct objet_ {
    int is_open, last_opening, nb_interieur;
    SDL_Rect position;
    SDL_Texture *texture_objet_interieur[3];
    char *char_objet_interieur[3];
} objet;

int inventaire(char **tab_inventaire);

int fonction_pick(char *texture_picked, char **tab);

int inspection(objet truc, char **tab);

void objet_init(objet *comptoir , objet *truc1, objet *truc2, objet *truc3, objet *truc4, objet *truc5, objet *truc6, objet *truc7, objet *truc8, objet *truc9, objet *truc10, objet *truc11, objet *truc12, objet *truc13, objet *truc14, objet *truc15, objet *truc16, objet *truc17, objet *truc18, objet *truc19, objet *truc20, objet *truc21);

#endif