#ifndef MPU6000_H
#define MPU6000_H

#include <stdlib.h>
#include <stdio.h>

struct MPU6000;

struct func{
    void (*destructor) (struct MPU6000* object);
};

struct prop{
    int clockData;
    int dataPin;
};

struct MPU6000{
    struct func* func;
    struct prop* prop;
    
};

struct MPU6000* initMPU6000(int clockPin, int dataPin);
void destructorMPU6000(struct MPU6000* object);

#endif