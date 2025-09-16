

/*
 * Functions for the game.
 * The logic is handled in main_project

*/

#include "ai_model.h"

#ifndef GAME_H
#define GAME_H

#define  ROWS 6
#define  COLS 7



//struct where i keep all variables for the game
typedef struct {
    int board[ROWS][COLS];

    int PLAYER_EMPTY ;
    int PLAYER_AI ;
    int PLAYER_HUMAN;
    int PLAYER_PREMOVE;

    uint16_t board_colour;
    uint16_t empty_colour;
    uint16_t human_colour;
    uint16_t ai_colour;
    uint16_t premove_colour;

} Connect4;

//making the game struct global across .c files
extern Connect4 game;




void reset_board(void);
void printf_render();
int make_move(int move_col, int player);
int subtract_move(int col);
int got_human_move(int* human_move );
void delete_pre_move(void);
int got_ai_move(ai_i8 state[147], int*move);
int check_win(int player);
int check_draw(void);
int check_if_valid(int move_col);
int get_state(ai_i8* state);

#endif /* GAME_H */
