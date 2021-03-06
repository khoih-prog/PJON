
// For printf used below
#include <cstdio>
// PJON library
#include <cinttypes>
#include <cstdlib>
#include <cstring>
// RPI serial interface
#include <wiringPi.h>
#include <wiringSerial.h>

#ifndef RPI
  #define RPI true
#endif

#define TS_RESPONSE_TIME_OUT 35000
/* Maximum accepted duration between transmission and acknowledgement.
   May be necessary to set a higher value if devices are separated by a long
   physical distance and or if long packets are transmitted. */


#define PJON_INCLUDE_TS true // Include only ThroughSerial
#include <PJON.h>

int main() {
  printf("PJON instantiation... \n");
  PJON<ThroughSerial> bus(45);
  uint32_t baud_rate = 9600;
  printf("Opening serial... \n");
  int s = serialOpen("/dev/ttyAMA0", baud_rate);
  if(int(s) < 0) printf("Serial open fail!");
  if(wiringPiSetup() == -1) printf("WiringPi setup fail");
  printf("Setting serial... \n");
  bus.strategy.set_serial(s);
  bus.strategy.set_baud_rate(baud_rate);

  printf("Opening bus... \n");
  bus.begin();
  printf("Attempting to send a packet... \n");
  bus.send(44, "B", 1);
  printf("Attempting to roll bus... \n");
  bus.update();
  printf("Attempting to receive from bus... \n");
  bus.receive();
  printf("Success! \n");

  while(true) {
    bus.update();
    bus.receive();
  }

  return 0;
};
