//MS5607_Driver.cpp
//
// Driver for the altimeter and thermometer


#include "/home/pi/bcm2835-1.50/src/bcm2835.h"
#include <stdio.h>
#include "MS5607_Driver.h"

//for parallax MS56XX chip
#define F_CPU 4000000UL // 4 MHz XTAL
#define CMD_RESET 0x1E // ADC reset command
#define CMD_ADC_READ 0x00 // ADC read command
#define CMD_ADC_CONV 0x40 // ADC conversion command
#define CMD_ADC_D1 0x00 // ADC D1 conversion
#define CMD_ADC_D2 0x10 // ADC D2 conversion
#define CMD_ADC_256 0x00 // ADC OSR=256
#define CMD_ADC_512 0x02 // ADC OSR=512
#define CMD_ADC_1024 0x04 // ADC OSR=1024
#define CMD_ADC_2048 0x06 // ADC OSR=2056
#define CMD_ADC_4096 0x08 // ADC OSR=4096
#define CMD_PROM_RD 0xA0 // Prom read command 


#define CSB RPI_BPLUS_GPIO_J8_24

#define _delay_ms(x) bcm2835_delayMicroseconds(x*1000)

const uint8_t CHIP_SEL = 8;

//TODO: move this to another class. maybe a helper class?
//return a^b (a raise to power b)
int MS5607_Driver::pow(int a, int b)
{
  int retval = 1; //a to the 0th power
  for(int i = 0; i < b; i++) //a to the 1st through b'th power
  {
    retval *= a; 
  }
  return retval;
}


//lower chip select bit 0
//assumes that this chip is on chip select 0
void MS5607_Driver::csb_low()
{
  bcm2835_gpio_write(CHIP_SEL, LOW);
}

//raise csb 0
void MS5607_Driver::csb_high()
{
  bcm2835_gpio_write(CHIP_SEL, HIGH);
}


//ctor
MS5607_Driver::MS5607_Driver()
{
  if(!bcm2835_init())
  {
    printf("bcm2835_init failed. Are you root?\n");
    return;
  }
  if(!bcm2835_spi_begin())
  {
    printf("bcm spi begin failed.\n");
    return;
  }
 
  //for manual chip select control
  bcm2835_gpio_fsel(CHIP_SEL, BCM2835_GPIO_FSEL_OUTP);

  //spi setup
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
  bcm2835_spi_chipSelect(BCM2835_SPI_CS_NONE);                  // Control manually
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

  m_pressure = 0;
  m_temperature = 0;

  //initialize sensor and load calibration values.
  init_sensor();
}

//dtor
MS5607_Driver::~MS5607_Driver()
{
  bcm2835_spi_end();
}

//initialize the altimeter and load all calibration data.
void MS5607_Driver::init_sensor()
{
  bcm2835_spi_transfer(CMD_RESET);

  for(int i = 0; i < 8; i++)
  {
    coefficients[i] = cmd_prom(i);
  }
}

//getter
//mbar
float MS5607_Driver::pressure()
{
  return m_pressure;
}

//getter
//Celsius
float MS5607_Driver::temperature()
{
  return m_temperature;
}

//not implemented yet
//feet
float MS5607_Driver::altitude()
{
  return -1;
}

//grab the data from the chip.
void MS5607_Driver::poll_data()
{
  unsigned long D1;
  unsigned long D2;
  unsigned long dT;
  unsigned long OFF;
  unsigned long SENS;

  D1 = cmd_adc(CMD_ADC_D1+CMD_ADC_256);
  D2 = cmd_adc(CMD_ADC_D2+CMD_ADC_4096);

  //TODO: this is the first order calibration. a 2nd order exists in
  //the data sheet

  dT = D2-coefficients[5]*pow(2,8);
  OFF = coefficients[2]*pow(2,17)+dT*coefficients[4]/pow(2,6);
  SENS = coefficients[1]*pow(2,16)+dT/pow(2,7);
  m_temperature = (2000 + (dT*coefficients[6]) / pow(2,23))/100;
  m_pressure = (((D1*SENS)/pow(2,21)-OFF)/pow(2,15))/100;

  //for debugging
  //printf("Pressure: %d\n", m_pressure);
  //printf("Temperature: %d\n", m_temperature);
}

//get the coefficient values
unsigned int MS5607_Driver::cmd_prom(char coef_num)
{
  unsigned int ret;
  unsigned int rc = 0;
  csb_low();
  char prom_read_command = CMD_PROM_RD | (coef_num*2);
  bcm2835_spi_transfer(prom_read_command); //tell chip we want this coef
  ret = bcm2835_spi_transfer(0x00); //get the msb
  rc = ret*256;
  ret = bcm2835_spi_transfer(0x00); //get lsb
  rc = rc + ret;
  csb_high();
  return rc;

}

unsigned long MS5607_Driver::cmd_adc(char cmd)
{
  char ret;
  unsigned long temp=0;
  csb_low(); // pull CSB low

  bcm2835_spi_transfer(CMD_ADC_CONV + cmd); //send conversion cmd

  switch (cmd & 0x0f) // wait necessary conversion time
  {
    case CMD_ADC_256 : _delay_ms(1); break;    
    case CMD_ADC_512 : _delay_ms(3); break;
    case CMD_ADC_1024: _delay_ms(4); break;
    case CMD_ADC_2048: _delay_ms(6); break;
    case CMD_ADC_4096: _delay_ms(10); break;
  }
 
  csb_high(); // pull CSB high to finish the conversion
  csb_low(); // pull CSB low to start new command

  bcm2835_spi_transfer(CMD_ADC_READ);

  ret = bcm2835_spi_transfer(0x00); //send 0 to read first byte
  temp = 65536*ret;


  ret = bcm2835_spi_transfer(0x00);
  temp = temp+256*ret;

  ret = bcm2835_spi_transfer(0x00);
  temp = temp+ret;

  csb_high(); // pull CSB high to finish the read command
  return temp;
}







