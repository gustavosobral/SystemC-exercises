#include "systemc.h"
#include "stimulus.h"
#include "exor2.h"
#include "monitor.h"

int sc_main(int argc, char* argv[]) {
  sc_signal<bool> ASig, BSig, FSig;
  sc_clock TestClk("TestClock", 10, SC_NS, 0.5);

  stimulus Stim("Stimulus");
  Stim.A(ASig); Stim.B(BSig); Stim.Clk(TestClk);

  exor2 DUT("exor2");
  DUT.A(ASig); DUT.B(BSig); DUT.F(FSig);
  
  monitor Monitor("Monitor");
  Monitor.A(ASig); Monitor.B(BSig); Monitor.F(FSig); Monitor.Clk(TestClk);

  // System trace
  sc_trace_file* Tf;
  Tf = sc_create_vcd_trace_file("traces");
  Tf->set_time_unit(10, SC_NS);
  sc_trace(Tf, ASig, "A");
  sc_trace(Tf, BSig, "B");
  sc_trace(Tf, FSig, "F");
  sc_trace(Tf, DUT.S1, "S1");
  sc_trace(Tf, DUT.S2, "S2");
  sc_trace(Tf, DUT.S3, "S3");

  sc_start();
  sc_close_vcd_trace_file(Tf);
  return 0;
}
