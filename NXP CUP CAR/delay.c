/***********************************************
* Author: Sahil Gogna and Patrick Landers
* Date: 11-8-18
* Description: Delay Function
************************************************/

/**
 * Waits for a delay (in milliseconds)
 * del - The delay in milliseconds
 */
void delay(int del){
	int i;
	for (i=0; i<del*50000; i++);
}
