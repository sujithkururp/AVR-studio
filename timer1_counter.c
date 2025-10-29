// timer1 counter uisng a T1 pin as input switch and each time press the button is print the counter value in TCNT1 regiter using uart



#define F_CPU 8000000UL
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <avr/interrupt.h>


void display(unsigned char *str) {
    while(*str) {
        while(!(UCSRA & (1<<UDRE)));  // Wait until transmit buffer is empty
        UDR = (*str++);
    }
}

void main(void) {
    TCCR1A=0X00;
    TCCR1B=0X07;
    DDRB=0X00;
    
    
    DDRD=0X02;
    UCSRA=0X00;
    UCSRB=0X18;
    UCSRC=0X86;
    UBRRL=51;
    
    int count=0;
    char buffer[20];
    while(1){
        while(PINB &(1<<1));
        while(!(PINB &(1<<1)));
        
        count=TCNT1;
        sprintf(buffer,"%d\r",count);
        display(buffer);
        display("\r \n");
        
       
    }
    return;
}
