#include "systemc.h"
#include <iomanip>

using namespace std;

SC_MODULE(monitor) {
  sc_in<sc_uint<64> > A, B, F;
  sc_in<bool> Clk;

  void monitor_loop() {
    cout << setw(10) << "Time";
    cout << setw(6) << "A";
    cout << setw(8) << "B |";
    cout << setw(8) << "B*(A+B)" << endl;
    while(true) {
      cout << setw(10) << sc_time_stamp();
      cout << setw(6) << A.read();
      cout << setw(6) << B.read() << " |";
      cout << setw(6) << F.read() << endl;
      wait();
    }
  }

  SC_CTOR(monitor) {
    SC_THREAD(monitor_loop);
    sensitive << Clk.pos();
  }
};
