/***********************************************
* Author: Sahil Gogna and Patrick Landers
* Date: 11-8-18
* Description: DC Motor and Servo Header File
************************************************/
#ifndef MOTORS_H_

#define MOTORS_H_

void SetDutyCycle(unsigned int DutyCycle, unsigned int Frequency, int dir);
void SetServo(unsigned int DutyCycle, unsigned int Frequency);
void InitPWM(void);
void PWM_ISR(void);

#endif /* PWM_H_ */