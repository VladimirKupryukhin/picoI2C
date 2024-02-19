#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>

#define BUS_ZERO(PIN) gpio_set_dir(PIN, GPIO_OUT) // This will make the bus go to low voltage
#define BUS_ONE(PIN) gpio_set_dir(PIN, GPIO_IN) // This will make the bus go to high voltage
#define DATA_PIN 14
#define CLOCK_PIN 15

#define SLAVE_ADDRESS_WRITE 0b11010000
#define SLAVE_ADDRESS_READ 0b11010001
#define PWR_MGMT_1_ADDRESS 0b01101011
#define SMPRT_DIV (char)(25)
#define CONFIG (char)(26)
#define GYRO_CONFIG (char)(27)
#define ACCEL_CONFIG (char)(28)

#define TEMP_OUT_H (char)(65)
#define TEMP_OUT_L (char)(66)
#define GYRO_X_H (char)(67)
#define GYRO_X_L (char)(68)



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
void writeByte(char);

void printArray(int* array, int length, bool shouldNewLine);
int* writeToMPU(char targetAddress, char dataToWrite);
int* readFromMPU(char targetAdress, int* dataArray);

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

    int* smprtAckArray = writeToMPU(SMPRT_DIV, 0b00000000);
    int* configAckArray = writeToMPU(CONFIG, 0b00000000);
    int* gyroConfigAckArray = writeToMPU(GYRO_CONFIG, 0b00001000);
    int* accelAckArray = writeToMPU(ACCEL_CONFIG, 0b00000000);
    int* pwrmgmtAckArray = writeToMPU(PWR_MGMT_1_ADDRESS, 0b00000001);


    int* temp15To8Array = malloc(8 * sizeof(int));
    int* temp7To0Array = malloc(8 * sizeof(int));
    int* temp15To8AckArray = readFromMPU(TEMP_OUT_H, temp15To8Array);
    int* temp7To0AckArray = readFromMPU(TEMP_OUT_L, temp7To0Array);

    int* readpwrmgmtAckArray = malloc(8 * sizeof(int));
    readFromMPU(PWR_MGMT_1_ADDRESS, readpwrmgmtAckArray);

    printf("---smprtAckArray---\n");
    printArray(smprtAckArray, 3, true);
    printf("---configAckArray---\n");
    printArray(configAckArray, 3, true);
    printf("---gyroConfigAckArray---\n");
    printArray(accelAckArray, 3, true);
    printf("---pwrmgmtAckArray---\n");
    printArray(pwrmgmtAckArray, 3, true);

    printf("---gyro15To8AckArray---\n");
    printArray(temp15To8AckArray, 3,true);
    printf("---gyro7To0AckArray---\n");
    printArray(temp7To0AckArray, 3, true);
    printf("---readpwrmgmtAckArray---\n");
    printArray(readpwrmgmtAckArray, 8, true);

    // while (true) {
    //     readFromMPU(TEMP_OUT_H, temp15To8Array);
    //     readFromMPU(TEMP_OUT_L, temp7To0Array);
    //     printf("---Temperature Data---\n");
    //     printArray(temp15To8Array, 8, false);
    //     printArray(temp7To0Array, 8, true);

    //     sleep_ms(1);

    // }

    double rawXValue = 0;//Zero degrees
    short gyroXVelocity = 0;
    double trueXAngle = 0;

    while (true) {
        readFromMPU(GYRO_X_H, temp15To8Array);
        readFromMPU(GYRO_X_L, temp7To0Array);
        printf("---GYRO X Data---\n");

        //the high
        for (int index = 0; index < 8; index++) {
            gyroXVelocity = (((short)(temp15To8Array[index])) << 15 - index) | gyroXVelocity;
        }

        //the low
        for (int index = 0; index < 8; index++) {
            gyroXVelocity = (((short)(temp7To0Array[index])) << 7 - index) | gyroXVelocity;
        }

        //Remove 2's complement
        gyroXVelocity = gyroXVelocity - 1;
        gyroXVelocity = ~gyroXVelocity;
        
        rawXValue = rawXValue + (gyroXVelocity * 0.05);
        trueXAngle = rawXValue * (360.0 / 65635.0);

        //rawXValue = rawXValue + ((double)(gyroXVelocity) * 0.001);

        //int actualDegrees = actualDegrees + (double)(rawXValue) * (360.0 / 65535.0);

        printf("rawXValue %f\n", rawXValue);
        printf("raw velocity %d\n", gyroXVelocity);
        printf("Degrees: %f\n", trueXAngle);
        printArray(temp15To8Array, 8, false);
        printf(" ");
        printArray(temp7To0Array, 8, true);

        sleep_ms(50);

    }



    //int[3] ackArray = writeToMPU(PWR_MGMT_1_ADDRESS, 0b00000001);





    // printf("---Write---\n");
    // sleep_ms(1);
    // printf("writeAck1 = %d\n", writeAck1);
    // sleep_ms(1);
    // printf("writeAck2 = %d\n", writeAck2);
    // sleep_ms(1);
    // printf("writeAck3 = %d\n", writeAck3);
    // sleep_ms(1);
    // printf("---Read---\n");
    // sleep_ms(1);
    // printf("readAck1 = %d\n", readAck1);
    // sleep_ms(1);
    // printf("readAck2 = %d\n", readAck2);
    // sleep_ms(1);
    // printf("readAck3 = %d\n", readAck3);
    // sleep_ms(1);
    // printf("Data = MSB %d%d%d%d%d%d%d%d LSB", d7, d6, d5, d4, d3, d2, d1, d0);
    // sleep_ms(1);

    // //Gyro config
    // start();
    // writeByte(0b11010000);
    // readACK();
    // writeByte(0b00011011);//address
    // readACK();
    // writeByte(0b11100000);//data
    // readACK();
    // stop();
    // idle();

    // sleep_us(10);

    // //Enable MPU
    // start();
    // writeByte(0b11010000);
    // readACK();
    // writeByte(0b01101011);
    // readACK();
    // writeByte(0b10100000);
    // readACK();
    // stop();
    // idle();

    // sleep_us(10);

    // // Gyro x out
    // idle();
    // start();
    // writeByte(0b11010000);
    // readACK();
    // //writeByte(0b01000100);
    // writeByte(0b01000010);
    // readACK();
    // repeatedStart();
    // writeByte(0b11010001);
    // readACK();
    // int d7 = readBit();
    // int d6 = readBit();
    // int d5 = readBit();
    // int d4 = readBit();
    // int d3 = readBit();
    // int d2 = readBit();
    // int d1 = readBit();
    // int d0 = readBit();
    // writeNACK();
    // stop();
    // idle();

    return 0;
}

