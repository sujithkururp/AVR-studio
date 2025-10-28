//the automatically reset the timer0 value from the intial value so we can get the desired delay oc0 pin otherwise it will get run upto 255 value and it set flag when we reach 
//we will again get the maximum delay of 32 us
/*
 * File:   avr_ctc.c
 * Author: USER
 *
 * Created on 28 October, 2025, 6:00 AM
 */


#define F_CPU 8000000UL
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <avr/interrupt.h>

void main(void) {
    TCCR0=0X1D;
    DDRB=0XFF;
    OCR0=80;
    while(1);
    return;
}
