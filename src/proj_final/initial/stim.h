#include "systemc.h"
#include <stdlib.h>
#include <time.h>

SC_MODULE(stim) {
  sc_in<bool> Clk;
  sc_out<sc_uint<8> > A1, A2, A3, A4, A5, A6, A7, A8, A9;

  void StimGen() {

    wait();

    A1.write(1); A2.write(2); A3.write(1); A4.write(2); A5.write(1); A6.write(2);
    A7.write(1); A8.write(2); A9.write(1); wait();

    A1.write(10); A2.write(2); A3.write(1); A4.write(2); A5.write(1); A6.write(2);
    A7.write(1); A8.write(2); A9.write(1); wait();

    A1.write(10); A2.write(25); A3.write(30); A4.write(42); A5.write(57); A6.write(69);
    A7.write(210); A8.write(168); A9.write(100); wait();

    sc_stop();
  }

  SC_CTOR(stim) {
    srand (time(NULL));

    SC_THREAD(StimGen);
    sensitive << Clk.pos();
  }
};
