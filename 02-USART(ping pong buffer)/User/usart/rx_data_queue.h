#ifndef __ESP_DATA_QUEUE_H_
#define __ESP_DATA_QUEUE_H_

#include "stm32f10x.h"

#include <string.h>
#include <stdio.h>

#define QUEUE_NODE_NUM        (2)            
#define QUEUE_NODE_DATA_LEN   (2*1024)    

#define QUEUE_DATA_TYPE  		DATA_FRAME

#define DATA_QUEUE_LOG  	 //QUEUE_DEBUG


typedef struct 
{
	char  *head; 		
	uint16_t len; 

}DATA_FRAME;



typedef struct {
	int         size;
	int         read; 
	int         write;   
	int         read_using;	
	int         write_using;		
	QUEUE_DATA_TYPE    *elems[QUEUE_NODE_NUM];  
} QueueBuffer;


#define QUEUE_DEBUG(fmt,arg...)          do{\
                                               printf("<<-QUEUE-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                           }while(0)



extern QueueBuffer rx_queue;

QUEUE_DATA_TYPE* cbWrite(QueueBuffer *cb);
QUEUE_DATA_TYPE* cbRead(QueueBuffer *cb);
void cbReadFinish(QueueBuffer *cb);
void cbWriteFinish(QueueBuffer *cb);
int cbIsFull(QueueBuffer *cb) ; 
int cbIsEmpty(QueueBuffer *cb) ;
void rx_queue_init(void);
void pull_data_from_queue(void);
void push_data_to_queue(char *src_dat,uint16_t src_len);


#endif



