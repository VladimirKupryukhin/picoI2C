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
    properties->clockPin = clockPin;
    properties->dataPin = dataPin;

    // Set the functions
    functions->destructor = &destructorMPU6000;
    functions->writeToMPU = &writeToMPU;
    functions->readFromMPU = &readFromMPU;

    object->func = functions;
    object->prop = properties;


    // Send the stuff needed for setup
    int* SMPRT_DIV_result = writeToMPU(SMPRT_DIV, 0b00000000, object);
    int* CONFIG_result = writeToMPU(CONFIG, 0b00000000, object);
    int* GYRO_CONFIG_result = writeToMPU(GYRO_CONFIG, 0b00001000, object);
    int* ACCEL_CONFIG_result = writeToMPU(ACCEL_CONFIG, 0b00000000, object);
    int* PWR_MGMT_1_ADDRESS_result = writeToMPU(PWR_MGMT_1_ADDRESS, 0b00000001, object);

    if (SMPRT_DIV_result[0] == 1 || SMPRT_DIV_result[1] == 1 || SMPRT_DIV_result[2] == 1) {
        printf("SMPRT_DIV_result is not all 0's!: %d %d %d\n", SMPRT_DIV_result[0], SMPRT_DIV_result[1], SMPRT_DIV_result[2]);
    }

    if (CONFIG_result[0] == 1 || CONFIG_result[1] == 1 || CONFIG_result[2] == 1) {
        printf("CONFIG_result is not all 0's!: %d %d %d\n", CONFIG_result[0], CONFIG_result[1], CONFIG_result[2]);
    }

    if (GYRO_CONFIG_result[0] == 1 || GYRO_CONFIG_result[1] == 1 || GYRO_CONFIG_result[2] == 1) {
        printf("GYRO_CONFIG_result is not all 0's!: %d %d %d\n", GYRO_CONFIG_result[0], GYRO_CONFIG_result[1], GYRO_CONFIG_result[2]);
    }

    if (ACCEL_CONFIG_result[0] == 1 || ACCEL_CONFIG_result[1] == 1 || ACCEL_CONFIG_result[2] == 1) {
        printf("ACCEL_CONFIG_result is not all 0's!: %d %d %d\n", ACCEL_CONFIG_result[0], ACCEL_CONFIG_result[1], ACCEL_CONFIG_result[2]);
    }

    if (PWR_MGMT_1_ADDRESS_result[0] == 1 || PWR_MGMT_1_ADDRESS_result[1] == 1 || PWR_MGMT_1_ADDRESS_result[2] == 1) {
        printf("PWR_MGMT_1_ADDRESS_result is not all 0's!: %d %d %d\n", PWR_MGMT_1_ADDRESS_result[0], PWR_MGMT_1_ADDRESS_result[1], PWR_MGMT_1_ADDRESS_result[2]);
    }



    free(SMPRT_DIV_result);
    free(CONFIG_result);
    free(GYRO_CONFIG_result);
    free(ACCEL_CONFIG_result);
    free(PWR_MGMT_1_ADDRESS_result);
    //TODO check if all of these results are filled with 0s to
    // confirm that everything works
    return object;



}


void destructorMPU6000(struct MPU6000* object) {
    printf("Destruct MPU6000\n");
    

}

int* writeToMPU(char targetAddress, char dataToWrite, struct MPU6000* object) {
    printf("writeToMPU\n");
    int clockPin = object->prop->clockPin;
    int dataPin = object->prop->dataPin;

    idle(clockPin, dataPin, 5);
    startSignal(clockPin, dataPin);
    writeByte(clockPin, dataPin, SLAVE_ADDRESS_WRITE);
    int writeAck1 = readACK(clockPin, dataPin);
    writeByte(clockPin, dataPin, targetAddress);
    int writeAck2 = readACK(clockPin, dataPin);
    writeByte(clockPin, dataPin, dataToWrite);
    int writeAck3 = readACK(clockPin, dataPin);
    stopSignal(clockPin, dataPin);
    idle(clockPin, dataPin, 5);

    int* ackArray = malloc(sizeof(10 * sizeof(int)));
    ackArray[0] = writeAck1;
    ackArray[1] = writeAck2;
    ackArray[2] = writeAck3;

    return ackArray;    
}

// dataArray = [MSB, ... , LSB]
int* readFromMPU(char targetAddress, int* dataArray, struct MPU6000* object) {
    printf("readFromMPU\n");

    int clockPin = object->prop->clockPin;
    int dataPin = object->prop->dataPin;

    startSignal(clockPin, dataPin);
    writeByte(clockPin, dataPin, SLAVE_ADDRESS_WRITE);
    int readAck1 = readACK(clockPin, dataPin);
    writeByte(clockPin, clockPin, targetAddress);
    int readAck2 = readACK(clockPin, dataPin);
    repeatedStart(clockPin, dataPin);
    writeByte(clockPin, dataPin, SLAVE_ADDRESS_READ);
    int readAck3 = readACK(clockPin, dataPin);
    dataArray[0] = readBit(clockPin, dataPin);
    dataArray[1] = readBit(clockPin, dataPin);
    dataArray[2] = readBit(clockPin, dataPin);
    dataArray[3] = readBit(clockPin, dataPin);
    dataArray[4] = readBit(clockPin, dataPin);
    dataArray[5] = readBit(clockPin, dataPin);
    dataArray[6] = readBit(clockPin, dataPin);
    dataArray[7] = readBit(clockPin, dataPin);
    writeNACK(clockPin, dataPin);
    stopSignal(clockPin, dataPin);
    idle(clockPin, dataPin, 0);

    int* ackArray = malloc(sizeof(3 * sizeof(int)));
    ackArray[0] = readAck1;
    ackArray[1] = readAck2;
    ackArray[2] = readAck3;

    return ackArray;

}