#include "systemc.h"

#include "master.cpp"

int sc_main(int argc, char* argv[]) {
  master Master("Master");

  sc_start(500000, SC_NS);
  return 0;
}
