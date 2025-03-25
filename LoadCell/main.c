#include "stm32f4xx.h"
#include "system_timetick.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <HX711P4.h>

#define		BUFF_SIZE			11
#define		SAMPLE_TIME		10

uint8_t txbuff[BUFF_SIZE];
uint8_t rxbuff[BUFF_SIZE];

uint8_t spi_rxbuff[3];
uint8_t concateStr[5];
int32_t data, data_calb;
int64_t sum = 0;
int32_t A0 = 52786;
int32_t A1 = 95615;
int32_t M0 = 0;
int32_t M1 = 1000;
int32_t offset = 0;
int32_t average = 0; 
bool toogle = false;


uint16_t rcv_flag = 0;
uint16_t i;

hx711_t hx711;

void init_USART4(void);
void init_DMA1(void);
				
int main(void)
{
	/* Enable SysTick at 10ms interrupt */
	SysTick_Config(SystemCoreClock/100);

	init_USART4();
	init_DMA1();
	
	hx711_init(&hx711, GPIOC, GPIO_Pin_13, GPIOC, GPIO_Pin_15);
	
	while(1){
		//IntToStr5(num, txbuff);
		
		if(tick_count == 100){
			tick_count = 0;
			
			//update();	
			
		}		 
	}
}

void init_USART4(void)
{
  GPIO_InitTypeDef 	GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;   
   
  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  /* Enable UART clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	/* Enable DMA1 clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

  /* Connect UART4 pins to AF2 */  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4); 

  /* GPIO Configuration for UART4 Tx */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* GPIO Configuration for USART Rx */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
       
  /* USARTx configured as follow:
		- BaudRate = 115200 baud  
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(UART4, &USART_InitStructure);
	
	/* Enable USART */
  USART_Cmd(UART4, ENABLE);
	
	/* Enable UART4 DMA */
  USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE); 
	USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE); 
}

void init_DMA1(void){
	
	DMA_InitTypeDef  	DMA_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;	
	
	/* DMA1 Stream4 Channel4 for UART4 Tx configuration */			
  DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)txbuff;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize = BUFF_SIZE;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream4, &DMA_InitStructure);
  DMA_Cmd(DMA1_Stream4, ENABLE);

	/* DMA1 Stream2 Channel4 for USART4 Rx configuration */			
  DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rxbuff;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = BUFF_SIZE;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream2, &DMA_InitStructure);
  DMA_Cmd(DMA1_Stream2, ENABLE);
		
	/* Enable DMA Interrupt to the highest priority */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Transfer complete interrupt mask */
  DMA_ITConfig(DMA1_Stream2, DMA_IT_TC, ENABLE);	
	
}

void DMA1_Stream2_IRQHandler(void)
{
	uint8_t dataStr[6];
	//hx711_t hx711;
  /* Clear the DMA1_Stream2 TCIF2 pending bit */
  DMA_ClearITPendingBit(DMA1_Stream2, DMA_IT_TCIF2);
	
	if (memcmp(&rxbuff, "CONN", 4) == 0) {
		memcpy(txbuff, rxbuff, BUFF_SIZE);
		
		DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);
		DMA1_Stream4->NDTR = BUFF_SIZE;
		DMA_Cmd(DMA1_Stream4, ENABLE);
		
	} else if(memcmp(&rxbuff, "READ", 4) == 0) {
		data_calb = read_average(&hx711, A0, A1, M0, M1, 1);
		IntToStr6(data_calb, dataStr);
		memcpy(txbuff, rxbuff, 4);
		memcpy(&txbuff[4], dataStr, 6);
		txbuff[10] = '\n';
		
		DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);
		DMA1_Stream4->NDTR = BUFF_SIZE;
		DMA_Cmd(DMA1_Stream4, ENABLE);
		
	}else if(memcmp(&rxbuff, "CALB", 4) == 0) {	
		
		A1 = read_average(&hx711, A0, A1, M0, M1, SAMPLE_TIME);
		//uint8_t concateStr[5];
		memcpy(concateStr, &rxbuff[4], 6);
		M1 = Str6ToInt(concateStr);

		memcpy(txbuff, "CALB 00000", 10);
		txbuff[10] = '\n';
		
		DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);
		DMA1_Stream4->NDTR = BUFF_SIZE;
		DMA_Cmd(DMA1_Stream4, ENABLE);
		
	} else if(memcmp(&rxbuff, "OFFS", 4) == 0) {
		
		A0 = read_average(&hx711, A0, A1, M0, M1, SAMPLE_TIME);
		//uint8_t concateStr[5];
		memcpy(concateStr, &rxbuff[4], 6);
		M1 -= Str6ToInt(concateStr);
		M0 = 0;
		
		memcpy(txbuff, "OFFS 00000", 10);
		txbuff[10] = '\n';
		
		DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);
		DMA1_Stream4->NDTR = BUFF_SIZE;
		DMA_Cmd(DMA1_Stream4, ENABLE);
	}
	else {
		//Error: invalid header
		for (int i = 0; i < BUFF_SIZE; i++) {
    rxbuff[i] = 0;  
		}
		
		memcpy(&txbuff[0], "EROR 00000", 10);
		txbuff[10] = '\n';
		
		DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);
		DMA1_Stream4->NDTR = BUFF_SIZE;
		DMA_Cmd(DMA1_Stream4, ENABLE);
	}
	
  rcv_flag = 1;
	
	DMA_Cmd(DMA1_Stream2, ENABLE);
}