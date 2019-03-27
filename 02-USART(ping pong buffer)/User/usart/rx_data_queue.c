
#include "./usart/rx_data_queue.h"




QUEUE_DATA_TYPE  node_data[QUEUE_NODE_NUM]; 

QueueBuffer rx_queue;


__align(4) char node_buff[QUEUE_NODE_NUM][QUEUE_NODE_DATA_LEN] ;



/**
  * @brief  init queue
  * @param  cb:struct of QueueBuffer
  * @param  size: number of buffer
  * @note
  */
void cbInit(QueueBuffer *cb, int size) 
{
    cb->size  = size;	/* maximum number of elements           */
    cb->read = 0; 		/* index of oldest element              */
    cb->write   = 0; 	 	/* index at which to write new element  */
//   cb->elems = (uint8_t *)calloc(cb->size, sizeof(uint8_t));  //new the data buffer
}
 
/**
  * @brief  (1)not full (0) full
  * @param  cb:struct of QueueBuffer
  */
int cbIsFull(QueueBuffer *cb) 
{
    return cb->write == (cb->read ^ cb->size); /* This inverts the most significant bit of read before comparison */ 
}
 
/**
  * @brief  (1)not empty(0)empty
  * @param  cb:struct of QueueBuffe
  */		
int cbIsEmpty(QueueBuffer *cb) 
{
    return cb->write == cb->read; 
}

/**
  read and write pointer ++

  */	
int cbIncr(QueueBuffer *cb, int p) 
{
    return (p + 1)&(2*cb->size-1); /* read and write pointers incrementation is done modulo 2*size */
}
 
/**
  * @brief  get a writable buffer pointer
  * @param  cb:struct of QueueBuffe
  * @return writable buffer pointer
  * @note   the write pointer does not add 1 immediately.
????When writing the data, you should call cbWriteFinish to update write pointer
  */
QUEUE_DATA_TYPE* cbWrite(QueueBuffer *cb) 
{
    if (cbIsFull(cb)) /* full, overwrite moves read pointer */
    {
			return NULL;
		}		
		else
		{
			//when write and write_using equal
			//it mean that previous buffer has been write,write_using add 1
			if(cb->write == cb->write_using)
			{
				cb->write_using = cbIncr(cb, cb->write); //Î´Âú£¬ÔòÔö¼Ó1
			}
		}
		
	return  cb->elems[cb->write_using&(cb->size-1)];
}



/**
  * @brief write finish,update write pointer
  * @param  
  */
void cbWriteFinish(QueueBuffer *cb)
{
    cb->write = cb->write_using;
}
 
/**
  * @brief  get a readable buffer pointer
  * @param 
  * @return  readable buffer pointer
  * @note  call cbReadFinish to update read pointer
  */
QUEUE_DATA_TYPE* cbRead(QueueBuffer *cb) 
{
		if(cbIsEmpty(cb))
			return NULL;
		
	//When read and read_using are equal, 
	//it means that the previous buffer has been read(cbReadFinish has been called)
	//read_using add 1
	if(cb->read == cb->read_using)	
		cb->read_using = cbIncr(cb, cb->read);
	
	return cb->elems[cb->read_using&(cb->size-1)];
}


/**
  * @brief  read finish,update read pointer
  * @param  
  */
void cbReadFinish(QueueBuffer *cb) 
{	
		//read finsh,reset read len
		cb->elems[cb->read_using&(cb->size-1)]->len = 0;
	
    cb->read = cb->read_using;
}



void camera_queue_free(void)
{
    uint32_t i = 0;

    for(i = 0; i < QUEUE_NODE_NUM; i ++)
    {
        if(node_data[i].head != NULL)
        {
			//if malloc memory
//            free(node_data[i].head);
            node_data[i].head = NULL;
        }
    }

    return;
}


/**
  * @brief  init queue
  * @param  
  * @retval 
  */
void rx_queue_init(void)
{
  uint32_t i = 0;

  memset(node_data, 0, sizeof(node_data));
		 
	cbInit(&rx_queue,QUEUE_NODE_NUM);

    for(i = 0; i < QUEUE_NODE_NUM; i ++)
    {
        node_data[i].head = node_buff[i];
        
        /*pointer to data buffer*/
        rx_queue.elems[i] = &node_data[i];
        
        DATA_QUEUE_LOG("node_data[i].head=0x%x,\r\nrx_queue.elems[i] =0x%x", (uint32_t)node_data[i].head,(uint32_t)rx_queue.elems[i]->head);

        memset(node_data[i].head, 0, QUEUE_NODE_DATA_LEN);
    }
		
}



/**
  * @brief 
  */
void push_data_to_queue(char *src_dat,uint16_t src_len)
{
	QUEUE_DATA_TYPE *data_p;
	uint8_t i;
	
	for(i=0;i<src_len;i++)
	{
		data_p = cbWrite(&rx_queue);
		
		if (data_p != NULL)	
		{		
			
			*(data_p->head + i) = src_dat[i];
				data_p->len++;
			printf("\r\ndata_p->len =%d",data_p->len);
		}else return;	
		
	}	
	
	cbWriteFinish(&rx_queue);
	

}


/**
  * @brief  
  */
void pull_data_from_queue(void)
{
	QUEUE_DATA_TYPE *rx_data;	
    uint8_t i=0;	

	rx_data = cbRead(&rx_queue); 
	if(rx_data != NULL)
	{		
        while(i<rx_data->len)
        {
            printf("%c",*(rx_data->head+i));
            i++;
        }
        printf("\n");
		cbReadFinish(&rx_queue);

	}
}


