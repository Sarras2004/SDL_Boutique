#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "menu.h"
#include "boutique.h"
#include "inspection.h"

#define MENU_WIDTH 400
#define MENU_HEIGHT 400

// Charge une image "*.bmp" et la converit en texture
SDL_Texture *loadImage(const char adresse[], SDL_Renderer *renderer)
{
    SDL_Surface *stock = NULL;
    SDL_Texture *texture = NULL;
    stock = SDL_LoadBMP(adresse);
    if(stock == NULL)
    {
        printf("Erreur SDL_LoadBMP: %s\n", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, stock);
    SDL_FreeSurface(stock);
    if(texture == NULL)
    {
        printf("Erreur de SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
        return NULL;
    }
    return texture;
}


int menu()
{   bool store = false;
    // Création de la fenêtre et du rendu
    SDL_Window *menu_window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MENU_WIDTH, MENU_HEIGHT, SDL_WINDOW_SHOWN);
    if (!menu_window)
    {
        printf("Erreur SDL_CreateWindow : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *menu_renderer = SDL_CreateRenderer(menu_window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture *texture_menu = loadImage("images/menu/GUI.bmp", menu_renderer);  // prepare la texture pour les boutons
    if(texture_menu == NULL)
    {
        SDL_DestroyRenderer(menu_renderer);
        SDL_DestroyWindow(menu_window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *texture_menu_shiny = loadImage("images/menu/GUI_shiny.bmp", menu_renderer);  // prepare la texture pour les boutons en surbrillance
    if(texture_menu_shiny == NULL)
    {
        SDL_DestroyRenderer(menu_renderer);
        SDL_DestroyWindow(menu_window);
        SDL_Quit();
        return 1;
    }
    // Définir les images des boutons
    SDL_Rect src_play = { 160, 16, 112, 32 }; // x, y, largeur, hauteur
    SDL_Rect src_credits = { 160, 64, 112, 32 };
    SDL_Rect src_exit = { 160, 112, 112, 32 };

    SDL_Rect menu_play = { MENU_WIDTH/2 - src_play.w/2 - 50, MENU_HEIGHT/2 - 5*src_play.h, 224, 96 }; // x, y, largeur, hauteur
    SDL_Rect menu_credits = { MENU_WIDTH/2 - src_play.w/2 - 50, MENU_HEIGHT/2 - 3*src_play.h/2, 224, 96 };
    SDL_Rect menu_exit = { MENU_WIDTH/2 - src_play.w/2 - 50, MENU_HEIGHT/2 + 2*src_play.h, 224, 96 };


    bool running = true;
    bool cred = true;
    SDL_Event event;

    while (running)
    {
        // Gestion des événements
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT){
                running = false;
            }
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            SDL_SetRenderDrawColor(menu_renderer, 0, 0, 0, 255);
            SDL_RenderClear(menu_renderer);

            if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &menu_play)){
                SDL_RenderCopy(menu_renderer, texture_menu_shiny, &src_play, &menu_play);
                //SDL_RenderCopy(menu_renderer, texture_menu, &src_credits, &menu_credits);
                SDL_RenderCopy(menu_renderer, texture_menu, &src_exit, &menu_exit);

            }
            else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &menu_credits)){
                SDL_RenderCopy(menu_renderer, texture_menu, &src_play, &menu_play);
                //SDL_RenderCopy(menu_renderer, texture_menu_shiny, &src_credits, &menu_credits);
                SDL_RenderCopy(menu_renderer, texture_menu, &src_exit, &menu_exit);
            }
            else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &menu_exit)){
                SDL_RenderCopy(menu_renderer, texture_menu, &src_play, &menu_play);
                //SDL_RenderCopy(menu_renderer, texture_menu, &src_credits, &menu_credits);
                SDL_RenderCopy(menu_renderer, texture_menu_shiny, &src_exit, &menu_exit);
            }
            else{
                SDL_RenderCopy(menu_renderer, texture_menu, &src_play, &menu_play);
                //SDL_RenderCopy(menu_renderer, texture_menu, &src_credits, &menu_credits);
                SDL_RenderCopy(menu_renderer, texture_menu, &src_exit, &menu_exit);
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) 
            {
                int x = event.button.x;
                int y = event.button.y;
                if (SDL_PointInRect(&(SDL_Point){x, y}, &menu_play))
                {
                    running = false;
                    store = true;
                } 
                else if (SDL_PointInRect(&(SDL_Point){x, y}, &menu_credits))
                {

                } 
                else if (SDL_PointInRect(&(SDL_Point){x, y}, &menu_exit))
                {
                    running = false;  
                    store = false;
                }
            }
        }


        // Dessin des boutons
        SDL_RenderPresent(menu_renderer);
    }
    // Libération des ressources
    SDL_DestroyTexture(texture_menu);
    SDL_DestroyRenderer(menu_renderer);
    SDL_DestroyWindow(menu_window);
    SDL_Quit();

    if(store == true) boutique();
    
    return 0;
}