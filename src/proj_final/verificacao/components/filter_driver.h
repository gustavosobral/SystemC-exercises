#ifndef _DRV_H_
#define _DRV_H_

//-----------------------------
// SystemC defines and includes
//-----------------------------
#include "systemc.h"
#include "tlm.h"
using namespace std;
using namespace tlm;

#include <filter_interface.h>
#include <filter_rst_interface.h>
#include <filter_sequence_item.h>

SC_MODULE(filter_driver)
{

  //-----------------------------
  // Input
  //-----------------------------
  sc_in<bool> clk;
  sc_in<bool> async_reset;

  filter_interface* drv_if;

  //Sequence item
  filter_sequence_item* filter_sqi;

  int driver_errors;

  string fname_h;
  ofstream file_h;

  bool update_interface;

  //-----------------------------
  // TLM Analysis Port
  //-----------------------------
  tlm_analysis_port<filter_sequence_item> drv_port;

  //-----------------------------
  // Process Declaration
  //-----------------------------
  void drive();
  void set_seed(int new_seed);
  //void set_data(double , double);
  // void set_sel(int);
  void randomize();

  SC_HAS_PROCESS(filter_driver);
  filter_driver(sc_module_name name, filter_interface * in_if)
    : sc_module(name), clk("clk"), async_reset("async_reset")
  {
    INFO(this->name(), "construtor");

    driver_errors = 0;
    update_interface = 0;
    fname_h = result_path + "filter_input.txt";
    file_h.open (fname_h.c_str(), ofstream::out);

    filter_sqi = new filter_sequence_item("filter_sqi");

    drv_if = in_if;

    srand(0);
    //----------------------------
    // Process registration
    //----------------------------
    SC_CTHREAD(drive, clk.pos());
    async_reset_signal_is(async_reset, false);

  }

};

//+--------------------------------------------------------------------------
//| FUNCTION: set_seed
//+--------------------------------------------------------------------------
//! This function randomize with
//! the seed that is put by prompt
//+--------------------------------------------------------------------------
void filter_driver::set_seed(int new_seed)
{
  srand(new_seed);
  update_interface = 1;
}

//+--------------------------------------------------------------------------
//| FUNCTION: drive
//+--------------------------------------------------------------------------
//! Get the data from the sequece item and drive in the DUT. Put the sequence
//! item used to a TLM port to be used in the bypass mode checker.
//+--------------------------------------------------------------------------
void filter_driver::drive()
{
  stringstream msg;
  bool current_reset;

  while (true) {
    current_reset = async_reset.read();
    if (current_reset == 0) {
      drv_if->in_data_en.write(0);
      drv_if->A1.write(0);
      drv_if->A2.write(0);
      drv_if->A3.write(0);
      drv_if->A4.write(0);
      drv_if->A5.write(0);
      drv_if->A6.write(0);
      drv_if->A7.write(0);
      drv_if->A8.write(0);
      drv_if->A9.write(0);

    }
    else if (update_interface == 1) {
      //Drive into drive's interface
      drv_if->in_data_en.write(filter_sqi->data_enable);

      drv_if->A1.write(filter_sqi->A1);
      drv_if->A2.write(filter_sqi->A2);
      drv_if->A3.write(filter_sqi->A3);
      drv_if->A4.write(filter_sqi->A4);
      drv_if->A5.write(filter_sqi->A5);
      drv_if->A6.write(filter_sqi->A6);
      drv_if->A7.write(filter_sqi->A7);
      drv_if->A8.write(filter_sqi->A8);
      drv_if->A9.write(filter_sqi->A9);

      //save drive at each clock
      file_h << drv_if->in_data_en << " " <<  drv_if->A1 << " " << drv_if->A2 << " " << drv_if->A3 << " "
             << drv_if->A4 << " " << drv_if->A5 << " " << drv_if->A6 << " " << drv_if->A7 << " " << drv_if->A8 << " "
             << drv_if->A9 << " " << endl;

      //send the data to checker
      drv_port.write(*filter_sqi);
      update_interface = 0;
    }
    wait(1);
  }
}


#endif
