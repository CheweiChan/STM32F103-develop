#include "stm32f10x.h"
#include "bsp_usart.h"

void USART2_printf( USART_TypeDef* USARTx, char *Data, ... ); 
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
    USART_Config();
	USART2_Config();
	/* ����һ���ַ��� */
	USART2_printf(USART2,"\nuart2");
	USART2_printf(USART1,"\nuart1");
	printf("\nUART TEST");


	
  while(1);

}
/*********************************************END OF FILE**********************/
