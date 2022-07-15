#include "tm4c123gh6pm.h"

#define GREEN 0x08
#define RED   0x02

void PORTF_init(void);
void delay_1ms(unsigned long msec);
void wait_for_as_low(void);
void wait_for_as_high(void);
void set_vt(void);
void clear_vt(void);
void set_ready(void);
void clear_ready(void);

int
main(void)
{
    PORTF_init();
    while (1) {
        set_ready();
        wait_for_as_low();
        clear_ready();
        delay_1ms(10);
        wait_for_as_high();
        delay_1ms(250);
        set_vt();
        delay_1ms(250);
        clear_vt();
    }
}

/* Subroutine to initialize port F pins for input and output */
/* PF4 is input SW1 and PF3-1 is output LEDs */
/* Inputs: None */
/* Outputs: None */
/* Notes: ... */
void
PORTF_init(void)
{ 
    SYSCTL_RCGC2_R |= 0x00000020;      /* 1) F clock */
    while ((SYSCTL_PRGPIO_R & 0x00000020) == 0); /* wait for PORTF to be ready */
    GPIO_PORTF_AMSEL_R &= 0x00;        /* 2) disable analog function */
    GPIO_PORTF_PCTL_R &= 0x00000000;   /* 3) GPIO clear bit PCTL */
    GPIO_PORTF_DIR_R &= ~0x10;         /* 4.1) PF4 input, */
    GPIO_PORTF_DIR_R |= 0x0E;          /* 4.2) PF3,2,1 output */
    GPIO_PORTF_AFSEL_R &= 0x00;        /* 5) no alternate function */
    GPIO_PORTF_PUR_R |= 0x10;          /* 6) enable pullup resistor on PF4  */
    GPIO_PORTF_DEN_R |= 0x1E;          /* 7) enable digital pins PF4-PF1 */
}

/* Subroutine reads AS input and waits for signal to be low */
/* If AS is already low, it returns right away */
/* If AS is currently high, it will wait until it to go low */
/* Inputs:  None */
/* Outputs: None */
void
wait_for_as_low(void)
{
    while (GPIO_PORTF_DATA_R & 0x10) {
        ;
    }
}

/* Subroutine reads AS input and waits for signal to be high */
/* If AS is already high, it returns right away */
/* If AS is currently low, it will wait until it to go high */
/* Inputs:  None */
/* Outputs: None */
void
wait_for_as_high(void)
{
    while (!(GPIO_PORTF_DATA_R & 0x10)) {
        ;
    }
}

/* Subroutine sets VT high */
/* Inputs:  None */
/* Outputs: None */
/* Notes:   friendly means it does not affect other bits in the port */
void
set_vt(void)
{
    GPIO_PORTF_DATA_R |= RED;
}

/* Subroutine clears VT low */
/* Inputs:  None */
/* Outputs: None */
/* Notes:   friendly means it does not affect other bits in the port */
void
clear_vt(void)
{
    GPIO_PORTF_DATA_R &= ~RED;
}

/* Subroutine sets Ready high */
/* Inputs:  None */
/* Outputs: None */
/* Notes:   friendly means it does not affect other bits in the port */
void
set_ready(void)
{
    GPIO_PORTF_DATA_R |= GREEN;
}

/* Subroutine clears Ready low */
/* Inputs:  None */
/* Outputs: None */
/* Notes:   friendly means it does not affect other bits in the port */
void
clear_ready(void)
{
    GPIO_PORTF_DATA_R &= ~GREEN;
}

/* Subroutine to delay in units of milliseconds */
/* Inputs:  Number of milliseconds to delay */
/* Outputs: None */
/* Notes:   assumes 80 MHz clock */
void
delay_1ms(unsigned long msec)
{
    while (msec > 0) {
        volatile unsigned long count = 2000;
        while (count > 0) {
            count--;
        }
        msec--;
    }
}
