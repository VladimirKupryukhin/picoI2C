#include "pico/stdlib.h"
#include <stdio.h>

#define BUS_ZERO(PIN) gpio_set_dir(PIN, GPIO_OUT) // This will make the bus go to low voltage
#define BUS_ONE(PIN) gpio_set_dir(PIN, GPIO_IN) // This will make the bus go to high voltage
#define DATA_PIN 14
#define CLOCK_PIN 15

//100kHz is default speed - 

// Foward declarations
void idle();
void start();
void write();
int readACK();
int readBit();
void writeNACK();
void stop();
void repeatedStart();

int main () {
    stdio_init_all();

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    for (int index = 0; index < 10; index++) {
        gpio_put(25,index % 2);
        sleep_ms(1000);
        printf("%d \n", index);
    }

    // int DATA_PIN = 14;
    // int CLOCK_PIN = 15;

    gpio_init(DATA_PIN);
    gpio_init(CLOCK_PIN);

    //Enable the MPU
    idle();
    start();
    write(1);
    write(1);
    write(0);
    write(1);
    write(0);
    write(0);
    write(0);
    write(0); //R/W
    BUS_ONE(DATA_PIN);// Release the data bus 
    int aack1 = readACK();
    write(0);
    write(1);
    write(1);
    write(0);
    write(1);
    write(0);
    write(1);
    write(1);
    BUS_ONE(DATA_PIN);// Release the data bus 
    int aack2 = readACK();
    write(0);
    write(0);
    write(1);
    write(0);
    write(0);
    write(0);
    write(0);
    write(1);
    BUS_ONE(DATA_PIN);// Release the data bus 
    int aack3 = readACK();
    // BUS_ZERO(DATA_PIN);
    // sleep_us(2.5);
    // BUS_ONE(CLOCK_PIN);
    // sleep_us(2.5);
    // BUS_ONE(DATA_PIN);
    // sleep_us(2.5);
    stop();
    idle();

    //stop();
    idle();

    sleep_us(10);

    //Request data from accel
    idle();
    start();
    write(1);
    write(1);
    write(0);
    write(1);
    write(0);
    write(0);
    write(0);
    write(0); //R/W
    BUS_ONE(DATA_PIN);// Release the data bus 
    int ack1 = readACK();
    write(0);
    write(1);
    write(0);
    write(0);
    write(0);
    write(1);
    write(0);
    write(0);
    BUS_ONE(DATA_PIN);// Release the data bus 
    int ack2 = readACK();
    repeatedStart();
    write(1);
    write(1);
    write(0);
    write(1);
    write(0);
    write(0);
    write(0);
    write(1);//R/W
    BUS_ONE(DATA_PIN);// Release the data bus 
    int ack3 = readACK();
    int d7 = readBit();
    int d6 = readBit();
    int d5 = readBit();
    int d4 = readBit();
    int d3 = readBit();
    int d2 = readBit();
    int d1 = readBit();
    int d0 = readBit();
    writeNACK();
    stop();

    // writeNACK();
    // stop();
    idle();

    return 0;
}

void idle(){
    //Idle the bus
    BUS_ONE(DATA_PIN);
    BUS_ONE(CLOCK_PIN);
}

void start() {
    //START
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);
}

void write(int bit) {
        //Slave addres 1
    
    if (bit == 1) {
        BUS_ONE(DATA_PIN);
    }
    else {
        BUS_ZERO(DATA_PIN);
    }


    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);
}

int readACK(){
        //  ack
    sleep_us(2.5);//Continue having the clock be zero
    BUS_ONE(CLOCK_PIN);
    sleep_us(2.5);
    int ack = gpio_get(DATA_PIN);
    sleep_us(2.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    return ack;
}

int readBit() {
        // D7
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(2.5);
    int bit = gpio_get(DATA_PIN);
    sleep_us(2.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    return bit;
}

void writeNACK() {
    write(1);
}

void stop() {
        //STOP
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(2.5);
    BUS_ONE(DATA_PIN);
    sleep_us(2.5);
}

void repeatedStart(){
        // repeated start
    BUS_ONE(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(2.5);
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);
}



