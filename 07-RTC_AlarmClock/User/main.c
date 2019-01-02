/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   rtc 测试，显示时间格式为: xx:xx:xx
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
	
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./rtc/bsp_rtc.h"
#include "./key/bsp_key.h"  
#include "./beep/bsp_beep.h"   


// N = 2^32/365/24/60/60 = 136 年

extern __IO uint32_t TimeDisplay ;
extern __IO uint32_t TimeAlarm ;
uint32_t timeup=120;
/*
  * @brief  主函数
  * @param  无  
  * @retval 无
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
	    /* 每过1s 更新一次时间*/
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

