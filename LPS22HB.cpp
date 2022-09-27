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
#include "LPS22HB.hpp"

// Air pressure sensor

using namespace std;

// TODO: Get this calibrated and reading correctly
// TODO: Make asysnc methods for the temp and pressure methods as they have to wait for a 
// Updates every time pressure() or temperature() is called

namespace sense_b {

// LPS22HBTR
LPS22HB::LPS22HB() {
	init();
}
int LPS22HB::read_whoami() {
	int file = open(device_filename.c_str(), O_RDWR);
	if (file < 0) {
		// cout << "\tERROR: Cannot open " << device_filename << endl;
		close(file);
		return -1;
	}
	if (ioctl(file, I2C_SLAVE, LPS_I2C_ADDRESS) < 0) {
		// cout << "\tERROR: Could not call device address 0x5C" << endl;
		close(file);
		return -1;
	}
	// Call SMBus commands and attempt to communicate with LPS22HB
	// Read LPS_WHO_AM_I register 0x0F, should return a value of 177
	uint8_t whoami = i2c_smbus_read_byte_data(file, LPS_WHO_AM_I);
	if (read < 0) {
		// I2C read failed
		// cout << "\tERROR: I2C read failed" << endl;
		close(file);
		return -1;
	}
	// Close
	close(file);
	return (int)whoami;
}
int LPS22HB::check_status() {
	int status = -1;
	if (!initialized) {
		cout << "\tError: LPS22HB was not initialized" << endl;
		return status;
	}
	int file = open(device_filename.c_str(), O_RDWR);
	if (file < 0) {
		cout << "\tERROR: Cannot open " << device_filename << endl;
		close(file);
		return -1;
	}
	if (ioctl(file, I2C_SLAVE, LPS_I2C_ADDRESS) < 0) {
		cout << "\tERROR: Could not call device address 0x5C" << endl;
		close(file);
		return -1;
	}
	// Check status
	status = (int)i2c_smbus_read_byte_data(file, LPS_STATUS);
	// Close
	close(file);
	return (int)status;
}
float LPS22HB::temperature() {
	float temp_value = -65535.0; // Celcius
	if (!initialized) {
		cout << "\tError: LPS22HB was not initialized" << endl;
		return temp_value;
	}
	int file = open(device_filename.c_str(), O_RDWR);
	if (file < 0) {
		cout << "\tERROR: Cannot open " << device_filename << endl;
		close(file);
		return -1;
	}
	if (ioctl(file, I2C_SLAVE, LPS_I2C_ADDRESS) < 0) {
		cout << "\tERROR: Could not call device address 0x5C" << endl;
		close(file);
		return -1;
	}
	// Enable one-shot mode
	int ctrl2_setting = 0x01;
	i2c_smbus_write_byte_data(file, LPS_CTRL_REG2, ctrl2_setting);
	while ((i2c_smbus_read_byte_data(file, LPS_STATUS) & 0x02) == 0) {
		this_thread::sleep_for(chrono::milliseconds(1));
	}
	// Read temperature data
	uint8_t temp_reg[2];
	temp_reg[0] = i2c_smbus_read_byte_data(file, LPS_TEMP_OUT_H);
	temp_reg[1] = i2c_smbus_read_byte_data(file, LPS_TEMP_OUT_L);
	// cout << "\LPS_TEMP_OUT_H: " << to_string(temp_reg[0]) << endl;
	// cout << "\LPS_TEMP_OUT_L: " << to_string(temp_reg[1]) << endl;
	temp_value = ((int16_t)temp_reg[0] << 8 | (int16_t)temp_reg[1]) / 100.f;
	// Close
	close(file);
	return temp_value;
}
float LPS22HB::pressure() {
	float pressure_value = -1.0; // hPa
	if (!initialized) {
		cout << "\tError: LPS22HB was not initialized" << endl;
		return pressure_value;
	}
	int file = open(device_filename.c_str(), O_RDWR);
	if (file < 0) {
		cout << "\tERROR: Cannot open " << device_filename << endl;
		close(file);
		return -1;
	}
	if (ioctl(file, I2C_SLAVE, LPS_I2C_ADDRESS) < 0) {
		cout << "\tERROR: Could not call device address 0x5C" << endl;
		close(file);
		return -1;
	}
	// Enable one shot mode
	int ctrl2_setting = 0x01; // Other Settings?: 0x95
	i2c_smbus_write_byte_data(file, LPS_CTRL_REG2, ctrl2_setting);
	while ((i2c_smbus_read_byte_data(file, LPS_CTRL_REG2) & 0x01) != 0x00) {
		this_thread::sleep_for(chrono::milliseconds(1));
	}
	// Read pressure data
	uint8_t press_reg[3];
	press_reg[0] = i2c_smbus_read_byte_data(file, LPS_PRESS_OUT_H);
	press_reg[1] = i2c_smbus_read_byte_data(file, LPS_PRESS_OUT_L);
	press_reg[2] = i2c_smbus_read_byte_data(file, LPS_PRESS_OUT_XL);
	// cout << "\tLPS_PRESS_OUT_H: " << to_string(press_reg[0]) << endl;
	// cout << "\tLPS_PRESS_OUT_L: " << to_string(press_reg[1]) << endl;
	// cout << "\tLPS_PRESS_OUT_XL: " << to_string(press_reg[2]) << endl;
	pressure_value = ((int32_t)press_reg[0] << 16 | (int32_t)press_reg[1] << 8 | (int32_t)press_reg[2]) / 4096.f;
	// Close and return pressure in hPa
	close(file);
	return pressure_value;
}
bool LPS22HB::is_initialized() {
	return initialized;
}
// Private
void LPS22HB::init() {
	initialized = false;
	int file = open(device_filename.c_str(), O_RDWR);
	if (file < 0) {
		cout << "\tERROR: Cannot open " << device_filename << endl;
		close(file);
		return;
	}
	if (ioctl(file, I2C_SLAVE, LPS_I2C_ADDRESS) < 0) {
		cout << "\tERROR: Could not call device address 0x5C" << endl;
		close(file);
		return;
	}
	// Check LPS_WHO_AM_I value
	if (read_whoami() == LPS_WHOAMI_ID) {
		initialized = true;
	}
	// Enable one-shot mode
	int ctrl2_setting = 0x01;
	i2c_smbus_write_byte_data(file, LPS_CTRL_REG2, ctrl2_setting);
	while ((i2c_smbus_read_byte_data(file, LPS_STATUS) & 0x02) == 0) {
		this_thread::sleep_for(chrono::milliseconds(1));
	}
	// Close
	close(file);
}

}
