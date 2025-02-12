#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "menu.h"
#include "boutique.h"
#include "inspection.h"


#define WINDOW_OBJET_WIDTH 400
#define WINDOW_OBJET_HEIGHT 350

#define WINDOW_INVENTAIRE_WIDTH 1110
#define WINDOW_INVENTAIRE_HEIGHT 750

int inventaire(char **tab) {
    SDL_Window *window_inventaire = SDL_CreateWindow("INVENTAIRE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_INVENTAIRE_WIDTH, WINDOW_INVENTAIRE_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window_inventaire) {
        printf("Erreur de création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer_inventaire = SDL_CreateRenderer(window_inventaire, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_inventaire) {
        printf("Erreur de création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window_inventaire);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *blanc = loadImage("images/objets/blanc.bmp", renderer_inventaire);

    SDL_Rect pos_frame1 = {20, 20, 330, 330};
    SDL_Rect pos_frame2 = {390, 20, 330, 330};
    SDL_Rect pos_frame3 = {760, 20, 330, 330};
    SDL_Rect pos_frame4 = {20, 390, 330, 330};
    SDL_Rect pos_frame5 = {390, 390, 330, 330};
    SDL_Rect pos_frame6 = {760, 390, 330, 330};

    SDL_Rect pos_frame[6] = {pos_frame1, pos_frame2, pos_frame3, pos_frame4, pos_frame5, pos_frame6};


    int running = 1;
    int compteur = 0;
    SDL_Event event;
    SDL_Texture **tab_texture = malloc(6*sizeof(SDL_Texture*));

    while(compteur < 6){
        if(tab[compteur][0] == '\0'){
            tab_texture[compteur] = NULL;
        } else {
            tab_texture[compteur] = loadImage(tab[compteur], renderer_inventaire);
        }
        compteur++;
    }

    while(running){
        while (SDL_PollEvent(&event)){
            const Uint8 *keystate = SDL_GetKeyboardState(NULL);
            if (event.type == SDL_QUIT || keystate[SDL_SCANCODE_ESCAPE]) running = 0;

            for (int i = 0; i < 6; i++) {
                if (tab_texture[i] != NULL) {
                    SDL_RenderCopy(renderer_inventaire, tab_texture[i], NULL, &pos_frame[i]);
                } else {
                    SDL_RenderCopy(renderer_inventaire, blanc, NULL, &pos_frame[i]);
                }
            }
        }
        SDL_RenderPresent(renderer_inventaire);
    }

    SDL_DestroyTexture(blanc);
    SDL_DestroyRenderer(renderer_inventaire);
    SDL_DestroyWindow(window_inventaire);

    return 0;
}



int fonction_pick(char *char_texture_picked, char **tab){
    int quit = 1, cpt = 0;
    while(quit){
        for(int i = 0; i < 6; i++){
            if(strcmp(tab[i], char_texture_picked) == 0){   
                quit = 0;
                return 0;
            }
        }
        for(int i = 0; i < 6; i++){
            if(tab[i][0] == '\0'){
                tab[i] = char_texture_picked;
                quit = 0;
                return 0;
            } else cpt++;
        }
        if(cpt == 6){
            quit = 0;
            return 0;
        }
    }

}

int fonction_drop(char *char_texture_picked, char **tab){
    int quit = 1, cpt = 0;
    while(quit){
        for(int i = 0; i < 6; i++){
            if(strcmp(tab[i], char_texture_picked) == 0){
                tab[i] = "";
                quit = 0;
                return 0;
            }
        }
        quit = 0;
        return 0;
    }
}

int inspection(objet truc, char **tab_inventaire){

    int changing_speed, indice = 0, e = 0;

    // Création de la fenêtre
    SDL_Window *window_objet = SDL_CreateWindow("OBJET_INSPECTION", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_OBJET_WIDTH, WINDOW_OBJET_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window_objet)
    {
        printf("Erreur de création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Création du renderer de l'objet
    SDL_Renderer *renderer_objet = SDL_CreateRenderer(window_objet, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_objet)
    {
        printf("Erreur de création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window_objet);
        SDL_Quit();
        return 1;
    }
    SDL_Texture *texture_inspection = loadImage("images/menu/inspection.bmp", renderer_objet);
    SDL_Texture *texture_inspection_shiny = loadImage("images/menu/inspection_shiny.bmp", renderer_objet);

    SDL_Rect src_prendre = { 160, 16, 112, 32 };
    SDL_Rect src_poser = { 160, 64, 112, 32 };

    SDL_Rect pos_item = {79, 16, 245, 245};
    SDL_Rect pos_prendre = {30, 284, 150, 50};
    SDL_Rect pos_poser = {220, 284, 150, 50}; 

    int running = 1, compteur = 0;
    while(compteur < truc.nb_interieur){
        truc.texture_objet_interieur[compteur] = loadImage(truc.char_objet_interieur[compteur], renderer_objet);
        compteur++;
    }
    SDL_Event event;
    while(running){
        while (SDL_PollEvent(&event)){
            const Uint8 *keystate = SDL_GetKeyboardState(NULL);
            if (event.type == SDL_QUIT || keystate[SDL_SCANCODE_ESCAPE]){
                running = 0;
                truc.last_opening = SDL_GetTicks();

            } else if(keystate[SDL_SCANCODE_SPACE]){
                indice = e % truc.nb_interieur;
                e++;
                SDL_Delay(15);
            }
            int x, y;
            SDL_GetMouseState(&x, &y);

            SDL_RenderClear(renderer_objet);

            if(SDL_PointInRect(&(SDL_Point){x,y}, &pos_prendre)){
                SDL_RenderCopy(renderer_objet, texture_inspection_shiny, &src_prendre, &pos_prendre);
                SDL_RenderCopy(renderer_objet, texture_inspection, &src_poser, &pos_poser);
            } else if(SDL_PointInRect(&(SDL_Point){x,y}, &pos_poser)){
                SDL_RenderCopy(renderer_objet, texture_inspection, &src_prendre, &pos_prendre);
                SDL_RenderCopy(renderer_objet, texture_inspection_shiny, &src_poser, &pos_poser);
            } else{
                SDL_RenderCopy(renderer_objet, texture_inspection, &src_prendre, &pos_prendre);
                SDL_RenderCopy(renderer_objet, texture_inspection, &src_poser, &pos_poser);
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) 
            {
                int x = event.button.x;
                int y = event.button.y;
                if (SDL_PointInRect(&(SDL_Point){x, y}, &pos_prendre))
                {
                    fonction_pick(truc.char_objet_interieur[indice], tab_inventaire);
                } 
                else if (SDL_PointInRect(&(SDL_Point){x, y}, &pos_poser))
                {
                    fonction_drop(truc.char_objet_interieur[indice], tab_inventaire);
                } 
            }
        }

        SDL_RenderCopy(renderer_objet, truc.texture_objet_interieur[indice], NULL, &pos_item);

        SDL_RenderPresent(renderer_objet);

    }
    SDL_DestroyTexture(texture_inspection_shiny);
    SDL_DestroyTexture(texture_inspection);
    SDL_DestroyRenderer(renderer_objet);
    SDL_DestroyWindow(window_objet);

    return 1;
}










void objet_init(objet *comptoir, objet *biblio1, objet *biblio2, objet *biblio3, objet *biblio4, objet *biblio5, objet *biblio6, objet *biblio7, objet *biblio8, objet *biblio9, objet *biblio10, objet *biblio11, objet *vase, objet *plante2, objet *biblio12, objet *biblio13, objet *biblio14, objet *biblio15, objet *biblio16, objet *biblio17, objet *biblio18, objet *biblio19){
    comptoir->position.x = 210; 
    comptoir->position.y = 50;
    comptoir->position.w = 207;
    comptoir->position.h = 61;
    comptoir->nb_interieur = 0;
    comptoir->last_opening = 0;

    biblio1->position.x = 40; 
    biblio1->position.y = 268;
    biblio1->position.w = 73;
    biblio1->position.h = 10;
    biblio1->nb_interieur = 2;
    biblio1->last_opening = 0;
    biblio1->char_objet_interieur[0] = "images/objets/plante2.bmp";
    biblio1->char_objet_interieur[1] = "images/objets/lampe1.bmp";

    biblio2->position.x = 112;
    biblio2->position.y = 268;
    biblio2->position.w = 73;
    biblio2->position.h = 10;
    biblio2->nb_interieur = 3;
    biblio2->last_opening = 0;
    biblio2->char_objet_interieur[0] = "images/objets/livre.bmp";
    biblio2->char_objet_interieur[1] = "images/objets/lampe3.bmp";
    biblio2->char_objet_interieur[2] = "images/objets/livre4.bmp";

    biblio3->position.x = 188; 
    biblio3->position.y = 268;
    biblio3->position.w = 53;
    biblio3->position.h = 10;
    biblio3->nb_interieur = 3;
    biblio3->last_opening = 0;
    biblio3->char_objet_interieur[0] = "images/objets/lampe3.bmp";
    biblio3->char_objet_interieur[1] = "images/objets/lampe2.bmp";
    biblio3->char_objet_interieur[2] = "images/objets/lampe1.bmp";

    biblio4->position.x = 40; 
    biblio4->position.y = 394;
    biblio4->position.w = 73;
    biblio4->position.h = 10;
    biblio4->nb_interieur = 3;
    biblio4->last_opening = 0;
    biblio4->char_objet_interieur[0] = "images/objets/potion.bmp";
    biblio4->char_objet_interieur[1] = "images/objets/plante2.bmp";
    biblio4->char_objet_interieur[2] = "images/objets/feuille.bmp";

    biblio5->position.x = 112; 
    biblio5->position.y = 394;
    biblio5->position.w = 73;
    biblio5->position.h = 10;
    biblio5->nb_interieur = 3;
    biblio5->last_opening = 0;
    biblio5->char_objet_interieur[0] = "images/objets/bouteille.bmp";
    biblio5->char_objet_interieur[1] = "images/objets/livre5.bmp";
    biblio5->char_objet_interieur[2] = "images/objets/livre1.bmp";

    biblio6->position.x = 188; 
    biblio6->position.y = 394;
    biblio6->position.w = 53;
    biblio6->position.h = 10;
    biblio6->nb_interieur = 3;
    biblio6->last_opening = 0;
    biblio6->char_objet_interieur[0] = "images/objets/bouteille.bmp";
    biblio6->char_objet_interieur[1] = "images/objets/feuille.bmp";
    biblio6->char_objet_interieur[2] = "images/objets/potion.bmp";

    biblio7->position.x = 245;
    biblio7->position.y = 394;
    biblio7->position.w = 32;
    biblio7->position.h = 10;
    biblio7->nb_interieur = 1;
    biblio7->last_opening = 0;
    biblio7->char_objet_interieur[0] = "images/objets/plante4.bmp";

    biblio8->position.x = 446; 
    biblio8->position.y = 268;
    biblio8->position.w = 73;
    biblio8->position.h = 10;
    biblio8->nb_interieur = 3;
    biblio8->last_opening = 0;
    biblio8->char_objet_interieur[0] = "images/objets/lampe1.bmp";
    biblio8->char_objet_interieur[1] = "images/objets/lampe2.bmp";
    biblio8->char_objet_interieur[2] = "images/objets/lampe3.bmp";

    biblio9->position.x = 520; 
    biblio9->position.y = 268;
    biblio9->position.w = 73;
    biblio9->position.h = 10;
    biblio9->nb_interieur = 1;
    biblio9->last_opening = 0;
    biblio9->char_objet_interieur[0] = "images/objets/cadre1.bmp";

    biblio10->position.x = 594; 
    biblio10->position.y = 268;
    biblio10->position.w = 73;
    biblio10->position.h = 10;
    biblio10->nb_interieur = 1;
    biblio10->last_opening = 0;
    biblio10->char_objet_interieur[0] = "images/objets/carde2.bmp";

    biblio11->position.x = 667; 
    biblio11->position.y = 268;
    biblio11->position.w = 53;
    biblio11->position.h = 10;
    biblio11->nb_interieur = 1;
    biblio11->last_opening = 0;
    biblio11->char_objet_interieur[0] = "images/objets/cadre1.bmp";

    vase->position.x = 410; 
    vase->position.y = 268;
    vase->position.w = 30;
    vase->position.h = 10;
    vase->nb_interieur = 2;
    vase->last_opening = 0;
    vase->char_objet_interieur[0] = "images/objets/potion.bmp";
    vase->char_objet_interieur[1] = "images/objets/livre.bmp";
 
    plante2->position.x = 742; 
    plante2->position.y = 260;
    plante2->position.w = 60;
    plante2->position.h = 20;
    plante2->nb_interieur = 1;
    plante2->last_opening = 0;
    plante2->char_objet_interieur[0] = "images/objets/plante2.bmp";

    biblio12->position.x = 446; 
    biblio12->position.y = 394;
    biblio12->position.w = 73;
    biblio12->position.h = 10;
    biblio12->nb_interieur = 3;
    biblio12->last_opening = 0;
    biblio12->char_objet_interieur[0] = "images/objets/plante1.bmp";
    biblio12->char_objet_interieur[1] = "images/objets/plante2.bmp";
    biblio12->char_objet_interieur[2] = "images/objets/plante3.bmp";

    biblio13->position.x = 520; 
    biblio13->position.y = 394;
    biblio13->position.w = 73;
    biblio13->position.h = 10;
    biblio13->nb_interieur = 3;
    biblio13->last_opening = 0;
    biblio13->char_objet_interieur[0] = "images/objets/plante5.bmp";;
    biblio13->char_objet_interieur[1] = "images/objets/plante4.bmp";
    biblio13->char_objet_interieur[2] = "images/objets/plante3.bmp";

    biblio14->position.x = 594; 
    biblio14->position.y = 394;
    biblio14->position.w = 73;
    biblio14->position.h = 10;
    biblio14->nb_interieur = 2;
    biblio14->last_opening = 0;
    biblio14->char_objet_interieur[0] = "images/objets/pizza.bmp";
    biblio14->char_objet_interieur[1] = "images/objets/pain.bmp";

    biblio15->position.x = 667; 
    biblio15->position.y = 394;
    biblio15->position.w = 53;
    biblio15->position.h = 10;
    biblio15->nb_interieur = 2;
    biblio15->last_opening = 0;
    biblio15->char_objet_interieur[0] = "images/objets/cadre1.bmp";
    biblio15->char_objet_interieur[1] = "images/objets/livre2.bmp";

    biblio16->position.x = 430; 
    biblio16->position.y = 50;
    biblio16->position.w = 70;
    biblio16->position.h = 20;
    biblio16->nb_interieur = 2;
    biblio16->last_opening = 0;
    biblio16->char_objet_interieur[0] = "images/objets/livre2.bmp";
    biblio16->char_objet_interieur[1] = "images/objets/livre.bmp";
    biblio16->char_objet_interieur[2] = "images/objets/livre3.bmp";

    biblio17->position.x = 560; 
    biblio17->position.y = 50;
    biblio17->position.w = 70;
    biblio17->position.h = 20;
    biblio17->nb_interieur = 3;
    biblio17->last_opening = 0;
    biblio17->char_objet_interieur[0] = "images/objets/livre4.bmp";
    biblio17->char_objet_interieur[1] = "images/objets/livre3.bmp";
    biblio17->char_objet_interieur[2] = "images/objets/livre2.bmp";


    biblio18->position.x = 680; 
    biblio18->position.y = 50;
    biblio18->position.w = 70;
    biblio18->position.h = 20;
    biblio18->nb_interieur = 3;
    biblio18->last_opening = 0;
    biblio18->char_objet_interieur[0] = "images/objets/livre.bmp";
    biblio18->char_objet_interieur[1] = "images/objets/livre2.bmp";
    biblio18->char_objet_interieur[2] = "images/objets/livre3.bmp";
    biblio18->char_objet_interieur[3] = "images/objets/livre4.bmp";

    biblio19->position.x = 30; 
    biblio19->position.y = 30;
    biblio19->position.w = 100;
    biblio19->position.h = 50;
    biblio19->nb_interieur = 3;
    biblio19->last_opening = 0;
    biblio19->char_objet_interieur[0] = "images/objets/mure.bmp";
    biblio19->char_objet_interieur[1] = "images/objets/poire.bmp";
    biblio19->char_objet_interieur[2] = "images/objets/pomme.bmp";
    biblio19->char_objet_interieur[3] = "images/objets/citron.bmp";
}
