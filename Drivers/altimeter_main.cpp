//main.cpp

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

//return a^b (a raise to power b)
int pow(int a, int b)
{
  int retval = a; //a to the first power
  for(int i = 1; i < b; i++) //a to the 2nd through b'th power
  {
    retval *= a; 
  }
  return retval;
}

//lower chip select bit 0
void csb_low()
{
  bcm2835_gpio_write(CHIP_SEL, LOW);
}

//raise csb 0
void csb_high()
{
  bcm2835_gpio_write(CHIP_SEL, HIGH);
}

//get the coefficient values
unsigned int cmd_prom(char coef_num)
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

unsigned long cmd_adc(char cmd)
{
  char ret;
  unsigned long temp=0;
  csb_low(); // pull CSB low
  //spi_send(CMD_ADC_CONV+cmd); // send conversion command
  bcm2835_spi_transfer(CMD_ADC_CONV + cmd);

  switch (cmd & 0x0f) // wait necessary conversion time
  {
    //case CMD_ADC_256 : _delay_us(900); break;
    case CMD_ADC_256 : _delay_ms(1); break;    
    case CMD_ADC_512 : _delay_ms(3); break;
    case CMD_ADC_1024: _delay_ms(4); break;
    case CMD_ADC_2048: _delay_ms(6); break;
    case CMD_ADC_4096: _delay_ms(10); break;
  }
 
  csb_high(); // pull CSB high to finish the conversion
  csb_low(); // pull CSB low to start new command
  //spi_send(CMD_ADC_READ); // send ADC read command
  bcm2835_spi_transfer(CMD_ADC_READ);

 //spi_send(0x00); // send 0 to read 1st byte (MSB)
 //ret=SPDR;
  ret = bcm2835_spi_transfer(0x00); //send 0 to read first byte
  temp=65536*ret;

  //spi_send(0x00); // send 0 to read 2nd byte
  //ret=SPDR;
  ret = bcm2835_spi_transfer(0x00);
  temp=temp+256*ret;

  //spi_send(0x00); // send 0 to read 3rd byte (LSB)
  //ret=SPDR;
  ret = bcm2835_spi_transfer(0x00);
  temp=temp+ret;

  csb_high(); // pull CSB high to finish the read command
  return temp;
}

//given the array of values we read from the prom (coefs and CRC) calculate
//the crc and make sure it matches
//code adapted from datasheet examples
unsigned char crc4(unsigned int n_prom[])
{
  unsigned int local_prom[8];
  for(int i = 0; i < 8; i++)
  {
    local_prom[i] = n_prom[i];
  }
  unsigned int n_rem = 0x00;
  local_prom[7] = (0xFF00 & (local_prom[7]));

  for(int i = 0; i < 16; i++)
  {
    if(i%2 == 1) //do we want the MSB or LSB 
    {
      //we want the lower (I think)
      n_rem ^= (unsigned short) ((local_prom[i>>1]) & 0x00FF); 
    } else
    {
      //we want the upper (I also think)
      n_rem ^= (unsigned short) (local_prom[i>>1] >> 8);
    }

    for(int nbit = 8; nbit > 0; nbit--)
    {
      if(n_rem & (0x8000))
      {
        n_rem = (n_rem << 1) ^ 0x3000;
      } 
      else
      {
        n_rem = (n_rem << 1);
      }
    } //end nested for
  } //end for
  n_rem = (0x000F & (n_rem >> 12));
  return (n_rem ^ 0x00);

}

//init hardware as we need it
int init()
{
  bcm2835_gpio_fsel(CHIP_SEL, BCM2835_GPIO_FSEL_OUTP);
 
}
int main()
{

  MS5607_Driver* altimeter1 = new MS5607_Driver();
  for(int i = 0; i < 10; i++)
  {
    altimeter1->poll_data();
    int t = altimeter1->temperature();
    int p = altimeter1->pressure();
    printf("Temp: %d, Pressure %d\n", t, p);
  }
  return 0;
  /*
  TESTING FOR MANUAL CHIP SELECT CONTROL
  if (!bcm2835_init())
  {
    printf("bcm2835_init failed. Are you running as root??\n");
    return 1;
  } 
  bcm2835_gpio_fsel(CHIP_SEL, BCM2835_GPIO_FSEL_OUTP);
  //testing
  for(int i = 0; i < 10; i++)
  {
    printf("In loop\n");
    csb_low();
    _delay_ms(1000);
    csb_high();
    _delay_ms(1000);
  }
  bcm2835_close();
  return 0;
  */

  /*if(!bcm2835_init())
  {
    printf("bcm2835_init failed. Are you root?\n");
  }
  if(!bcm2835_spi_begin())
  {
    printf("bcm spi begin failed.\n");
    return 1;
  }
  init(); //TODO: get all these init cases into the init function

  //***********
  // SPI Init
  //***********
  // bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
  bcm2835_spi_chipSelect(BCM2835_SPI_CS_NONE);                  // Control manually
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

  //***********
  // Chip Init
  //***********
  bcm2835_spi_transfer(CMD_RESET);

  //get coefs
  unsigned int coefs[8];
  for(char i = 0; i < 8; i++)
  {
    coefs[i] = cmd_prom(i);
    printf("Coef %d: %x\n", (int) i, coefs[i]);
  }
  unsigned char retcrc = crc4(coefs);
  printf("Read CRC %d, Calculated CRC %d\n", coefs[7], retcrc);

  unsigned long D1;
  unsigned long D2;
  unsigned long dT;
  unsigned long OFF;
  unsigned long SENS;
  unsigned long T;
  unsigned long P;

  while(true)
  {

    D1 = cmd_adc(CMD_ADC_D1+CMD_ADC_256);
    D2 = cmd_adc(CMD_ADC_D2+CMD_ADC_4096);
  
    dT = D2-coefs[5]*pow(2,8);
    OFF = coefs[2]*pow(2,17)+dT*coefs[4]/pow(2,6);
    SENS = coefs[1]*pow(2,16)+dT/pow(2,7);
    T = (2000 + (dT*coefs[6]) / pow(2,23))/100;
    P = (((D1*SENS)/pow(2,21)-OFF)/pow(2,15))/100;

    printf("Pressure: %d\n", P);
    printf("Temperature: %d\n", T);
    _delay_ms(1000);
  }

  D1=cmd_adc(CMD_ADC_D1+CMD_ADC_256); // read uncompensated pressure
  D2=cmd_adc(CMD_ADC_D2+CMD_ADC_4096); // read uncompensated temperature

  // calcualte 1st order pressure and temperature (MS5607 1st order algorithm)
  dT=D2-C[5]*pow(2,8);
  OFF=C[2]*pow(2,17)+dT*C[4]/pow(2,6);
  SENS=C[1]*pow(2,16)+dT*C[3]/pow(2,7);

  T=(2000+(dT*C[6])/pow(2,23))/100;
  P=(((D1*SENS)/pow(2,21)-OFF)/pow(2,15))/100; 
  
  bcm2835_spi_end();
  */
  return 0;
}


