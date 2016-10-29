#define SC_INCLUDE_FX

#include "systemc.h"

SC_MODULE(filter) {
  sc_in<sc_uint<8> > A1, A2, A3, A4, A5, A6, A7, A8, A9;
  sc_in<bool> reset_n;    // Rest enable at negative edge
  sc_in<bool> in_data_en; // Flag to say that in_data_a and in_data_b is valid

  sc_out<sc_uint<8> > F;
  sc_out<bool> out_data_rdy; //Flag to say that the out_data is valid

  void do_filter() {
    int iA1, iA2, iA3, iA4, iA5, iA6, iA7, iA8, iA9, iF;

    if (reset_n.read() == false) {
      out_data_rdy.write(0);
    }
    else if (in_data_en.read() == 1) {
      iA1 = A1.read();
      iA2 = A2.read();
      iA3 = A3.read();
      iA4 = A4.read();
      iA5 = A5.read();
      iA6 = A6.read();
      iA7 = A7.read();
      iA8 = A8.read();
      iA9 = A9.read();

      iF = (iA1 + iA2 + iA3 + iA4 + iA5 + iA6 + iA7 + iA8 + iA9) / 9;

      F.write(iF);
      out_data_rdy.write(1);
    }
  }

  SC_CTOR(filter) {
    SC_METHOD(do_filter);
    sensitive << reset_n << in_data_en;
  }
};
