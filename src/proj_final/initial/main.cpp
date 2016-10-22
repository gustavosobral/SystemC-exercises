#include "systemc.h"
#include "monitor.h"
#include "stim.h"
#include "filter.h"

int sc_main(int argc, char* argv[]) {
  sc_signal<sc_uint<8> > A1Sig, A2Sig, A3Sig, A4Sig, A5Sig, A6Sig, A7Sig, A8Sig, A9Sig, FSig;
  sc_clock TestClk("TestClock", 10, SC_NS, 0.5);

  stim Stim("Stim");
  Stim.A1(A1Sig); Stim.A2(A2Sig); Stim.A3(A3Sig); Stim.A4(A4Sig); Stim.A5(A5Sig);
  Stim.A6(A6Sig); Stim.A7(A7Sig); Stim.A8(A8Sig); Stim.A9(A9Sig);
  Stim.Clk(TestClk);

  _filter DUT("DUT");
  DUT.A1(A1Sig); DUT.A2(A2Sig); DUT.A3(A3Sig); DUT.A4(A4Sig); DUT.A5(A5Sig);
  DUT.A6(A6Sig); DUT.A7(A7Sig); DUT.A8(A8Sig); DUT.A9(A9Sig);
  DUT.F(FSig);

  monitor Monitor("Monitor");
  Monitor.A1(A1Sig); Monitor.A2(A2Sig); Monitor.A3(A3Sig); Monitor.A4(A4Sig); Monitor.A5(A5Sig);
  Monitor.A6(A6Sig); Monitor.A7(A7Sig); Monitor.A8(A8Sig); Monitor.A9(A9Sig);
  Monitor.F(FSig);
  Monitor.Clk(TestClk);

  sc_start();

  return 0;
}
