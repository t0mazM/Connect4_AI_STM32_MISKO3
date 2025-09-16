#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ai_model.h"
#include "main.h"
/*
 * ai_model.c
 *
 *  Created on: 19 Jun 2023
 *  Author: Tomaž Miklavčič
 */


#include "ai_datatypes_defines.h"
#include "python_model.h"
#include "python_model_data.h"
#include "game.h"
#include "DEBUG_functions.h"

// Input/output buffers
ai_i8 data_in_1[AI_PYTHON_MODEL_IN_1_SIZE_BYTES];
ai_i8 data_out_1[AI_PYTHON_MODEL_OUT_1_SIZE_BYTES];
ai_i8* data_ins[AI_PYTHON_MODEL_IN_NUM] = { data_in_1 };
ai_i8* data_outs[AI_PYTHON_MODEL_OUT_NUM] = { data_out_1 };

// Activation buffer for intermediate calculations
static uint8_t layer1_activation_buffer[AI_PYTHON_MODEL_DATA_ACTIVATION_1_SIZE];
ai_handle activation_buffer[] = { layer1_activation_buffer };

static ai_handle python_model = AI_HANDLE_NULL;
static ai_buffer* ai_input;
static ai_buffer* ai_output;

// ---------------- Private Functions ----------------

static int INIT_AI_Model(ai_handle *act_addr) {
    ai_error err = ai_python_model_create_and_init(&python_model, act_addr, NULL);
    if (err.type != AI_ERROR_NONE) {
        printf("Error initializing AI model\n");
        return -1;
    }

    ai_input = ai_python_model_inputs_get(python_model, NULL);
    ai_output = ai_python_model_outputs_get(python_model, NULL);

    for (int i = 0; i < AI_PYTHON_MODEL_IN_NUM; i++) {
        ai_input[i].data = data_ins[i];
    }
    for (int i = 0; i < AI_PYTHON_MODEL_OUT_NUM; i++) {
        ai_output[i].data = data_outs[i];
    }

    return 0;
}

static int ai_run(void) {
    ai_i32 batch = ai_python_model_run(python_model, ai_input, ai_output);
    if (batch != 1) {
        printf("Error: AI run batch != 1\n");
        return -1;
    }
    return 0;
}

static int choose_highest_node(ai_i8* data[]) {
    float max_value = -1000;
    int move = -1;
    float* probabilities = (float*)data[0];

    for (int i = 0; i < COLS; i++) {
        if (probabilities[i] > max_value && check_if_valid(i)) {
            max_value = probabilities[i];
            move = i;
        }
    }

    if (move == -1) {
        while(1) {
            printf("Error: could not find any valid move\n");
        }
    }

    return move;
}

// ---------------- Public Functions ----------------

void MX_X_CUBE_AI_Init(void) {
    INIT_AI_Model(activation_buffer);
}

int get_action(ai_i8* state) {
    int best_move = -1;

    if (python_model) {
        // Copy state to AI input
        for (int i = 0; i < AI_PYTHON_MODEL_IN_1_SIZE; i++) {
            ((float*)ai_input[0].data)[i] = state[i];
        }

        if (ai_run() == 0) {
            best_move = choose_highest_node(data_outs);
        }
    }

    if (best_move == -1) {
        printf("Failed to get best move\n");
    }

    return best_move;
}
