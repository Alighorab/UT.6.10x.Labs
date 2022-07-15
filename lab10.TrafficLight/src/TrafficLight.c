#include "tm4c123gh6pm.h"
#include "TrafficLight.h"


void SysTick_init(void);
void SysTick_wait(unsigned long delay);
void SysTick_wait_10ms(unsigned long delay);
void PLL_init(void);
void PortB_init(void);
void PortE_init(void);
void PortF_init(void);

int
main(void)
{
    system_init();
	while (1) {
        traffic_light[state].state_function();
        SysTick_wait_10ms(traffic_light[state].delay);
        system_read_event();
        state = trans_matrix[state][event].next_state;
	}
}


static void
system_out(unsigned long s)
{
    unsigned long red, green, out;
    red = (s & 0x01) << 1;
    green = (s & 0x02) << 2;
    out = red | green;

    GPIO_PORTB_DATA_R = s >> 2;
    GPIO_PORTF_DATA_R = out;
}

void
system_init(void)
{
    PLL_init();
    PortB_init();
    PortE_init();
    PortF_init();
    SysTick_init();
}

void
system_go_south(void)
{
    system_out(GO_SOUTH);
}

void
system_wait_south(void)
{
    system_out(WAIT_SOUTH);
}

void
system_go_east(void)
{
    system_out(GO_EAST);
}

void
system_wait_east(void)
{
    system_out(WAIT_EAST);
}

void
system_walk_green(void)
{
    system_out(WALK_GREEN);
}

void
system_walk_red1(void)
{
    system_out(WALK_RED1);
}

void
system_walk_off1(void)
{
    system_out(WALK_OFF1);
}

void
system_walk_red2(void)
{
    system_out(WALK_RED2);
}

void
system_walk_off2(void)
{
    system_out(WALK_OFF2);
}

void
system_walk_red3(void)
{
    system_out(WALK_RED3);
}

void
system_walk_off3(void)
{
    system_out(WALK_OFF3);
}

void
system_walk_red(void)
{
    system_out(WALK_RED);
}

void
system_read_event(void)
{
    event = GPIO_PORTE_DATA_R & 0x07;
}

void
SysTick_init(void)
{
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_CTRL_R = 0x00000005;
}

void
SysTick_wait(unsigned long delay)
{
    NVIC_ST_RELOAD_R = delay - 1;
    NVIC_ST_CURRENT_R = 0;
    while ((NVIC_ST_CTRL_R&0x00010000)==0) {
        ;
    }
}

void
SysTick_wait_10ms(unsigned long delay)
{
    unsigned long i;
    for (i=0; i < delay; i++) {
        SysTick_wait(800000);
    }
}

void
PLL_init(void)
{
    SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
    SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;
    SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;
    SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;
    SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO;
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
    SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000) + (4<<22);
    while ((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS) == 0) {
        ;
    }
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}

void
PortF_init(void)
{ 
    SYSCTL_RCGC2_R |= 0x00000020;
    while((SYSCTL_PRGPIO_R&0x00000020) == 0);
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = 0x1F;
    GPIO_PORTF_AMSEL_R = 0x00;
    GPIO_PORTF_PCTL_R = 0x00000000;
    GPIO_PORTF_DIR_R = 0x0E;
    GPIO_PORTF_AFSEL_R = 0x00;
    GPIO_PORTF_DEN_R = 0x0E;
}

void
PortE_init(void)
{
    SYSCTL_RCGC2_R |= 0x00000010;
    while((SYSCTL_PRGPIO_R&0x00000010) == 0);
    GPIO_PORTE_LOCK_R = 0x4C4F434B;
    GPIO_PORTE_CR_R = 0x1F;
    GPIO_PORTE_AMSEL_R = 0x00;
    GPIO_PORTE_PCTL_R = 0x00000000;
    GPIO_PORTE_DIR_R = 0x00;
    GPIO_PORTE_AFSEL_R = 0x00;
    GPIO_PORTE_DEN_R = 0xFF;

}

void
PortB_init(void)
{
    SYSCTL_RCGC2_R |= 0x00000002;
    while((SYSCTL_PRGPIO_R&0x00000002) == 0);
    GPIO_PORTB_LOCK_R = 0x4C4F434B;
    GPIO_PORTB_CR_R = 0xFF;
    GPIO_PORTB_AMSEL_R = 0x00;
    GPIO_PORTB_PCTL_R = 0x00000000;
    GPIO_PORTB_DIR_R = 0xFF;
    GPIO_PORTB_AFSEL_R = 0x00;
    GPIO_PORTB_DEN_R = 0xFF;
}
