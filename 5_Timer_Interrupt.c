#include <LPC214X.H>

int flag=0;

void timer_init()
{
	T1PR=59999;//T1PR (Timer1 Prescale Register),It holds the maximum value of the Prescale Counter.
	T1MCR|=(1<<3)|(1<<4);//Interrupt on MR1: an interrupt is generated when MR1 matches the value in the TC.and Reset on MR1: the TC will be reset if MR1 matches it.
	T1MR1=1000;//Match Register 1.(TIMER/COUNTER1 register map),contains 1000 bcz 1000*1msec=1sec.
	T1TCR=(1<<1);//T1TCR (Timer1 Timer Control Register),Bit1=1,Counter Reset.
	T1TCR=(1<<0);//the Timer Counter and Prescale Counter are enabled for counting
}

void TIMER_ISR(void)__irq
{
	if(flag==0)
	{
		IO0SET|=(1<<31);
		flag =1;
	}
	else
	{
		IO0CLR|=(1<<31);
		flag = 0;
	}
	T1IR |= (1<<1);//Interrupt flag for match channel 1.Writting 1 to it will reset the interrupt.
	VICVectAddr=0x00;
}
 
void intr_init()
{
	VICVectAddr0=(unsigned long)TIMER_ISR;
	VICVectCntl0=0x20|5;
	VICIntEnable|=(1<<5);
}

void main()
{
	IO0DIR|=(1<<31);
	VPBDIV=0x01;
	timer_init();
	intr_init();
	while(1)
	{
	}		
}

