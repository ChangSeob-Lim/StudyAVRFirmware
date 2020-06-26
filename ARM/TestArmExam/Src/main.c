/*
    Created: 2020-06-25
    Author: 임창섭
*/

#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "lcd.h"
#include "stdio.h"

// TEMP and HUMI
#define SHT2x_ADDR              0x40<<1
#define SHT2x_HOLD_MASTER_T     0xE3
#define SHT2x_HOLD_MASTER_RH    0xE5
#define SHT2x_NOHOLD_MASTER_T   0xF3
#define SHT2x_NOHOLD_MASTER_RH  0xF5
#define SHT2x_WRITE_USER_REG    0xE6
#define SHT2x_READ_USER_REG     0xE7
#define SHT2x_SOFT_RESET        0xFE

char menu = 0;
// UART
uint8_t rxData;

// LCD
char str[16];

// LED
uint16_t LED_Light=0;

// CDS
uint16_t CDS_Data;

// TEMP and HUMI
uint8_t i2cData[2];
uint16_t val = 0;
uint8_t mode;
float TEMP, HUMI;

// Piano
unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};
unsigned long pwmFreq;
unsigned char piano = 0;

void SystemClock_Config(void);

int fputc(int ch, FILE *stream)
{
  HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 10);
  return ch;
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_TIM5_Init();
  MX_USART1_UART_Init();
  
  lcdInit();
  HAL_UART_Receive_IT(&huart1, &rxData, 1); // UART 인터럽트 실행
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); // LED PWM 사용을 위한 설정
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&CDS_Data, sizeof(CDS_Data)); // ADC -> CDS 사용을 위한 DMA 설정
  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3); // 부저 PWM 사용을 위한 설정

  lcdClear();
  printf("++++ Menu ++++\n");
  printf("L : LED\n");
  printf("C : CDS\n");
  printf("0~7 : Piano\n");
  printf("T : Temp & Humi\n");
  printf("push button : stop\n");
  
  while (1)
  {
        if(menu == 1)
        {
            // LED START
            TIM2->CCR1 = LED_Light;
            LED_Light+=15;
            if(LED_Light > 255) LED_Light = 0;
            // LED END
        }
        
        else if(menu == 2)
        {
            // CDS START
            lcdGotoXY(0, 0);
            sprintf(str, "Cds : %4d", CDS_Data);
            lcdPrint(str);
            // CDS END
        }
        
        else if(menu == 3)
        {
            // TEMP and HUMI START
            // TEMP
            mode = SHT2x_NOHOLD_MASTER_T;
            HAL_I2C_Master_Transmit(&hi2c1, SHT2x_ADDR, &mode, 1, 10);
            HAL_Delay(100);
            HAL_I2C_Master_Receive(&hi2c1, SHT2x_ADDR, i2cData, 2, 10);
            
            val = i2cData[0] << 8 | i2cData[1];
            TEMP = -46.85 + 175.72 * ((float)val / 65536);
            lcdGotoXY(0, 0);
            sprintf(str, "TEMP : %5.2lf", TEMP);
            lcdPrint(str);
            // HUMI
            mode = SHT2x_NOHOLD_MASTER_RH;
            HAL_I2C_Master_Transmit(&hi2c1, SHT2x_ADDR, &mode, 1, 10);
            HAL_Delay(100);
            HAL_I2C_Master_Receive(&hi2c1, SHT2x_ADDR, i2cData, 2, 10);
            
            val = i2cData[0] << 8 | i2cData[1];
            HUMI = -6 + 125 * ((float)val / 65536);
            lcdGotoXY(0, 1);
            sprintf(str, "HUMI : %5.2lf", HUMI);
            lcdPrint(str);
            // TEMP and HUMI END
        }
        
      
      else if(menu == 4)
      {
             // Piano START
            TIM5->EGR = TIM5->EGR & 0xFE; //~(0x01)
            pwmFreq = 84000000 / DoReMi[piano];
            TIM5->ARR = pwmFreq - 1;
            TIM5->CCR3 = pwmFreq / 2;
            TIM5->EGR = TIM5->EGR | 0x01;
            HAL_Delay(200);
            TIM5->CCR3 = 0;
            menu=0;
             // Piano END
      }
    
    HAL_Delay(100);
  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))
  {
     menu=0;
     LED_Light=0;
     TIM2->CCR1 = 0;
     TIM5->CCR3 = 0;
     lcdClear();
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  HAL_UART_Receive_IT(&huart1, &rxData, 1);
  if(rxData == 'L' || rxData == 'l')
  {
     menu=1;
     LED_Light=0;
     TIM2->CCR1 = 0;
     TIM5->CCR3 = 0;
     lcdClear();
  }
  else if(rxData == 'C' || rxData == 'c')
  {
     menu=2;
     LED_Light=0;
     TIM2->CCR1 = 0;
     TIM5->CCR3 = 0;
     lcdClear();
  }
  else if(rxData == 'T' || rxData == 't')
  {
     menu=3;
     LED_Light=0;
     TIM2->CCR1 = 0;
     TIM5->CCR3 = 0;
     lcdClear();
  }
  else if(rxData >= '0' && rxData <='7')
  {
     menu=4;
     piano=rxData - '0';
     LED_Light=0;
     TIM2->CCR1 = 0;
     TIM5->CCR3 = 0;
     lcdClear();
  }
}
/* USER CODE END 4 */

void Error_Handler(void)
{
  
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{ 
  
}
#endif