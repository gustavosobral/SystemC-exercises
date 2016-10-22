// interface definitions for VIP

#ifndef _IF_H_
#define _IF_H_

#include <systemc>

class filter_interface
{

public:

  sc_signal<bool>       in_data_en;
  sc_signal<sc_uint<8> > A1;
  sc_signal<sc_uint<8> > A2;
  sc_signal<sc_uint<8> > A3;
  sc_signal<sc_uint<8> > A4;
  sc_signal<sc_uint<8> > A5;
  sc_signal<sc_uint<8> > A6;
  sc_signal<sc_uint<8> > A7;
  sc_signal<sc_uint<8> > A8;
  sc_signal<sc_uint<8> > A9;

  sc_signal<sc_uint<8> > F;
  sc_signal<bool>      out_data_rdy;

  filter_interface() {}
  ~filter_interface() {}
};


#endif /* _IF_H_ */
