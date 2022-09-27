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
#include "ICM20948.hpp"

// 9-axis Sensor (3-axis gyroscope, 3-axis accelerometer, 3-axis compass, digital motion processor)

using namespace std;

namespace sense_b {

// ICM20948
ICM20948::ICM20948() {
	init();
}
int ICM20948::read_whoami() {
	int whoami = -1;
	int file = open(device_filename.c_str(), O_RDWR);
	if (file < 0) {
		cout << "\tERROR: Cannot open " << device_filename << endl;
		close(file);
		return -1;
	}
	if (ioctl(file, I2C_SLAVE, ICM_I2C_ADDRESS) < 0) {
		cout << "\tERROR: Could not call device address 0x5C" << endl;
		close(file);
		return -1;
	}
	// Read ICM_WHO_AM_I register and return value
	whoami = i2c_smbus_read_byte_data(file, ICM_WHO_AM_I);
	// Close
	close(file);
	return whoami;
}
bool ICM20948::is_initialized() {
	return initialized;
}
// Private
void ICM20948::init() {
	initialized = false;
	if (read_whoami() == ICM_WHOAMI_ID) {
		initialized = true;
	}
}

}
