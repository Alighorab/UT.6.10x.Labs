#include "tm4c123gh6pm.h"

#define GREEN 0x08
#define RED   0x02

void PortF_Init(void);
void Delay1ms(unsigned long msec);
void WaitForASLow(void);
void WaitForASHigh(void);
void SetVT(void);
void ClearVT(void);
void SetReady(void);
void ClearReady(void);

int
main(void)
{
    PortF_Init();
    while (1) {
        SetReady();
        WaitForASLow();
        ClearReady();
        Delay1ms(10);
        WaitForASHigh();
        Delay1ms(250);
        SetVT();
        Delay1ms(250);
        ClearVT();
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
WaitForASHigh(void)
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
SetVT(void)
{
    GPIO_PORTF_DATA_R |= RED;
}

/* Subroutine clears VT low */
/* Inputs:  None */
/* Outputs: None */
/* Notes:   friendly means it does not affect other bits in the port */
void
ClearVT(void)
{
    GPIO_PORTF_DATA_R &= ~RED;
}

/* Subroutine sets Ready high */
/* Inputs:  None */
/* Outputs: None */
/* Notes:   friendly means it does not affect other bits in the port */
void
SetReady(void)
{
    GPIO_PORTF_DATA_R |= GREEN;
}

/* Subroutine clears Ready low */
/* Inputs:  None */
/* Outputs: None */
/* Notes:   friendly means it does not affect other bits in the port */
void
ClearReady(void)
{
    GPIO_PORTF_DATA_R &= ~GREEN;
}

/* Subroutine to delay in units of milliseconds */
/* Inputs:  Number of milliseconds to delay */
/* Outputs: None */
/* Notes:   assumes 80 MHz clock */
void
Delay1ms(unsigned long msec)
{
    while (msec > 0) {
        volatile unsigned long count = 4000;
        while (count > 0) {
            count--;
        }
        msec--;
    }
}

// Delay1ms disassembly

// 00000324 <Delay1ms>:
//  324:	sub	sp, #8
//  326:	cbz	r0, 33c <Delay1ms+0x18>
//  328:	movw	r3, #3333	; 0xd05
// -------------- Inner Loop --------------
//  32c:	str	r3, [sp, #4]            ; takes 1 cycle to execute
//  32e:	ldr	r3, [sp, #4]            ; takes 2 to 5 cycles to execute
//  330:	cbz	r3, 338 <Delay1ms+0x14> ; takes 1 to 4 cycles to execute
//  332:	ldr	r3, [sp, #4]            ; takes 2 to 5 cycles to execute
//  334:	subs	r3, #1              ; takes 1 cycle to execute
//  336:	b.n	32c <Delay1ms+0x8>      ; takes 1 to 4 cycles to execute
// ----------------------------------------
//  338:	subs	r0, #1
//  33a:	b.n	326 <Delay1ms+0x2>
//  33c:	add	sp, #8
//  33e:	bx	lr
//

// To calculate 1ms delay:
// 1. T = 1/80,000,000 = 1.25 * 10^-8 s
// 2. Inner loop takes at most
//     L = 1 + 5 + 4 + 5 + 1 + 4 = 20 cycles
// 3. We need this peice of code to take 1 ms 
//     i = L * T = 20 * (1.25 * 10^-8) = 2.5 * 10^-7 s
//     1ms = (1/1000) / i = (1 / 1000) / (2.5 * 10^-7) = 4000 cycles
