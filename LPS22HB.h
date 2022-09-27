#ifndef SENSE_B_LPS22HB_H
#define SENSE_B_LPS22HB_H
#ifdef __cplusplus
extern "C" {
#endif

// Air pressure sensor

using namespace std;

namespace sense_b {

// LPS22HBTR
const static uint8_t LPS_I2C_ADDRESS = 0x5C;
const static uint8_t LPS_WHOAMI_ID = 0xB1;
// Registers
const static uint8_t LPS_INT_CFG = 0x0B; 	 // Interrupt register
const static uint8_t LPS_THS_P_L = 0x0C;	 // Pressure threshold registers
const static uint8_t LPS_THS_P_H = 0x0D;
const static uint8_t LPS_WHO_AM_I = 0x0F;
const static uint8_t LPS_CTRL_REG1 = 0x10;
const static uint8_t LPS_CTRL_REG2 = 0x11;
const static uint8_t LPS_CTRL_REG3 = 0x12;
const static uint8_t LPS_FIFO_CTRL = 0x14; 	  // FIFO configuration register
const static uint8_t LPS_REF_P_XL = 0x15; 	  // Reference pressure registers
const static uint8_t LPS_REF_P_L = 0x16;
const static uint8_t LPS_REF_P_H = 0x17;
const static uint8_t LPS_RPDS_L = 0x18; 	  // Pressure offset registers
const static uint8_t LPS_RPDS_H = 0x19;
const static uint8_t LPS_RES_CONF = 0x1A; 	  // Resolution register
const static uint8_t LPS_INT_SOURCE = 0x25;   // Interrupt register
const static uint8_t LPS_FIFO_STATUS = 0x26;  // FIFO status register
const static uint8_t LPS_STATUS = 0x27; 	  // Status register
const static uint8_t LPS_PRESS_OUT_XL = 0x28; // Pressure output registers
const static uint8_t LPS_PRESS_OUT_L = 0x29;
const static uint8_t LPS_PRESS_OUT_H = 0x2A;
const static uint8_t LPS_TEMP_OUT_L = 0x2B;   // Temperature output registers
const static uint8_t LPS_TEMP_OUT_H = 0x2C;
const static uint8_t LPS_FILTER_RESET = 0x33; // Filter reset register

class LPS22HB {
	public:
		LPS22HB(void);
		~LPS22HB();
		int read_whoami(void);
		int check_status(void);
		float temperature(void);
		float pressure(void);
		bool is_initialized(void);
	private:
		bool initialized;
		const string device_filename = "/dev/i2c-1";
		void init(void);
};

}

#ifdef __cplusplus
}
#endif
#endif
