extern "C" {
    #include <linux/i2c-dev.h>
	#include <i2c/smbus.h>
    #include <fcntl.h>
    #include <unistd.h>
	#include <sys/ioctl.h>
}
#include <iostream>
#include <thread>
#include <chrono>
#include "SHTC3.hpp"

using namespace std;

// Temperature and humidity sensor
// TODO: Finish writing this, it's broken

namespace sense_b {

// SHTC3
SHTC3::SHTC3() {
    init();
}
int SHTC3::check_id() {
    int id = -1;
    uint8_t msb;
    uint8_t lsb;
    // Open I2C
    int file = open(device_filename.c_str(), O_RDWR);
	if (file < 0) {
		cout << "\tERROR: Cannot open " << device_filename << endl;
		close(file);
        // TODO: Error
	}
	if (ioctl(file, I2C_SLAVE, SHTC3_I2C_ADDRESS) < 0) {
		cout << "\tERROR: Could not call device address 0x70" << endl;
		close(file);
        // TODO: Error
	}
    // Send read ID command SHTC3_CMD_READ_ID
    msb = SHTC3_CMD_READ_ID >> 8;
    lsb = SHTC3_CMD_READ_ID & 0xFF;
    cout << "\tWriting SHTC3_CMD_READ_ID Command: 0x" << hex << uppercase << SHTC3_CMD_READ_ID << endl;
    i2c_smbus_write_byte(file, SHTC3_I2C_WRITE);
    i2c_smbus_write_byte(file, msb);
    i2c_smbus_write_byte(file, lsb);
    // Read ID
    cout << "\tReading ID response" << endl;
    uint8_t num_response = 3;
    uint8_t response[num_response];
    i2c_smbus_write_byte(file, SHTC3_I2C_READ);
    for (int i = 0; i < num_response; ++i) {
        response[i] = i2c_smbus_read_byte(file);
        cout << "\t\tRead Byte: 0x" << hex << uppercase << (int)response[i] << endl;
    }

    // TODO: Read response to ID (int)

    // Close
    close(file);
    return id;
}
// TODO: Debug and fix below method
uint8_t *SHTC3::full_measurement() {
    uint8_t *results;
    uint8_t num_results = 6;
    results = new uint8_t[num_results];
    uint8_t msb;
    uint8_t lsb;
    // Open I2C
    int file = open(device_filename.c_str(), O_RDWR);
	if (file < 0) {
		cout << "\tERROR: Cannot open " << device_filename << endl;
		close(file);
        // TODO: Error
	}
	if (ioctl(file, I2C_SLAVE, SHTC3_I2C_ADDRESS) < 0) {
		cout << "\tERROR: Could not call device address 0x70" << endl;
		close(file);
        // TODO: Error
	}
    // Wakeup
    msb = SHTC3_WAKEUP >> 8;
    lsb = SHTC3_WAKEUP & 0xFF;
    cout << "\tWriting SHTC3_WAKEUP Command: 0x" << hex << uppercase << SHTC3_WAKEUP << endl;
    i2c_smbus_write_byte(file, SHTC3_I2C_WRITE);
    i2c_smbus_write_byte(file, msb);
    i2c_smbus_write_byte(file, lsb);
    this_thread::sleep_for(chrono::milliseconds(SHTC3_RESET_DELAY));
    // Send measurement command
    msb = SHTC3_CMD_CSD_RHF_NPM >> 8;
    lsb = SHTC3_CMD_CSD_RHF_NPM & 0xFF;
    cout << "\tWriting SHTC3_CMD_CSD_RHF_NPM Command: 0x" << hex << uppercase << SHTC3_CMD_CSD_RHF_NPM << endl;
    i2c_smbus_write_byte(file, SHTC3_I2C_WRITE);
    i2c_smbus_write_byte(file, msb);
    i2c_smbus_write_byte(file, lsb);
    this_thread::sleep_for(chrono::milliseconds(SHTC3_RESET_DELAY));
    // Read measurements (Up to here is probably right)
    cout << "\tReading measurement responses" << endl;
    for (uint8_t i = 0; i < num_results; ++i) {
        i2c_smbus_write_byte(file, SHTC3_I2C_READ);
        results[i] = i2c_smbus_read_byte(file);
        cout << "\t\tRead Measurement(" << to_string(i + 1) << "): 0x" << hex << uppercase << (int)results[i] << endl;
    }
    // Send sleep command
    msb = SHTC3_SLEEP >> 8;
    lsb = SHTC3_SLEEP & 0xFF;
    cout << "\tWriting SHTC3_SLEEP Command: 0x" << hex << uppercase << SHTC3_SLEEP << endl;
    i2c_smbus_write_byte(file, SHTC3_I2C_WRITE);
    i2c_smbus_write_byte(file, msb);
    i2c_smbus_write_byte(file, lsb);
    this_thread::sleep_for(chrono::milliseconds(SHTC3_RESET_DELAY));
    // Close
    close(file);
    return results;
}


// Private
void SHTC3::init() {
    // int file = open(device_filename.c_str(), O_RDWR);
	// if (file < 0) {
	// 	cout << "\tERROR: Cannot open " << device_filename << endl;
	// 	close(file);
	// 	return;
	// }
	// if (ioctl(file, I2C_SLAVE, SHTC3_I2C_ADDRESS) < 0) {
	// 	cout << "\tERROR: Could not call device address 0x70" << endl;
	// 	close(file);
	// 	return;
	// }
    // // Reset
    // i2c_smbus_write_byte_data(file, SHTC3_I2C_WRITE, (SHTC3_CMD_RESET >> 8));
    // i2c_smbus_write_byte_data(file, SHTC3_I2C_WRITE, (SHTC3_CMD_RESET & 0xFF));
    // this_thread::sleep_for(chrono::milliseconds(SHTC3_RESET_DELAY));
    // Close
    // close(file);
}
uint8_t SHTC3::crc8(const uint8_t *data, uint8_t len) {
    // Method was found on every library found for this sensor
    uint8_t crc = 0xff;
    for (uint8_t byte_ctr = 0; byte_ctr < len; ++byte_ctr) {
        crc ^= data[byte_ctr];
        for (uint8_t bit = 8; bit > 0; --bit) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x31;
            } else {
                crc = (crc << 1);
            }
        }
    }
    return crc;
}

}
