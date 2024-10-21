#include "g_interface.h"
#include "board.h"
#include "maingame.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <assert.h>


// Ensure that the player returned can play
char getNextPLayerVerified(char player, board_t* b, int* resultat_de_p, int* round){
    *resultat_de_p = de();
    char np = getNextPlayer(player, round);
    if (peut_joueur_deplacer_ligne(b, *resultat_de_p)){
        return np;
    }
    return getNextPLayerVerified(np, b, resultat_de_p, round);
}


char getNextPlayer(char player, int* round){
    if (player == 'a' + NB_JOUEURS - 1){
        (*round)++;
        return 'a';
    }
    return player + 1;
}


void exit_sdl(int nb_free, SDL_Texture* to_free[], SDL_Window* window, SDL_Renderer* render){
    for (int i = 0; i < nb_free; i++){
        if (to_free[i] != NULL)
            SDL_DestroyTexture(to_free[i]);
    }
    if (render != NULL)
        SDL_DestroyRenderer(render);
    if (window != NULL)
        SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_SUCCESS);
}


SDL_Texture* load_image(const char* path, SDL_Renderer* render, SDL_Window* window){
    SDL_Surface* image = SDL_LoadBMP(path);
    if (image == NULL){
        fprintf(stderr, "[*] Failed to open %s with error : %s\n", path, SDL_GetError());
        exit_sdl(0, NULL, window, render);
    }
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(render, image);
    if (image_texture == NULL){
        fprintf(stderr, "[*] Failed to open %s with error : %s\n", path, SDL_GetError());
        exit_sdl(0, NULL, window, render);
    }
    SDL_FreeSurface(image);
    return image_texture;
}


void run_game(){

    if(SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0){
        fprintf(stderr, "[*] Failed to intialise SDL2: %s\n", SDL_GetError());
    }
    printf("[*] Sucessfully initialised SDL2\n");

    if(TTF_Init() != 0){
        fprintf(stderr, "[*] Failed to intialise TTF: %s\n", SDL_GetError());
    }
    printf("[*] Sucessfully initialised TTF\n");

    SDL_Window* window = SDL_CreateWindow("Igel Ärgern", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL){
        fprintf(stderr, "[*] Failed to create the window with error: %s\n", SDL_GetError());
        exit_sdl(0, NULL, NULL, NULL);
    }
    printf("[*] Sucessfully created the window\n");
    SDL_ShowWindow(window);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        fprintf(stderr, "[*] Failed to create the renderer with error: %s\n", SDL_GetError());
        exit_sdl(0, NULL, window, NULL);
    }
    printf("[*] Sucessfully created the renderer\n");

    SDL_Texture* images_tab[NB_IMAGES] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    /*In images tab we have 
    0 : board image
    1 : red hedgehog image
    2 : blue hedgehog image
    3 : green hedgehog image
    4 : purple hedgehog image
    5 : red token image
    6 : blue token image
    7 : green token image
    8 : red token image
    */

    images_tab[0] = load_image(BOARD_BMP_PATH, renderer, window);
    images_tab[1] = load_image(RED_HG_BMP_PATH, renderer, window);
    images_tab[2] = load_image(BLUE_HG_BMP_PATH, renderer, window);
    images_tab[3] = load_image(GREEN_HG_BMP_PATH, renderer, window);
    images_tab[4] = load_image(PURPLE_HG_BMP_PATH, renderer, window);
    images_tab[5] = load_image(RED_TOKEN_HG_BMP_PATH, renderer, window);
    images_tab[6] = load_image(BLUE_TOKEN_HG_BMP_PATH, renderer, window);
    images_tab[7] = load_image(GREEN_TOKEN_HG_BMP_PATH, renderer, window);
    images_tab[8] = load_image(PURPLE_TOKEN_HG_BMP_PATH, renderer, window);


    board_t board;
    init_board(&board);
    initialize_game(&board);
    
    int row = 0;
    int line = 0;

    int finishedHedgehogs[NB_JOUEURS];
    char winners[NB_JOUEURS];

    for(int i = 0; i < NB_JOUEURS; i++){
        finishedHedgehogs[i] = 0;
        winners[i] = '0';
    }     

    SDL_Event event;
    bool quit = false;

    int resultat_de = de();
    int round = 0;
    int finished_round = -1;

    char player = 'a';
    if (!peut_joueur_deplacer_ligne(&board, resultat_de)) 
        player = getNextPLayerVerified(player, &board, &resultat_de, &round);

    int phase = 0;
    /* To help distinguish between each different phases of a player round
        0 : go up/down a hedgehog
        1 : make a hedgehog go forward
        2 : the final round is done
    */

   int way = 1;
   /* To indicate in which way should the hedgehog move
        1 : down
        -1 : up
   */

   bool asked = true;

    while(!quit)
    {
        while(SDL_PollEvent(&event)){
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            if (line > 0)
                                line--;
                            break;
                        case SDLK_DOWN:
                            if (line < NB_LINE - 1)
                                line++;
                            break;
                        case SDLK_LEFT:
                            if (row > 0)
                                row--;
                            break;
                        case SDLK_RIGHT:
                            if (row < NB_ROW - 1)
                                row++;
                            break;
                        case SDLK_u:
                            if (asked){
                                way = 0;
                            }
                            break;
                        case SDLK_d:
                            if (asked){
                                way = 1;
                            }
                            break;
                        case SDLK_n:
                            if (asked){
                                if (!peut_joueur_deplacer_ligne(&board, resultat_de))
                                    player = getNextPLayerVerified(player, &board, &resultat_de, &round);
                                asked = false;
                                phase++;
                            }
                            break;
                        case SDLK_SPACE:
                            if (phase == 0 && 0 < line + way && line + way < NB_LINE){
                                if (board_height(&board, line, row) > 0 && board_top(&board, line, row) == player && move_hedgehog(&board, line, row, line + 1, row)){
                                    if (!peut_joueur_deplacer_ligne(&board, resultat_de)) 
                                        player = getNextPLayerVerified(player, &board, &resultat_de, &round);
                                    phase++;
                                    asked = false;
                                }
                            }
                            else if (phase == 1 && row + 1 < NB_ROW  && resultat_de == line && move_hedgehog(&board, line, row, line, row + 1)){
                                if (row + 1 == NB_ROW - 1)
                                    finishedHedgehogs[board_top(&board, line, row + 1) - 'a']++;
                                if (get_winner_right(finishedHedgehogs, winners)){
                                    if (finished_round == -1){
                                        finished_round = round;
                                    }
                                }
                                player = getNextPLayerVerified(player, &board, &resultat_de, &round);
                                if (finished_round != -1 && round > finished_round){
                                    phase = 2;
                                }
                                if (phase != 2){
                                    phase = 0;
                                    asked = true;
                                }
                            }
                            break;
                    }
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
            }
            display_board(&board, window, renderer, row, line, images_tab, player, resultat_de, asked, phase, finishedHedgehogs, winners);
        }
    }   

    SDL_DestroyWindow(window);
    printf("[*] Window exited sucessfully!!\n");
    exit_sdl(NB_IMAGES, images_tab, window, renderer);
}


