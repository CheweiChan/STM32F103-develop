#include "stm32f10x.h"
#include "bsp_usart.h"

void USART2_printf( USART_TypeDef* USARTx, char *Data, ... ); 
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
    USART_Config();
	USART2_Config();
	/* 发送一个字符串 */
	USART2_printf(USART2,"\nuart2");
	USART2_printf(USART1,"\nuart1");
	printf("\nUART TEST");


	
  while(1);

}
/*********************************************END OF FILE**********************/
