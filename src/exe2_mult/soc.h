#include "systemc.h"
#include "addr64.h"
#include "mult64.h"

SC_MODULE(soc) {
  sc_in<sc_uint<64> > A, B;
  sc_out<sc_uint<64> > F;
  addr64 add1;
  mult64 mult1;
  sc_signal<sc_uint<64> > S;

  SC_CTOR(soc): add1("ADDR"), mult1("MULT") {
    add1.A(A); add1.B(B); add1.F(S);
    mult1.A(S); mult1.B(B); mult1.F(F);
  }
};
