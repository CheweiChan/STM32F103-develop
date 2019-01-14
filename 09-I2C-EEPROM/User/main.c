
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./led/bsp_led.h" 
#include "./i2c/bsp_i2c_ee.h"

 /**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
  
    LED_GPIO_Config();
  
    /* ���ڳ�ʼ�� */
		USART_Config();
	
		i2c_CfgGpio();

		printf("eeprom ���ģ��i2c�������� \r\n");		
  
    if(ee_Test() == 1)
  	{
			LED2_ON;
    }
    else
    {
        LED1_ON;
    }
    while(1);
}
/*********************************************END OF FILE**********************/
