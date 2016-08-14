#include "systemc.h"

SC_MODULE(addr1) {
  sc_in<bool> A, B, Cin;
  sc_out<bool> F, Cout;

  void do_addr() {
    F.write(
      ((!A.read()) && (!B.read()) && (Cin.read())) ||
      ((!A.read()) && (B.read()) && (!Cin.read())) ||
      ((A.read()) && (!B.read()) && (!Cin.read())) ||
      ((A.read()) && (B.read()) && (Cin.read()))
     );
    Cout.write(
      ((!A.read()) && (B.read()) && (Cin.read())) ||
      ((A.read()) && (!B.read()) && (Cin.read())) ||
      ((A.read()) && (B.read()) && (!Cin.read())) ||
      ((A.read()) && (B.read()) && (Cin.read()))
    );
  }

  SC_CTOR(addr1) {
    SC_METHOD(do_addr);
    sensitive << A << B << Cin;
  }
};
