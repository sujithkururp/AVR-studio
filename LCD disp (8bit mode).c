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




//#define RS PORTC|=(1<<0)
//#define RW PORTC|=(1<<1)
//#define E PORTC|=(1<<2)



void lcd_cmd(unsigned char cmd){
   PORTD= cmd;
   PORTC&=~(1<<0);
   PORTC&=~(1<<1);
  
   PORTC |=(1<<2);
  
    _delay_ms(5);
   PORTC &=~(1<<2);
    _delay_ms(5);
    
}
void lcd_data(unsigned char data ){
   PORTD= data;
   PORTC|=(1<<0);
   PORTC&=~(1<<1);
  
   PORTC |=(1<<2);
    _delay_ms(5);
   PORTC &=~(1<<2);
    _delay_ms(5);
    
    
}
void lcd_intial(){
    lcd_cmd(0x38);
    lcd_cmd(0x0c);
    lcd_cmd(0x06);
    lcd_cmd(0X01);
    
}
void lcd_string(const char *str){
    while(*str){
        lcd_data(*str++);
    }
}
void main(void) {
    
    DDRD=0XFF;
    DDRC=0XFF;
    lcd_intial();
   

    lcd_string("HELLOW");
        
    while(1);
    
    
  
    return;
}
