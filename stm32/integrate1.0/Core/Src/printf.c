#include "stdio.h"
#include "usart.h"
#include "printf.h"
#pragma import(__use_no_semihosting)
struct __FILE
{
	int handle;
};
FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
	x = x;
}
//重定义fput函数
int fputc(int ch, FILE *f)
{
	while((USART2->SR&0X40)==0);//循环发送，直到发送完毕
	USART1->DR = (uint8_t) ch;
	return ch;
}

