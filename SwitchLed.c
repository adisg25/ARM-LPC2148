#include <LPC214X.H>

void delay(unsigned int);

void main()
{
	
	IO0DIR&=~(1<<15);//SW1 connected to P0.15 pin
	IO0DIR|=(1<<31);//LED connected to P0.31 pin
	
	while(1)
	{
	
		if(!(IO0PIN&(1<<15)))
		{
			delay(10);
			if(!(IO0PIN&(1<<15)))
				IO0CLR|=(1<<31);
				
			
		}
		else
		{
				IO0SET|=(1<<31);
		}
		
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