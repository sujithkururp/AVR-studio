


#define F_CPU 8000000UL
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <avr/interrupt.h>

void main(void) {
    TCCR1A=0X00;
    TCCR1B=0X05;
    DDRB=0XFF;
    TCNT1=57723;
    while(1){
        while(!(TIFR &(1<<2)));
        PORTB =~(PORTB);
        TIFR |=(1<<2); 
        TCNT1=57723;
    }
    return;
}