bool move_hedgehog(board_t* b, int line_src, int row_src, int line_dest, int row_dest){
    assert(line_src < NB_LINE && row_src < NB_ROW && line_dest < NB_LINE && row_dest < NB_ROW);
    if (board_height(b, line_src, row_src) > 0 && row_src != NB_ROW - 1){
        if((board_height(b, line_src, row_src) == 1 && allow_trapped_move(b, line_src, row_src)) || board_height(b, line_src, row_src) > 1){
            board_push(b, line_dest, row_dest, board_pop(b, line_src, row_src));
            return true;
        }
    }
    return false;
}


void clear_renderer(SDL_Renderer* renderer, SDL_Window* window, SDL_Texture* imgs[]){
    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0) != 0){
        fprintf(stderr, "[*] Failed to clear the renderer : %s\n", SDL_GetError());
        exit_sdl(NB_IMAGES, imgs, window, renderer); 
    }

    if (SDL_RenderClear(renderer)){
        fprintf(stderr, "[*] Failed to clear the renderer : %s\n", SDL_GetError());
        exit_sdl(NB_IMAGES, imgs, window, renderer);   
    }
}


void display_hedgehog(board_t* b, SDL_Window* window, SDL_Renderer* renderer, int i, int j, SDL_Texture* imgs[], int pos){
    static int step = 15;

    SDL_Rect hg_pos;
    hg_pos.h = HEDGEHOG_HEIGHT;
    hg_pos.w = HEDGEHOG_WIDTH;
    hg_pos.x = 130 + 140*j - step*pos; // column
    hg_pos.y = 130 + 125*i; // line
    if (SDL_RenderCopy(renderer, imgs[board_peek(b, i, j, pos) - 'a' + 1], NULL, &hg_pos)){
        fprintf(stderr, "[*] Failed to render an hedgehog : %s\n", SDL_GetError());
        exit_sdl(NB_IMAGES, imgs, window, renderer);
    }
}


