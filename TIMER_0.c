// maximu delay of 32ms

void main(void) {
    DDRB=0XFF;
    TCCR0=0X05;
    while(1){
        if(TIFR & (1<<0))
        {
        PORTB =~(PORTB);
        TIFR |=(1<<0);
    }
}
}

// delay of 10 ms
/*
 * File:   AVR_TM0.c
 * Author: USER
 *
 * Created on 27 October, 2025, 11:30 AM
 */
#define F_CPU 8000000UL
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <avr/interrupt.h>



void main(void) {
    DDRB=0XFF;
    TCCR0=0X05;
    TCNT0=177;
    while(1){
        if(TIFR & (1<<0))
        {
        TCNT0=177;
        PORTB =~(PORTB);
        TIFR |=(1<<0);
    }
}
}
