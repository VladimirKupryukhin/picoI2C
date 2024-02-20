#include "pico/stdlib.h"
#include "../header/myi2c.h"
#include <stdio.h>
#include <stdlib.h>

#define SLAVE_ADDRESS_WRITE 0b11010000
#define SLAVE_ADDRESS_READ 0b11010001
#define PWR_MGMT_1_ADDRESS 0b01101011
#define SMPRT_DIV (char)(25)
#define CONFIG (char)(26)
#define GYRO_CONFIG (char)(27)
#define ACCEL_CONFIG (char)(28)

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

// int* writeToMPU(char targetAddress, char dataToWrite){
//     startSignal(CLOCK_PIN, DATA_PIN);
//     writeByte(CLOCK_PIN, DATA_PIN, SLAVE_ADDRESS_WRITE);
//     int writeAck1 = readACK(CLOCK_PIN, DATA_PIN);
//     writeByte(CLOCK_PIN, DATA_PIN, targetAddress);
//     int writeAck2 = readACK(CLOCK_PIN, DATA_PIN);
//     writeByte(CLOCK_PIN, DATA_PIN, dataToWrite);
//     int writeAck3 = readACK(CLOCK_PIN, DATA_PIN);
//     stopSignal(CLOCK_PIN, DATA_PIN);
//     idle(CLOCK_PIN, DATA_PIN);

//     int* ackArray = malloc(sizeof(10 * sizeof(int)));
//     ackArray[0] = writeAck1;
//     ackArray[1] = writeAck2;
//     ackArray[2] = writeAck3;
//     //int ackArray[3] = {writeAck1, writeAck2, writeAck3};

//     return ackArray;
// }

// // dataArray = [MSB, ... , LSB]
// int* readFromMPU(char targetAdress, int* dataArray) {
//     //Read from the power managment register
//     startSignal(CLOCK_PIN, DATA_PIN);
//     writeByte(CLOCK_PIN, DATA_PIN, SLAVE_ADDRESS_WRITE);
//     int readAck1 = readACK(CLOCK_PIN, DATA_PIN);
//     writeByte(CLOCK_PIN, DATA_PIN, targetAdress);
//     int readAck2 = readACK(CLOCK_PIN, DATA_PIN);
//     repeatedStart(CLOCK_PIN, DATA_PIN);
//     writeByte(CLOCK_PIN, DATA_PIN, SLAVE_ADDRESS_READ);
//     int readAck3 = readACK(CLOCK_PIN, DATA_PIN);
//     dataArray[0] = readBit(CLOCK_PIN, DATA_PIN);
//     dataArray[1] = readBit(CLOCK_PIN, DATA_PIN);
//     dataArray[2] = readBit(CLOCK_PIN, DATA_PIN);
//     dataArray[3] = readBit(CLOCK_PIN, DATA_PIN);
//     dataArray[4] = readBit(CLOCK_PIN, DATA_PIN);
//     dataArray[5] = readBit(CLOCK_PIN, DATA_PIN);
//     dataArray[6] = readBit(CLOCK_PIN, DATA_PIN);
//     dataArray[7] = readBit(CLOCK_PIN, DATA_PIN);
//     writeNACK(CLOCK_PIN, DATA_PIN);
//     stopSignal(CLOCK_PIN, DATA_PIN);
//     idle(CLOCK_PIN, DATA_PIN);

//     int* ackArray = malloc(sizeof(10 * sizeof(int)));
//     ackArray[0] = readAck1;
//     ackArray[1] = readAck2;
//     ackArray[2] = readAck3;

//     return ackArray;

// }

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

    // BUS_HIGH(DATA_PIN);
    // BUS_HIGH(CLOCK_PIN);

    idle(CLOCK_PIN, DATA_PIN, 20);
    startSignal(CLOCK_PIN, DATA_PIN);
    writeByte(CLOCK_PIN, DATA_PIN, SLAVE_ADDRESS_WRITE);
    readACK(CLOCK_PIN, DATA_PIN);
    writeByte(CLOCK_PIN, DATA_PIN, PWR_MGMT_1_ADDRESS);
    readACK(CLOCK_PIN, DATA_PIN);
    writeByte(CLOCK_PIN, DATA_PIN, 0b00000001);
    readACK(CLOCK_PIN, DATA_PIN);
    stopSignal(CLOCK_PIN, DATA_PIN);
    idle(CLOCK_PIN, DATA_PIN, 0);

    printf("Full T us: %f\n", PERIOD_T_IN_US);
    sleep_ms(1);
    printf("Half T us: %f\n", HALF_PERIOD_T_IN_US);
    sleep_ms(1);
    printf("Quarter T us: %f\n", QUARTER_PERIOD_T_IN_US );


    // int* pwrmgmtAckArray = writeToMPU(PWR_MGMT_1_ADDRESS, 0b00000001);

    // int* readpwrmgmtAckArray = malloc(8 * sizeof(int));
    // readFromMPU(PWR_MGMT_1_ADDRESS, readpwrmgmtAckArray);

    // printf("---pwrmgmtAckArray---\n");
    // printArray(pwrmgmtAckArray, 3, true);

    // printf("---readpwrmgmtAckArray---\n");
    // printArray(readpwrmgmtAckArray, 8, true);


    return 0;
}