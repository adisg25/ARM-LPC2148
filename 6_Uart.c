
#include <LPC176X.H>

void stringTx(char str[50]);
void stringRx(char str[30]);


void uart_init()
{
	U1LCR|=(1<<0)|(1<<1)|(1<<7);//UART1 Line Control Register => bit[1:0]= 11 for 8 bit character length,bit[2]=0 for 1 stop bit,bit[3]=0 to disable parity,bit[7]=1 to enable DLAB...
	U1DLM=0x00;
	U1DLL=0xC3;
}

void uartTx(char data)
{
	while(!(U1LSR&(1<<5)));//UART1 Line Status Register  Transmitter Holding Register Empty(THRE)
	U1THR=data;
}

char uartRx()
{
	while(!(U1LSR & (1<<0)));
	return U1RBR;
}

void main()
{
	//char ch;
	VPBDIV=0x02;
	PINSEL0=0X00050000;
	uart_init();
	U1LCR &= ~(1<<7);//bit[7]=1 to disable DLAB.
	while(1)
	{
	//	ch=uartRx();
	//	uartTx(ch);
		char str[20];
		stringRx(str);
		stringTx(str);
		
	}
}

void stringTx(char str[50])
{
	int i=0;
	while(str[i] != '\0')
	{
		uartTx(str[i++]);
	}
	uartTx('\n');
	uartTx('\r');
}



void stringRx(char str[30])
	{
	char data;
	int i=0;
	while(data != '\r') { // Stop Receiving the string when the enter key is pressed
		data=uartRx();
		str[i++] = data;
		}
	str[i] = '\0';
}