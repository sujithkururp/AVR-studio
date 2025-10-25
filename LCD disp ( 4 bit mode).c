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








void lcd_cmd(unsigned char cmd){
   unsigned char cmd_u = (cmd & 0xF0);
   unsigned char cmd_l = ((cmd << 4) & 0xF0);
   PORTD= (cmd_u>>4);
   
   PORTC&=~(1<<0);
   PORTC&=~(1<<1);
  
   PORTC |=(1<<2);
  
    _delay_ms(5);
   PORTC &=~(1<<2);
    _delay_ms(5);
    
    PORTD= (cmd_l>>4);

  
   PORTC |=(1<<2);
  
    _delay_ms(5);
   PORTC &=~(1<<2);
    _delay_ms(5);
    
}
void lcd_data(unsigned char data ){
   unsigned char data_u = (data & 0xF0);
   unsigned char data_l = ((data << 4) & 0xF0);
   PORTD= (data_u>>4);
   
   PORTC|=(1<<0);
   PORTC&=~(1<<1);
  
   PORTC |=(1<<2);
    _delay_ms(5);
   PORTC &=~(1<<2);
    _delay_ms(5);
    
    PORTD= (data_l>>4);
   
  
   PORTC |=(1<<2);
    _delay_ms(5);
   PORTC &=~(1<<2);
    _delay_ms(5);
}
void lcd_intial(){
    lcd_cmd(0x33);
    _delay_ms(15);
     lcd_cmd(0x32);
    _delay_ms(15);
    lcd_cmd(0x20);        // Initialize in 4-bit mode
    lcd_cmd(0x28);        // 2 line, 5x8 matrix
    lcd_cmd(0x0C);        // Display ON, Cursor OFF
    lcd_cmd(0x06);        // Entry mode
    lcd_cmd(0x01); 
    
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
