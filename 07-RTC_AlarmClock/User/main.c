/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   rtc ���ԣ���ʾʱ���ʽΪ: xx:xx:xx
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
	
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./rtc/bsp_rtc.h"
#include "./key/bsp_key.h"  
#include "./beep/bsp_beep.h"   


// N = 2^32/365/24/60/60 = 136 ��

extern __IO uint32_t TimeDisplay ;
extern __IO uint32_t TimeAlarm ;
uint32_t timeup=120;
/*
  * @brief  ������
  * @param  ��  
  * @retval ��
*/
int main()
{		
	USART_Config();			
	
	Key_GPIO_Config();
	
	BEEP_GPIO_Config();
		
/* ����RTC���ж����ȼ� */
	RTC_NVIC_Config();
	RTC_CheckAndConfig();
		
	  while (1)
	  {
	    /* ÿ��1s ����һ��ʱ��*/
	    if (TimeDisplay == 1)
	    {
   		    /* ��ǰʱ�� */
	        TimeDisplay = 0;
            printf("timeup=%d,time=%d:%d\n",timeup,timecnt/60,timecnt%60);
            if(timeup==timecnt) TimeAlarm=1;
                
	    }
			
			//���°�����ͨ�������޸�ʱ��
			if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON  )
			{
				printf("please press AlarmTime(sec)\n");
				scanf("%d",&timeup);
                timecnt=0;
			} 	
			
			//����
			if( TimeAlarm == 1)
			{
				BEEP(ON);
			}

			//���°������رշ�����
			if( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON  )
			{
				BEEP(OFF);
				TimeAlarm = 0;
			}
	  }
}

/***********************************END OF FILE*********************************/

