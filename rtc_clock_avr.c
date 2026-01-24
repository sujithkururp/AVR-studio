#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
// ---------------- I2C SETUP ----------------
#define SCL_CLOCK 100000
#define RTC_WRITE_ADDR 0xD0
#define RTC_READ_ADDR  0xD1
volatile uint8_t int0_flag = 0;     // ISR flag
volatile uint8_t debounce = 0;

volatile uint8_t int1_flag = 0;     // ISR flag
volatile uint8_t debounce1 = 0;
volatile uint8_t int2_flag = 0;
int a=22,b=77;

// ---------------- 7-SEGMENT LOOKUP TABLE ----------------
uint8_t segMap[10] = {
    0x3F, //0
    0x06, //1
    0x5B, //2
    0x4F, //3
    0x66, //4
    0x6D, //5
    0x7D, //6
    0x07, //7
    0x7F, //8
    0x6F  //9
};

// ---------------- I2C FUNCTIONS ----------------
void I2C_Init(void)
{
    TWSR = 0x00;
    TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2;
    TWCR = (1 << TWEN);
}

void i2c_start() {
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

void i2c_rep_start() {
    i2c_start();
}

void i2c_stop() {
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

uint8_t i2c_read_ack() {
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while(!(TWCR & (1<<TWINT)));
    return TWDR;
}

uint8_t i2c_read_nack() {
    TWCR = (1<<TWINT)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
    return TWDR;
}

// ------------- BCD conversion -------------
uint8_t BCDtoDEC(uint8_t val) {
    return ((val>>4)*10) + (val & 0x0F);
}

uint8_t DECtoBCD(uint8_t val) {
    return ((val/10)<<4) | (val%10);
}

// ------------ RTC FUNCTIONS ----------------
void RTC_set_time(uint8_t hr, uint8_t min, uint8_t sec)
{
    i2c_start();
    i2c_write(RTC_WRITE_ADDR);
    i2c_write(0x00);
    i2c_write(DECtoBCD(sec));
    i2c_write(DECtoBCD(min));
    i2c_write(DECtoBCD(hr));
    i2c_stop();
}

void RTC_get_time(uint8_t *hr, uint8_t *min, uint8_t *sec)
{
    i2c_start();
    i2c_write(RTC_WRITE_ADDR);
    i2c_write(0x00);

    i2c_rep_start();
    i2c_write(RTC_READ_ADDR);

    *sec = BCDtoDEC(i2c_read_ack());
    *min = BCDtoDEC(i2c_read_ack());
    *hr  = BCDtoDEC(i2c_read_nack());

    i2c_stop();
}

// -------------------------------------------------
// 2-DIGIT MULTIPLEXED DISPLAY (PORTD=segments, PORTB=digits)
// -------------------------------------------------
void display2Digit(uint8_t num,uint8_t num1)
{
    
    uint8_t d1 = num / 10;   // tens
    uint8_t d2 = num % 10;   // ones
    uint8_t d3 = num1 / 10;
    uint8_t d4 = num1 % 10;
    // Digit 1 (Tens)
    PORTB = 0b11111110;      // Enable digit 1 (PB0)
    PORTA = segMap[d1];
    _delay_ms(3);

    // Digit 2 (Ones)
    PORTB = 0b11111101;      // Enable digit 2 (PB1)
    PORTA = segMap[d2];
    _delay_ms(3);
    PORTB = 0b11111011;      // Enable digit 2 (PB1)
    PORTA = segMap[d3];
    _delay_ms(3);
    PORTB = 0b11110111;      // Enable digit 2 (PB1)
    PORTA = segMap[d4];
    _delay_ms(3);
    
}


ISR(INT0_vect)// the external intf0 flag hardware automatically cleared 
{
    if (!debounce){
        int0_flag = 1;
        debounce = 1;
    }
}

ISR(INT1_vect)// the external intf0 flag hardware automatically cleared 
{
    if (!debounce1){
        int1_flag = 1;
        
        debounce1 = 1;
        
        
    }
}

// -------------------------------------------------
// MAIN PROGRAM
// -------------------------------------------------
int main(void)
{
    DDRD = 0x00;  // segments
    DDRB = 0xFF;  // digit select
    DDRA = 0xff;
    DDRC = 0x00;
    MCUCR=0X0E;
    GICR=0XC0;
    int n=0;
    int m=0;
    I2C_Init();
    RTC_set_time(07, 45, 30);  // Set time once

    uint8_t hr, min, sec;
     sei();

    while(1)
    {
        RTC_get_time(&hr, &min, &sec);


        // show hour:
        for(int i = 0; i < 50; i++)   // refresh fast to avoid flicker
        {
            display2Digit(hr,min);
            
        }
        
         if (int0_flag)
        {
          _delay_ms(3); 
             
          int1_flag=0;
          int m=min;
                 
                 while(!(int1_flag)){
                     
                    
                     while(!(PINC&(1<<7)))
                     {
                          display2Digit(n,min); 
                         _delay_ms(3);
                     }
                     n++;
                     while((PINC&(1<<7))){
                         RTC_get_time(&hr, &min, &sec);
                         _delay_ms(3);
                         RTC_set_time(hr,min,sec);
                         
                     }
                    
                     while(!(PINC&(1<<7))){
                         
                        display2Digit(n,min); 
                         _delay_ms(3);
                     }
                     RTC_set_time(n,m,00); 
                     
                     
                     _delay_ms(3);
                 }
                 
                 
                
           
             
             RTC_get_time(&hr, &min, &sec);
             _delay_ms(3);
             RTC_set_time(hr,min,00); 
             int1_flag=0;
             debounce1 = 0;
             
                 
                 
                 int n=hr;
                 while(!(int1_flag)){
                     
                     
                     
                     while(!(PINC&(1<<7)))
                     {
                       display2Digit(n,m); 
                         _delay_ms(3);  
                     }
                      m++;
                     while((PINC&(1<<7))){
                       RTC_set_time(n,m,00); 
                       _delay_ms(3);  
                     }
                       
                     while(!(PINC&(1<<7))){
                         
                        display2Digit(n,m); 
                         _delay_ms(3);
                     }
                     
                     RTC_set_time(n,m,00);
                      
                     
                     _delay_ms(3);
                 }
            _delay_ms(3);
            RTC_set_time(n,m,00); 
                   
            int0_flag = 0;
            debounce = 0;
                
     
            int1_flag = 0;
            debounce1 = 0;
            RTC_get_time(&hr, &min, &sec);
             _delay_ms(3);
            RTC_set_time(hr,min,00); 
        }
         
         
    }
}
