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

    // Make everything go idle
    BUS_ONE(CLOCK_PIN)
    BUS_ONE(DATA_PIN)

    // START
    BUS_ZERO(DATA_PIN)
    sleep_us(0.25);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // SLAVE ADDRESS: 1
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // SLAVE ADDRESS: 1
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // SLAVE ADDRESS: 0
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // SLAVE ADDRESS: 1
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // SLAVE ADDRESS: 0
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // SLAVE ADDRESS: 0
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // SLAVE ADDRESS: 0
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // R/~W 0
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // SLAVE ACK?
    // Release the bus
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    int firstACK = gpio_get(DATA_PIN);
    sleep_us(0.5);
    BUS_ZERO(0.25);
    sleep_us(0.25);

    // REGISER ADDRESS: 0
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // REGISER ADDRESS: 1
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // REGISER ADDRESS: 0
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // REGISER ADDRESS: 0
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // REGISER ADDRESS: 0
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // REGISER ADDRESS: 1
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // REGISER ADDRESS: 0
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // REGISER ADDRESS: 0
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // SLAVE ACK?
    // Release the bus
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    int secondACK = gpio_get(DATA_PIN);
    sleep_us(0.5);
    BUS_ZERO(0.25);
    sleep_us(0.25);

    // REPEATED START
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.25);
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

        // SLAVE ADDRESS: 1
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // SLAVE ADDRESS: 1
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // SLAVE ADDRESS: 0
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // SLAVE ADDRESS: 1
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // SLAVE ADDRESS: 0
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // SLAVE ADDRESS: 0
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // SLAVE ADDRESS: 0
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // R/~W 1
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);

    // SLAVE ACK?
    // Release the bus
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    int thirdACK = gpio_get(DATA_PIN);
    sleep_us(0.5);
    BUS_ZERO(0.25);
    sleep_us(0.25);

    // D7
    // Release the bus
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    int d7 = gpio_get(DATA_PIN);
    sleep_us(0.5);
    BUS_ZERO(0.25);
    sleep_us(0.25);

        // D6
    // Release the bus
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    int d6 = gpio_get(DATA_PIN);
    sleep_us(0.5);
    BUS_ZERO(0.25);
    sleep_us(0.25);

        // D5
    // Release the bus
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    int d5 = gpio_get(DATA_PIN);
    sleep_us(0.5);
    BUS_ZERO(0.25);
    sleep_us(0.25);

        // D4
    // Release the bus
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    int d4 = gpio_get(DATA_PIN);
    sleep_us(0.5);
    BUS_ZERO(0.25);
    sleep_us(0.25);

    // D3
    // Release the bus
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    int d3 = gpio_get(DATA_PIN);
    sleep_us(0.5);
    BUS_ZERO(0.25);
    sleep_us(0.25);
    
    // D2
    // Release the bus
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    int d2 = gpio_get(DATA_PIN);
    sleep_us(0.5);
    BUS_ZERO(0.25);
    sleep_us(0.25);

    // D1
    // Release the bus
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    int d1 = gpio_get(DATA_PIN);
    sleep_us(0.5);
    BUS_ZERO(0.25);
    sleep_us(0.25);

    // D0
    // Release the bus
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    int d0 = gpio_get(DATA_PIN);
    sleep_us(0.5);
    BUS_ZERO(0.25);
    sleep_us(0.25);

    // MASTER NACK
    BUS_ONE(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.5);
    BUS_ZERO(CLOCK_PIN);
    sleep_us(0.25);
    

    // STOP
    BUS_ZERO(DATA_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    sleep_us(0.25);
    BUS_ONE(CLOCK_PIN);
    BUS_ONE(DATA_PIN)
    sleep_us(0.25);

    




    return 0;
}