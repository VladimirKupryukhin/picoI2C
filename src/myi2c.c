#include "../header/myi2c.h"


void idle(int pinSCL, int pinSDA){
    BUS_HIGH(pinSCL);
    BUS_HIGH(pinSDA);
}

void startSignal(int pinSCL, int pinSDA){
    BUS_HIGH(pinSCL);
    sleep_ms(QUARTER_PERIOD_T_IN_MS);
    BUS_LOW(pinSDA);
    sleep_ms(QUARTER_PERIOD_T_IN_MS);
}

void writeBit(int pinSCL, int pinSDA, int bit){
    if (bit) {
        BUS_HIGH(pinSDA);
    }
    else {
        BUS_LOW(pinSDA);
    }

    sleep_ms(QUARTER_PERIOD_T_IN_MS);
    BUS_HIGH(pinSCL);
    sleep_ms(HALF_PERIOD_T_IN_MS);
    BUS_LOW(pinSCL);
    sleep_ms(QUARTER_PERIOD_T_IN_MS);

}

int readACK(int pinSCL, int pinSDA){
    BUS_HIGH(pinSDA); // Release the data bus
    int ack = readBit(pinSCL, pinSDA);
    // sleep_ms(QUARTER_PERIOD_T_IN_MS);
    // BUS_HIGH(pinSCL);
    // sleep_ms(QUARTER_PERIOD_T_IN_MS);
    // int ack = gpio_get(pinSDA);
    // sleep_ms(QUARTER_PERIOD_T_IN_MS);
    // BUS_LOW(pinSCL);
    // sleep_ms(QUARTER_PERIOD_T_IN_MS);

    return ack;
}   

int readBit(int pinSCL, int pinSDA){
    sleep_ms(QUARTER_PERIOD_T_IN_MS);
    BUS_HIGH(pinSCL);
    int bit = gpio_get(pinSDA);
    sleep_ms(QUARTER_PERIOD_T_IN_MS);
    BUS_LOW(pinSCL);
    sleep_ms(QUARTER_PERIOD_T_IN_MS);

    return bit;

}

void writeNACK(int pinSCL, int pinSDA){
    writeBit(pinSCL, pinSDA, 1);
}

void repeatedStart(int pinSCL, int pinSDA){
    BUS_HIGH(pinSDA);
    sleep_ms(QUARTER_PERIOD_T_IN_MS);
    BUS_HIGH(pinSCL);
    sleep_ms(QUARTER_PERIOD_T_IN_MS);
    BUS_LOW(pinSDA);
    sleep_ms(QUARTER_PERIOD_T_IN_MS);
    BUS_LOW(pinSCL);
    sleep_ms(QUARTER_PERIOD_T_IN_MS);
}

void stopSignal(int pinSCL, int pinSDA){
    BUS_LOW(pinSDA);
    sleep_ms(QUARTER_PERIOD_T_IN_MS);
    BUS_HIGH(pinSCL);
    sleep_ms(QUARTER_PERIOD_T_IN_MS);
    BUS_HIGH(pinSDA);
    sleep_ms(QUARTER_PERIOD_T_IN_MS);
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