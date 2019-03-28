#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./usart/bsp_usart_blt.h"
#include "./SysTick/bsp_SysTick.h"
#include "./hc05/bsp_hc05.h"
#include <string.h>
#include <stdlib.h>

/** Private constant and macro definitions using #define*/
#define SLAVE 0
#define MASTER 1
#define DEVICEMODE SLAVE

/*Global variable or extern global variabls*/
unsigned int Task_Delay[3]; 
BLTDev bltDevList;
char sendData[1024];
int luck=0;
char BTcStr [ 100 ] = { 0 };
uint8_t matchDevice=1;

/*function prototypes*/
void Task_Master(void);
void Task_Slave(void);

/*******************************************************/

int main(void)
{
	char hc05_nameCMD[40];
	
	//Init timer
	SysTick_Init();
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	USART_Config();
		
	HC05_INFO("test HC-05");
	
	if(HC05_Init() == 0)
		HC05_INFO("HC05...OK¡£");
	else
	{
		HC05_ERROR("Init Fail");
		while(1);
	}


	/*Reset status*/
	HC05_Send_CMD("AT+RESET\r\n",1);	
	delay_ms(800);
	
	HC05_Send_CMD("AT+ORGL\r\n",1);
	delay_ms(200);

    /*AT Mode setting*/
	HC05_Send_CMD("AT+VERSION?\r\n",1);
	
	HC05_Send_CMD("AT+ADDR?\r\n",1);
	
	HC05_Send_CMD("AT+UART?\r\n",1);
	
	HC05_Send_CMD("AT+CMODE?\r\n",1);
	
	HC05_Send_CMD("AT+STATE?\r\n",1);	
#if (DEVICEMODE == MASTER)
    HC05_Send_CMD("AT+ROLE=1\r\n",1);
    sprintf(hc05_nameCMD,"AT+NAME=HC05_MASTER\r\n");
#else
	HC05_Send_CMD("AT+ROLE=0\r\n",1);
	sprintf(hc05_nameCMD,"AT+NAME=HC05_SLAVE\r\n");
#endif
	/*SPP*/
	HC05_Send_CMD("AT+INIT\r\n",1);
	HC05_Send_CMD("AT+CLASS=0\r\n",1);
	HC05_Send_CMD("AT+INQM=1,9,48\r\n",1);
	
	/*setting device name*/
	HC05_Send_CMD(hc05_nameCMD,1);

	if(DEVICEMODE == SLAVE)
	    HC05_Send_CMD("AT+INQ\r\n",0);
	    
	while(1)
	{
#if (DEVICEMODE == MASTER)
		Task_Master();
#else	
		Task_Slave();
#endif
	}
	
	 
}


/**************************************************************/
void Task_Master(void)
{
	
	//search device
	if(Task_Delay[2]==0 && !IS_HC05_CONNECTED()) 
	{
		if(matchDevice == 1)	
		{
			HC05_INFO("search device...");
			matchDevice = linkHC05();
			Task_Delay[2]=1000;
            Usart_SendString(HC05_USART,"Hello\r\n");
		}
	}
    if(Task_Delay[1]==0 && IS_HC05_CONNECTED())  
    {
        Usart_SendString(HC05_USART,"Hello\r\n");
        Task_Delay[1]= 10000;
    }
}

/************************************************************/
void Task_Slave(void)
{   
    char* redata;
    uint16_t len;
    if(Task_Delay[0]==0 && IS_HC05_CONNECTED() && luck ==0)  
    {
    	redata = get_rebuff(&len); 
        /*get receive data*/
    	if(len<200 && len != 0)
    	{	 
    		sprintf (BTcStr,redata);
    	    printf("\nreceive=%s",BTcStr);
    		clean_rebuff(); 
    		Usart_SendString(HC05_USART,"Slave:OK\r\n");		
    	}
    Task_Delay[0]=1000;
    }
}


