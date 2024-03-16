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
    functions->getTemperature = &getTemperature;
    functions->getAccelX = &getAccelX;
    functions->getAccelY = &getAccelY;
    functions->getAccelZ = &getAccelZ;
    functions->getGyroX = &getGyroX;
    functions->getGyroY = &getGyroY;
    functions->getGyroZ = &getGyroZ;
    functions->getXAngleInDegrees = &getXAngleInDegrees;
    functions->getYAngleInDegrees = &getYAngleInDegrees;
    functions->getZAngleInDegrees = &getZAngleInDegrees;


    object->func = functions;
    object->prop = properties;


    // Send the stuff needed for setup
    int* SMPRT_DIV_result = writeToMPU(SMPRT_DIV, 0b00000000, object, true);
    int* CONFIG_result = writeToMPU(CONFIG, 0b00000000, object, true);
    int* GYRO_CONFIG_result = writeToMPU(GYRO_CONFIG, 0b00001000, object, true);
    int* ACCEL_CONFIG_result = writeToMPU(ACCEL_CONFIG, 0b00000000, object, true);
    int* PWR_MGMT_1_ADDRESS_result = writeToMPU(PWR_MGMT_1_ADDRESS, 0b00000001, object, true);

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

    sleep_ms(1000);

    double accelX = getAccelX(object);
    object->prop->xOffset = acos(accelX);

    double accelY = getAccelY(object);
    object->prop->yOffset = acos(accelY);

    double accelZ = getAccelZ(object);
    object->prop->zOffset = acos(accelZ);

    printf("xOffset: %f\n", object->prop->xOffset);
    printf("yOffset: %f\n", object->prop->yOffset);
    printf("zOffset: %f\n", object->prop->zOffset);

    printf("Finished MPU6000 setup!\n");

    return object;



}


void destructorMPU6000(struct MPU6000* object) {
    printf("Destruct MPU6000\n");
    free(object->func);
    free(object->prop);
    free(object);

}

int* writeToMPU(char targetAddress, char dataToWrite, struct MPU6000* object, bool sendAckBits) {
    //printf("writeToMPU\n");

    if (object == NULL) {
        printf("writeToMPU: MPU IS NULL with targetAddress of ");
        printf("%d",((int)targetAddress));
        printf("\n");
    }

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

    if (sendAckBits) {
        int* ackArray = malloc(sizeof(10 * sizeof(int)));
        ackArray[0] = writeAck1;
        ackArray[1] = writeAck2;
        ackArray[2] = writeAck3;

        return ackArray;
    }


    return NULL;    
}

// dataArray = [MSB, ... , LSB]
int* readFromMPU(char targetAddress, int* dataArray, struct MPU6000* object, bool sendAckBits) {
    //printf("readFromMPU\n");

    if (object == NULL) {
        printf("readFromMPU: MPU IS NULL with targetAddress of ");
        printf("%d",((int)targetAddress));
        printf("\n");
    }

    int clockPin = object->prop->clockPin;
    int dataPin = object->prop->dataPin;

    startSignal(clockPin, dataPin);
    writeByte(clockPin, dataPin, SLAVE_ADDRESS_WRITE);
    int readAck1 = readACK(clockPin, dataPin);
    writeByte(clockPin, dataPin, targetAddress);
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

    
    if (sendAckBits) {
        int* ackArray = malloc(sizeof(10 * sizeof(int)));
        ackArray[0] = readAck1;
        ackArray[1] = readAck2;
        ackArray[2] = readAck3;

        return ackArray;
    }


    return NULL;    

}


double getTemperature(struct MPU6000* object){
    int* tempDataHIGH = malloc(8 * sizeof(int));
    readFromMPU(TEMP_OUT_H, tempDataHIGH, object, false);

    int* tempDataLOW = malloc(8 * sizeof(int));
    readFromMPU(TEMP_OUT_L, tempDataLOW, object, false);

    short signedTempRaw = convertReadDataToShort(tempDataHIGH, tempDataLOW);

    free(tempDataHIGH);
    free(tempDataLOW);

    double tempInCelsius = ((double)(signedTempRaw) / 340.0) + 36.53;

    return tempInCelsius;
}

short convertReadDataToShort(int* high, int* low){
    short number = 0;

    //The high
    for (int index = 0; index < 8; index++) {
        number = (((short)(high[index])) << 15 - index) | number;
    }

    //the low
    for (int index = 0; index < 8; index++) {
        number = (((short)(low[index])) << 7 - index) | number;
    }

    return number;
}

