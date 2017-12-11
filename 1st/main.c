#include <stdio.h>
#include "simulator.h"

int main(int argc, char const *argv[]) {
  simulator sim;
  init(&sim, argc, argv);
  sim.run(&sim);
  return 0;
}
