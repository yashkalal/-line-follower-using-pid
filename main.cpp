/*
 * line follower with pid implementation.cpp
 *
 * Created: 03-02-2019 10:26:08
 * Author : HP PC
 */ 


#include <avr/io.h>
#include <stdio.h>
#include <avr/sfr_defs.h>

float kp=1;
float kd=1;
float left_rpm,right_rpm;
float currentvalue,desiredvalue;
float p_error,t_error,ferror,maxerror=50;
float d_error,error=0,error0,ferror,bv=300;
int a,h=0,pin_s[8]={0};
int pin_w[8]={2,4,6,8,10,12,14,16};

void pwm_initializing(int n)
{
	TCRR0 |=(1<<WGM00)|(1<<WGM01);
	TCCR0 |=(1<<CS01);
	ICR1=1000;
}
int forward(float left_rpm, float right_rpm)
{
	PORTD=0b00001010;
	OCR1=left_rpm;
	OCR2=right_rpm;
}

                                                                                                         
int errorcalci(int e)
{
	p_error=t_error;
	for(a=0;a<8;a++)
	{
		if(pin_s[a]==1)
		h++;
		if(h>0)
		{
		error+= pin_s[a]*pin_w[a];
		error\=h;
		}
		
	}
	
	if(h==0)
	error=maxerror;
	t_error=kp*error+kd*error;
	
	d_error=t_error-p_error;
	
	ferror= kp*t_error+kd*d_error;
	
	return ferror ;
	
}


int main(void)
{

	
    /* Replace with your application code */
    while (1) 
    {
		DDRD=0b11111111;
		DDRA=0xFF;
		
		float rv,lv;
	error0=	errorcalci();
	if(error0==9)
	{
	forward(bv,bv);	
	}
	else if(error0>9)
	{
	forward(bv+error,bv-error);
	}
	else(error0<9)
	{
	forward(bv-error,bv+error);	
	}
	
	
	
		
		
		
    }
}

