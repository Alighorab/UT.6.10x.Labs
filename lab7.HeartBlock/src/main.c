#include "tm4c123gh6pm.h"

void PortF_Init(void);
void Delay1ms(unsigned long msec);
void WaitForASLow(void);
void WaitForASHigh(void);
void SetVT(void);
void ClearVT(void);
void SetReady(void);
void ClearReady(void);

// a) Ready signal goes high
// b) wait for switch to be pressed
// c) Ready signal goes low
// d) wait 10ms
// e) wait for switch to be released
// f) wait 250ms
// g) VT signal goes high
// h) wait 250ms
// i) VT signal goes low

int
main(void)
{
    PortF_Init();
    while (1) {
    }
}

/* Subroutine to initialize port F pins for input and output */
/* PF4 is input SW1 and PF3-1 is output LEDs */
/* Inputs: None */
/* Outputs: None */
/* Notes: ... */
void
PortF_Init(void)
{ 
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x00000020;      // 1) F clock
    delay = SYSCTL_RCGC2_R;            // delay to allow clock to stabilize     
#pragma GCC diagnostic pop
    GPIO_PORTF_AMSEL_R &= 0x00;        // 2) disable analog function
    GPIO_PORTF_PCTL_R &= 0x00000000;   // 3) GPIO clear bit PCTL  
    GPIO_PORTF_DIR_R &= ~0x10;         // 4.1) PF4 input,
    GPIO_PORTF_DIR_R |= 0x0E;          // 4.2) PF3,2,1 output  
    GPIO_PORTF_AFSEL_R &= 0x00;        // 5) no alternate function
    GPIO_PORTF_PUR_R |= 0x10;          // 6) enable pullup resistor on PF4       
    GPIO_PORTF_DEN_R |= 0x1E;          // 7) enable digital pins PF4-PF1
}

/* Subroutine reads AS input and waits for signal to be low */
/* If AS is already low, it returns right away */
/* If AS is currently high, it will wait until it to go low */
/* Inputs:  None */
/* Outputs: None */
void
WaitForASLow(void)
{

}

/* Subroutine reads AS input and waits for signal to be high */
/* If AS is already high, it returns right away */
/* If AS is currently low, it will wait until it to go high */
/* Inputs:  None */
/* Outputs: None */
void
WaitForASHigh(void)
{
    
}

/* Subroutine sets VT high */
/* Inputs:  None */
/* Outputs: None */
/* Notes:   friendly means it does not affect other bits in the port */
void
SetVT(void)
{
    
}

/* Subroutine clears VT low */
/* Inputs:  None */
/* Outputs: None */
/* Notes:   friendly means it does not affect other bits in the port */
void
ClearVT(void)
{
    
}

/* Subroutine sets Ready high */
/* Inputs:  None */
/* Outputs: None */
/* Notes:   friendly means it does not affect other bits in the port */
void
SetReady(void)
{
    
}

/* Subroutine clears Ready low */
/* Inputs:  None */
/* Outputs: None */
/* Notes:   friendly means it does not affect other bits in the port */
void
ClearReady(void)
{
    
}

/* Subroutine to delay in units of milliseconds */
/* Inputs:  Number of milliseconds to delay */
/* Outputs: None */
/* Notes:   assumes 80 MHz clock */
void
Delay1ms(unsigned long msec)
{

}

