#include "systemc.h"
#include "addr1.h"

SC_MODULE(addr2) {
  sc_in<bool> A1, A2, B1, B2, Cin;
  sc_out<bool> F1, F2, Cout;
  addr1 add1, add2;
  sc_signal<bool> S1;

  SC_CTOR(addr2): add1("ADD1"), add2("ADD2") {
    add1.A(A1); add1.B(B1); add1.Cin(Cin); add1.F(F1); add1.Cout(S1);
    add2.A(A2); add2.B(B2); add2.Cin(S1); add2.F(F2); add2.Cout(Cout);
  }
};
