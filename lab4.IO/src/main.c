#include "tm4c123gh6pm.h"

#define BLUE  0x04
#define GREEN 0x08
#define RED   0x02

unsigned long sw1, sw2;

void PORTF_init(void);

int
main(void)
{    
    PORTF_init();
    while (1) {
        sw1 = (GPIO_PORTF_DATA_R & 0x10) ^ 0x10;
        sw2 = (GPIO_PORTF_DATA_R & 0x01) ^ 0x01;
        if (sw1 && sw2) {
            GPIO_PORTF_DATA_R = BLUE;
        } else if (sw1 && !sw2) {
            GPIO_PORTF_DATA_R = GREEN;
        } else if (!sw1 && sw2) {
            GPIO_PORTF_DATA_R = RED;
        } else {
            GPIO_PORTF_DATA_R = 0x00;
        }
    }
}

void
PORTF_init(void)
{ 
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
    delay = SYSCTL_RCGC2_R;           // delay   
#pragma GCC diagnostic pop
    GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
    GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0       
    GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
    GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
    GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
    GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
    GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0       
    GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0        
}
