#include "systemc.h"

SC_MODULE(mult64) {
  sc_in<sc_uint<64> > A, B;
  sc_out<sc_uint<64> > F;

  void do_mult() {
    F.write(A.read() * B.read());
  }

  SC_CTOR(mult64) {
    SC_METHOD(do_mult);
    sensitive << A << B;
  }
};
