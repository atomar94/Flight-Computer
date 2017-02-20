//MS5607_Driver.h
//driver for altimeter and thermometer

class MS5607_Driver
{
  public:
    MS5607_Driver();
    ~MS5607_Driver();

    void poll_data(); //grabs data & applies calibrations

    //mbar
    int pressure();

    //Celsius
    int temperature();

    //feet
    int altitude();

  private:
    int m_pressure;
    int m_temperature;
    unsigned int coefficients[8];

    void csb_low();
    void csb_high();
    unsigned int cmd_prom(char coef_num);
    unsigned long cmd_adc(char cmd);
    void init_sensor();

    //returns a^b (a raised to power of b)
    //both must be positive.
    int pow(int a, int b);

};
