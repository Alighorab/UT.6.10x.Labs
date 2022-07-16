#include "tm4c123gh6pm.h"

void PORTF_init(void);
void delay(void);

int
main(void)
{
    PORTF_init();
    while (1) {
        delay();
        if ((GPIO_PORTF_DATA_R & (1 << 4)) == 0x00) {
            GPIO_PORTF_DATA_R ^= (1 << 2);
        } else {
            GPIO_PORTF_DATA_R |= (1 << 2);
        }
    }
}


void
PORTF_init(void)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF; /* 1) activate clock for Port F */
    delay = SYSCTL_RCGC2_R;
#pragma GCC diagnostic pop
    GPIO_PORTF_AMSEL_R = 0x00;            /* 3) disable analog on PF */
    GPIO_PORTF_PCTL_R = 0x00000000;       /* 4) PCTL GPIO on PF4-0 */
    GPIO_PORTF_DIR_R &= ~(1 << 4);        /* 5) PF4 as input */
    GPIO_PORTF_DIR_R |= (1 << 2);         /* 5) PF2 as output */
    GPIO_PORTF_AFSEL_R = 0x00;            /* 6) disable alt funct on PF7-0 */
    GPIO_PORTF_PUR_R = 0x10;              /* enable pull-up on PF4 */
    GPIO_PORTF_DEN_R |= 0x14;             /* 7) enable digital I/O on PF4-2 */
}

void
delay(void)
{
    unsigned long volatile time;
    time = 727240*200/91/6;  // 0.1sec
    while(time){
        time--;
    }
}
