#include "systemc.h"
#include <bitset>

SC_MODULE(stimulus) {
  sc_out<bool> A1, A2, B1, B2, Cin;
  sc_in<bool> Clk;

  void stim_gen() {
    int i;
    for(i = 0; i < 32; i++) {
      std::bitset<5> stim(i);
      Cin.write(stim[0]); B1.write(stim[1]); A1.write(stim[2]); B2.write(stim[3]); A2.write(stim[4]); wait();
    }
    sc_stop();
  }

  SC_CTOR(stimulus) {
    SC_THREAD(stim_gen);
    sensitive << Clk.pos();
  }
};
