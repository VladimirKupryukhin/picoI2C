#ifndef MPU6000_H
#define MPU6000_H

#include <stdlib.h>
#include <stdio.h>
#include "myi2c.h"

#define SLAVE_ADDRESS_WRITE 0b11010000
#define SLAVE_ADDRESS_READ 0b11010001
#define PWR_MGMT_1_ADDRESS (char) (107)
#define SMPRT_DIV (char)(25)
#define CONFIG (char)(26)
#define GYRO_CONFIG (char)(27)
#define ACCEL_CONFIG (char)(28)

#define TEMP_OUT_H (char)(65) // TEMP_OUT[15:8]
#define TEMP_OUT_L (char)(66) // TEMP_OUT[7:0]

struct MPU6000;

struct func{
    void (*destructor) (struct MPU6000* object);
    int* (*writeToMPU) (char targetAddress, char dataToWrite, struct MPU6000* object, bool sendAckBits);
    int* (*readFromMPU) (char targetAddress, int* dataArray, struct MPU6000* object, bool sendAckBits);
    double (*getTemperature) (struct MPU6000* object);
};

struct prop{
    int clockPin;
    int dataPin;
};

struct MPU6000{
    struct func* func;
    struct prop* prop;
    
};

struct MPU6000* initMPU6000(int clockPin, int dataPin);
void destructorMPU6000(struct MPU6000* object);

int* writeToMPU(char targetAddress, char dataToWrite, struct MPU6000* object, bool sendAckBits); 
int* readFromMPU(char targetAddress, int* dataArray, struct MPU6000* object, bool sendAckBits);
double getTemperature(struct MPU6000* object);


#endif