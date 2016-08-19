#include "systemc.h"
#include "stimulus.h"
#include "soc.h"
#include "monitor.h"

int sc_main(int argc, char* argv[]) {
  sc_signal<sc_uint<64> > ASig, BSig, FSig;
  sc_clock TestClk("TestClock", 10, SC_NS, 0.5);

  stimulus Stim("Stimulus");
  Stim.A(ASig); Stim.B(BSig); Stim.Clk(TestClk);

  soc DUT("DUT");
  DUT.A(ASig); DUT.B(BSig); DUT.F(FSig);

  monitor Monitor("Monitor");
  Monitor.A(ASig); Monitor.B(BSig); Monitor.F(FSig); Monitor.Clk(TestClk);

  sc_start();
  return 0;
}
