
#include <LPC214X.H>

char ch;
void uart_init()
{
	U1LCR|=(1<<0)|(1<<1)|(1<<7);	//UART1 Line Control Register => bit[1:0]= 11 for 8 bit character length,bit[2]=0 for 1 stop bit,bit[3]=0 to disable parity,
					//bit[7]=1 to enable DLAB...
	U1DLM=0x00;	//in formula for calculating DLL value DLM is kept zero
	U1DLL=0xC3;	//UART1 Divisor Latch LSB register
	U1LCR &= ~(1<<7);	//bit[7]=1 to disable DLAB.

}

void uartTx(char data)
{
	while(!(U1LSR&(1<<5)));		//UART1 Line Status Register  Transmitter Holding Register Empty(THRE)
	U1THR=data;			//UART1 Transmitter Holding Register
	/*Writing to the UART1 Transmit Holding Register causes the data to be stored in the UART1 transmit FIFO. The byte will be sent
when it reaches the bottom of the FIFO and the transmitter is available*/
}


void uart1_isr(void)__irq
{
	U1LSR &= ~(1<<0);	//UART1 Line Status Register(The U1LSR is a read-only register that provides status information on the UART1 TX and RX blocks)
				//U1LSR[0] is set when the U1RBR holds an unread character and is cleared when the UART1 RBR FIFO is empty.
		ch=U1RBR;	//UART1 Receiver Buffer Register
		uartTx(ch);
	VICVectAddr=0x00;	//VICVectAddr Vector Address Register. When an IRQ interrupt occurs, the IRQ service routine can read this register and jump to the
//value read.
}

void intr_init()
{
	VICVectAddr0=(unsigned long)uart1_isr;	//Vector address 0 register used to hold address of the ISR
	VICVectCntl0=0x20|7;			//Vector Control 0 register to control one of the 16 vectored IRQ slots
	VICIntEnable|=(1<<7);			//Interrupt Enable register
}

void main()
{
	//char ch;
	VPBDIV=0x02;
	PINSEL0=0X00050000;	//Pin function Select register 0
	U1IER|=(1<<0);		//UART1 Interrupt Enable Register (to enable receive Data Available Interrupt)
	uart_init();
	intr_init();
	
	while(1)
	{
	}
}
