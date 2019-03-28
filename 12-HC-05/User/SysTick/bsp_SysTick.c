#include "./SysTick/bsp_SysTick.h"

static __IO uint32_t TimingDelay=0;
__IO uint32_t g_ul_ms_ticks=0;
 
/**
  * @brief  ����ϵͳ�δ�ʱ�� SysTick
  * @param  ��
  * @retval ��
  */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
	if (SysTick_Config(SystemCoreClock/1000))	
	{ 
		/* Capture error */ 
		while (1);
	}
		// �رյδ�ʱ��  
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}



void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
		TimingDelay--;
}

void mdelay(unsigned long nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);
}


int get_tick_count(unsigned long *count)
{
        count[0] = g_ul_ms_ticks;
	return 0;
}



void TimeStamp_Increment(void)
{
	g_ul_ms_ticks++;
}


/*********************************************END OF FILE**********************/
