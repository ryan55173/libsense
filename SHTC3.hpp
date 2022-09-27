#ifndef SENSE_B_SHTC3_H
#define SENSE_B_SHTC3_H
#ifdef __cplusplus
extern "C" {
#endif

// Temperature and humidity sensor
// TODO: Finish writing this, it's broken still

using namespace std;

namespace sense_b {

// SHTC3
const static uint8_t SHTC3_I2C_ADDRESS = 0x70;
const static uint8_t SHTC3_I2C_WRITE = 0xE0;
const static uint8_t SHTC3_I2C_READ = 0xE1;
// Values
const static uint16_t SHTC3_ID = 0xBC;
const static int SHTC3_MAX_CLOCK_FREQ = 1000000;  // Hz?
const static uint8_t SHTC3_RESET_DELAY = 26;  // In milliseconds
// Commands
const static uint16_t SHTC3_SLEEP = 0xB098;
const static uint16_t SHTC3_WAKEUP = 0x3517;
const static uint16_t SHTC3_CMD_SFT_RST = 0x805D;
const static uint16_t SHTC3_CMD_READ_ID = 0xEFC8;
const static uint16_t SHTC3_CMD_RESET = 0x0006;
// Measurement Commands
const static uint16_t SHTC3_CMD_CSE_RHF_NPM = 0x5C24;   // Clock stretching, RH (Relative Humidity) first, Normal power mode
const static uint16_t SHTC3_CMD_CSE_RHF_LPM = 0x44DE;   // Clock stretching, RH first, Low power mode
const static uint16_t SHTC3_CMD_CSE_TF_NPM = 0x7CA2; 	// Clock stretching, T first, Normal power mode
const static uint16_t SHTC3_CMD_CSE_TF_LPM = 0x6458;    // Clock stretching, T first, Low power mode
const static uint16_t SHTC3_CMD_CSD_RHF_NPM = 0x58E0;   // Polling, RH first, Normal power mode   # THIS
const static uint16_t SHTC3_CMD_CSD_RHF_LPM = 0x401A;   // Polling, RH first, Low power mode      # THIS
const static uint16_t SHTC3_CMD_CSD_TF_NPM = 0x7866;    // Polling, T first, Normal power mode
const static uint16_t SHTC3_CMD_CSD_TF_LPM = 0x609C;	// Polling, T first, Low power mode

class SHTC3 {
    public:
        SHTC3(void);
        ~SHTC3();
        int check_id(void);
        uint8_t *full_measurement(void);
    private:
        const string device_filename = "/dev/i2c-1";
        void init(void);
        uint8_t crc8(const uint8_t *data, uint8_t len);
};

}

#ifdef __cplusplus
}
#endif
#endif
