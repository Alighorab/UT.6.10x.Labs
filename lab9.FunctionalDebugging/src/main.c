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
void systic_init(void);
void delay(void);

unsigned long time[50];
unsigned long data[50];
unsigned long led;

int
main(void)
{  
    unsigned long i, last, now;
    PORTF_init();
    systic_init();
    i = 0;
    last = NVIC_ST_CURRENT_R;
    while(1){
        led = GPIO_PORTF_DATA_R;
        led = led ^ RED;
        GPIO_PORTF_DATA_R = led;
        if (i < 50) {
            now = NVIC_ST_CURRENT_R;
            time[i] = (last - now) & 0x00FFFFFF;
            data[i] = GPIO_PORTF_DATA_R&0x02;
            last = now;
            i++;
        }
        delay();
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
systic_init(void)
{
    NVIC_ST_CTRL_R = 0;               /* disable SysTick during setup */
    NVIC_ST_RELOAD_R = 0x00FFFFFF;    /* maximum reload value */
    NVIC_ST_CURRENT_R = 0;            /* any write to current clears it */
    NVIC_ST_CTRL_R = 0x00000005;      /* enable SysTick with core clock */
}

void
delay(void)
{
    volatile unsigned long ttime;
    ttime = 160000; // 0.1sec
    while (ttime) {
        ttime--;
    }
}
