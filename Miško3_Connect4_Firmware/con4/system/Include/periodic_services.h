/*
 * periodic_services.h
 *
 *  Created on: Apr 19, 2023
 *      Author: Vaje
 */

#ifndef INCLUDE_PERIODIC_SERVICES_H_
#define INCLUDE_PERIODIC_SERVICES_H_

// void LL_TIM_EnableCounter(TIM_TypeDef *TIMx)
// void LL_TIM_EnableIT_UPDATE(TIM_TypeDef *TIMx)
// void LL_TIM_DisableIT_UPDATE(TIM_TypeDef *TIMx)
// uint32_t LL_TIM_IsEnabledIT_UPDATE(TIM_TypeDef *TIMx)
// uint32_t LL_TIM_IsActiveFlag_UPDATE(TIM_TypeDef *TIMx)
// void LL_TIM_ClearFlag_UPDATE(TIM_TypeDef *TIMx)

#include "stm32g4xx_ll_tim.h"




void PSERV_init(void);
void PSERV_enable(void);
void PSERV_disable(void);
void PSERV_run_services_Callback(void);

#endif /* INCLUDE_PERIODIC_SERVICES_H_ */
