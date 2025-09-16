/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32g4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SCI.h"
#include "periodic_services.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc4;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
	  printf("HardFault error! \n");
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32G4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel1 global interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc4);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles USART3 global interrupt / USART3 wake-up interrupt through EXTI line 28.
  */
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */

  /* USER CODE END USART3_IRQn 0 */
  /* USER CODE BEGIN USART3_IRQn 1 */



	if( LL_USART_IsEnabledIT_RXNE_RXFNE(USART3) )		// sploh omogočena prekinitev ob RXNE?
	{
		// Če je prekinitev omogočena, potem preverimo še, če je postavljena ustrezna zastavica.
		if( LL_USART_IsActiveFlag_RXNE_RXFNE(USART3) )	// postavljena zastavica RXNE?
		{
			// Če je ta specifična prekinitev omogočena in če je postavljena zastavica tega specifičnega
			// prekinitvenega dogodka, potem se odzovemo s klicem ustrezne "callback" rutine.

			SCI_receive_byte_Callback();

			// V vednost: zastavica RXNE se zbriše avtomatsko, ko preberemo sprejemni register RDR.
		}
	}


	// V premislek: ker se nahajamo znotraj USART3 splošne prekinitvene rutine (tj. USART3_IRQHandler() ),
	// je popolnoma jasno, da je smiselno preverjati le zastavice enote USART3. Vidite, da tu
	// ne potrebujemo informacije o tem, katera USARTx enota se uporablja - ker je to implicitno določeno:
	// znotraj USART3_IRQHandler() nas seveda zanimajo zastavice vmesnika USART3.





	// ------ Odzivanje na sprostitev oddajnega podatkovnega registra TDR (zastavica TXE = Transmitter Empty) -------

	// Najprej preverimo, če je ta specifična prekinitev sploh omogočena. Uporabimo LL funkcijo.
	if( LL_USART_IsEnabledIT_TXE_TXFNF(USART3) )		// sploh omogočena prekinitev ob TXE?
	{
		// Če je prekinitev omogočena, potem preverimo še, če je postavljena ustrezna zastavica.
		if(  LL_USART_IsActiveFlag_TXE_TXFNF(USART3) )		// postavljena zastavica TXE?
		{
			// Če je ta specifična prekinitev omogočena in če je postavljena zastavica tega specifičnega
			// prekinitvenega dogodka, potem se odzovemo s klicem ustrezne "callback" rutine.

			SCI_transmit_byte_Callback();

			// V vednost: zastavica TXE se zbriše avtomatsko, ko pišemo v oddajni podatkovni register TDR.
		}
	}


		// V premislek: ker se nahajamo znotraj USART3 splošne prekinitvene rutine (tj. USART3_IRQHandler() ),
		// je popolnoma jasno, da je smiselno preverjati le zastavice enote USART3. Vidite, da tu
		// ne potrebujemo informacije o tem, katera USARTx enota se uporablja - ker je to implicitno določeno:
		// znotraj USART3_IRQHandler() nas seveda zanimajo zastavice vmesnika USART3.













  /* USER CODE END USART3_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global interrupt, DAC1 and DAC3 channel underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */
	if(LL_TIM_IsEnabledIT_UPDATE(TIM6))
	{
		if(LL_TIM_IsActiveFlag_UPDATE(TIM6))
		{
			//naredi periodicne stvari
			PSERV_run_services_Callback();

			//tbrise flag za interupt
			LL_TIM_ClearFlag_UPDATE (TIM6);
		}

	}



  /* USER CODE END TIM6_DAC_IRQn 0 */

  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/* USER CODE BEGIN 1 */


//-------------------------------------------------------------------------------


// ******** Prekinitvam je potrebno dodati sistemsko funkcionalnost SCI vmesnika:

// Znotraj prekinitvene rutine USART3_IRQHandler() moramo biti sposobni poklicati,
// t.i. "callback" funkcije za sprejemanje novega podatka oziroma pošiljanje novega
// podatka preko serijskega vmesnika SCI. Te "callback" funkcije so pravzaprav del sistema,
// ki se odziva na prekinitve na strojnem nivoju. Vidite lahko, da tokrat pa
// nižje-nivojski strojni nivo (tj. USART enota) potrebuje storitve
// višjega sistemskega nivoja (tj. medpomnilnikov SCI vmesnika):
//		- ob sprejemu želimo sprejeti podatek shraniti v sistemski SCI RX medpomnilnik
//		- pri pošiljanju podatkov želimo podatke jemati iz sistemskega SCI TX medpomnilnika





// Namig: zgornji "include" stavek umestite v sledeči odsek
//
//		/* USER CODE BEGIN Includes */
//
//		/* USER CODE END Includes */














/* USER CODE END 1 */
