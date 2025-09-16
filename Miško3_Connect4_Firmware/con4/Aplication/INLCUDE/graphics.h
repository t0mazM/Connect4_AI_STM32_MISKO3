/*
 * graphics.h
 *
 *  Created on: 19 Jun 2023
 *      Author: Tomaž
 */

#ifndef INLCUDE_GRAPHICS_H_
#define INLCUDE_GRAPHICS_H_

#define WALL_WITH 5
#define PIECE_RADIUS 17
#define SHIFT_X 0
#define SHIFT_Y -17

void draw_circle(int x0, int y0, int radius, uint16_t piece_colour);
void render_empty_board(void);
void render_pieces(void);
void render_ai_won(void);
void render_human_won(void);
void render_draw(void);
void render_press_any_button(void);

#endif /* INLCUDE_GRAPHICS_H_ */
