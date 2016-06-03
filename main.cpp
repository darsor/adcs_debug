#include "adcs.h"

int main() {
    ADCS adcs("/dev/ttyS0", 115200);
    adcs.readReg(MAGI_Z);
    adcs.readReg(FRT_WEEK_LO);
    return 0;
}
