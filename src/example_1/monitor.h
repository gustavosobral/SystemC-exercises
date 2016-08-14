#include "systemc.h"
#include <iomanip>

using namespace std;

SC_MODULE(monitor) {
  sc_in<bool> A, B, F;
  sc_in<bool> Clk;

  void monitor_loop() {
    cout << setw(10) << "Time";
    cout << setw(2) << "A";
    cout << setw(2) << "B";
    cout << setw(2) << "F" << endl;
    while(true) {
      cout << setw(10) << sc_time_stamp();
      cout << setw(2) << A.read();
      cout << setw(2) << B.read();
      cout << setw(2) << F.read() << endl;
      wait();
    }
  }

  SC_CTOR(monitor) {
    SC_THREAD(monitor_loop);
    sensitive << Clk.pos();
  }
};
