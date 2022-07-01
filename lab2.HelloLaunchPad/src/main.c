#include "tm4c123gh6pm.h"

void PORTF_init(void);
void delay(void);


int
main(void)
{ 
    unsigned long sw1;
    PORTF_init();
    while (1) {
        sw1 = GPIO_PORTF_DATA_R&0x10;
        if (sw1 == 0x00) {
            GPIO_PORTF_DATA_R = 0x08;
        } else {
            GPIO_PORTF_DATA_R = 0x02;
        }
        delay();
        GPIO_PORTF_DATA_R = 0x04;
        delay();
    }
}

void
PORTF_init(void)
{
    /* #pragma to ignre a warning */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x00000020;    /* 1) F clock */
    delay = SYSCTL_RCGC2_R;          /* delay */
#pragma GCC diagnostic pop
    GPIO_PORTF_LOCK_R = 0x4C4F434B;  /* 2) unlock PortF PF0 */
    GPIO_PORTF_CR_R = 0x1F;          /* allow changes to PF4-0 */
    GPIO_PORTF_AMSEL_R = 0x00;       /* 3) disable analog function */
    GPIO_PORTF_PCTL_R = 0x00000000;  /* 4) GPIO clear bit PCTL */
    GPIO_PORTF_DIR_R = 0x0E;         /* 5) PF4,PF0 input, PF3,PF2,PF1 output */
    GPIO_PORTF_AFSEL_R = 0x00;       /* 6) no alternate function */
    GPIO_PORTF_PUR_R = 0x11;         /* enable pullup resistors on PF4,PF0 */
    GPIO_PORTF_DEN_R = 0x1F;         /* 7) enable digital pins PF4-PF0 */
}

void
delay(void)
{
    unsigned long volatile time;
    time = 727240*200/91;  // 0.1sec
    while(time){
        time--;
    }
}
