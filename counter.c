//counter using a switch is connected to T0 pin and and when ever the switch is pressed the value TCNTO is send using uart 
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

void display(unsigned char *str ){
        while(*str)
        {
            while(!(UCSRA&(1<<5)));
            UDR=(*str++);
        }
    }

void main(void) {
   char buffer[20];
    DDRB=0x00;
    DDRD=0X02;
    TCCR0=0X07;
    UCSRA=0X00;
    UCSRB=0X18;
    UCSRC=0X86;
    UBRRL=51;
    
    while(1){
        int a=TCNT0;
        while(PINB&(1<<0));
        while(!(PINB&(1<<0)));
        sprintf(buffer,"%d\r",a);
        display(buffer);
}
}
