/*
 * DEBUG_functions.h
 *
 *  Created on: 12. Jul 2023
 *      Author: Tomaž
 */

#include <stdio.h>
#include <stdlib.h>
#include "ai_model.h"

#ifndef INLCUDE_DEBUG_FUNCTIONS_H_
#define INLCUDE_DEBUG_FUNCTIONS_H_

void DEBUG_printf_nodes(float* probabilities);
void visualize_state(ai_i8 state[147]);

#endif /* INLCUDE_DEBUG_FUNCTIONS_H_ */
