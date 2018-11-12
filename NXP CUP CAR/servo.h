/***********************************************
* Author: Sahil Gogna and Patrick Landers
* Date: 11-8-18
* Description: Servo Header File
************************************************/
#ifndef SERVO_H_
#define SERVO_H_

#define SERVO_LEFT 4.4
#define SERVO_CENTER 6.4
#define SERVO_RIGHT 7.7

void SERVO_SetServo(double DutyCycle);
void SERVO_init(void);

#endif /* SERVO_H_ */
