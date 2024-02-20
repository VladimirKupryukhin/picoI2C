#ifndef MYI2C_H
#define MYI2C_H

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#define BUS_HIGH(PIN) gpio_set_dir(PIN, GPIO_IN)
#define BUS_LOW(PIN) gpio_set_dir(PIN, GPIO_OUT)

#define FREQUENCY_IN_HZ 100000.0
#define PERIOD_T_IN_US (1.0 / FREQUENCY_IN_HZ) * 1000000.0
#define HALF_PERIOD_T_IN_US (PERIOD_T_IN_US) / 2.0
#define QUARTER_PERIOD_T_IN_US (HALF_PERIOD_T_IN_US) / 2.0

// struct myi2cProps;
// struct myi2cOps;

// struct myi2c {
//     struct myi2cProps* props;
//     struct myi2cOps* ops;
// };


/**
 * void idle()
 * -----------
 * Keeps both the SCL and SDA pins high
 * 
*/
void idle(int pinSCL, int pinSDA, int cycles);


/**
 * void startSignal()
 * -----------
 * Initiates the I2C start signal.
 * SCL is high while SDA goes low
 * 
 * 
 * SCL ‾‾‾‾__‾‾__‾‾__‾‾__‾‾__‾‾
 * SDA ‾‾‾_....................
*/
void startSignal(int pinSCL, int pinSDA);


/**
 * void writeBit()
 * ----------
 * Writes a single bit to the bus
*/
void writeBit(int pinSCL, int pinSDA, int bit);

/**
 * int readACK()
 * ----------
 * Reads the acknowledgment from a slave
 * 
 * Returns the read ack as an integer
 * 0 = ACK
 * 1 = NACK
*/
int readACK(int pinSCL, int pinSDA);

/**
 * readBit()
 * ----------
 * Reads the bit from a slave
 * 
 * Returns the read bit as an integer
 * 
*/
int readBit(int pinSCL, int pinSDA);

/**
 * writeNACK()
 * ----------
 * Write a NACK as the master to the bus
*/
void writeNACK(int pinSCL, int pinSDA);

/**
 * void repeatedStart()
 * ----------
 * Executes the repeated start of I2C
*/
void repeatedStart(int pinSCL, int pinSDA);

/**
 * void stopSignal()
 * ----------
 * Executes the stop signal
*/
void stopSignal(int pinSCL, int pinSDA);

/**
 * void writeByte(char byte)
 * ----------
 * 
 * Sends the 8 bits to the bus.
 * MSB is sent first
*/
void writeByte(int pinSCL, int pinSDA, char byte);





#endif