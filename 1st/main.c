#include <stdio.h>
#include "simulator.h"
#include "exec.h"

int main(int argc, char const *argv[]) {
  simulator sim;
  init(&sim, argc, argv);
  sim.exec = exec;
  sim.run(&sim);
  return 0;
}
