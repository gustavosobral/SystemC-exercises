#include "systemc.h"

SC_MODULE(stimulus) {
  sc_out<sc_uint<64> > A, B;
  sc_in<bool> Clk;

  void stim_gen() {
    A.write(0); B.write(0); wait();
    A.write(84); B.write(10); wait();
    A.write(6); B.write(10); wait();
    A.write(23); B.write(45); wait();
    sc_stop();
  }

  SC_CTOR(stimulus) {
    SC_THREAD(stim_gen);
    sensitive << Clk.pos();
  }
};
