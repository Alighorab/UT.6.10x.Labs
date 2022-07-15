#include "tm4c123gh6pm.h"

void PORTE_init(void);
unsigned long switch_read(void);
void LED_on(void);
void LED_toggle(void);
void delay_ms(unsigned long msec);

int
main(void) 
{
    unsigned long sw;
    PORTE_init();
    LED_on();
	while (1) {
        delay_ms(100);
        sw = switch_read();
        if (sw == 0) {
            LED_on();
        } else {
            LED_toggle();
        }
	}
}

/* switch -> PE0 */
/* LED -> PE1 */
/* Deactivate internal pull-up resistor */
void
PORTE_init(void)
{
    SYSCTL_RCGC2_R |= 0x10;
    while ((SYSCTL_PRGPIO_R & 0x10) == 0) {}
    GPIO_PORTE_AMSEL_R &= ~0x03;
    GPIO_PORTE_PCTL_R = 0x00000000;
    GPIO_PORTE_DIR_R &= ~0x01;
    GPIO_PORTE_DIR_R |= 0x02;
    GPIO_PORTE_AFSEL_R = 0x00;
    GPIO_PORTE_PUR_R &= ~0x03;
    GPIO_PORTE_DEN_R |= 0x03;
}

unsigned long
switch_read(void)
{
    return GPIO_PORTE_DATA_R & 0x01;
}

void
LED_on(void)
{
    GPIO_PORTE_DATA_R |= 0x02;
}

void
LED_toggle(void)
{
    GPIO_PORTE_DATA_R ^= 0x02;
}

void
delay_ms(unsigned long msec)
{
    while (msec > 0) {
        volatile unsigned long count = 1600; // 0.1ms
        while (count > 0) {
            count--;
        }
        msec--;
    }
}
