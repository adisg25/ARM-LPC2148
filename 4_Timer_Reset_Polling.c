#include <LPC214X.H>
void timer_init()
{
	//T1CTCR&=~(1<<0)|(1<<1);//T1CTCR (Timer1 Counter Control Register),Used to select between timer or counter mode.
	T1PR=59999;//T1PR (Timer1 Prescale Register),It holds the maximum value of the Prescale Counter.
	T1TCR=(1<<1);//T1TCR (Timer1 Timer Control Register),Bit1=1,Counter Reset.
	T1MR1=1000;//Match Register 1.(TIMER/COUNTER1 register map),contains 1000 bcz 1000*1msec=1sec.
}

void timer_delay()
{
	T1MCR|=(1<<4);//Match Control Register,Reset on MR1: the TC will be reset if MR1 matches it.
	//T1MCR|=(1<<5);//Match Control Register,Stop on MR1: the TC will be stopped if MR1 matches it.
	T1TCR=(1<<1);//T1TCR (Timer1 Timer Control Register),Bit1=1,Counter Reset.
	T1TCR=(1<<0);//T1TCR (Timer1 Timer Control Register),Bit0=1,Counter Enable.
	while(!(T1TC==1000));//Timer Counter Register Map.
}

void main()
{
	IO0DIR|=(1<<31);
	VPBDIV=0x01;
	timer_init();

	while(1)
	{
		IO0SET|=(1<<31);
		timer_delay();
		IO0CLR|=(1<<31);
		timer_delay();
	}
}

