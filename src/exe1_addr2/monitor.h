#include "systemc.h"
#include <iomanip>

using namespace std;

SC_MODULE(monitor) {
  sc_in<bool> A1, A2, B1, B2, F1, F2, Cin, Cout;
  sc_in<bool> Clk;

  void monitor_loop() {
    cout << setw(10) << "Time";
    cout << setw(3) << "A2";
    cout << setw(3) << "B2";    
    cout << setw(3) << "A1";
    cout << setw(3) << "B1";
    cout << setw(6) << "Cin| ";   
    cout << setw(4) << "Cout";
    cout << setw(3) << "F2";
    cout << setw(3) << "F1" << endl;
    while(true) {
      cout << setw(10) << sc_time_stamp();
      cout << setw(3) << A2.read();
      cout << setw(3) << B2.read();
      cout << setw(3) << A1.read();
      cout << setw(3) << B1.read();
      cout << setw(3) << Cin.read() << " | ";
      cout << setw(3) << Cout.read();
      cout << setw(3) << F2.read();
      cout << setw(3) << F1.read() << endl;
      wait();
    }
  }

  SC_CTOR(monitor) {
    SC_THREAD(monitor_loop);
    sensitive << Clk.pos();
  }
};
