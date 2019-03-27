#include "stm32f10x.h"
#include "bsp_usart.h"
#include "./usart/rx_data_queue.h"


void Delay(__IO uint32_t nCount)
{
    for(; nCount != 0; nCount--);
}


  
int main(void)
{	

    USART_Config();
	USART2_Config();
	/* ·¢ËÍÒ»¸ö×Ö·û´® */
	USART2_printf(USART2,"\nuart2");
	USART2_printf(USART1,"\nuart1");

	rx_queue_init();
	
	printf("\nuart rx_tx test (receive use ping pong buffer)\n\n");

  while(1)
	{	
	    Delay(0xffffff);//delay for test buffer is work

		pull_data_from_queue();
	}	
}
/*********************************************END OF FILE**********************/
