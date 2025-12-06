#define F_CPU 8000000UL
#include <avr/io.h>
#include <xc.h>
#include <util/delay.h>

#define SCL_CLOCK 100000  // 100kHz standard I2C speed
//#define SLA_W 0xD0         // Slave address + Write bit (0x68 << 1 = 0xD0)


unsigned char const myin[10]={0x3f,0x30,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void I2C_Init(void)
{
    // Set bit rate: TWBR = ((F_CPU / SCL) - 16) / (2 * Prescaler)
    DDRC = 0X00;
    TWSR = 0x00;                        // Prescaler = 1
    TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2;  // Bit rate register
    TWCR = (1 << TWEN);                // Enable TWI
}

void i2c_start(void)
{
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);  // Send START
    while (!(TWCR & (1 << TWINT)));                    // Wait for TWINT flag
}
void i2c_rep_start(void) {
    i2c_start();  // same as start in AVR
}
void i2c_stop(void)
{
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);  // Send STOP
}

void  i2c_write(uint8_t data)
{
    TWDR = data;                                     // Load data
    TWCR = (1 << TWEN) | (1 << TWINT);               // Start transmission
    while (!(TWCR & (1 << TWINT)));                  // Wait for TWINT flag
}

void TM1637_displayDigit(uint8_t pos, uint8_t num) {
    
    i2c_start();
    i2c_write(0x40); // Write to display register  Write data to display register (automatic address increment mode)
    i2c_stop();
    //i2c_rep_start();
    i2c_start();
    i2c_write(0xc0 + pos); // Position of 4 digit 7 segment
    i2c_write(myin[num]);
    i2c_stop();
     //i2c_rep_start();
    i2c_start();
    i2c_write(0x88 + 7); // Brightness 0?7
    i2c_stop();
}





void TM1637_displayNumber(int num) {
    TM1637_displayDigit(0, (num / 10));//extract the firt digit of the data 23-(2)
    TM1637_displayDigit(1, (num  % 10));//extrct the second digit of the data (3)
    
}


void main(void) {
    I2C_Init();
    while(1){
    TM1637_displayNumber(23);
    
    
    }
        
    
    return;
}
