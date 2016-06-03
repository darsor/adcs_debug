#ifndef ADCS_H
#define ADCS_H

#define MAGI_X          0x0210
#define MAGI_Y          0x0212
#define MAGI_Z          0x0214
#define MAGE_X          0x0230
#define MAGE_Y          0x0232
#define MAGE_Z          0x0234

#define IMU1_X          0x0310
#define IMU1_Y          0x0312
#define IMU1_Z          0x0314
#define IMU2_X          0x0330
#define IMU2_Y          0x0332
#define IMU2_Z          0x0334

#define FRT_WEEK_HI     0x0810
#define FRT_WEEK_LO     0x0812
#define FRT_MILLI_HI    0x0814
#define FRT_MILLI_LO    0x0816

#include "cosmos/packets.h"
#include <unistd.h>
#include <string>

class ADCS {
    public:
        ADCS(std::string dev, int baud);
        ~ADCS();
        uint16_t readReg(uint16_t reg);
        void writeReg(uint16_t reg, uint16_t data);
        void readAttitudeData(AttitudePacket &packet);
        
    private:
        int fd;
        static void printHex(unsigned char* data, int size);
};

#endif
