#include "systemc.h"
#include <iomanip>

using namespace std;

SC_MODULE(monitor) {
  sc_in<sc_uint<8> > A1, A2, A3, A4, A5, A6, A7, A8, A9, F;
  sc_in<bool> Clk;

  void monitor_display() {
    cout << setw(10) << "Time";
    cout << setw(10) << "A1";
    cout << setw(10) << "A2";
    cout << setw(10) << "A3";
    cout << setw(10) << "A4";
    cout << setw(10) << "A5";
    cout << setw(10) << "A6";
    cout << setw(10) << "A7";
    cout << setw(10) << "A8";
    cout << setw(10) << "A9 |";
    cout << setw(9) << "Mean" << endl;

    while (true) {
      cout << setw(10) << sc_time_stamp();
      cout << setw(10) << A1.read();
      cout << setw(10) << A2.read();
      cout << setw(10) << A2.read();
      cout << setw(10) << A4.read();
      cout << setw(10) << A5.read();
      cout << setw(10) << A6.read();
      cout << setw(10) << A7.read();
      cout << setw(10) << A8.read();
      cout << setw(8) << A9.read() << " |";
      cout << setw(9) << F.read() << endl;
      wait();
    }
  }

  SC_CTOR(monitor) {
    SC_THREAD(monitor_display);
    sensitive << Clk.pos();
  }
};
