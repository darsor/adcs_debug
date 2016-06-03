/**********************
 * Packet Definitions *
 **********************/
#ifndef PACKETS_H
#define PACKETS_H

#define ATT_PKT_SIZE        38

#include <cstdint>

class Packet {
    public:
        Packet(const uint32_t length, const uint16_t id);
        Packet(const Packet& that);
        Packet& operator=(const Packet& that);
        virtual ~Packet();
        virtual void convert();
        uint32_t length;
        uint16_t id;
        unsigned char* buffer;
};

class AttitudePacket: public Packet {
    public:
        AttitudePacket();
        void convert();
        int16_t magi_x;
        int16_t magi_y;
        int16_t magi_z;
        int16_t mage_x;
        int16_t mage_y;
        int16_t mage_z;
        int16_t imu1_x;
        int16_t imu1_y;
        int16_t imu1_z;
        int16_t imu2_x;
        int16_t imu2_y;
        int16_t imu2_z;
        uint32_t time_frt_week;
        uint32_t time_frt_milli;
};

#endif
