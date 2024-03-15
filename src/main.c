#include "pico/stdlib.h"
#include "../header/myi2c.h"
#include <stdio.h>
#include <stdlib.h>
#include "../header/mpu6000.h"



#define DATA_PIN 14
#define CLOCK_PIN 15


void printArray(int* array, int length, bool shouldNewLine){

    for (int index = 0; index < length; index++) {
        sleep_ms(1);
        printf("%d", array[index]);
    }

    sleep_ms(1);
    if (shouldNewLine)  printf("\n");
}


int main () {
    stdio_init_all();

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    for (int index = 0; index < 10; index++) {
        gpio_put(25,index % 2);
        sleep_ms(1000);
        printf("%d \n", index);
    }

    gpio_init(DATA_PIN);
    gpio_init(CLOCK_PIN);

    struct MPU6000* mpu = initMPU6000(CLOCK_PIN, DATA_PIN);;

    for (int index = 0; index < 10; index++) {
        sleep_ms(1000);
        double temp = mpu->func->getTemperature(mpu);
        printf("The current temperature: %f\n", temp);
    }


    (*(mpu->func->destructor))(mpu);

    sleep_ms(2);
    printf("end of program");
    sleep_ms(2);



    return 0;
}