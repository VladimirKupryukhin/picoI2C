#include "../header/mpu6000.h"

struct MPU6000* initMPU6000(int clockPin, int dataPin) {
    printf("Init MPU6000\n");

    // Create MPU600
    struct MPU6000* object = (struct MPU6000*)malloc(sizeof(struct MPU6000));

    // Create functions
    struct func* functions = (struct func*)malloc(sizeof(struct func));
    // Create properties
    struct prop* properties = (struct prop*)malloc(sizeof(struct prop));


    // Set the I2C pins
    properties->clockData = clockPin;
    properties->dataPin = dataPin;

    // Set the functions
    functions->destructor = &destructorMPU6000;

    object->func = functions;
    object->prop = properties;
    return object;

}


void destructorMPU6000(struct MPU6000* object) {
    printf("Destruct MPU6000\n");


}