void display_token(board_t* b, SDL_Window* window, SDL_Renderer* renderer, int i, int j, SDL_Texture* imgs[], char player){
    SDL_Rect token_pos;
    token_pos.h = TOKEN_HEIGHT;
    token_pos.w = TOKEN_WIDTH;
    token_pos.x = 110 + 140*j; // column
    token_pos.y = 120 + 125*i; // line
    if (SDL_RenderCopy(renderer, imgs[5 + player - 'a'], NULL, &token_pos)){
        fprintf(stderr, "[*] Failed to render the token : %s\n", SDL_GetError());
        exit_sdl(NB_IMAGES, imgs, window, renderer);
    }
}


void display_text(board_t* b, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* imgs[], const char* text, int i, int j, int h, int w){
    TTF_Font* font = TTF_OpenFont(FONT_FILE, 20);
    static SDL_Color black = {0, 0, 0, 255};
    if (font == NULL){
        fprintf(stderr, "[*] Failed to open the font: %s\n", TTF_GetError());
        exit_sdl(NB_IMAGES, imgs, window, renderer);
    }  

    SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, black);
    if (text_surface == NULL){
        fprintf(stderr, "[*] Failed bind text to surface: %s\n", SDL_GetError());
        exit_sdl(NB_IMAGES, imgs, window, renderer);
    }
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (text_texture == NULL){
        SDL_FreeSurface(text_surface);
        fprintf(stderr, "[*] Failed bind a texture to the surface: %s\n", SDL_GetError());
        exit_sdl(NB_IMAGES, imgs, window, renderer);
    }
    SDL_FreeSurface(text_surface);

    SDL_Rect texRect;
    texRect.h = h;
    texRect.w = w;

    texRect.x = j;
    texRect.y = i;
    if (SDL_RenderCopy(renderer, text_texture, NULL, &texRect)){
        fprintf(stderr, "[*] Failed to render the text : %s\n", SDL_GetError());
        exit_sdl(NB_IMAGES, imgs, window, renderer);
    }
}


void display_board(board_t* b, SDL_Window* window, SDL_Renderer* renderer, int cursor_row, int cursor_line, SDL_Texture* imgs[], char player, int resultat_de, bool asked, int phase, int* finishedHg, char* winners){
    clear_renderer(renderer, window, imgs);

    if (SDL_RenderCopy(renderer, imgs[0], NULL, NULL) != 0){
        fprintf(stderr, "[*] Failed to bind the board image to the window : %s\n", SDL_GetError());
        exit_sdl(NB_IMAGES, imgs, window, renderer);
    }

    for (int i = 0; i < NB_LINE; i++){
        for(int j = 0; j < NB_ROW; j++){
            if (board_height(b, i, j) > 2){
                display_hedgehog(b, window, renderer, i, j, imgs, 2);
                display_hedgehog(b, window, renderer, i, j, imgs, 1);
                display_hedgehog(b, window, renderer, i, j, imgs, 0);
            }
            else if (board_height(b, i, j) == 2){
                display_hedgehog(b, window, renderer, i, j, imgs, 1);
                display_hedgehog(b, window, renderer, i, j, imgs, 0);
            }
            else if(board_height(b, i, j) == 1){
                display_hedgehog(b, window, renderer, i, j, imgs, 0);
            }
        }
    }
    display_token(b, window, renderer, cursor_line, cursor_row, imgs, player);

    if (asked){
        display_text(b, window, renderer, imgs, "Type 'n' to skip line movement", 50, 300, 60, 1000);
    }
    else if(phase == 1){
        display_text(b, window, renderer, imgs, "Move an hedgehog on the line selected by the dice", 50, 300, 60, 1000);
    }
    else if(phase == 2){
        display_text(b, window, renderer, imgs, "Game is finished here is the leaderboard:", 50, 300, 60, 1000);
        int rank = 1;
        char t_hg[23];
        sprintf(t_hg, "[%d] %c (%d hedgehog(s))\n", rank, winners[0], finishedHg[winners[0] - 'a']);
        display_text(b, window, renderer, imgs, t_hg, 150, 300, 50, 1000);
        for(int i = 1; i < NB_JOUEURS; i++){
            if (finishedHg[winners[i] - 'a'] != finishedHg[winners[i - 1] - 'a'])
                rank++;
            sprintf(t_hg, "[%d] %c (%d hedgehog(s))\n", rank, winners[i], finishedHg[winners[i] - 'a']);
            display_text(b, window, renderer, imgs, t_hg, 150 + 70*i, 300, 50, 1000);
        }
    }
    
    char t_rd[18];
    sprintf(t_rd, "Dice: %d", resultat_de + 1);

    display_text(b, window, renderer, imgs, t_rd, 900, 510, 100, 300);

    SDL_RenderPresent(renderer);
}