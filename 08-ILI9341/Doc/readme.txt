﻿/*********************************************************************************************

【*】 引脚分配

液晶屏：
使用模拟时序产生8080时序与液晶屏驱动芯片ILI9341通讯.


		/*液晶控制信号线*/
		ILI9341_CS 	<--->	PC4      	//片选
		ILI9341_DC  <---> 	PC7			//选择输出命令还是数据
		ILI9341_WR 	<---> 	PC6			//写使能
		ILI9341_RD  <---> 	PC5			//读使能
		ILI9341_RST	<---> 	NRST		//STM32的复位引脚，上电同时复位液晶
		ILI9341_BK 	<---> 	PD2 		//背光引脚
		
		ILI9341_D0~D15 <---> PB0~PB15
		
	本实验没有驱动触摸屏，详看触摸画板实验。

串口(TTL-USB TO USART)：
CH340的收发引脚与STM32的发收引脚相连。
	RX<--->PA9
	TX<--->PA10
												
/*********************************************************************************************/
