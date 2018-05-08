#include <LPC214X.H>

void delay(unsigned int);
void pll_init(void);

int main()
{
	IO0DIR|=(1<<31);//LED connnected to P0.31 and direction set as output
	IO1DIR|=(1<<25);//Buzzer connected to P1.25 and direction set as output
	
	while(1)
	{
		IO0SET|=(1<<31);
		IO1SET|=(1<<25);
		delay(1000);
		IO0CLR|=(1<<31);
		IO1CLR|=(1<<25);
		delay(1000);
	}
	

}
void delay(unsigned int count)
{
	unsigned int i,j;
	for(i=0;i<count;i++)
	{
		for(j=0;j<3000;j++);
	}
}
void pll_init()
{
	PLL0CON=0x01;//Enable PLL.
	PLL0CFG|=(1<<0)|(1<<1)|(1<<5);//0x24 multiplier and divider set as 5 and 2 respectively.
	PLL0FEED=0xAA;//PLL Feed Sequence
	PLL0FEED=0x55;
	
	while(!(PLL0STAT&(1<<10)));//checking if PLL locked???
	PLL0CON=0x03;//connect PLL
	PLL0FEED=0xAA;//PLL Feed Sequence
	PLL0FEED=0x55;
	VPBDIV=0x01;
	
}