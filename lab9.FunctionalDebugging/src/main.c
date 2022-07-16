#include "tm4c123gh6pm.h"

#define RED 0x02
#define BLUE 0x04
#define GREEN 0x08
#define YELLOW 0x0A
#define SKYBLUE 0x0C
#define WHITE 0x0E
#define PINK 0x06
#define OFF 0x00

void PORTF_init(void);
void delay(void);
void save(unsigned char repeat);

unsigned long data[50];
unsigned long sw1, sw2;

int
main(void)
{  
    PORTF_init();
    while (1) {
        sw1 = GPIO_PORTF_DATA_R & 0x10;
        sw2 = GPIO_PORTF_DATA_R & 0x01;
        if (!sw1 || !sw2) {
            GPIO_PORTF_DATA_R ^= RED; 
            save(1);
        } else {
            GPIO_PORTF_DATA_R &= ~(0x02);
            save(0);
        } 
        delay();
    }
}

/* Save state of PF4,PF1,PF0 to data array */
/* If repeat is 1, then record every call */
/* else if equals zero, record one time untile a call to save(1) */
void
save(unsigned char repeat)
{
    static unsigned char prev_call = 1;
    static unsigned char i = 0;
    if (i < 50) {
        if (prev_call == 0 && repeat == 0) {
            return;
        }
        data[i] = GPIO_PORTF_DATA_R & 0x13;
        i++;
        prev_call = repeat;
    }
}

void
PORTF_init(void)
{ 
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x00000020;     /* 1) activate clock for Port F */
    delay = SYSCTL_RCGC2_R;           /* allow time for clock to start */
#pragma GCC diagnostic pop
    GPIO_PORTF_LOCK_R = 0x4C4F434B;   /* 2) unlock GPIO Port F */
    GPIO_PORTF_CR_R = 0x1F;           /* allow changes to PF4-0 */
    GPIO_PORTF_AMSEL_R = 0x00;        /* 3) disable analog on PF */
    GPIO_PORTF_PCTL_R = 0x00000000;   /* 4) PCTL GPIO on PF4-0 */
    GPIO_PORTF_DIR_R = 0x0E;          /* 5) PF4,PF0 in, PF3-1 out */
    GPIO_PORTF_AFSEL_R = 0x00;        /* 6) disable alt funct on PF7-0 */
    GPIO_PORTF_PUR_R = 0x11;          /* enable pull-up on PF0 and PF4 */
    GPIO_PORTF_DEN_R = 0x1F;          /* 7) enable digital I/O on PF4-0 */
}

void
delay(void)
{
    volatile unsigned long ttime;
    ttime = 80000; // 0.05sec
    while (ttime) {
        ttime--;
    }
}
