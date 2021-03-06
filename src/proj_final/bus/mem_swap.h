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
    int width = 14;
    int height = 14;
    unsigned int address_1 = 0x00;
    unsigned int address_2 = 0xE10;
    // create instances
    bus = new simple_bus("bus");
    arbiter = new simple_bus_arbiter("arbiter");
    master_b = new simple_bus_master_blocking("master_b", 4, false, 3, width*height,
                                               0x04, address_1, address_2, width, height);
    mem_slow_init = new simple_bus_slow_mem("mem_slow_init", address_1, address_1 + width*height*0x04 - 1, 1);
    mem_slow_final = new simple_bus_slow_mem("mem_slow_final", address_2, address_2 + width*height*0x04 - 1, 1);

    int i, data;
    unsigned int addr = address_1;
    for (i = 0; i < width*height; i++) {
      data = rand() % 256;
      mem_slow_init->direct_write(&data, addr);
      addr += 4;
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
