/*
 * File:   avr_interrupt.c
 * Author: USER
 *
 * Created on 24 October, 2025, 11:31 AM
 */


#define F_CPU 8000000UL
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <avr/interrupt.h>


ISR(INT0_vect){
    PORTC ^=(1<<7);//TOGGLING THE PORTC0
}
ISR(INT1_vect){
    PORTC ^=(1<<6);//TOGGLING THE PORTC1
}

void main(void) {
    
    DDRD=0X00;
    DDRC=0XF0;
    MCUCR=0X0E;
    GICR=0XC0;
    sei();
    while(1);
    return;
}
