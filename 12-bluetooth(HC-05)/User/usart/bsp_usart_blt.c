#include "./usart/bsp_usart_blt.h"
#include <stdarg.h>

extern int luck;
/// ����USART�����ж�
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = BLT_USART_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/*
 * ��������USARTx_Config
 * ����  ��USART GPIO ����,����ģʽ����
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void BLT_USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* config USART2 clock */
	BLT_USART_APBxClock_FUN(BLT_USART_CLK, ENABLE); 
	BLT_USART_GPIO_APBxClock_FUN(BLT_USART_GPIO_CLK, ENABLE);

	/* USART2 GPIO config */
	 /* Configure USART2 Tx (PA.02) as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin = BLT_USART_TX_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(BLT_USART_TX_PORT, &GPIO_InitStructure);
	    
    /* Configure USART2 Rx (PA.03) as input floating */
    GPIO_InitStructure.GPIO_Pin = BLT_USART_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(BLT_USART_RX_PORT, &GPIO_InitStructure);
	  
	/* USART2 mode config */
	USART_InitStructure.USART_BaudRate = BLT_USART_BAUD_RATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(BLT_USARTx, &USART_InitStructure); 
	
	USART_ITConfig ( BLT_USARTx, USART_IT_IDLE, ENABLE ); //ʹ�ܴ������߿����ж� 	
	
	/*	�����ж����ȼ� */
	NVIC_Configuration();
	/* ʹ�ܴ���2�����ж� */
	USART_ITConfig(BLT_USARTx, USART_IT_RXNE, ENABLE);

	USART_Cmd(BLT_USARTx, ENABLE);
	USART_ClearFlag(BLT_USARTx, USART_FLAG_TC);
}

/***************** ����һ���ַ�  **********************/
static void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch )
{
	/* ����һ���ֽ����ݵ�USART1 */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ�������� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}


/*****************  ����ָ�����ȵ��ַ��� **********************/
void Usart_SendStr_length( USART_TypeDef * pUSARTx, uint8_t *str,uint32_t strlen )
{
	unsigned int k=0;
    do 
    {
        Usart_SendByte( pUSARTx, *(str + k) );
        k++;
    } while(k < strlen);
}


/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, uint8_t *str)
{
	unsigned int k=0;
    do 
    {
        Usart_SendByte( pUSARTx, *(str + k) );
        k++;
    } while(*(str + k)!='\0');
}


//�жϻ��洮������
#define UART_BUFF_SIZE      1024
volatile    uint16_t uart_p = 0;
uint8_t     uart_buff[UART_BUFF_SIZE];

void bsp_USART_Process(void)
{
    if(uart_p<UART_BUFF_SIZE)
    {
        if(USART_GetITStatus(BLT_USARTx, USART_IT_RXNE) != RESET)
        {
            luck = 1;
            uart_buff[uart_p] = USART_ReceiveData(BLT_USARTx);
            uart_p++;
        }
    }
	else
	{
		USART_ClearITPendingBit(BLT_USARTx, USART_IT_RXNE);
		clean_rebuff();       
	}
	
	if ( USART_GetITStatus( BLT_USARTx, USART_IT_IDLE ) == SET )                                         //����֡�������
	{  
	    luck=0;
		USART_ReceiveData(BLT_USARTx);  
    }
}

//��ȡ���յ������ݺͳ���
char *get_rebuff(uint16_t *len) 
{
    *len = uart_p;
    return (char *)&uart_buff;
}

//��ջ�����
void clean_rebuff(void)
{

    uint16_t i=UART_BUFF_SIZE+1;
    uart_p = 0;
	while(i)
		uart_buff[--i]=0;

}
