#include "adcs/adcs.h"
#include "cosmos/cosmosQueue.h"
#include <sys/time.h>
#include <sstream>
#include <wiringPi.h>

CosmosQueue queue(4811, 256);

PI_THREAD (cosmosQueue) {
    while (true) {
        queue.connect();
        while (queue.isConnected()) {
            while (queue.pop());
            usleep(10000);
        }
        printf("connection with COSMOS lost\n");
    }
}

int main() {
    // launch cosmosQueue thread
    if (piThreadCreate(cosmosQueue) != 0) {
        perror("COSMOS queue thread didn't start");
    }
    // set high priority for this thread
    pid_t pid = getpid();
    std::stringstream cmd;
    cmd << "renice -n -2 -p " << pid;
    if (pid > 0)
        system(cmd.str().c_str());

    // initialize ADCS and packet
    ADCS adcs("/dev/ttyS0", 115200);
    AttitudePacket* aPacket;
    struct timeval start, end;
    long difference, timer = 0;
    while (true) {
        do {
            usleep(500);
            gettimeofday(&start, NULL);
        } while (start.tv_usec > 5000);
        timer = 0;
        for (int i=0; i<50; i++) {
            aPacket = new AttitudePacket;
            do {
                usleep(500);
                gettimeofday(&end, NULL);
                difference = (end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec);
            } while (difference < timer);
            //printf("started packet at %li\n", end.tv_usec);
            adcs.readAttitudeData(*aPacket);
            queue.push(aPacket);
            timer += 20000;
        }
    }
    return 0;
}
