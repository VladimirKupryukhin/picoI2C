#include "../header/myi2c.h"


void idle(int pinSCL, int pinSDA, int cycles){
    BUS_HIGH(pinSCL);
    BUS_HIGH(pinSDA);
    sleep_us(PERIOD_T_IN_US * cycles);
}

void startSignal(int pinSCL, int pinSDA){
    idle(pinSCL, pinSDA, 1);
    BUS_LOW(pinSDA);
    sleep_us(QUARTER_PERIOD_T_IN_US);
    BUS_LOW(pinSCL);
    sleep_us(QUARTER_PERIOD_T_IN_US);
    //sleep_ms(QUARTER_PERIOD_T_IN_MS);
}

void writeBit(int pinSCL, int pinSDA, int bit){
    if (bit) {
        BUS_HIGH(pinSDA);
    }
    else {
        BUS_LOW(pinSDA);
    }

    sleep_us(QUARTER_PERIOD_T_IN_US);
    BUS_HIGH(pinSCL);
    sleep_us(5);
    BUS_LOW(pinSCL);
    sleep_us(QUARTER_PERIOD_T_IN_US);

}

int readACK(int pinSCL, int pinSDA){
    BUS_HIGH(pinSDA); // Release the data bus
    //int ack = readBit(pinSCL, pinSDA);
    sleep_us(QUARTER_PERIOD_T_IN_US);
    BUS_HIGH(pinSCL);
    sleep_us(QUARTER_PERIOD_T_IN_US);
    int ack = gpio_get(pinSDA);
    sleep_us(QUARTER_PERIOD_T_IN_US);
    BUS_LOW(pinSCL);
    sleep_us(QUARTER_PERIOD_T_IN_US);

    return ack;
}   

int readBit(int pinSCL, int pinSDA){
    sleep_us(QUARTER_PERIOD_T_IN_US);
    BUS_HIGH(pinSCL);
    int bit = gpio_get(pinSDA);
    sleep_us(QUARTER_PERIOD_T_IN_US);
    BUS_LOW(pinSCL);
    sleep_us(QUARTER_PERIOD_T_IN_US);

    return bit;

}

void writeNACK(int pinSCL, int pinSDA){
    writeBit(pinSCL, pinSDA, 1);
}

void repeatedStart(int pinSCL, int pinSDA){
    BUS_HIGH(pinSDA);
    sleep_us(QUARTER_PERIOD_T_IN_US);
    BUS_HIGH(pinSCL);
    sleep_us(QUARTER_PERIOD_T_IN_US);
    BUS_LOW(pinSDA);
    sleep_us(QUARTER_PERIOD_T_IN_US);
    BUS_LOW(pinSCL);
    sleep_us(QUARTER_PERIOD_T_IN_US);
}

void stopSignal(int pinSCL, int pinSDA){
    BUS_LOW(pinSDA);
    sleep_us(QUARTER_PERIOD_T_IN_US);
    BUS_HIGH(pinSCL);
    sleep_us(QUARTER_PERIOD_T_IN_US);
    BUS_HIGH(pinSDA);
    sleep_us(QUARTER_PERIOD_T_IN_US);
}

void writeByte(int pinSCL, int pinSDA, char byte){
    writeBit(pinSCL, pinSDA, (byte & 0b10000000) >> 7); // MSB
    writeBit(pinSCL, pinSDA, (byte & 0b01000000) >> 6); 
    writeBit(pinSCL, pinSDA, (byte & 0b00100000) >> 5); 
    writeBit(pinSCL, pinSDA, (byte & 0b00010000) >> 4); 
    writeBit(pinSCL, pinSDA, (byte & 0b00001000) >> 3); 
    writeBit(pinSCL, pinSDA, (byte & 0b00000100) >> 2); 
    writeBit(pinSCL, pinSDA, (byte & 0b00000010) >> 1); 
    writeBit(pinSCL, pinSDA, (byte & 0b00000001) >> 0); // MSB
}