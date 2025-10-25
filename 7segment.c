/*
 * File:   ledblink.c
 * Author: USER
 *
 * Created on 14 October, 2025, 12:00 PM
 */

#define F_CPU 8000000UL
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>


#include <xc.h>
#define _XTAL_FREQ 2000000


unsigned char const myin[10]={0x3f,0x30,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};


void main(void) {
    
    DDRD=0XFF;
    DDRC=0XFF;
    int n=0;
   
        
    while(1){
        //int myin[10]={0x3f,0x30,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++)
            {
                n=0;
                while(n<40)
                {
                    PORTC=myin[j];
                    PORTD = 0X01;
                    _delay_ms(10);
                    PORTC=myin[i];
                    PORTD =0X02;
                    _delay_ms(10);
                    n++;
                }
                
            }
        }
    }
    
    
  
    return;
}
