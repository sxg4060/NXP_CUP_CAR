/***********************************************
* Author: Sahil Gogna and Patrick Landers
* Date: 11-8-18
* Description: Camera Header
************************************************/
#ifndef CAMERA_H
#define CAMERA_H

#define DEFAULT_SYSTEM_CLOCK 20485760u

#define INTEGRATION_TIME .0075f

#define CAMERA_LINE_THRESHOLD 8000

void init_FTM2(void);
void init_GPIO(void);
void init_PIT(void);
void init_ADC0(void);
void FTM2_IRQHandler(void);
void PIT1_IRQHandler(void);
void ADC0_IRQHandler(void);
void camera_init(void);

uint16_t* CAMERA_getLine(void);
int CAMERA_getDebugcamdata(void);
int CAMERA_getCapcnt(void);
void CAMERA_setCapcnt(int);

#endif /* ifndef CAMERA_H */
