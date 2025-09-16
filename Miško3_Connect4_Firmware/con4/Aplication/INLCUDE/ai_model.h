
#ifndef __APP_AI_H
#define __APP_AI_H
#ifdef __cplusplus
extern "C" {
#endif

#include "ai_platform.h"

void MX_X_CUBE_AI_Init(void);
int get_action(ai_i8* state);

#ifdef __cplusplus
}
#endif
#endif
