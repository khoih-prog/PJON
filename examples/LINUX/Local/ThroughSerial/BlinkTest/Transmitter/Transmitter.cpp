
// For printf used below
#include <stdio.h>
// PJON library
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#define PJON_INCLUDE_TS // Include only ThroughSerial
#include <PJON.h>

int main() {
  printf("PJON instantiation... \n");
  PJON<ThroughSerial> bus(45);
  uint32_t baud_rate = 9600;
  printf("Opening serial... \n");

  // The name of the serial port may need to be edited
  int s = serialOpen("/dev/ttyUSB0", baud_rate);

  if(int(s) < 0) printf("Serial open fail!");
  printf("Setting serial... \n");
  bus.strategy.set_serial(s);
  bus.strategy.set_baud_rate(baud_rate);

  printf("Opening bus... \n");
  bus.begin();
  printf("Attempting to send a B every second... \n");
  bus.send_repeatedly(44, "B", 1, 1000000);
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
