#include "stm32f10x.h"
#include "ff.h"
#include "./flash/bsp_spi_flash.h"
#include "./usart/bsp_usart.h"
#include "./led/bsp_led.h"

FATFS fs;						  /* FatFs File system object */
FIL fnew;						  /* File object */
FRESULT res_flash;                /* File operation result */
UINT fnum;            			  /* The number of successfully read and write files */
BYTE ReadBuffer[1024]={0};       
BYTE WriteBuffer[] ="Hello this is a program which file system test\r\n"; 

int main(void)
{

	LED_GPIO_Config();	
	USART_Config();	
    printf("-------------Spi flash file system test------------\r\n");
  
	//File system setup flow as fllow: 
	//f_mount()->find_volume()->disk_initialize->SPI_FLASH_Init()
	res_flash = f_mount(&fs,"1:",1);
	
/*---------------------- format -----------------*/  
	/* if not file system,create file system */
	if(res_flash == FR_NO_FILESYSTEM)
	{
		printf("No file system,just formatting...\r\n");
    /* format */
		res_flash=f_mkfs("1:",0,0);							
		
		if(res_flash == FR_OK)
		{
			printf("file system successful\r\n");
      /* After formatting, unmount  */
			res_flash = f_mount(NULL,"1:",1);			
      /* Remount*/			
			res_flash = f_mount(&fs,"1:",1);
		}
		else
		{
			LED1_ON;
			printf(" Formatting failed \r\n");
			while(1);
		}
	}
  else if(res_flash!=FR_OK)
  {
       printf("External Flash mount file system failed.(%d)\r\n",res_flash);
       while(1);
  }
  else
  {
       printf("The file system is mounted successfully.\r\n");
  }
  
/*----------------------- write test -------------------*/
	/* open&&create .txt  */
	printf("\r\n-----------Write test...\r\n");	
	res_flash = f_open(&fnew, "1:FatFsTest.txt",FA_CREATE_ALWAYS | FA_WRITE );
	if ( res_flash == FR_OK )
	{
		printf("Open FatFsTest.txt successful\r\n");
    /* write buffer to file */
		res_flash=f_write(&fnew,WriteBuffer,sizeof(WriteBuffer),&fnum);
    if(res_flash==FR_OK)
    {
      printf("The amount of data written is %d\n",fnum);
      printf(">>>:%s\r\n",WriteBuffer);
    }
    else
    {
      printf("write failed(%d)\n",res_flash);
    }    
		/* close file*/
    f_close(&fnew);
	}
	else
	{	
		LED1_ON;
		printf("open FatFsTest.txt failed\r\n");
	}
	
/*------------------- read test--------------------------*/
	printf("\r\n----------Read test... \r\n");
	res_flash = f_open(&fnew, "1:FatFsTest.txt",FA_OPEN_EXISTING | FA_READ); 	 
	if(res_flash == FR_OK)
	{
		LED2_ON;
		printf("Open FatFsTest.txt successful\r\n");
		 /* read buffer from file */
		res_flash = f_read(&fnew, ReadBuffer, sizeof(ReadBuffer), &fnum); 
    if(res_flash==FR_OK)
    {
      printf("The amount of data read£º%d\r\n",fnum);
      printf(">>>:%s \r\n", ReadBuffer);	
    }
    else
    {
      printf("read failed(%d)\n",res_flash);
    }		
	}
	else
	{
		LED1_ON;
		printf("open FatFsTest.txt failed\r\n");
	}
	/* Close file */
	f_close(&fnew);	
  
	/*unmount */
	f_mount(NULL,"1:",1);
  
	while(1);

}

/*********************************************END OF FILE**********************/
