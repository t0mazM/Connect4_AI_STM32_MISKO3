/*
 * state_machine.c
 *
 *  Created on: 7. June 2023
 *      Author: Tomaž Miklavčič
 */
#include <stdio.h>
#include <stdlib.h>

#include "state_machine.h"
#include "kbd.h"
#include "game.h"
#include "ai_model.h"
#include "graphics.h"
#include "ugui.h"
#include "images.h"
#include "timing_utils.h"

typedef enum GAME_states {
    GAME_INTRO_STATE,
    GAME_PLAY_STATE,
    GAME_OVER_STATE,
} GAME_states_t;

typedef enum GAMEPLAY_states {
    GAMEPLAY_INIT,
    GAMEPLAY_HUMAN_MOVE,
    GAMEPLAY_AI_MOVE
} GAMEPLAY_states_t;

typedef enum GAMEOVER_states {
    GAMEOVER_SET_TIMER,
    GAMEOVER_WAIT_BEFORE_END_IMAGE_RENDER,
    GAMEOVER_SHOW_PIC,
    GAMEOVER_WAIT_BEFORE_BUTTON_PRESS,
    GAMEOVER_RENDER_PRESS_ANY_BUTTON,
    GAMEOVER_PRESS_BUTTON
} GAMEOVER_states_t;

typedef enum GAME_RESULT {
    HUMAN_WON,
    AI_WON,
    DRAW
} game_result_t;

// Prototypes
static int Intro(void);
static int GamePlay(game_result_t* game_result);
static int GameOver(game_result_t* game_result);

// Helper function: check game over conditions
static int check_update_game_result(game_result_t* game_result) {
    if (check_win(game.PLAYER_HUMAN)) {
        *game_result = HUMAN_WON;
        return 1;
    } else if (check_win(game.PLAYER_AI)) {
        *game_result = AI_WON;
        return 1;
    } else if (check_draw()) {
        *game_result = DRAW;
        return 1;
    }
    return 0;
}

void Game(void) {
    static int state = GAME_INTRO_STATE;
    static game_result_t game_result = HUMAN_WON;
    static int exit_value = 0;

    switch (state) {
        case GAME_INTRO_STATE:
            exit_value = Intro();
            if (exit_value) state = GAME_PLAY_STATE;
            break;

        case GAME_PLAY_STATE:
            exit_value = GamePlay(&game_result);
            if (exit_value) state = GAME_OVER_STATE;
            break;

        case GAME_OVER_STATE:
            exit_value = GameOver(&game_result);
            if (exit_value) state = GAME_INTRO_STATE;
            break;

        default:
            printf("Game(): Error - undefined state (%d)\n", state);
            HAL_Delay(5000);
            state = GAME_INTRO_STATE;
            exit_value = 0;
            break;
    }
}

static int Intro(void) {
    printf("Hello. Let's play a game \n");
    reset_board();
    render_empty_board();
    printf_render();
    return 1;
}

static int GamePlay(game_result_t *game_result) {
    static GAMEPLAY_states_t state = GAMEPLAY_INIT;
    static int human_move = 0;
    int ai_move = -1;
    ai_i8 board_state[147]; // reduced from 1000

    int exit_value = 0;

    switch (state) {
        case GAMEPLAY_INIT:
            KBD_flush();
            reset_board();
            render_empty_board();
            state = GAMEPLAY_AI_MOVE;
            break;

        case GAMEPLAY_HUMAN_MOVE:
            if (got_human_move(&human_move)) {
                make_move(human_move, game.PLAYER_HUMAN);
                state = GAMEPLAY_AI_MOVE;

                render_pieces();
                printf_render();

                exit_value = check_update_game_result(game_result);
            }
            break;

        case GAMEPLAY_AI_MOVE:
            get_state(board_state);
            ai_move = get_action(board_state);
            make_move(ai_move, game.PLAYER_AI);

            render_pieces();
            printf_render();

            if (!check_update_game_result(game_result)) {
                state = GAMEPLAY_HUMAN_MOVE;
            } else {
                exit_value = 1;
            }
            break;
    }
    return exit_value;
}

static int GameOver(game_result_t* game_result) {
    static GAMEOVER_states_t state = GAMEOVER_SET_TIMER;
    static stopwatch_handle_t stopwatch;
    #define DELAY_BEFORE_PIC_RENDER 2000
    #define DELAY_BEFORE_PRESS_ANY_BUTTON 3000

    int exit_value = 0;

    switch (state) {
        case GAMEOVER_SET_TIMER:
            TIMUT_stopwatch_set_time_mark(&stopwatch);
            state = GAMEOVER_WAIT_BEFORE_END_IMAGE_RENDER;
            break;

        case GAMEOVER_WAIT_BEFORE_END_IMAGE_RENDER:
            if (TIMUT_stopwatch_has_X_ms_passed(&stopwatch, DELAY_BEFORE_PIC_RENDER)) {
                state = GAMEOVER_SHOW_PIC;
            }
            break;

        case GAMEOVER_SHOW_PIC:
            TIMUT_stopwatch_set_time_mark(&stopwatch);
            switch (*game_result) {
                case HUMAN_WON: render_human_won(); break;
                case AI_WON: render_ai_won(); break;
                case DRAW: render_draw(); break;
            }
            state = GAMEOVER_WAIT_BEFORE_BUTTON_PRESS;
            break;

        case GAMEOVER_WAIT_BEFORE_BUTTON_PRESS:
            if (TIMUT_stopwatch_has_X_ms_passed(&stopwatch, DELAY_BEFORE_PRESS_ANY_BUTTON)) {
                state = GAMEOVER_RENDER_PRESS_ANY_BUTTON;
            }
            break;

        case GAMEOVER_RENDER_PRESS_ANY_BUTTON:
            render_press_any_button();
            state = GAMEOVER_PRESS_BUTTON;
            break;

        case GAMEOVER_PRESS_BUTTON:
            if (KBD_any_button_been_pressed()) {
                KBD_flush();
                state = GAMEOVER_SET_TIMER;
                exit_value = 1;
            }
            break;

        default:
            printf("Undefined state in GAMEOVER! Restarting\n");
            state = GAMEOVER_SET_TIMER;
            exit_value = 1;
            break;
    }
    return exit_value;
}
