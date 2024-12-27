#include "stm32g030xx.h"
#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_gpio.h"
#include "system_stm32g0xx.h"

#include <FreeRTOS.h>
#include <task.h>

void GPIO_PA4_Init();
void SystemClock_Config(void);
void emptyTask(void *pvParameters);
void blink(void *pvParameters);

int main() {
  HAL_Init();
  SystemClock_Config();
  SystemCoreClockUpdate();
  GPIO_PA4_Init();
  if (SystemCoreClock == 160000UL) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
    HAL_Delay(100);
  }

  xTaskCreate(emptyTask,                // Task function
              "Task 1",                 // Task name (for debugging)
              configMINIMAL_STACK_SIZE, // Stack size (in words, not bytes)
              NULL,                     // Parameters passed to the task
              1,                        // Task priority
              NULL                      // Task handle (not used here)
  );

  xTaskCreate(blink,    // Task function
              "Task 2", // Task name
              configMINIMAL_STACK_SIZE, NULL,
              2, // Higher priority than Task 1
              NULL);
  vTaskStartScheduler();

  return 0;
}

void emptyTask(void *pvParameters) {
  (void)pvParameters; // Unused parameter

  for (;;) {
    // Blink LED1 or do other processing
    vTaskDelay(pdMS_TO_TICKS(2000)); // Delay for 1000ms
  }
}

// Task 2 function
void blink(void *pvParameters) {
  (void)pvParameters; // Unused parameter

  for (;;) {
    // Blink LED2 or do other processing
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void GPIO_PA4_Init() {
  __HAL_RCC_GPIOA_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
   */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType =
      RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}