void printArray(int* array, int length, bool shouldNewLine){

    for (int index = 0; index < length; index++) {
        sleep_ms(1);
        printf("%d", array[index]);
    }

    sleep_ms(1);
    if (shouldNewLine)  printf("\n");
}

int* writeToMPU(char targetAddress, char dataToWrite){
    start();
    writeByte(SLAVE_ADDRESS_WRITE);
    int writeAck1 = readACK();
    writeByte(targetAddress);
    int writeAck2 = readACK();
    writeByte(dataToWrite);
    int writeAck3 = readACK();
    stop();
    idle();

    int* ackArray = malloc(sizeof(10 * sizeof(int)));
    ackArray[0] = writeAck1;
    ackArray[1] = writeAck2;
    ackArray[2] = writeAck3;
    //int ackArray[3] = {writeAck1, writeAck2, writeAck3};

    return ackArray;
}

// dataArray = [MSB, ... , LSB]
int* readFromMPU(char targetAdress, int* dataArray) {
    //Read from the power managment register
    start();
    writeByte(SLAVE_ADDRESS_WRITE);
    int readAck1 = readACK();
    writeByte(targetAdress);
    int readAck2 = readACK();
    repeatedStart();
    writeByte(SLAVE_ADDRESS_READ);
    int readAck3 = readACK();
    dataArray[0] = readBit();
    dataArray[1] = readBit();
    dataArray[2] = readBit();
    dataArray[3] = readBit();
    dataArray[4] = readBit();
    dataArray[5] = readBit();
    dataArray[6] = readBit();
    dataArray[7] = readBit();
    writeNACK();
    stop();
    idle();

    int* ackArray = malloc(sizeof(10 * sizeof(int)));
    ackArray[0] = readAck1;
    ackArray[1] = readAck2;
    ackArray[2] = readAck3;

    return ackArray;

}



void idle(){
    //Idle the bus
    BUS_ONE(DATA_PIN);
    BUS_ONE(CLOCK_PIN);
    sleep_us(10);
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
    BUS_ONE(DATA_PIN);// Release the data bus 
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

void writeByte(char byte){
    write((byte & 0b10000000) >> 7); // MSB
    write((byte & 0b01000000) >> 6); 
    write((byte & 0b00100000) >> 5); 
    write((byte & 0b00010000) >> 4); 
    write((byte & 0b00001000) >> 3); 
    write((byte & 0b00000100) >> 2); 
    write((byte & 0b00000010) >> 1); 
    write((byte & 0b00000001) >> 0); // MSB
}



