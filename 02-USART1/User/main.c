/
 
#include "stm32f10x.h"
#include "bsp_usart.h"


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();
	
	/* 发送一个字符串 */
	Usart_SendString( DEBUG_USARTx,"这是一个串口中断接收回显实验\n");
	printf("欢迎使用秉火STM32开发板\n\n\n\n");
	
  while(1)
	{	
		
	}	
}
/*********************************************END OF FILE**********************/
