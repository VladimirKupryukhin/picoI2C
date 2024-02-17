#include "pico/stdlib.h"
#include <stdio.h>

#define BUS_ZERO(PIN) gpio_set_dir(PIN, GPIO_OUT) // This will make the bus go to low voltage
#define BUS_ONE(PIN) gpio_set_dir(PIN, GPIO_IN) // This will make the bus go to high voltage

//100kHz is default speed - 

int main () {
    stdio_init_all();

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    for (int index = 0; index < 10; index++) {
        gpio_put(25,index % 2);
        sleep_ms(1000);
        printf("%d \n", index);
    }

    int DATA_PIN = 14;
    int CLOCK_PIN = 15;

    gpio_init(DATA_PIN);
    gpio_init(CLOCK_PIN);

    //Idle the bus
    BUS_ONE(DATA_PIN);
    BUS_ONE(CLOCK_PIN);

    //START
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    //Slave addres 1
    BUS_ONE(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    //Slave addres 1
    BUS_ONE(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    //Slave addres 0
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    //Slave addres 1
    BUS_ONE(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    //Slave addres 0
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    //Slave addres 0
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    //Slave addres 0
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    //Slave addres 0
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    //Let go of the data bus
    BUS_ONE(DATA_PIN);
    
    //  ack
    sleep_us(2.5);//Continue having the clock be zero
    BUS_ONE(CLOCK_PIN);
    sleep_us(2.5);
    int firstAck = gpio_get(DATA_PIN);
    sleep_us(2.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

        //Slave addres 0
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

        //Slave addres 1
    BUS_ONE(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

        //Slave addres 0
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);
        //Slave addres 0
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);
        //Slave addres 0
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

        //Slave addres 1
    BUS_ONE(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

        //Slave addres 0
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

        //Slave addres 0
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    //Let go of the data bus
    BUS_ONE(DATA_PIN);
    
    //  ack2
    sleep_us(2.5);//Continue having the clock be zero
    BUS_ONE(CLOCK_PIN);
    sleep_us(2.5);
    int secondAck = gpio_get(DATA_PIN);
    sleep_us(2.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    // repeated start
    BUS_ONE(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(2.5);
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

           //Slave addres 1
    BUS_ONE(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

           //Slave addres 1
    BUS_ONE(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

           //Slave addres 0
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

           //Slave addres 1
    BUS_ONE(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

               //Slave addres 0
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

               //Slave addres 0
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

               //Slave addres 0
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

               //Slave addres 1
    BUS_ONE(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);


    //Let go of the data bus
    BUS_ONE(DATA_PIN);
        //  ack3
    sleep_us(2.5);//Continue having the clock be zero
    BUS_ONE(CLOCK_PIN);
    sleep_us(2.5);
    int thirdAck = gpio_get(DATA_PIN);
    sleep_us(2.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    // Read the 8 bits of data

    // D7
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(2.5);
    int d7 = gpio_get(DATA_PIN);
    sleep_us(2.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

// D6
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(2.5);
    int d6 = gpio_get(DATA_PIN);
    sleep_us(2.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);    

    // D5
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(2.5);
    int d5 = gpio_get(DATA_PIN);
    sleep_us(2.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    // D4
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(2.5);
    int d4 = gpio_get(DATA_PIN);
    sleep_us(2.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    // D3
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(2.5);
    int d3 = gpio_get(DATA_PIN);
    sleep_us(2.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    // D2
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(2.5);
    int d2 = gpio_get(DATA_PIN);
    sleep_us(2.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    // D1
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(2.5);
    int d1 = gpio_get(DATA_PIN);
    sleep_us(2.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    // D0
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(2.5);
    int d0 = gpio_get(DATA_PIN);
    sleep_us(2.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(2.5);

    // Master NACK
    BUS_ONE(DATA_PIN);
    sleep_us(2.5);
    BUS_ONE(CLOCK_PIN);
    sleep_us(5);
    BUS_ZERO(DATA_PIN);
    sleep_us(2.5);

    //STOP
    BUS_ONE(CLOCK_PIN);
    sleep_us(2.5);
    BUS_ONE(DATA_PIN);
    sleep_us(2.5);







    return 0;
}