double getAccelX(struct MPU6000* object){
    int* dataHIGH = malloc(8 * sizeof(int));
    readFromMPU(ACCEL_XOUT_H, dataHIGH, object, false);

    int* dataLOW = malloc(8 * sizeof(int));
    readFromMPU(ACCEL_XOUT_L, dataLOW, object, false);

    short twosComp = convertReadDataToShort(dataHIGH, dataLOW);
    short accelX = undo2sComp(twosComp);

    free(dataHIGH);
    free(dataLOW);

    double finalValue = (double)(accelX) / 16384.0;
    if (finalValue < -1) {
        finalValue = -1;
    }
    else if (finalValue > 1) {
        finalValue = 1;
    }

    return finalValue;
}

double getAccelY(struct MPU6000* object){
    int* dataHIGH = malloc(8 * sizeof(int));
    readFromMPU(ACCEL_YOUT_H, dataHIGH, object, false);

    int* dataLOW = malloc(8 * sizeof(int));
    readFromMPU(ACCEL_YOUT_L, dataLOW, object, false);

    short twosComp = convertReadDataToShort(dataHIGH, dataLOW);
    short accelX = undo2sComp(twosComp);

    free(dataHIGH);
    free(dataLOW);

    double finalValue = (double)(accelX) / 16384.0;
    if (finalValue < -1) {
        finalValue = -1;
    }
    else if (finalValue > 1) {
        finalValue = 1;
    }

    return finalValue;
}

double getAccelZ(struct MPU6000* object){
    int* dataHIGH = malloc(8 * sizeof(int));
    readFromMPU(ACCEL_ZOUT_H, dataHIGH, object, false);

    int* dataLOW = malloc(8 * sizeof(int));
    readFromMPU(ACCEL_ZOUT_L, dataLOW, object, false);

    short twosComp = convertReadDataToShort(dataHIGH, dataLOW);
    short accelX = undo2sComp(twosComp);

    free(dataHIGH);
    free(dataLOW);

    double finalValue = (double)(accelX) / 16384.0;
    if (finalValue < -1) {
        finalValue = -1;
    }
    else if (finalValue > 1) {
        finalValue = 1;
    }

    return finalValue;

}

double getGyroX(struct MPU6000* object){
    int* dataHIGH = malloc(8 * sizeof(int));
    readFromMPU(GYRO_XOUT_H, dataHIGH, object, false);

    int* dataLOW = malloc(8 * sizeof(int));
    readFromMPU(GYRO_XOUT_L, dataLOW, object, false);

    short twosComp = convertReadDataToShort(dataHIGH, dataLOW);
    short accelX = undo2sComp(twosComp);

    free(dataHIGH);
    free(dataLOW);

    return (double)accelX / 131.0;
}

double getGyroY(struct MPU6000* object){
    int* dataHIGH = malloc(8 * sizeof(int));
    readFromMPU(GYRO_YOUT_H, dataHIGH, object, false);

    int* dataLOW = malloc(8 * sizeof(int));
    readFromMPU(GYRO_YOUT_L, dataLOW, object, false);

    short twosComp = convertReadDataToShort(dataHIGH, dataLOW);
    short accelX = undo2sComp(twosComp);

    free(dataHIGH);
    free(dataLOW);

    return (double)accelX / 131.0;
}

double getGyroZ(struct MPU6000* object){
    int* dataHIGH = malloc(8 * sizeof(int));
    readFromMPU(GYRO_ZOUT_H, dataHIGH, object, false);

    int* dataLOW = malloc(8 * sizeof(int));
    readFromMPU(GYRO_ZOUT_L, dataLOW, object, false);

    short twosComp = convertReadDataToShort(dataHIGH, dataLOW);
    short accelX = undo2sComp(twosComp);

    free(dataHIGH);
    free(dataLOW);

    return (double)accelX / 131.0;
}

short undo2sComp(short input){
    input = input - 1;
    input = ~input;

    return input;
}


double getXAngleInDegrees(struct MPU6000* object){
    double accelX = getAccelX(object);
    double radians = acos(accelX);
    return (object->prop->xOffset * (180.0 / 3.14)) - ((radians) * (180.0 / 3.14));
}

double getYAngleInDegrees(struct MPU6000* object){
    double accelY = getAccelY(object);
    double radians = acos(accelY);
    return (object->prop->yOffset * (180.0 / 3.14)) - ((radians) * (180.0 / 3.14));
}

double getZAngleInDegrees(struct MPU6000* object){
    double accelZ = getAccelZ(object);
    double radians = acos(accelZ);
    return (object->prop->zOffset * (180.0 / 3.14)) - ((radians) * (180.0 / 3.14));
}