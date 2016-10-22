#include <systemc.h>
#include <assert.h>
#include <filter_driver.h>
#include <filter_sequence_item.h>


//+--------------------------------------------------------------------------
//| FUNCTION: randomize
//+--------------------------------------------------------------------------
//! Generate a randomize data
//+--------------------------------------------------------------------------
void filter_driver::randomize()
{
  stringstream msg;
  filter_sqi->data_enable = 1;
  filter_sqi->A1 = rand() % 256;
  filter_sqi->A2 = rand() % 256;
  filter_sqi->A3 = rand() % 256;
  filter_sqi->A4 = rand() % 256;
  filter_sqi->A5 = rand() % 256;
  filter_sqi->A6 = rand() % 256;
  filter_sqi->A7 = rand() % 256;
  filter_sqi->A8 = rand() % 256;
  filter_sqi->A9 = rand() % 256;

  msg << "Generate: data_a1 = " << filter_sqi->A1 << " data_a2 = " << filter_sqi->A2
      << " data_a3 = " << filter_sqi->A3 << " data_a4 = " << filter_sqi->A4
      << " data_a5 = " << filter_sqi->A5 << " data_a6 = " << filter_sqi->A6
      << " data_a7 = " << filter_sqi->A7 << " data_a8 = " << filter_sqi->A8
      << " data_a9 = " << filter_sqi->A9;
  INFO(name(), msg.str().c_str(), HIGH);
  msg.str(""); //clean

  update_interface = 1;
  wait(1);
}
