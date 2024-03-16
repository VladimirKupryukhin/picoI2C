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


    //printf("Accel Z %f\n", mpu->func->getAccelZ(mpu));

    // for (int index = 0; index < 10; index++) {
    //     sleep_ms(1000);
    //     double temp = mpu->func->getTemperature(mpu);
    //     printf("The current temperature: %f\n", temp);
    // }

    while (true) {
        // double accelX = mpu->func->getAccelX(mpu);
        // double accelY = mpu->func->getAccelY(mpu);
        // double accelZ = mpu->func->getAccelZ(mpu);

        // // double gyroX = mpu->func->getGyroX(mpu);
        // // double gyroY = mpu->func->getGyroY(mpu);
        // // double gyroZ = mpu->func->getGyroZ(mpu);

        // printf("Accel X: %f\n", accelX);
        // printf("Accel Y: %f\n", accelY);
        // printf("Accel Z: %f\n", accelZ);

        // // printf("Gyro X: %f\n", gyroX);
        // // printf("Gyro Y: %f\n", gyroY);
        // // printf("Gyro Z: %f\n", gyroZ);


        // double xAngle = mpu->func->getXAngleInDegrees(mpu);
        // double yAngle = mpu->func->getYAngleInDegrees(mpu);
        // double zAngle = mpu->func->getZAngleInDegrees(mpu);

        // printf("X Angle: %f\n", xAngle);
        // printf("Y Angle: %f\n", yAngle);
        // printf("Z Angle: %f\n", zAngle);

        // printf("--------\n");

        sleep_ms(20);
    }


    (*(mpu->func->destructor))(mpu);

    sleep_ms(2);
    printf("end of program");
    sleep_ms(2);



    return 0;
}