#include "adcs.h"
#include <wiringPi.h>
#include <wiringSerial.h>
#include <cstdio>
#include <errno.h>

ADCS::ADCS(std::string dev, int baud) {
    fd = serialOpen(dev.c_str(), baud);
    if (fd < 0) perror("ADCS failed to open");
}

ADCS::~ADCS() {
    serialClose(fd);
}

uint16_t ADCS::readReg(uint16_t reg) {
    unsigned char cmd[4] = {'$', (unsigned char)((reg >> 8) | 0x80), (unsigned char) (reg & 0x00FF), ']'};
    unsigned char tlm[8];
    printf("sending: ");
    printHex(cmd, 4);
    printf("\n");
    serialFlush(fd);
    if (write(fd, cmd, 4) < 0) perror("failed to write");
    if (read(fd, tlm, 8) < 0) perror("failed to read");
    printf("received: ");
    printHex(tlm, 8);
    printf("\n");
    return *((uint16_t*)(tlm+5));
}

void ADCS::writeReg(uint16_t reg, uint16_t data) {
    unsigned char cmd[6] = {'$', (unsigned char) (reg >> 8), (unsigned char) (reg & 0x00FF), (unsigned char) (data >> 8), (unsigned char) (data & 0x00FF), ']'};
    printf("sending: ");
    printHex(cmd, 6);
    printf("\n");
    serialFlush(fd);
    if (write(fd, cmd, 6) < 0) perror("failed to write");
}

void ADCS::readAttitudeData(AttitudePacket &packet) {
    unsigned char cmd[4] = {'$', ' ', ' ', ']'};
    uint16_t cmds[16] = {MAGI_X, MAGI_Y, MAGI_Z,
                         MAGE_X, MAGE_Y, MAGE_Z,
                         IMU1_X, IMU1_Y, IMU1_Z,
                         IMU2_X, IMU2_Y, IMU2_Z,
                         FRT_WEEK_HI, FRT_WEEK_LO,
                         FRT_MILLI_HI, FRT_MILLI_LO};
    unsigned char tlm[128];
    uint16_t dh;
    uint16_t dl;
    serialFlush(fd);
    printf("sending: ");
    for (int i=0; i<16; i++) {
        cmd[1] = (unsigned char) ((cmds[i] >> 8) | 0x80);
        cmd[2] = (unsigned char) (cmds[i] & 0x00FF);
        printHex(cmd, 4);
        if (write(fd, cmd, 4) < 0) perror("failed to write");
    }
    printf("\n");
    if (read(fd, tlm, 128) < 0) perror("failed to read");
    printf("received: ");
    printHex(tlm, 128);
    printf("\n");
    packet.magi_x = *((int16_t*) tlm+5);
    packet.magi_y = *((int16_t*) tlm+13);
    packet.magi_z = *((int16_t*) tlm+21);
    packet.mage_x = *((int16_t*) tlm+29);
    packet.mage_y = *((int16_t*) tlm+37);
    packet.mage_z = *((int16_t*) tlm+45);
    packet.imu1_x = *((int16_t*) tlm+53);
    packet.imu1_y = *((int16_t*) tlm+61);
    packet.imu1_z = *((int16_t*) tlm+69);
    packet.imu2_x = *((int16_t*) tlm+77);
    packet.imu2_y = *((int16_t*) tlm+85);
    packet.imu2_z = *((int16_t*) tlm+93);
    dh = *((uint16_t*) tlm+101);
    dl = *((uint16_t*) tlm+109);
    packet.time_frt_week = (dh << 8) | dl;
    dh = *((uint16_t*) tlm+117);
    dl = *((uint16_t*) tlm+125);
    packet.time_frt_milli = (dh << 8) | dl;
}

void ADCS::printHex(unsigned char* data, int size) {
    for (int i=0; i<size; i++) {
        if (data[i] < 0x10) printf("0");
        printf("%x ", data[i]);
    }
}
