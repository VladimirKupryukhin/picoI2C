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
    

    printf("Address of mpu = %p\n", &mpu);
    sleep_ms(1);
    printf("address of destructor = %p\n", (mpu->func->destructor));
    
    //writeToMPU(PWR_MGMT_1_ADDRESS, 0b00000001, mpu);

    BUS_HIGH(DATA_PIN);
    BUS_HIGH(CLOCK_PIN);

    idle(CLOCK_PIN, DATA_PIN, 20);
    startSignal(CLOCK_PIN, DATA_PIN);
    writeByte(CLOCK_PIN, DATA_PIN, SLAVE_ADDRESS_WRITE);
    int test1 = readACK(CLOCK_PIN, DATA_PIN);
    writeByte(CLOCK_PIN, DATA_PIN, PWR_MGMT_1_ADDRESS);
    int test2 = readACK(CLOCK_PIN, DATA_PIN);
    writeByte(CLOCK_PIN, DATA_PIN, 0b00000001);
    int test3 = readACK(CLOCK_PIN, DATA_PIN);
    stopSignal(CLOCK_PIN, DATA_PIN);
    idle(CLOCK_PIN, DATA_PIN, 5);


    int* response = malloc(3 * sizeof(int));

    int* readpwrmgmtData = malloc(8 * sizeof(int));
    response = mpu->func->readFromMPU(PWR_MGMT_1_ADDRESS, readpwrmgmtData, mpu);

    printf("Response: %d%d%d\n", response[0], response[1], response[2]);

    printArray(readpwrmgmtData, 8, true);

    (*(mpu->func->destructor))(mpu);

    // -------
    // BUS_HIGH(DATA_PIN);
    // BUS_HIGH(CLOCK_PIN);

    // idle(CLOCK_PIN, DATA_PIN, 20);
    // startSignal(CLOCK_PIN, DATA_PIN);
    // writeByte(CLOCK_PIN, DATA_PIN, SLAVE_ADDRESS_WRITE);
    // int test1 = readACK(CLOCK_PIN, DATA_PIN);
    // writeByte(CLOCK_PIN, DATA_PIN, PWR_MGMT_1_ADDRESS);
    // int test2 = readACK(CLOCK_PIN, DATA_PIN);
    // writeByte(CLOCK_PIN, DATA_PIN, 0b00000001);
    // int test3 = readACK(CLOCK_PIN, DATA_PIN);
    // stopSignal(CLOCK_PIN, DATA_PIN);
    // idle(CLOCK_PIN, DATA_PIN, 5);

    // printf("test %d %d %d\n", test1, test2, test3);

    startSignal(CLOCK_PIN, DATA_PIN);
    writeByte(CLOCK_PIN, DATA_PIN, SLAVE_ADDRESS_WRITE);
    readACK(CLOCK_PIN, DATA_PIN);
    writeByte(CLOCK_PIN, DATA_PIN, PWR_MGMT_1_ADDRESS);
    readACK(CLOCK_PIN, DATA_PIN);
    repeatedStart(CLOCK_PIN, DATA_PIN);
    writeByte(CLOCK_PIN, DATA_PIN, SLAVE_ADDRESS_READ);
    readACK(CLOCK_PIN, DATA_PIN);
    int d7 = readBit(CLOCK_PIN, DATA_PIN);
    int d6 = readBit(CLOCK_PIN, DATA_PIN);
    int d5 = readBit(CLOCK_PIN, DATA_PIN);
    int d4 = readBit(CLOCK_PIN, DATA_PIN);
    int d3 = readBit(CLOCK_PIN, DATA_PIN);
    int d2 = readBit(CLOCK_PIN, DATA_PIN);
    int d1 = readBit(CLOCK_PIN, DATA_PIN);
    int d0 = readBit(CLOCK_PIN, DATA_PIN);
    writeNACK(CLOCK_PIN, DATA_PIN);
    stopSignal(CLOCK_PIN, DATA_PIN);
    idle(CLOCK_PIN, DATA_PIN, 0);

    printf("Result: %d%d%d%d%d%d%d%d\n", d7, d6, d5, d4, d3, d2, d1, d0);

    sleep_ms(2);
    printf("end of program");
    sleep_ms(2);
    // BUS_HIGH(DATA_PIN);
    // BUS_HIGH(CLOCK_PIN);

    // idle(CLOCK_PIN, DATA_PIN, 20);
    // startSignal(CLOCK_PIN, DATA_PIN);
    // writeByte(CLOCK_PIN, DATA_PIN, SLAVE_ADDRESS_WRITE);
    // readACK(CLOCK_PIN, DATA_PIN);
    // writeByte(CLOCK_PIN, DATA_PIN, PWR_MGMT_1_ADDRESS);
    // readACK(CLOCK_PIN, DATA_PIN);
    // writeByte(CLOCK_PIN, DATA_PIN, 0b00000001);
    // readACK(CLOCK_PIN, DATA_PIN);
    // stopSignal(CLOCK_PIN, DATA_PIN);
    // idle(CLOCK_PIN, DATA_PIN, 5);

    // startSignal(CLOCK_PIN, DATA_PIN);
    // writeByte(CLOCK_PIN, DATA_PIN, SLAVE_ADDRESS_WRITE);
    // readACK(CLOCK_PIN, DATA_PIN);
    // writeByte(CLOCK_PIN, DATA_PIN, PWR_MGMT_1_ADDRESS);
    // readACK(CLOCK_PIN, DATA_PIN);
    // repeatedStart(CLOCK_PIN, DATA_PIN);
    // writeByte(CLOCK_PIN, DATA_PIN, SLAVE_ADDRESS_READ);
    // readACK(CLOCK_PIN, DATA_PIN);
    // int d7 = readBit(CLOCK_PIN, DATA_PIN);
    // int d6 = readBit(CLOCK_PIN, DATA_PIN);
    // int d5 = readBit(CLOCK_PIN, DATA_PIN);
    // int d4 = readBit(CLOCK_PIN, DATA_PIN);
    // int d3 = readBit(CLOCK_PIN, DATA_PIN);
    // int d2 = readBit(CLOCK_PIN, DATA_PIN);
    // int d1 = readBit(CLOCK_PIN, DATA_PIN);
    // int d0 = readBit(CLOCK_PIN, DATA_PIN);
    // writeNACK(CLOCK_PIN, DATA_PIN);
    // stopSignal(CLOCK_PIN, DATA_PIN);
    // idle(CLOCK_PIN, DATA_PIN, 0);

    // printf("Full T us: %f\n", PERIOD_T_IN_US);
    // sleep_ms(1);
    // printf("Half T us: %f\n", HALF_PERIOD_T_IN_US);
    // sleep_ms(1);
    // printf("Quarter T us: %f\n", QUARTER_PERIOD_T_IN_US );
    // sleep_ms(1);
    // //printf("hello\n");
    // printf("pwr data: %d%d%d%d%d%d%d%d", d7, d6, d5, d4, d3, d2, d1, d0);


    // int* pwrmgmtAckArray = writeToMPU(PWR_MGMT_1_ADDRESS, 0b00000001);

    // int* readpwrmgmtAckArray = malloc(8 * sizeof(int));
    // readFromMPU(PWR_MGMT_1_ADDRESS, readpwrmgmtAckArray);

    // printf("---pwrmgmtAckArray---\n");
    // printArray(pwrmgmtAckArray, 3, true);

    // printf("---readpwrmgmtAckArray---\n");
    // printArray(readpwrmgmtAckArray, 8, true);


    return 0;
}