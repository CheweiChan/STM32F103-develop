
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./led/bsp_led.h" 
#include "./i2c/bsp_i2c_ee.h"

 /**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
  
    LED_GPIO_Config();
  
    /* 串口初始化 */
		USART_Config();
	
		i2c_CfgGpio();

		printf("eeprom 软件模拟i2c测试例程 \r\n");		
  
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
