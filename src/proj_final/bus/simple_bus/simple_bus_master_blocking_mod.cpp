/*****************************************************************************/

/*****************************************************************************

  simple_bus_master_blocking.cpp : The master using the blocking BUS interface.

  Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11

 *****************************************************************************/

#include "simple_bus_master_blocking_mod.h"

//#include "../design/filter.h"
//#include <filter.h>

void simple_bus_master_blocking::main_action()
{
  const int num_items = 1000;
  const unsigned int mylength = 0x04; // storage capacity/burst length in words
  unsigned int shift = 0;
  int mydata;
  int iter = 0;
  unsigned int addr_init_mem_1 = 0x00;
  unsigned int addr_init_mem_2 = 0x1388;
  simple_bus_status status;


  filter_if->A1.write(1);
  filter_if->A2.write(1);
  filter_if->A3.write(1);
  filter_if->A4.write(1);
  filter_if->A5.write(1);
  filter_if->A6.write(1);
  filter_if->A7.write(1);
  filter_if->A8.write(1);
  filter_if->A9.write(20);
  filter_if->in_data_en.write(1);

  int iF = filter_if->F.read();

  while (filter_if->out_data_rdy != 1) continue;
  sb_fprintf(stdout, "\nF: %d", iF);


  sb_fprintf(stdout, "\nInitial state of Slow Memory 1:\n");

  while (addr_init_mem_1 + shift != 0x28) {

    /* Slow Memory 2: initially empty */
    status = bus_port->burst_read(m_unique_priority, &mydata, addr_init_mem_1 + shift, 1, m_lock);
    if (status == SIMPLE_BUS_ERROR) sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
          sc_time_stamp().to_string().c_str(), name(), addr_init_mem_1 + shift);
    else sb_fprintf(stdout, "(%x) | ",
                      mydata);

    shift += mylength;

  }

  sb_fprintf(stdout, "... \n");
  shift = 0;

  sb_fprintf(stdout, "Initial state of Slow Memory 2:\n");

  while (addr_init_mem_2 + shift != 0x13B0) {

    /* Slow Memory 2: initially empty */
    status = bus_port->burst_read(m_unique_priority, &mydata, addr_init_mem_2 + shift, 1, m_lock);
    if (status == SIMPLE_BUS_ERROR) sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
          sc_time_stamp().to_string().c_str(), name(), addr_init_mem_2 + shift);
    else sb_fprintf(stdout, "(%x) | ",
                      mydata);

    shift += mylength;

  }

  sb_fprintf(stdout, "... \n\n");
  shift = 0;

  sb_fprintf(stdout, "BEGGINING SWAP: %s\n", sc_time_stamp().to_string().c_str() );

  while (true)
  {

    wait(); // ... for the next rising clock edge

    // sb_fprintf(stdout, "Iteraction: %i\n", iter);

    status = bus_port->burst_read(m_unique_priority, &mydata, addr_init_mem_1 + shift, 1, m_lock);
    if (status == SIMPLE_BUS_ERROR) sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
          sc_time_stamp().to_string().c_str(), name(), addr_init_mem_1 + shift);
    /*else sb_fprintf(stdout, "%s %s : Read from mem[%x:%x] = (%x)\n",
        sc_time_stamp().to_string().c_str(), name(), addr_init_mem_1 + shift,
        addr_init_mem_1 + shift + 3,
        mydata);*/

    status = bus_port->burst_write(m_unique_priority, &mydata, addr_init_mem_2 + shift, 1, m_lock);
    if (status == SIMPLE_BUS_ERROR) sb_fprintf(stdout, "%s %s : blocking-write failed at address %x\n",
          sc_time_stamp().to_string().c_str(), name(), addr_init_mem_2 + shift);

    /*else sb_fprintf(stdout, "%s %s : Write in mem[%x:%x] = (%x)\n\n",
        sc_time_stamp().to_string().c_str(), name(), addr_init_mem_2 + shift,
        addr_init_mem_2 + shift +3,
        mydata);*/

    wait(m_timeout, SC_NS);

    if (++iter == num_items) {

      shift = 0;

      sb_fprintf(stdout, "SWAP FINISHED: %s\n", sc_time_stamp().to_string().c_str() );


      sb_fprintf(stdout, "\nFinal state of Slow Memory 2:\n");

      while (addr_init_mem_2 + shift != 0x2328) {

        /* Slow Memory 2: initially empty */
        status = bus_port->burst_read(m_unique_priority, &mydata, addr_init_mem_2 + shift, 1, m_lock);
        if (status == SIMPLE_BUS_ERROR) sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
              sc_time_stamp().to_string().c_str(), name(), addr_init_mem_2 + shift);
        else sb_fprintf(stdout, "(%x) | ",
                          mydata);

        shift += mylength;

      }

      sb_fprintf(stdout, "\n\n");

      break;
    }

    shift += mylength;

  }
}
