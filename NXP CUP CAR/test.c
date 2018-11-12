/***********************************************
* Author: Sahil Gogna and Patrick Landers
* Date: 11-8-18
* Description: Test all parts!
************************************************/

#include "MK64F12.h"
#include "uart.h"
#include "stdio.h"
#include "dc.h"
#include "servo.h"
#include "camera.h"

void TEST_servo(void)
{
//	char str[128];
	uart_put("Servo test mode\n\r");
	SERVO_SetServo(5);
}

void TEST_camera(void){}

void TEST_motor(void)
{
//	char str[128];
	uart_put("Motor test mode\n\r");
	for(;;){
	DC_SetDutyCycle(50,MOTOR_DRIVE);
	}
}
