/*****************************************************************************/

/*****************************************************************************

  simple_bus_master_blocking.cpp : The master using the blocking BUS interface.

  Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11

 *****************************************************************************/

#include "simple_bus_master_blocking_mod.h"

int * simple_bus_master_blocking::read_frame(unsigned int shift)
{
  int i;
  int buffer[9];
  simple_bus_status status;

  unsigned int adresses[9] = {
    addr_mem_1 + shift - word_length - width*word_length,
    addr_mem_1 + shift - width*word_length,
    addr_mem_1 + shift + word_length - width*word_length,
    addr_mem_1 + shift - word_length,
    addr_mem_1 + shift,
    addr_mem_1 + shift + word_length,
    addr_mem_1 + shift - word_length + width*word_length,
    addr_mem_1 + shift + width*word_length,
    addr_mem_1 + shift + word_length + width*word_length
  };

  for(i = 0; i < 9; i++) {
    if ((adresses[i] > addr_mem_1) && (adresses[i] < (addr_mem_1 + width*height*word_length))) {
      status = bus_port->burst_read(m_unique_priority, &buffer[i], adresses[i], 1, m_lock);
      if (status == SIMPLE_BUS_ERROR)
        sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n", sc_time_stamp().to_string().c_str(), name(), addr_mem_1 + shift);
    } else {
      buffer[i] = 0;
    }
    // sb_fprintf(stdout, "%03d ", adresses[i]);
  }
  // sb_fprintf(stdout, "\n");

  return buffer;
}

void simple_bus_master_blocking::main_action()
{
  int data;
  int i = 0;
  int * buffer;
  unsigned int shift = 0;
  simple_bus_status status;

  sb_fprintf(stdout, "\nInitial state of Slow Memory 1:\n");

  while (addr_mem_1 + shift != (addr_mem_1 + word_length*10)) {
    status = bus_port->burst_read(m_unique_priority, &data, addr_mem_1 + shift, 1, m_lock);

    if (status == SIMPLE_BUS_ERROR) {
      sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n", sc_time_stamp().to_string().c_str(), name(), addr_mem_1 + shift);
    } else {
      sb_fprintf(stdout, "| (%03d) ", data);
    }

    shift += word_length;
  }

  sb_fprintf(stdout, "| ... \n");
  sb_fprintf(stdout, "Initial state of Slow Memory 2:\n");
  shift = 0;

  while (addr_mem_2 + shift != (addr_mem_2 + word_length*10)) {
    status = bus_port->burst_read(m_unique_priority, &data, addr_mem_2 + shift, 1, m_lock);
    if (status == SIMPLE_BUS_ERROR) {
      sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n", sc_time_stamp().to_string().c_str(), name(), addr_mem_2 + shift);
    } else {
      sb_fprintf(stdout, "| (%03d) ", data);
    }

    shift += word_length;
  }

  sb_fprintf(stdout, "| ... \n\n");
  sb_fprintf(stdout, "BEGGINING SWAP: %s\n", sc_time_stamp().to_string().c_str() );
  shift = 0;

  // Initialize swap
  while (true) {
    wait();

    buffer = read_frame(shift);

    data = (buffer[0] + buffer[1] + buffer[2] + buffer[3] + buffer[4] + buffer[5] + buffer[6] + buffer[7] + buffer[8]) / 9;

    status = bus_port->burst_write(m_unique_priority, &data, addr_mem_2 + shift, 1, m_lock);
    if (status == SIMPLE_BUS_ERROR)
      sb_fprintf(stdout, "%s %s : blocking-write failed at address %x\n", sc_time_stamp().to_string().c_str(), name(), addr_mem_2 + shift);

    wait(m_timeout, SC_NS);

    shift += word_length;
    i++;

    // If finished the process
    if (i == num_items) {
      sb_fprintf(stdout, "SWAP FINISHED: %s\n", sc_time_stamp().to_string().c_str() );
      sb_fprintf(stdout, "\nFinal state of Slow Memory 2:\n");

      i = 0;
      shift = 0;

      while (i < num_items) {
        status = bus_port->burst_read(m_unique_priority, &data, addr_mem_2 + shift, 1, m_lock);

        if (status == SIMPLE_BUS_ERROR) {
          sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n", sc_time_stamp().to_string().c_str(), name(), addr_mem_2 + shift);
        } else {
          sb_fprintf(stdout, "| (%03d) ", data);
        }

        shift += word_length;
        i++;
      }

      sb_fprintf(stdout, "|\n\n");
      break;
    }
  }
}
