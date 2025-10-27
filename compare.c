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
   char buffer[20];
    DDRB=0xff;
 
    TCCR0=0X15;
    OCR0=100;
    
    while(1){
        if(TIFR&(1<<1)){
          TCNT0=0;
          PORTB=~(PORTB);
          TIFR |=(1<<1);//TIMER FLAG IS CLEARED USING THE GIVING LOGIC 1
        }
            
        }
}
