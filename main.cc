#include <unistd.h>

#include <iostream>

#include "transport/shm/xsi_segment.h"

int main() {
  cyber_k::transport::XsiSegment test(10);
  sleep(10);
  printf("test zmk\n");
}