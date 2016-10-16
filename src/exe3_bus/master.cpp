#include "systemc.h"

#include "simple_bus/simple_bus.h"
#include "simple_bus/simple_bus_arbiter.h"
#include "simple_bus/simple_bus_slow_mem.h"
#include "simple_bus/simple_bus_master_blocking.h"

SC_MODULE(master) {

  sc_clock Clk;

  // module instances
  simple_bus                     *bus;
  simple_bus_arbiter             *arbiter;
  simple_bus_slow_mem            *mem_slow1, *mem_slow2;
  simple_bus_master_blocking     *master_b;  

  SC_CTOR(master):Clk("Clk") {
    // create instances
    bus = new simple_bus("bus");
    arbiter = new simple_bus_arbiter("arbiter");
    mem_slow1 = new simple_bus_slow_mem("mem_slow1", 0x00, 0xF9F, 1);
    mem_slow2 = new simple_bus_slow_mem("mem_slow2", 0xFA0, 0x1F3F, 1);
    master_b = new simple_bus_master_blocking("master_b", 1, 0x4c, false, 300);

    // populate slow memory 1
    int i, data;
    unsigned int address = 0x00;
    for(i = 0; i < 1000; i++) {
      data = i*i;
      mem_slow1->direct_write(&data, address);
      address += 4;
    }

    // connect instances
    bus->clock(Clk);
    master_b->clock(Clk);
    mem_slow1->clock(Clk);
    mem_slow2->clock(Clk);
    master_b->bus_port(*bus);
    bus->arbiter_port(*arbiter);
    bus->slave_port(*mem_slow1);
    bus->slave_port(*mem_slow2);
  }

  // destructor
  ~master() {
    if (bus) {delete bus; bus = 0;}
    if (arbiter) {delete arbiter; arbiter = 0;}
    if (mem_slow1) {delete mem_slow1; mem_slow1 = 0;}
    if (mem_slow2) {delete mem_slow2; mem_slow2 = 0;}
    if (master_b) {delete master_b; master_b = 0;}
  }
};
