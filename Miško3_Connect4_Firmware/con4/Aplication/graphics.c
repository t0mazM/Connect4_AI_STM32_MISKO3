/*
 * graphics.c
 *
 *  Created on: 19 Jun 2023
 *  Author: Tomaž Miklavčič
 */

#include <stdio.h>
#include <stdlib.h>

#include "lcd.h"
#include "graphics.h"
#include "game.h"
#include "images.h"
#include "ugui.h"

// ------------------- Helpers ---------------------

static void clear_screen(uint16_t colour) {
    ILI9341_SetDisplayWindow(0, 0, 320, 240);
    for (int i = 0; i < 320 * 240; i++) {
        ILI9341_SendData(&colour, 1);
    }
}

static void render_text(int x, int y, const char* text, const UG_FONT* font, uint16_t colour) {
    UG_FontSelect(font);
    UG_SetForecolor(colour);
    UG_PutString(x, y, text);
}

// ------------------- Drawing ---------------------

void draw_circle(int x0, int y0, int radius, uint16_t piece_colour) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y < radius * radius) {
                ILI9341_SetDisplayWindow(x0 + x, y0 + y, 1, 1);
                ILI9341_SendData(&piece_colour, 1);
            }
        }
    }
}

// ------------------- Rendering ---------------------

void render_pieces(void) {
    int step = (WALL_WITH + PIECE_RADIUS * 2);

    for (int row = ROWS - 1; row >= 0; row--) {
        for (int col = 0; col < COLS; col++) {
            int row_multi = ROWS - row;
            int col_multi = col + 1;

            int piece = game.board[row][col];
            uint16_t colour;

            // Choose colour based on piece type
            if (piece == game.PLAYER_EMPTY) {
                colour = game.empty_colour;
            } else if (piece == game.PLAYER_HUMAN) {
                colour = game.human_colour;
            } else if (piece == game.PLAYER_AI) {
                colour = game.ai_colour;
            } else if (piece == game.PLAYER_PREMOVE) {
                colour = game.premove_colour;
            } else {
                printf("Error in render -> unknown piece\n");
                HAL_Delay(5000);
                continue;
            }

            // Draw the circle at the right spot
            draw_circle(col_multi * step + SHIFT_X,
                        row_multi * step + SHIFT_Y,
                        PIECE_RADIUS,
                        colour);
        }
    }
}


void render_empty_board() {
    clear_screen(game.board_colour);
}

void render_ai_won() {
    clear_screen(C_BLACK);

    ILI9341_SetDisplayWindow(0, 240 - AI_WON_HEIGHT, AI_WON_WIDTH, AI_WON_HEIGHT);
    ILI9341_SendData((LCD_IO_Data_t*)ai_won, AI_WON_WIDTH * AI_WON_HEIGHT);

    render_text(25, 10, "Judgement day is\nupon you humans!", &FONT_16X26, C_WHITE);
}

void render_human_won() {
    clear_screen(C_BLACK);

    ILI9341_SetDisplayWindow(0, 55, HUMAN_WON_WIDTH, HUMAN_WON_HEIGHT);
    ILI9341_SendData((LCD_IO_Data_t*)human_won, HUMAN_WON_WIDTH * HUMAN_WON_HEIGHT);

    render_text(10, 0, "THAT FEELING, WHEN\n YOU BEAT THE AI:", &FONT_16X26, C_WHITE);
    render_text(60, 212, "AM I THE AI?", &FONT_16X26, C_WHITE);
}

void render_draw() {
    clear_screen(C_BLACK);

    ILI9341_SetDisplayWindow(0, 240 - DRAW_HEIGHT, DRAW_WIDTH, DRAW_HEIGHT);
    ILI9341_SendData((LCD_IO_Data_t*)draw, DRAW_WIDTH * DRAW_HEIGHT);

    render_text(15, 0, "GOOD GAME, HUMAN", &FONT_16X26, C_WHITE);
}

void render_press_any_button() {
    render_text(40, 150, "PRESS ANY BUTTON TO CONTINUE", &FONT_8X12, C_WHITE);
}
