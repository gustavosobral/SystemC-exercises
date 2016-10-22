#ifndef _CHK_H_
#define _CHK_H_

#include <systemc.h>
#include <filter_interface.h>

//+--------------------------------------------------------------------------
//| SC_MODULE: filter_checker
//+--------------------------------------------------------------------------
SC_MODULE(filter_checker)
{
public:
  sc_in<bool> clk;
  sc_in<bool> clk2;
  sc_in<bool> async_reset;

  //-----------------------------
  // TLM Analysis Port
  //-----------------------------
  tlm_analysis_port<filter_sequence_item> chk_port;
  tlm_analysis_port<filter_sequence_item> chk_rm_port;
  tlm_analysis_port<filter_sequence_item> chk_drv_port;

  bool previous_reset;
  bool current_reset;
  bool reset_detected;

  int select_checker;

  filter_sequence_item filter_sqi;
  filter_sequence_item filter_drv_sqi;

  filter_subscriber*  filter_dut_sub;
  filter_subscriber*  filter_rm_sub;
  filter_subscriber*  filter_drv_sub;

  //-----------------------------
  // Process Declaration
  //-----------------------------
  void check();
  void compare_dut_refmod(filter_sequence_item item);
  void compare_reset(filter_sequence_item item);

  //+--------------------------------------------------------------------------
  //| FUNCTION: is_close_out
  //+--------------------------------------------------------------------------
  bool is_close_out(double x1, double x2,  double tol = exp2(-7)/*1e-10*/) {
    bool rv;
    rv = abs(x1 - x2) < tol;
    return rv;
  }

  //+--------------------------------------------------------------------------
  //| FUNCTION: is_close_in
  //+--------------------------------------------------------------------------
  bool is_close_in(double x1, double x2,  double tol = exp2(-7)/*1e-10*/) {
    bool rv;
    rv = abs(x1 - x2) < tol;
    return rv;
  }

  SC_HAS_PROCESS(filter_checker);
  filter_checker(sc_module_name name): sc_module(name)
  {
    INFO(this->name(), "constructor");

    filter_dut_sub = new filter_subscriber("filter_dut_sub");
    chk_port.bind(*filter_dut_sub);

    filter_rm_sub = new filter_subscriber("filter_rm_sub");
    chk_rm_port.bind(*filter_rm_sub);

    filter_drv_sub = new filter_subscriber("filter_drv_sub");
    chk_drv_port.bind(*filter_drv_sub);

    select_checker = 0;
    previous_reset = 1;
    reset_detected = 0;

    SC_THREAD(check)
    sensitive << clk.pos();
    async_reset_signal_is(async_reset, false);
  }
};

//+--------------------------------------------------------------------------
//| FUNCTION: check
//+--------------------------------------------------------------------------
//! Wait to receive a valid clock, and call the function which compare the
//! input data with the output data.
//+--------------------------------------------------------------------------
void filter_checker::check() {
  stringstream msg;


  while (true) {
    filter_sqi = filter_dut_sub->fifo.get();

    if (select_checker == 4) {
      filter_checker::compare_reset(filter_sqi);
    }

    if (filter_sqi.data_valid) {
      switch (select_checker) {
      case 1: filter_checker::compare_dut_refmod(filter_sqi);
        break;
      default: INFO(name(), "foi pro DEFAULT", MEDIUM); break;
      }
    }
    wait(1);
  }
}

//+--------------------------------------------------------------------------
//| FUNCTION: compare_reset
//+--------------------------------------------------------------------------
//! Check reset values on dut outputs
//+--------------------------------------------------------------------------
void filter_checker::compare_reset(filter_sequence_item item) {
  stringstream msg;

  INFO(name(), "Check reset is active!!!");
  if (!async_reset.read()) {

    if (item.data_valid != 0) {
      ERROR(name(), "Mismatch o_rdy is not going to zero after reset");
    }

    if (item.F != 0) {
      ERROR(name(), "Mismatch data_out is not going to zero after reset");
    }

  }
}


//+--------------------------------------------------------------------------
//| FUNCTION: compare_dut_refmod
//+--------------------------------------------------------------------------
//! Compare output values between reference model and dut
//+--------------------------------------------------------------------------
void filter_checker::compare_dut_refmod(filter_sequence_item item) {


  stringstream msg;
  bool find_valid = 0;
  filter_sequence_item filter_rm_sqi;

  while (!find_valid) {
    //INFO(name(), "procurando item valido", MEDIUM);

    filter_rm_sqi = filter_rm_sub->fifo.get();
    if (filter_rm_sqi.data_valid) {
      find_valid = 1;
    }
  }
  find_valid = 0;
  // int *a;
  // a = item.sel;

  // INFO(name(), "nO compare_dut_refmod", MEDIUM);

  if (filter_rm_sqi.F != item.F) {
    msg << "MISMATCH between DUT and Reference Model: data_valid(DUT) = " << item.F << " - data_valid(RM) = "
        << filter_rm_sqi.F;
    ERROR(name(), msg.str().c_str());
    msg.str(""); //clean
  }

  else {
    //INFO(name(), "nO ELSE compare_dut_refmod", MEDIUM);
    msg << "MATCH between DUT and Reference Model: data_valid(DUT) = " << item.F << " - data_valid(RM) = "
        << filter_rm_sqi.F;
    INFO(name(), msg.str().c_str(), HIGH);
    //INFO(name(), msg.str().c_str(), MEDIUM);
    msg.str(""); //clean
  }

}

#endif /* VIP_SC_CHK_H_ */
