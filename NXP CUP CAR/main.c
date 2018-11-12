/***********************************************
* Author: Sahil Gogna and Patrick Landers
* Date: 11-8-18
* Description: Main Program File
************************************************/

#include "uart.h"
#include "stdio.h"
#include "dc.h"
#include "servo.h"
#include "camera.h"
#include "delay.h"
#include "test.h"
#include "MK64F12.h"

#define IDEAL_CENTER 57
#define DEBUG 0

//Prototypes
void delay(int);
void initializePeripherals(void);

void cameraTest_matlab(void);
void servoTest(void);
void motorTest(void);

void cameraAndServo(void);


int main(void){
	cameraAndServo();
	//motorTest();
} //main

void cameraAndServo(void){
	if(DEBUG){uart_init();}
	uart_put("Running camera control servo test\n\r");
	camera_init();
	SERVO_init();
	
	double doody = SERVO_CENTER;
	SERVO_SetServo(doody);
	
	/* STATE
		0:	Looking for 3 above threshold (white) RIGHT of track
		1:	Looking for 3 below threshold (black) LEFT of track
		2:	Done
	*/
	int state=0;
	int track_right=0;
	int track_left=0;
	signed int track_center=0;
	
	int a,b,c;
	
	int i;
	uint16_t* duData;
	for(;;) {
		if(DEBUG){delay(70);}
		a=0;
		b=0;
		c=0;
		state=0;
		track_right=0;
		track_left=0;
		
		GPIOB_PCOR |= (1 << 22);
		
		// send the array over uart
		uart_put("||\n\r");
		duData = CAMERA_getLine();
		
		a=duData[0];
		b=duData[1];
		uart_put("#");
		uart_put("#");
		for (i = 2; i < 127; i++) {
			a=b;b=c;c=duData[i];			//Update last three data points
			
			if(!state && a > CAMERA_LINE_THRESHOLD && b > CAMERA_LINE_THRESHOLD && c > CAMERA_LINE_THRESHOLD){
				track_right = i;
				uart_put("R");
				state++;
			}
			else if(state==1 && a < CAMERA_LINE_THRESHOLD && b < CAMERA_LINE_THRESHOLD && c < CAMERA_LINE_THRESHOLD){
				track_left = i-2;
				uart_put("L");
				state++;
			}
			else if(c > CAMERA_LINE_THRESHOLD){
				uart_put("-");
			}
			else{
				uart_put("#");
			}
			
		}
		
		uart_put("||\n\r");
		track_center = ((track_left - track_right) / 2) + track_right;
		printf("Center at %d :: Center error is: %d\n\r",track_center, IDEAL_CENTER-track_center);
		
		//Positive error is to far LEFT
		if(IDEAL_CENTER-track_center > 0){
			uart_put("Detected line on LEFT! Turning car RIGHT.\n\r");
			//if(doody<SERVO_RIGHT){doody += (IDEAL_CENTER-track_center)*0.1;}
		}
		//Negative error is to far RIGHT
		else if(IDEAL_CENTER-track_center < 0){
			uart_put("Detected line on RIGHT! Turning car LEFT.\n\r");
			//if(doody>SERVO_LEFT){doody += (IDEAL_CENTER-track_center)*0.1;}
		}
		
		if(track_center<33){
			doody=SERVO_RIGHT;
		}
		else if(track_center<=96){
			doody = (((SERVO_RIGHT-SERVO_LEFT)/(96-33))*(96-track_center))+SERVO_LEFT;
		}
		else{
			doody=SERVO_LEFT;
		}
		SERVO_SetServo(doody);
		
		CAMERA_setCapcnt(0);
		GPIOB_PSOR |= (1 << 22);

	} //for
}

/*
 *	-- initializePeripherals --
 *
 * Calls initialization functions for each
 * peripheral used in this excercise
 *
 * UART   : for debug statements
 * MOTOR1 : PWM for motor 1
 * MOTOR2 : PWM for motor 2
 * SERVO  : PWM for Servo
 * CAMERA
 *
*/
void init(void){
	uart_init();
	DC_init();
	SERVO_init();
	camera_init();
}




void cameraTest_matlab(void){
	uart_init();
	uart_put("Running camera matlab test\n\r");
	camera_init();
	
	//int i;
	for(;;) {
		if (CAMERA_getDebugcamdata()) {
			// Every 2 seconds
			//if (capcnt >= (2/INTEGRATION_TIME)) {
			if (CAMERA_getCapcnt() >= (500)) {
				GPIOB_PCOR |= (1 << 22);
				// send the array over uart
				uart_put("-1\n\r");
				//for (i = 0; i < 127; i++) {
				//	uart_put("%i\n", CAMERA_getLine()[i]);
				//}
				uart_put("-2\n\r");
				CAMERA_setCapcnt(0);
				GPIOB_PSOR |= (1 << 22);
			}
		}

	} //for
}

void servoTest(void){
	uart_init();
	uart_put("Running servo test\n\r");
	SERVO_init();
	
	double doody;
	for(;;) {
		switch(uart_getchar()){
			case '1':
				if(doody<100){doody+=0.1;}
				if(doody>100){doody=100;}
				break;
			case '2':
				if(doody>0){doody-=0.1;}
				if(doody<0){doody=0;}
				break;
			case '3':
				if(doody<100){doody+=1;}
				if(doody>100){doody=100;}
				break;
			case '4':
				if(doody>0){doody-=1;}
				if(doody<0){doody=0;}
				break;	
			case '5':
				if(doody<100){doody+=10;}
				if(doody>100){doody=100;}
				break;
			case '6':
				if(doody>0){doody-=10;}
				if(doody<0){doody=0;}
				break;
		}
		SERVO_SetServo(doody);
		delay(5);
	}
}

void motorTest(void){
	uart_init();
	uart_put("Running motor test\n\r");
	DC_init();
	
	int doody;
	int dir;
	for(;;) {
		switch(uart_getchar()){
			case 'f':
			case 'F':
				uart_put("FORWARD\n\r");
				dir = MOTOR_DRIVE;
				break;
			case 'r':
			case 'R':
				uart_put("REVERSE\n\r");
				dir = MOTOR_REVERSE;
				break;
			case '1':
				if(doody<100){doody+=1;}
				if(doody>100){doody=100;}
				break;
			case '2':
				if(doody>0){doody-=1;}
				if(doody<0){doody=0;}
				break;	
			case '3':
				if(doody<100){doody+=10;}
				if(doody>100){doody=100;}
				break;
			case '4':
				if(doody>0){doody-=10;}
				if(doody<0){doody=0;}
				break;
		}

		DC_SetDutyCycle(doody, dir);
		delay(5);
	}
}
