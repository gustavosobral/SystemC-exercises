#include "systemc.h"
#include "stimulus.h"
#include "addr2.h"
#include "monitor.h"

int sc_main(int argc, char* argv[]) {
  sc_signal<bool> A1Sig, A2Sig, B1Sig, B2Sig, F1Sig, F2Sig, CinSig, CoutSig;
  sc_clock TestClk("TestClock", 10, SC_NS, 0.5);

  stimulus Stim("Stimulus");
  Stim.A1(A1Sig); Stim.A2(A2Sig); Stim.B1(B1Sig); Stim.B2(B2Sig); Stim.Cin(CinSig); Stim.Clk(TestClk);

  addr2 DUT("DUT");
  DUT.A1(A1Sig); DUT.A2(A2Sig); DUT.B1(B1Sig); DUT.B2(B2Sig);
  DUT.F1(F1Sig); DUT.F2(F2Sig); DUT.Cin(CinSig); DUT.Cout(CoutSig);

  monitor Monitor("Monitor");
  Monitor.A1(A1Sig); Monitor.A2(A2Sig); Monitor.B1(B1Sig); Monitor.B2(B2Sig);
  Monitor.F1(F1Sig); Monitor.F2(F2Sig); Monitor.Cin(CinSig); Monitor.Cout(CoutSig);
  Monitor.Clk(TestClk);

  sc_start();
  return 0;
}
