/***********************************************
* Author: Sahil Gogna and Patrick Landers
* Date: 11-8-18
* Description: DC Motor and Servo Initialization
************************************************/

#include "MK64F12.h"
#include "dc.h"
#include "stdio.h"
#include "uart.h"

/*From clock setup 0 in system_MK64f12.c*/
#define DEFAULT_SYSTEM_CLOCK 20485760u /* Default System clock value */
#define CLOCK					20485760u
#define PWM1_FREQUENCY_SERVO 			50
#define FTM3_MOD_VALUE			(CLOCK/128/PWM1_FREQUENCY_SERVO)

static volatile unsigned int PWM0Tick = 0;
static volatile unsigned int PWM1Tick = 0;


/*
* Function responsible for utilizing Servo motors 
*/
void SERVO_SetServo(double DutyCycle)
{
	char str[100];
	
	sprintf(str, "Setting Duty Cycle: %f Frequency: %d\n\r", DutyCycle, PWM1_FREQUENCY_SERVO);
	uart_put(str);
	
	// Calculate the new cutoff value
	uint16_t mod = (uint16_t) (((CLOCK/128/PWM1_FREQUENCY_SERVO) * DutyCycle) / 100);
  
	FTM3_C3V = mod;

	// Update the clock to the new frequency
	FTM3_MOD = (CLOCK/128/PWM1_FREQUENCY_SERVO);
}

/*
 * Initialize the FlexTimer for PWM
 */
void SERVO_init(void)
{
	// 12.2.13 Enable the Clock to the FTM0 Module
	SIM_SCGC3 |= SIM_SCGC3_FTM3_MASK;
	
	// Enable clock on PORT A so it can output
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	// 11.4.1 Route the output of FTM channel 0 to the pins
	// Use drive strength enable flag to high drive strength
	//These port/pins may need to be updated for the K64 <Yes, they do. Here are two that work.>
	
	// SERVO
	PORTD_PCR3	= PORT_PCR_MUX(4)	 | PORT_PCR_DSE_MASK; //FTM 3 Ch3
	
	// 39.3.10 Disable Write Protection
	FTM3_MODE |= FTM_MODE_WPDIS_MASK;
	
	// 39.3.4 FTM Counter Value
	// Initialize the CNT to 0 before writing to MOD
	FTM3_CNT = 0;
	
	// 39.3.8 Set the Counter Initial Value to 0
	FTM3_CNTIN = 0;
	
	// 39.3.5 Set the Modulo resister
	FTM3_MOD = FTM3_MOD_VALUE;
	
	//FTM0->MOD = (DEFAULT_SYSTEM_CLOCK/(1<<7))/1000;

	// 39.3.6 Set the Status and Control of both channels
	// Used to configure mode, edge and level selection
	// See Table 39-67,  Edge-aligned PWM, High-true pulses (clear out on match)
	
	FTM3_C3SC |= FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
	FTM3_C3SC &= ~FTM_CnSC_ELSA_MASK;

	
	// 39.3.3 FTM Setup
	// Set prescale value to 1 
	// Chose system clock source
	// Timer Overflow Interrupt Enable
	FTM3_SC = FTM_SC_PS(7) | FTM_SC_CLKS(1);
	

	
	// Enable Interrupt Vector for FTM
    //NVIC_EnableIRQ(FTM0_IRQn);
}

