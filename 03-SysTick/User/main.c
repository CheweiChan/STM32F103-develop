
#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "bsp_led.h"

/*
 * t : ��ʱʱ�� 
 * Ticks : ���ٸ�ʱ�����ڲ���һ���ж� 
 * f : ʱ��Ƶ�� 72000000
 * t = Ticks * 1/f = (72000000/100000) * (1/72000000) = 10us 
 */ 

/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();

#if 0
	/* ����SysTick Ϊ10us�ж�һ�� */
	SysTick_Init();	
	for(;;)
	{

		LED1( ON ); 
	    Delay_us(100000);    	// 100000 * 10us = 1000ms
		//Delay_ms(100);
		LED1( OFF );
	  
		LED2( ON );
	    Delay_us(100000);		// 100000 * 10us = 1000ms
		//Delay_ms(100);
		LED2( OFF );	

	}     
#else // ��ʹ���жϣ�ʹ�ò�ѯ�ķ���
	for(;;)
	{

		LED1( ON ); 
		SysTick_Delay_Ms( 1000 );
		LED1( OFF );
	  
		LED2( ON );
		SysTick_Delay_Ms( 1000 );
		LED2( OFF );
	} 
#endif	
}


/*********************************************END OF FILE**********************/
