#ifndef _MON_H_
#define _MON_H_

//-----------------------------
// SystemC defines and includes
//-----------------------------
#include "systemc.h"
#include <string>
#include "tlm.h"

using namespace std;
using namespace tlm;

#include "filter_interface.h"
#include "filter_define.h"

//-----------------------------
// Constants
//-----------------------------


SC_MODULE(filter_monitor)
{
  //-----------------------------
  // Input
  //-----------------------------
  sc_in<bool> clk;
  sc_in<bool> async_reset;

  filter_interface* filter_if;
  filter_sequence_item* filter_sqi;
  filter_sequence_item* filter_sqi_clone;

  int monitor_errors;
  string fname_data_out;
  ofstream file_data_out;

  //-----------------------------
  // TLM Analysis Port
  //-----------------------------
  tlm_analysis_port<filter_sequence_item> mon_port;

  //-----------------------------
  // Process Declaration
  //-----------------------------
  void capture_signals();
  void copy_if_sqi();

  //-----------------------------
  // Constructor
  //-----------------------------
  SC_HAS_PROCESS(filter_monitor);
  filter_monitor(sc_module_name name, filter_interface * sc_if) : sc_module(name)
  {

    INFO(this->name(), "construtor");
    const char *c = name;
    string n(c);
    monitor_errors = 0;
    fname_data_out = result_path + n + "_output.txt";
    file_data_out.open (fname_data_out.c_str(), ofstream::out);

    filter_sqi = new filter_sequence_item("filter_sqi");
    filter_sqi_clone = new filter_sequence_item("filter_sqi_clone"); //Necessary to avoid overwrite

    filter_if = sc_if;
    //----------------------------
    // Process registration
    //----------------------------

    SC_THREAD(capture_signals);
    sensitive <<  async_reset.neg() << clk.pos();
  }
};

//+--------------------------------------------------------------------------
//| FUNCTION: capture_signals
//+--------------------------------------------------------------------------
//! Check if reset happens, copy the DUT interface to a sequence item and
//! write it in the TLM port.
//+--------------------------------------------------------------------------
void filter_monitor::capture_signals() {
  stringstream msg;
  while (true) {
    if (!async_reset.read()) {
      wait(1, ASYNC_RST_TIMEUNIT);
    }
    filter_monitor::copy_if_sqi();
    filter_sqi_clone = filter_sqi;
    mon_port.write(*filter_sqi_clone);
    wait(1);
  }
}

//+--------------------------------------------------------------------------
//| FUNCTION: copy_if_sqi
//+--------------------------------------------------------------------------
//! Copy interface signals to sequence item
//+--------------------------------------------------------------------------
void filter_monitor::copy_if_sqi() {
  filter_sqi->data_valid  = filter_if->out_data_rdy.read();
  filter_sqi->F    = filter_if->F.read();

  //save output data
  file_data_out << filter_if->out_data_rdy << " " << filter_if->F << " " << endl;
}

#endif
