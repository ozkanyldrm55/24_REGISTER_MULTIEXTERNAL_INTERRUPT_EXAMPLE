
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void delay(uint32_t time)
{
	while(time--);
}

GPIO_Config(void)
{
	RCC->AHB1ENR = 0x00000009;//A ve D portlarý aktif edildi.

	GPIOD->MODER = 0x55000000;//output yapildi
	GPIOD->OTYPER = 0x00000000;//Push-pull
	GPIOD->OSPEEDR = 0xFF000000;

}

void EXTI_Config(void)
{
	RCC->APB2ENR = 0x00004000;//EXTI olarak kullanilmak icin aktif edildi SYSCFG EN

	NVIC_EnableIRQ(EXTI0_IRQn);//1. hatti aktif ettik
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);

	SYSCFG->EXTICR[0] = 0x00000000;//PA pinini external interrupt icin aktif ettik
	SYSCFG->EXTICR[1] = 0x00000000;
	SYSCFG->EXTICR[2] = 0x00000000;

	NVIC_SetPriority(EXTI0_IRQn, 0);//kesmeler arasýnda oncelik tanýmlaniyor.degeri kucul olanin onceligi buyuk
	NVIC_SetPriority(EXTI1_IRQn, 1);
	NVIC_SetPriority(EXTI2_IRQn, 2);


	EXTI->IMR = 0x00000007;
	EXTI->RTSR = 0x00000007;

}

void EXTI0_IRQnHandler() //interrupt bayragý kalkmýs mi kontrol ediyoruz
{
	if(EXTI->PR & (1 << 0)) // bayragin gercekten kalkýp kalkmadigi kontrol ediliyor .(1<<0) 0 inci bit 1 lendi mi anlamina gelir
	{
		int i = 0;

		do
		{
			GPIOD->ODR = 0x00001000;//12. pin e bagli led i yakiyoruz
			delay(1680000);
			GPIOD->ODR = 0x00000000;
			delay(1680000);

			i++;

		}
		while(i<5);

		EXTI->PR = (1 << 0);//interrupt bayragi indiriliyor
	}
}

void EXTI1_IRQnHandler()
{
	if(EXTI->PR & (1 << 1)) // bayragin gercekten kalkýp kalkmadigi kontrol ediliyor .(1<<0) 0 inci bit 1 lendi mi anlamina gelir
		{
			int i = 0;

			do
			{
				GPIOD->ODR = 0x00002000;//12. pin e bagli led i yakiyoruz
				delay(1680000);
				GPIOD->ODR = 0x00000000;
				delay(1680000);

				i++;
			}
			while(i<5);

			EXTI->PR = (1 << 1);//interrupt bayragi indiriliyor
		}

}

void EXTI2_IRQnHandler()
{
	if(EXTI->PR & (1 << 2)) // bayragin gercekten kalkýp kalkmadigi kontrol ediliyor .(1<<0) 0 inci bit 1 lendi mi anlamina gelir
		{
			int i = 0;

			do
			{
				GPIOD->ODR = 0x00003000;//12. pin e bagli led i yakiyoruz
				delay(1680000);
				GPIOD->ODR = 0x00000000;
				delay(1680000);

				i++;

			}
			while(i<5);

			EXTI->PR = (1 << 2);//interrupt bayragi indiriliyor
		}
}

int main(void)
{
	GPIO_Config();
	EXTI_Config();
  while (1)
  {

  }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
