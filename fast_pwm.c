//pwm with increment and decremt pwm



#define F_CPU 8000000UL
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <avr/interrupt.h>

void main(void) {
    TCCR0=0X6D;
    DDRB=0XFF;
    while(1){
    for(int i=0;i<256;i++){
         OCR0=i;
         _delay_ms(3);
    }
    
    for(int i=256;i>0;i--){
         OCR0=i;
         _delay_ms(3);
    }
    }
    return;
}
//withe fixed pwm............................
void main(void) {
    TCCR0=0X6D;
    DDRB=0XFF;
    OCR0=80;
    while(1);
    return;
}
