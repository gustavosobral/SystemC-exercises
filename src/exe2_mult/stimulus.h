#include "systemc.h"

#include <stdlib.h>
#include <time.h>

SC_MODULE(stimulus) {
  sc_out<sc_uint<64> > A, B;
  sc_in<bool> Clk;

  void stim_gen() {
    int i;
    for(i = 0; i < 32; i++) {
      A.write(rand() % 99 + 1); B.write(rand() % 99 + 1); wait();
    }
    sc_stop();
  }

  SC_CTOR(stimulus) {
    srand (time(NULL));

    SC_THREAD(stim_gen);
    sensitive << Clk.pos();
  }
};
