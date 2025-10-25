/*
 * File:   avr_adc.c
 * Author: USER
 *
 * Created on 23 October, 2025, 12:34 PM
 */

#define F_CPU 8000000UL
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>



void display(unsigned char *str ){
        while(*str)
        {
            while(!(UCSRA&(1<<5)));
            UDR=(*str++);
        }
    }


void main(void) {
    
    DDRA=0X00;
    ADCSRA=0X87;
    
    int i=0;
    char data[20];
    char ch;
    DDRD=0X02;
    UCSRA=0X00;
    UCSRB=0X18;
    UCSRC=0X86;
    UBRRL=51;
    
    char buffer[20];
    
    while(1){
        ADCSRA |=(1<<ADSC);
        while( ADCSRA&(1<<ADSC));
      
       int ADC_value =ADCL;
       ADC_value |=ADCH<<8;
       sprintf(buffer,"%d\r",ADC_value);
       
       
       
      
       display(buffer);
       display("\r \n");
    }
    return;
}
