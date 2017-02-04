//Globals.h

#ifndef GLOBALS_H
#define GLOBALS_H

//if a reading has 3 components (like gyro or accel)
struct three_axis {
    int x;
    int y;
    int z;
};

//Fill this in once we know what the data will look like
struct datastruct {
    //leave data1 and data2 for now
    int data1 = 0;
    int data2 = 0;

    //Altimeter - MS5607 
    int pressure = 0;
    int temperature = 0;
    int altitude = 0;

    //Flight Profile - Adafruit IMU
    three_axis gyro =   (three_axis) {.x=0, .y=0, .z=0};
    three_axis accel =  (three_axis) {.x=0, .y=0, .z=0};
    three_axis mag =   (three_axis) {.x=0, .y=0, .z=0};

};

#endif
