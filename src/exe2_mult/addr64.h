#include "systemc.h"

SC_MODULE(addr64) {
  sc_in<sc_uint<64> > A, B;
  sc_out<sc_uint<64> > F;

  void do_addr() {
    F.write(A.read() + B.read());
  }

  SC_CTOR(addr64) {
    SC_METHOD(do_addr);
    sensitive << A << B;
  }
};
