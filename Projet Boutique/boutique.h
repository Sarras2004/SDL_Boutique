#ifndef BOUTIQUE_H
#define BOUTIQUE_H

int boutique();

typedef struct player_ {
    SDL_Rect position;
    SDL_Texture *texture_sheet;
} player;


#endif