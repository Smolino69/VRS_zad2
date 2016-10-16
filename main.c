/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-February-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup IO_Toggle
  * @{
  */ 
#include <stddef.h>
#include "stm32l1xx.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

void Blick(int frequency);
void Wait(int timeInterval);

/* Private function prototypes -----------------------------------------------*/
RCC_ClocksTypeDef RCC_Clocks;
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int freq0L = 3920;
   int freq0H = 3060;
   int freq1L = 2000;
   int freq1H = 2020;
   int freq2L = 2880;
   int freq2H = 2930;
   int freq3L = 3440;
   int freq3H = 3465;
   int freq4L = 3640;
   int freq4H = 3670;

void Init()
{
    // Init structures
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef  ADC_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); // Enable GPIO clock
    /* Configure ADCx Channel 0 as analog input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    RCC_HSICmd(ENABLE); // Enable the HSI oscillator
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET); // Check that HSI oscillator is ready
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // Enable ADC clock
    ADC_StructInit(&ADC_InitStructure); // Initialize ADC structure
    /* ADC1 configuration */
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADC1, &ADC_InitStructure);
    /* ADCx regular channel8 configuration */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_16Cycles);
    /* Enable the ADC */
    ADC_Cmd(ADC1, ENABLE);
    /* Wait until the ADC1 is ready */
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
    {
    }
    /* Start ADC Software Conversion */
    ADC_SoftwareStartConv(ADC1);


}




int main(void)
{
	int AD_value;
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32l1xx_xl.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32l1xx.c file
     */ 
	while (1)
	    {
	        Init();

	        /* Start ADC Software Conversion
	         * Setting up the frequency range of buttons
	         */
	        //ADC_SoftwareStartConv(ADC1);
	        //while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) {}
	        //AD_value=ADC_GetConversionValue(ADC1);


	        if ((AD_value >> freq1L) && (AD_value << freq1H))
	        {
	            Blick(10000);
	        }
	        else if ((AD_value >> freq2L) && (AD_value << freq2H))
	        {
	            Blick(40000);
	        }
	        else if ((AD_value >> freq3L) && (AD_value << freq3H))
	        {
	            Blick(70000);
	        }
	        else if ((AD_value >> freq4L) && (AD_value << freq4H))
	        {
	            Blick(100000);
	        }
	        else // LED is not blicking
	        {
	            Blick(0);
	        }
	    }

	    return 0;
	}
  
void Blick(int frequency)
{
    if (frequency != 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_0);
        Wait(frequency);
        GPIO_ResetBits(GPIOA, GPIO_Pin_0);
        Wait(frequency);
    }
}

void Wait(int timeInterval)
{
    for(int i=0; i<timeInterval; i++)
    {}

    /* include time.h or sth */
    //int startTime = getTime();
    //int currTime = 0;
    //do
    //{
    //  currTime = getTime();
    //  int diff = currTime - startTime;
    //}while(diff >= timeInterval || timeInterval != 0)

}


/**
* @brief  Inserts a delay time.
* @param  nTime: specifies the delay time length, in 1 ms.
* @retval None
*/


/**
* @brief  Decrements the TimingDelay variable.
* @param  None
* @retval None
*/


#ifdef  USE_FULL_ASSERT

/**
* @brief  Reports the name of the source file and the source line number
*         where the assert_param error has occurred.
* @param  file: pointer to the source file name
* @param  line: assert_param error line source number
* @retval None
*/
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  
  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
* @}
*/


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
