/*
 * File:   avr_uart.c
 * Author: USER
 *
 * Created on 22 October, 2025, 12:09 PM
 */

#define F_CPU 8000000UL
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

void display(unsigned char *str ){
        while(*str)
        {
            while(!(UCSRA&(1<<5)));
            UDR=(*str++);
        }
    }

void reverse(unsigned char *str){//data address is send to the str so the data
    
    int len =strlen(str);
    int i;
    char temp;
    for(i=0;i<len/2;i++){
      temp=str[i];
      str[i]=str[len-1-i];
      str[len -1-i]=temp;
      
    }
    
    }


void main(void) {
    int i=0;
    
    unsigned char data[20];
    unsigned char rev[20];
    unsigned char ch;
    DDRD=0X02;
    UCSRA=0X00;
    UCSRB=0X18;
    UCSRC=0X86;
    UBRRL=51;
    
    
    while(1)
    {
//       
        
    
      
       while(!(UCSRA&(1<<7)));//when ever the rcreg full the rcif is high then exit the loop
       ch=UDR;
       if(ch=='\r'){
           
             data[i]='\0';
             
             reverse(data);
             display(data);
             display("\r \n");
             i=0;
       }
       else  {
           
        data[i]=ch;
        i++;
       
      }
       
       
      
        
    
        
    }
    return;
}
