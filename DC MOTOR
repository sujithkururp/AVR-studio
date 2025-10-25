#define F_CPU 8000000UL
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>


#include <xc.h>
#define _XTAL_FREQ 2000000





void main(void) {
    
    
    DDRC=0XFF;
    DDRD=0X00;
   
        
    while(1){
        while(!(PIND&(1<<0)));
        while(PIND&(1<<0));
        
        PORTC |=(1<<0);
        PORTC &=~(1<<1);
        while(!(PIND&(1<<0)));
        while(PIND&(1<<0));
        PORTC &=~(1<<0);
        PORTC &=~(1<<1);
        PORTC |=(1<<2);
        PORTC &=~(1<<3);
        while(!(PIND&(1<<0)));
        while(PIND&(1<<0));
        PORTC |=(1<<0);
        PORTC &=~(1<<1);
        PORTC &=~(1<<2);
        PORTC &=~(1<<3);
    }
    
    
  
    return;
}
