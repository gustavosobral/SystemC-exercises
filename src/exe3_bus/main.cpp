#include "systemc.h"

#include "master.cpp"

int sc_main(int argc, char* argv[]) {
  sc_clock TestClk("TestClock", 500000, SC_NS, 0.5);
  master Master("Master");

  sc_start();
  return 0;
}
