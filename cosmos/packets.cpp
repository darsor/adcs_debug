#include "packets.h"
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>

Packet::Packet(const uint32_t length, const uint16_t id):
    length(length), id(id) {
    buffer = new unsigned char[length];
}
Packet::Packet(const Packet& that): length(that.length), id(that.id) {
    buffer = new unsigned char[that.length];
}
Packet::~Packet() {
    delete[] buffer;
}
Packet& Packet::operator=(const Packet& that) {
    if (this != &that)
    {
        delete[] buffer;
        buffer = new unsigned char[that.length];
        length = that.length;
        id = that.id;
    }
    return *this;
}
void Packet::convert() {}

AttitudePacket::AttitudePacket(): Packet(ATT_PKT_SIZE, 3) {}

void AttitudePacket::convert() {
    int16_t i16;
    uint16_t u16;
    uint32_t u32;
    u32 = htonl(length);
    memcpy(buffer+0,  &u32, 4);
    u16 = htons(id);
    memcpy(buffer+4,  &u16, 2);
    i16 = htons(magi_x);
    memcpy(buffer+6,  &i16, 2);
    i16 = htons(magi_y);
    memcpy(buffer+8,  &i16, 2);
    i16 = htons(magi_z);
    memcpy(buffer+10,  &i16, 2);
    i16 = htons(mage_x);
    memcpy(buffer+12,  &i16, 2);
    i16 = htons(mage_y);
    memcpy(buffer+14,  &i16, 2);
    i16 = htons(mage_z);
    memcpy(buffer+16,  &i16, 2);
    i16 = htons(imu1_x);
    memcpy(buffer+18,  &i16, 2);
    i16 = htons(imu1_y);
    memcpy(buffer+20,  &i16, 2);
    i16 = htons(imu1_z);
    memcpy(buffer+22,  &i16, 2);
    i16 = htons(imu2_x);
    memcpy(buffer+24,  &i16, 2);
    i16 = htons(imu2_y);
    memcpy(buffer+26,  &i16, 2);
    i16 = htons(imu2_z);
    memcpy(buffer+28,  &i16, 2);
    u32 = htonl(time_frt_week);
    memcpy(buffer+30,  &u32, 4);
    u32 = htonl(time_frt_milli);
    memcpy(buffer+34,  &u32, 4);
};
