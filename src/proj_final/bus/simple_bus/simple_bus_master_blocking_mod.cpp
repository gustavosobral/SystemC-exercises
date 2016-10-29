/*****************************************************************************/

/*****************************************************************************

  simple_bus_master_blocking.cpp : The master using the blocking BUS interface.

  Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11

 *****************************************************************************/

#include "simple_bus_master_blocking_mod.h"

void simple_bus_master_blocking::main_action()
{
  const int num_items = 1000;
  const unsigned int mylength = 0x04; // storage capacity/burst length in words
  unsigned int shift = 0;
  unsigned int shift_2 = 0;
  int mydata;
  int buffer[8];
  int iter = 0;
  int i = 0;
  unsigned int addr_init_mem_1 = 0x00;
  unsigned int addr_init_mem_2 = 0x1388;
  simple_bus_status status;

  sb_fprintf(stdout, "\nInitial state of Slow Memory 1:\n");

  while (addr_init_mem_1 + shift != 0x28) {

    /* Slow Memory 2: initially empty */
    status = bus_port->burst_read(m_unique_priority, &mydata, addr_init_mem_1 + shift, 1, m_lock);
    if (status == SIMPLE_BUS_ERROR) sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
          sc_time_stamp().to_string().c_str(), name(), addr_init_mem_1 + shift);
    else sb_fprintf(stdout, "(%03d) | ",
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
    else sb_fprintf(stdout, "(%03d) | ",
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

    status = bus_port->burst_read(m_unique_priority, &buffer[i], addr_init_mem_1 + shift, 1, m_lock);
    if (status == SIMPLE_BUS_ERROR) sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
          sc_time_stamp().to_string().c_str(), name(), addr_init_mem_1 + shift);
    i++;

    if (i == 9) {
      mydata = (buffer[0] + buffer[1] + buffer[2] + buffer[3] + buffer[4] + buffer[5] + buffer[6] + buffer[7] + buffer[8]) / 9;

      status = bus_port->burst_write(m_unique_priority, &mydata, addr_init_mem_2 + shift_2, 1, m_lock);
      if (status == SIMPLE_BUS_ERROR) sb_fprintf(stdout, "%s %s : blocking-write failed at address %x\n",
            sc_time_stamp().to_string().c_str(), name(), addr_init_mem_2 + shift);
      i = 0;
      shift_2 += mylength;
    }

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
        else sb_fprintf(stdout, "%03d|",
                          mydata);

        shift += mylength;

      }

      sb_fprintf(stdout, "\n");

      break;
    }

    shift += mylength;

  }
}
