/*
 * game.c
 *
 *  Created on: 19 Jun 2023
 *  Author: Tomaž Miklavčič
 */



#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include "kbd.h"
#include "ai_model.h"
#include "ugui.h"
#include "game.h"
#include "graphics.h"


Connect4 game = {
    .board = {{0}},
    .PLAYER_EMPTY   = 0,
    .PLAYER_AI      = 1,
    .PLAYER_HUMAN   = 2,
    .PLAYER_PREMOVE = 3,

    .board_colour   = C_BLUE,
    .empty_colour   = C_BEIGE,
    .human_colour   = C_RED,
    .ai_colour      = C_YELLOW,
    .premove_colour = C_LIGHT_CORAL
};

/* Reset the board: fill all cells with empty (0) */
void reset_board() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            game.board[i][j] = game.PLAYER_EMPTY;
        }
    }
}

/* Print the board in text form (for debugging) */
void printf_render() {
    // Print from top row (ROW-1) downwards
    for (int row = ROWS - 1; row >= 0; row--) {
        printf("|");

        for (int col = 0; col < COLS; col++) {
            if (game.board[row][col] == game.PLAYER_EMPTY) {
                printf(" |");  // empty cell
            } else {
                printf("%d|", game.board[row][col]);  // occupied cell
            }
        }
        printf("\n");
    }
    printf(" 1 2 3 4 5 6 7\n");
}

/* Check if a column is valid (not full) */
int check_if_valid(int col) {
    return (game.board[ROWS - 1][col] == game.PLAYER_EMPTY);
}

/* Place a piece in the given column for the given player */
int make_move(int col, int player) {
    if (check_if_valid(col)) {
        for (int row = 0; row < ROWS; row++) {
            if (game.board[row][col] == game.PLAYER_EMPTY) {
                game.board[row][col] = player;
                return 1;  // success
            }
        }
    } else {
        printf("Error in make_move: column %d is full\n", col);
    }
    return 0;  // failure
}

/* Undo the most recent move in a column */
int subtract_move(int col) {
    if (game.board[ROWS - 1][col] != game.PLAYER_EMPTY) {
        game.board[ROWS - 1][col] = game.PLAYER_EMPTY;
        return 1;
    }

    for (int row = 0; row < ROWS; row++) {
        if (game.board[row][col] == game.PLAYER_EMPTY) {
            game.board[row - 1][col] = game.PLAYER_EMPTY;
            return 1;
        }
    }

    printf("Error in subtract_move!\n");
    return 0;
}

/* Get human move from keyboard input */
int got_human_move(int* human_move) {
    /*
     * If OK is pressed → return 1 and save move
     * Otherwise → update pre-move cursor and return 0
     */
    buttons_enum_t pressed_key = KBD_get_pressed_button();

    switch (pressed_key) {
        case BTN_LEFT:
            (*human_move)--;
            break;
        case BTN_RIGHT:
            (*human_move)++;
            break;
        case BTN_OK:
            delete_pre_move();
            KBD_flush();
            return 1;
        default:
            break;
    }

    // Delete previous pre-move
    delete_pre_move();

    // Keep human_move within [0..6], skip full columns
    for (int i = 0; i < COLS; i++) {
        if (*human_move < 0) {
            *human_move = COLS - 1;
        } else if (*human_move >= COLS) {
            *human_move = 0;
        }

        if (check_if_valid(*human_move)) {
            break;  // found valid move
        } else {
            (*human_move)++;
        }
    }

    // Place pre-move and render
    make_move(*human_move, game.PLAYER_PREMOVE);
    render_pieces();

    return 0;  // OK not pressed
}

/* Remove all pre-moves from the board */
void delete_pre_move(void) {
    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            if (game.board[row][col] == game.PLAYER_PREMOVE) {
                game.board[row][col] = game.PLAYER_EMPTY;
            }
        }
    }
}

/* Check if a player has won */
int check_win(int player) {
    // Horizontal
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS - 3; col++) {
            if (game.board[row][col]     == player &&
                game.board[row][col + 1] == player &&
                game.board[row][col + 2] == player &&
                game.board[row][col + 3] == player) {
                return 1;
            }
        }
    }

    // Vertical
    for (int row = 0; row < ROWS - 3; row++) {
        for (int col = 0; col < COLS; col++) {
            if (game.board[row][col]     == player &&
                game.board[row + 1][col] == player &&
                game.board[row + 2][col] == player &&
                game.board[row + 3][col] == player) {
                return 1;
            }
        }
    }

    // Diagonal ↘
    for (int row = 0; row < ROWS - 3; row++) {
        for (int col = 0; col < COLS - 3; col++) {
            if (game.board[row][col]     == player &&
                game.board[row + 1][col + 1] == player &&
                game.board[row + 2][col + 2] == player &&
                game.board[row + 3][col + 3] == player) {
                return 1;
            }
        }
    }

    // Diagonal ↗
    for (int row = ROWS - 1; row >= 3; row--) {
        for (int col = 0; col < COLS - 3; col++) {
            if (game.board[row][col]     == player &&
                game.board[row - 1][col + 1] == player &&
                game.board[row - 2][col + 2] == player &&
                game.board[row - 3][col + 3] == player) {
                return 1;
            }
        }
    }

    return 0;  // no winner yet
}

/* Check if the board is full → draw */
int check_draw(void) {
    for (int col = 0; col < COLS; col++) {
        if (game.board[ROWS - 1][col] == game.PLAYER_EMPTY) {
            return 0;  // still space left
        }
    }
    printf("Draw\n");
    return 1;
}

/* Convert current board state into feature vector for AI */
int get_state(ai_i8* state) {
    int i = 0;

    // Encode board (one-hot: empty, AI, human)
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (game.board[row][col] == game.PLAYER_EMPTY) {
                state[i]   = 1; state[i+1] = 0; state[i+2] = 0;
            } else if (game.board[row][col] == game.PLAYER_AI) {
                state[i]   = 0; state[i+1] = 1; state[i+2] = 0;
            } else if (game.board[row][col] == game.PLAYER_HUMAN) {
                state[i]   = 0; state[i+1] = 0; state[i+2] = 1;
            }
            i += 3;
        }
    }

    // Encode valid moves
    for (int col = 0; col < COLS; col++) {
        state[i++] = check_if_valid(col) ? 1 : 0;
    }

    // Encode blocking moves
    for (int col = 0; col < COLS; col++) {
        if (check_if_valid(col)) {
            make_move(col, game.PLAYER_HUMAN);
            state[i] = check_win(game.PLAYER_HUMAN) ? 1 : 0;
            subtract_move(col);
        } else {
            state[i] = 0;
        }
        i++;
    }

    // Encode winning moves
    for (int col = 0; col < COLS; col++) {
        if (check_if_valid(col)) {
            make_move(col, game.PLAYER_AI);
            state[i] = check_win(game.PLAYER_AI) ? 1 : 0;
            subtract_move(col);
        } else {
            state[i] = 0;
        }
        i++;
    }

    return 1;
}
