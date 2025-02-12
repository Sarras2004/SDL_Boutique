#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "menu.h"
#include "boutique.h"
#include "inspection.h"


// Dimensions de la fenêtre
#define BOUTIQUE_WIDTH 816
#define BOUTIQUE_HEIGHT 444

// Dimensions du joueur 
#define PLAYER_WIDTH 64
#define PLAYER_HEIGHT 64
#define PLAYER_SPEED 7

int animation_speed, i;
SDL_Rect prev_position;

int boutique() {
    // Création de la fenêtre
    SDL_Window *window_boutique = SDL_CreateWindow("Boutique", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, BOUTIQUE_WIDTH, BOUTIQUE_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window_boutique)
    {
        printf("Erreur de création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Création du renderer de la boutique
    SDL_Renderer *renderer_boutique = SDL_CreateRenderer(window_boutique, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_boutique)
    {
        printf("Erreur de création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window_boutique);
        SDL_Quit();
        return 1;
    }  
    

    //On crée la texture qui dessine la map
    SDL_Texture *texture_map = loadImage("images/map_finale.bmp", renderer_boutique);

    objet comptoir, table1, table2, table3, table4, table5, table6, plante1, table7, table8, table9, table10, vase, plante2, table11, table12, table13, table14, table15, table16, table17, table18; 
    objet_init(&comptoir, &table1, &table2, &table3, &table4, &table5, &table6, &plante1, &table7, &table8, &table9, &table10, &vase, &plante2, &table11, &table12, &table13, &table14, &table15, &table16, &table17, &table18);

    // Création de la fenetre "source" du personnage
    SDL_Rect src_frame = {0, 0, PLAYER_WIDTH - 15, PLAYER_HEIGHT - 5};

    // Initialisation du personnage
    player adibou = {
        .position = {60, 150, PLAYER_WIDTH, PLAYER_HEIGHT},
        .texture_sheet = loadImage("adibou_sheet.bmp", renderer_boutique),

    };

    //Initialisation du tableau de l'inventaire
    char **tab_inventaire = malloc(6 * sizeof(char*));
    for(int i = 0; i < 6; i++){
        tab_inventaire[i] = "";
    }

    // Boucle principale
    int running = 1;
    SDL_Event event;
    while (running)
    {
        // Gestion des événements
        SDL_PollEvent(&event);
        //while (SDL_PollEvent(&event)){
            prev_position = adibou.position;

            const Uint8 *keystate = SDL_GetKeyboardState(NULL);

            animation_speed = SDL_GetTicks() / 175;
            i = animation_speed % 4; // 0, 1, 2, 3
            
            if (event.type == SDL_QUIT || keystate[SDL_SCANCODE_ESCAPE]) running = 0;
            
            // Gestion des touches
            else if (keystate[SDL_SCANCODE_RIGHT]) {
                adibou.position.x += PLAYER_SPEED;
                src_frame.x = PLAYER_WIDTH * i + 10;
                src_frame.y = PLAYER_HEIGHT * 2 + 10;

            } else if (keystate[SDL_SCANCODE_LEFT]) {
                adibou.position.x -= PLAYER_SPEED;
                src_frame.x = PLAYER_WIDTH * i + 10;
                src_frame.y = PLAYER_HEIGHT + 10;


            } else if (keystate[SDL_SCANCODE_UP]) {
                adibou.position.y -= PLAYER_SPEED;
                src_frame.x = PLAYER_WIDTH * i + 10;
                src_frame.y = PLAYER_HEIGHT * 3 + 10;


            } else if (keystate[SDL_SCANCODE_DOWN]) {
                adibou.position.y += PLAYER_SPEED;
                src_frame.x = PLAYER_WIDTH * i + 10;
                src_frame.y = 0 + 10;

            }

            // Gestion des obstacles 
            // Limites de la fenêtre
            if (adibou.position.x < 0) adibou.position.x = 0;
            if (adibou.position.y < 0) adibou.position.y = 0;
            if (adibou.position.x + adibou.position.w > BOUTIQUE_WIDTH) adibou.position.x = BOUTIQUE_WIDTH - adibou.position.w;
            if (adibou.position.y + adibou.position.h > BOUTIQUE_HEIGHT) adibou.position.y = BOUTIQUE_HEIGHT - adibou.position.h;


            if(SDL_HasIntersection(&adibou.position, &comptoir.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    comptoir.last_opening = SDL_GetTicks();
                    inventaire(tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table1.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table1.last_opening = SDL_GetTicks();
                    inspection(table1, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table2.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table2.last_opening = SDL_GetTicks();
                    inspection(table2, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table3.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table3.last_opening = SDL_GetTicks();
                    inspection(table3, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table4.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table4.last_opening = SDL_GetTicks();
                    inspection(table4, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table5.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table5.last_opening = SDL_GetTicks();
                    inspection(table5, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table6.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table6.last_opening = SDL_GetTicks();
                    inspection(table6, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &plante1.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    plante1.last_opening = SDL_GetTicks();
                    inspection(plante1, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table7.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table7.last_opening = SDL_GetTicks();
                    inspection(table7, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table8.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table8.last_opening = SDL_GetTicks();
                    inspection(table8, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table9.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table9.last_opening = SDL_GetTicks();
                    inspection(table9, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table10.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table10.last_opening = SDL_GetTicks();
                    inspection(table10, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &vase.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    vase.last_opening = SDL_GetTicks();
                    inspection(vase, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &plante2.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    plante2.last_opening = SDL_GetTicks();
                    inspection(plante2, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table11.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table11.last_opening = SDL_GetTicks();
                    inspection(table11, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table12.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table12.last_opening = SDL_GetTicks();
                    inspection(table12, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table13.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table13.last_opening = SDL_GetTicks();
                    inspection(table13, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table14.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table14.last_opening = SDL_GetTicks();
                    inspection(table14, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table15.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table15.last_opening = SDL_GetTicks();
                    inspection(table15, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table16.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table16.last_opening = SDL_GetTicks();
                    inspection(table16, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table17.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table17.last_opening = SDL_GetTicks();
                    inspection(table17, tab_inventaire);
                }
                adibou.position = prev_position;
            }
            if(SDL_HasIntersection(&adibou.position, &table18.position)){
                if(keystate[SDL_SCANCODE_SPACE]){
                    table18.last_opening = SDL_GetTicks();
                        inspection(table18, tab_inventaire);
                }
                adibou.position = prev_position;
            }
        


        // Rendu
        SDL_RenderClear(renderer_boutique);
        SDL_RenderCopy(renderer_boutique, texture_map, NULL, NULL);
        SDL_RenderCopy(renderer_boutique, adibou.texture_sheet, &src_frame, &adibou.position);
        
        SDL_RenderPresent(renderer_boutique);

        // Délai pour limiter la vitesse de la boucle
        SDL_Delay(30); // ~60 FPS
    }

    // Nettoyage

    SDL_DestroyRenderer(renderer_boutique);
    SDL_DestroyWindow(window_boutique);

    

    SDL_Quit();

    menu();

    return 0;
}