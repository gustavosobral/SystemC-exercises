#ifndef __mem_swap_h
#define __mem_swap_h

#include "systemc.h"

#include "simple_bus/simple_bus_master_blocking_mod.h"
#include "simple_bus/simple_bus_slow_mem.h"
#include "simple_bus/simple_bus.h"
#include "simple_bus/simple_bus_arbiter.h"

SC_MODULE(mem_swap)
{
  // channels
  sc_clock C1;

  // module instances
  simple_bus_master_blocking     *master_b;
  simple_bus_slow_mem            *mem_slow_init, *mem_slow_final;
  simple_bus                     *bus;
  simple_bus_arbiter             *arbiter;

  // constructor
  SC_CTOR(mem_swap)
    : C1("C1")
  {
    int width = 4;
    int height = 4;
    unsigned int initial_address_1 = 0x00;
    unsigned int final_address_1;
    unsigned int initial_address_2;
    unsigned int final_address_2;

    final_address_1 = (initial_address_1 + (width*height + width*2 + height*2 + 4)*0x04) - 1;
    initial_address_2 = final_address_1 + 1;
    final_address_2 = (initial_address_2 + width*height*0x04) - 1;

    // create instances
    bus = new simple_bus("bus");
    arbiter = new simple_bus_arbiter("arbiter");
    master_b = new simple_bus_master_blocking("master_b", 4, false, 3, width*height,
                                               0x04, initial_address_1, initial_address_2, width, height);
    mem_slow_init = new simple_bus_slow_mem("mem_slow_init", initial_address_1, final_address_1, 1);
    mem_slow_final = new simple_bus_slow_mem("mem_slow_final", initial_address_2, final_address_2, 1);

    int i, j, data;
    unsigned int addr = initial_address_1;
    for (i = 0; i < height+1; i++) {
      if(i == 0 || i == height) {
        data = 0;
        mem_slow_init->direct_write(&data, addr);
        addr += 4;
      } else {
        for (j = 0; j < width+1; j++) {
          if(i == 0 || i == height) {
            data = 0;                    
          } else {
            data = rand() % 256;
          }
          mem_slow_init->direct_write(&data, addr);    
          addr += 4;
        }
      }      
    }

    // connect instances
    bus->clock(C1);
    master_b->clock(C1);
    mem_slow_init->clock(C1);
    mem_slow_final->clock(C1);
    master_b->bus_port(*bus);
    bus->arbiter_port(*arbiter);
    bus->slave_port(*mem_slow_init);
    bus->slave_port(*mem_slow_final);
  }

  // destructor
  ~mem_swap()
  {
    if (master_b) {delete master_b; master_b = 0;}
    if (mem_slow_final) {delete mem_slow_final; mem_slow_final = 0;}
    if (mem_slow_init) {delete mem_slow_init; mem_slow_final = 0;}
    if (bus) {delete bus; bus = 0;}
    if (arbiter) {delete arbiter; arbiter = 0;}
  }

}; // end class mem_swap

#endif
