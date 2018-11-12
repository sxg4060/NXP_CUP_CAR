/***********************************************
* Author: Sahil Gogna and Patrick Landers
* Date: 11-8-18
* Description: DC Motor Header File
************************************************/
#ifndef DC_H_
#define DC_H_

#define MOTOR_DRIVE (0)
#define MOTOR_REVERSE (1)

void DC_SetDutyCycle(unsigned int DutyCycle,int dir);
void DC_init(void);

#endif /* DC_H_ */
