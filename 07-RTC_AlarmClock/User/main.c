
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./rtc/bsp_rtc.h"
#include "./key/bsp_key.h"  
#include "./beep/bsp_beep.h"   

extern __IO uint32_t TimeDisplay ;
extern __IO uint32_t TimeAlarm ;
uint32_t timeup=120;
/*
  * @brief  主函�?
  * @param  �? 
  * @retval �?
*/
int main()
{		
	USART_Config();			
	
	Key_GPIO_Config();
	
	BEEP_GPIO_Config();
		
/* 配置RTC秒中断优先级 */
	RTC_NVIC_Config();
	RTC_CheckAndConfig();
	  while (1)
	  {
	    /* 每过1s 更新一次时�?/
	    if (TimeDisplay == 1)
	    {
   		    /* 当前时间 */
	        TimeDisplay = 0;
            printf("timeup=%d,time=%d:%d\n",timeup,timecnt/60,timecnt%60);
            if(timeup==timecnt) TimeAlarm=1;
                
	    }
			
			//按下按键，通过串口修改时间
			if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON  )
			{
				printf("please press AlarmTime(sec)\n");
				scanf("%d",&timeup);
                timecnt=0;
			} 	
			
			//响铃
			if( TimeAlarm == 1)
			{
				BEEP(ON);
			}

			//按下按键，关闭蜂鸣器
			if( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON  )
			{
				BEEP(OFF);
				TimeAlarm = 0;
			}
	  }
}

/***********************************END OF FILE*********************************/

