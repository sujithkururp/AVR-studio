#define F_CPU 8000000UL
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <avr/interrupt.h>




void main(void) {
    
    TCCR1A=0X40;
    TCCR1B=0X05;
    DDRD=0XFF;
    OCR1A=7812;//0 t0 7812 will give u the 1ms delay so timer will cout from 0 t0 7812 
    TCNT1=0;// and we start the timer1 register start from the 0 
    while(1){
        
        while(!(TIFR &(1<<4)));//check the OCIFA flag is clear 
        TIFR |=(1<<4);//clear OCIFA flag making it logic 1
        
        TCNT1=0;//satrt the timer value from 0
        
    }
    
    return;
}
