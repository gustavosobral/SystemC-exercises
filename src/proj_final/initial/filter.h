#include "systemc.h"

SC_MODULE(_filter) {
  sc_in<sc_uint<8> > A1, A2, A3, A4, A5, A6, A7, A8, A9;
  sc_out<sc_uint<8> > F;

  void do_filter() {
    F.write( (A1.read() + A2.read() + A3.read() + A4.read() + A5.read() +
              A6.read() + A7.read() + A8.read() + A9.read()) / 9 );
  }

  SC_CTOR(_filter) {
    SC_METHOD(do_filter);
    sensitive << A1 << A2 << A3 << A4 << A5 << A6 << A7 << A8 << A9;
  }
};
