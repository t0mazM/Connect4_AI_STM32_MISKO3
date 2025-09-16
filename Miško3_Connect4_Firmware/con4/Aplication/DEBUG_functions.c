/*
 * DEBUG_functions.c
 *
 *  Created on: 19 Jun 2023
 *  Author: Tomaž Miklavčič
 */


#include "DEBUG_functions.h"

/* Print probabilities for debugging.*/
void DEBUG_printf_nodes(float* probabilities) {
    for (int i = 1; i < 8; i++) {
        int integer = (int)probabilities[i];
        int decimal = (int)(probabilities[i] * 100) % 100;
        printf("Probability[%d] = %d.%02d\n", i, integer, decimal);
    }
}

/* Visualize the contents of the state array (length = 147).*/
void visualize_state(ai_i8 state[147]) {
    int num;

    // First 126 elements
    for (num = 0; num < 126; num++) {
        printf("%d, ", state[num]);
    }
    printf("\nIndex after first block: %d\n", num);

    // Elements [126..132]
    for (num = 126; num < 133; num++) {
        printf("%d, ", state[num]);
    }
    printf("\nIndex after second block: %d\n", num);

    // Elements [133..139]
    for (num = 133; num < 140; num++) {
        printf("%d, ", state[num]);
    }
    printf("\nIndex after third block: %d\n", num);

    // Elements [140..146]
    for (num = 140; num < 147; num++) {
        printf("%d, ", state[num]);
    }
    printf("\nIndex after last block: %d\n", num);
}
