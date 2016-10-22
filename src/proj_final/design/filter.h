#define SC_INCLUDE_FX

#include "systemc.h"

SC_MODULE(filter)
{
  sc_in<sc_uint<8> > A1, A2, A3, A4, A5, A6, A7, A8, A9;
  sc_in<bool> clock;
  sc_in<bool> reset_n;    // Rest enable at negative edge
  sc_in<bool> in_data_en; // Flag to say that in_data_a and in_data_b is valid

  sc_out<sc_uint<8> > F;
  sc_out<bool> out_data_rdy; //Flag to say that the out_data is valid

  void func();

  filter(sc_module_name nm);
};
