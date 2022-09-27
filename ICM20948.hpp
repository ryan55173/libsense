#ifndef SENSE_B_ICM20948_H
#define SENSE_B_ICM20948_H
#ifdef __cplusplus
extern "C" {
#endif

// 9-axis Sensor (3-axis gyroscope, 3-axis accelerometer, 3-axis compass, digital motion processor)

using namespace std;

namespace sense_b {

// ICM20948
const static uint8_t ICM_I2C_ADDRESS = 0x68;
const static uint8_t ICM_WHOAMI_ID = 0xEA;
const static int ICM_SPI_DEFAULT_FREQ = 4000000;
// Registers
const static uint8_t ICM_REG_BANK_SEL = 0x7F;
// Register Bank 0
const static uint8_t ICM_WHO_AM_I = 0x00;
const static uint8_t ICM_USER_CTRL = 0x03;
const static uint8_t ICM_LP_CONFIG = 0x05;
const static uint8_t ICM_PWR_MGMT_1 = 0x06;
const static uint8_t ICM_PWR_MGMT_2 = 0x07;
const static uint8_t ICM_INT_PIN_CFG = 0x0F;
const static uint8_t ICM_INT_ENABLE = 0x10;
const static uint8_t ICM_INT_ENABLE_1 = 0x11;
const static uint8_t ICM_INT_ENABLE_2 = 0x12;
const static uint8_t ICM_INT_ENABLE_3 = 0x12;
const static uint8_t ICM_I2C_MST_STATUS = 0x17;
const static uint8_t ICM_INT_STATUS = 0x19;
const static uint8_t ICM_INT_STATUS_1 = 0x1A;
const static uint8_t ICM_INT_STATUS_2 = 0x1B;
const static uint8_t ICM_INT_STATUS_3 = 0x1C;
const static uint8_t ICM_DELAY_TIME_H = 0x28;
const static uint8_t ICM_DELAY_TIME_L = 0x29;
const static uint8_t ICM_ACCEL_XOUT_H = 0x2D;
const static uint8_t ICM_ACCEL_XOUT_L = 0x2E;
const static uint8_t ICM_ACCEL_YOUT_H = 0x2F;
const static uint8_t ICM_ACCEL_YOUT_L = 0x30;
const static uint8_t ICM_ACCEL_ZOUT_H = 0x31;
const static uint8_t ICM_ACCEL_ZOUT_L = 0x32;
const static uint8_t ICM_GYRO_XOUT_H = 0x33;
const static uint8_t ICM_GYRO_XOUT_L = 0x34;
const static uint8_t ICM_GYRO_YOUT_H = 0x35;
const static uint8_t ICM_GYRO_YOUT_L = 0x36;
const static uint8_t ICM_GYRO_ZOUT_H = 0x37;
const static uint8_t ICM_GYRO_ZOUT_L = 0x38;
const static uint8_t ICM_TEMP_OUT_H = 0x39;
const static uint8_t ICM_TEMP_OUT_L = 0x3A;
const static uint8_t ICM_EXT_SLV_SENS_DATA_00 = 0x3B;
const static uint8_t ICM_EXT_SLV_SENS_DATA_01 = 0x3C;
const static uint8_t ICM_EXT_SLV_SENS_DATA_02 = 0x3D;
const static uint8_t ICM_EXT_SLV_SENS_DATA_03 = 0x3E;
const static uint8_t ICM_EXT_SLV_SENS_DATA_04 = 0x3F;
const static uint8_t ICM_EXT_SLV_SENS_DATA_05 = 0x40;
const static uint8_t ICM_EXT_SLV_SENS_DATA_06 = 0x41;
const static uint8_t ICM_EXT_SLV_SENS_DATA_07 = 0x42;
const static uint8_t ICM_EXT_SLV_SENS_DATA_08 = 0x43;
const static uint8_t ICM_EXT_SLV_SENS_DATA_09 = 0x44;
const static uint8_t ICM_EXT_SLV_SENS_DATA_10 = 0x45;
const static uint8_t ICM_EXT_SLV_SENS_DATA_11 = 0x46;
const static uint8_t ICM_EXT_SLV_SENS_DATA_12 = 0x47;
const static uint8_t ICM_EXT_SLV_SENS_DATA_13 = 0x48;
const static uint8_t ICM_EXT_SLV_SENS_DATA_14 = 0x49;
const static uint8_t ICM_EXT_SLV_SENS_DATA_15 = 0x4A;
const static uint8_t ICM_EXT_SLV_SENS_DATA_16 = 0x4B;
const static uint8_t ICM_EXT_SLV_SENS_DATA_17 = 0x4C;
const static uint8_t ICM_EXT_SLV_SENS_DATA_18 = 0x4D;
const static uint8_t ICM_EXT_SLV_SENS_DATA_19 = 0x4E;
const static uint8_t ICM_EXT_SLV_SENS_DATA_20 = 0x4F;
const static uint8_t ICM_EXT_SLV_SENS_DATA_21 = 0x50;
const static uint8_t ICM_EXT_SLV_SENS_DATA_22 = 0x51;
const static uint8_t ICM_EXT_SLV_SENS_DATA_23 = 0x52;
const static uint8_t ICM_FIFO_EN_1 = 0x66;
const static uint8_t ICM_FIFO_EN_2 = 0x67;
const static uint8_t ICM_FIFO_RST = 0x68;
const static uint8_t ICM_FIFO_MODE = 0x69;
const static uint8_t ICM_FIFO_COUNT_H = 0x70;
const static uint8_t ICM_FIFO_COUNT_L = 0x71;
const static uint8_t ICM_FIFO_R_W = 0x72;
const static uint8_t ICM_DATA_RDY_STATUS = 0x74;
const static uint8_t ICM_FIFO_CFG = 0x76;
// Register Bank 1
const static uint8_t ICM_SELF_TEST_X_GYRO = 0x02;
const static uint8_t ICM_SELF_TEST_Y_GYRO = 0x03;
const static uint8_t ICM_SELF_TEST_Z_GYRO = 0x04;
const static uint8_t ICM_SELF_TEST_X_ACCEL = 0x0E;
const static uint8_t ICM_SELF_TEST_Y_ACCEL = 0x0F;
const static uint8_t ICM_SELF_TEST_Z_ACCEL = 0x10;
const static uint8_t ICM_XA_OFFS_H = 0x14;
const static uint8_t ICM_XA_OFFS_L = 0x15;
const static uint8_t ICM_YA_OFFS_H = 0x17;
const static uint8_t ICM_YA_OFFS_L = 0x18;
const static uint8_t ICM_ZA_OFFS_H = 0x1A;
const static uint8_t ICM_ZA_OFFS_L = 0x1B;
const static uint8_t ICM_TIMEBASE_CORRECTION_PLL = 0x28;
// Register Bank 2
const static uint8_t ICM_GYRO_SMPLRT_DIV = 0x00;
const static uint8_t ICM_GYRO_CONFIG_1 = 0x01;
const static uint8_t ICM_GYRO_CONFIG_2 = 0x02;
const static uint8_t ICM_XG_OFFS_USR_H = 0x03;
const static uint8_t ICM_XG_OFFS_USR_L = 0x04;
const static uint8_t ICM_YG_OFFS_USR_H = 0x05;
const static uint8_t ICM_YG_OFFS_USR_L = 0x06;
const static uint8_t ICM_ZG_OFFS_USR_H = 0x07;
const static uint8_t ICM_ZG_OFFS_USR_L = 0x08;
const static uint8_t ICM_ODR_ALIGN_EN = 0x09;
const static uint8_t ICM_ACCEL_SMPLRT_DIV_1 = 0x10;
const static uint8_t ICM_ACCEL_SMPLRT_DIV_2 = 0x11;
const static uint8_t ICM_ACCEL_INTEL_CTRL = 0x12;
const static uint8_t ICM_ACCEL_WOM_THR = 0x13;
const static uint8_t ICM_ACCEL_CONFIG = 0x14; 
const static uint8_t ICM_ACCEL_CONFIG_2 = 0x15;
const static uint8_t ICM_FSYNC_CONFIG = 0x52;
const static uint8_t ICM_TEMP_CONFIG = 0x53;
const static uint8_t ICM_MOD_CTRL_USR = 0x54;
// Register Bank 3
const static uint8_t ICM_I2C_MST_ODR_CONFIG = 0x00;
const static uint8_t ICM_I2C_MST_CTRL = 0x01;
const static uint8_t ICM_I2C_MST_DELAY_CTRL = 0x02;
const static uint8_t ICM_I2C_SLV0_ADDR = 0x03;
const static uint8_t ICM_I2C_SLV0_REG = 0x04;
const static uint8_t ICM_I2C_SLV0_CTRL = 0x05;
const static uint8_t ICM_I2C_SLV0_DO = 0x06;
const static uint8_t ICM_I2C_SLV1_ADDR = 0x07;
const static uint8_t ICM_I2C_SLV1_REG = 0x08;
const static uint8_t ICM_I2C_SLV1_CTRL = 0x09;
const static uint8_t ICM_I2C_SLV1_DO = 0x0A;
const static uint8_t ICM_I2C_SLV2_ADDR = 0x0B;
const static uint8_t ICM_I2C_SLV2_REG = 0x0C;
const static uint8_t ICM_I2C_SLV2_CTRL = 0x0D;
const static uint8_t ICM_I2C_SLV2_DO = 0x0E;
const static uint8_t ICM_I2C_SLV3_ADDR = 0x0F;
const static uint8_t ICM_I2C_SLV3_REG = 0x10;
const static uint8_t ICM_I2C_SLV3_CTRL = 0x11;
const static uint8_t ICM_I2C_SLV3_DO = 0x12;
const static uint8_t ICM_I2C_SLV4_ADDR = 0x13;
const static uint8_t ICM_I2C_SLV4_REG = 0x14;
const static uint8_t ICM_I2C_SLV4_CTRL = 0x15;
const static uint8_t ICM_I2C_SLV4_DO = 0x16;
const static uint8_t ICM_I2C_SLV4_DI = 0x17;

class ICM20948 {
    public:
        ICM20948(void);
        int read_whoami(void);
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
