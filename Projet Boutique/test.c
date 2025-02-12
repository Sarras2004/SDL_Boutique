#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "menu.h"
#include "boutique.h"


//compilation UBUNTU : gcc boutique.c menu.c test.c $(sdl2-config --cflags --libs) -o prog_test



int main(int argc, char ***argv)
{
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL_Init : %s\n", SDL_GetError());
        return 1;
    }

    menu();


    return 0;
}
