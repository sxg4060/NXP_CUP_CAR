/***********************************************
* Author: Sahil Gogna and Patrick Landers
* Date: 11-8-18
* Description: DC Motor and Servo Test
************************************************/

#include "MK64F12.h"
#include "uart.h"
#include "motors.h"
#include "stdio.h"

void initialize();
void en_interrupts();
void delay();

int main(void){
	
	char str[100];
	
	initialize();
	
	//Generate 20% duty cycle at 10kHz, 25% at 50Hz
	SetDutyCycle(20, 10000, 1);
	SetServo(25, 50);

}

/**
 * Waits for a delay (in milliseconds)
 * 
 * del - The delay in milliseconds
 */
void delay(int del){
	int i;
	for (i=0; i<del*50000; i++){
		// Do nothing
	}
}

void initialize()
{
	// Initialize UART
	uart_init();	
	
	// Initialize the FlexTimer
	InitPWM();
}