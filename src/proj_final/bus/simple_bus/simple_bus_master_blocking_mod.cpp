/*****************************************************************************/

/*****************************************************************************

  simple_bus_master_blocking.cpp : The master using the blocking BUS interface.

  Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11

 *****************************************************************************/

#include "simple_bus_master_blocking_mod.h"

int * simple_bus_master_blocking::read_frame(int shift)
{
  int i;
  simple_bus_status status;
  int row = shift / height;
  int column = shift % width;  

  int adresses[9] = {
     shift - 1 - width,
     shift - width,
     shift + 1 - width,
     shift - 1,
     shift,
     shift + 1,
     shift - 1 + width,
     shift + width,
     shift + 1 + width
  };

  if(row == 0 && column == 0) {
    adresses[0] = -1; adresses[1] = -1; adresses[2] = -1;
    adresses[3] = -1; adresses[6] = -1;
  } else if(row == 0 && column == (width-1)) {
    adresses[0] = -1; adresses[1] = -1; adresses[2] = -1;
    adresses[5] = -1; adresses[8] = -1;
  } else if(row == (height-1) && column == 0) {
    adresses[0] = -1; adresses[3] = -1; adresses[6] = -1;
    adresses[7] = -1; adresses[8] = -1;
  } else if(row == (height-1) && column == (width-1)) {
    adresses[2] = -1; adresses[5] = -1; adresses[6] = -1;
    adresses[7] = -1; adresses[8] = -1;
  } else if(row == 0) {
    adresses[0] = -1; adresses[1] = -1; adresses[2] = -1;
  } else if (row == (height-1)) {
    adresses[6] = -1; adresses[7] = -1; adresses[8] = -1;
  } else if (column == 0) {
    adresses[0] = -1; adresses[3] = -1; adresses[6] = -1;
  } else if (column == (width-1)) {
    adresses[2] = -1; adresses[5] = -1; adresses[8] = -1;
  }

  for(i = 0; i < 9; i++) {
    if (adresses[i] >= 0) {
      status = bus_port->burst_read(m_unique_priority, &buffer[i], adresses[i]*word_length, 1, m_lock);
      if (status == SIMPLE_BUS_ERROR)
        sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n", sc_time_stamp().to_string().c_str(), name(), addr_mem_1 + shift);
    } else {
      buffer[i] = 0;
    }
  }

  return buffer;
}

void simple_bus_master_blocking::main_action()
{
  int data;
  int i = 0;
  int j = 0;
  int * buffer;
  float data_temp;
  unsigned int shift = 0;
  simple_bus_status status;

  sb_fprintf(stdout, "\nInitial state of Slow Memory 1:\n");
  shift = 0;

  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      status = bus_port->burst_read(m_unique_priority, &data, addr_mem_1 + shift, 1, m_lock);

      if (status == SIMPLE_BUS_ERROR) {
        sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n", sc_time_stamp().to_string().c_str(), name(), addr_mem_1 + shift);
      } else {   
        sb_fprintf(stdout, "(%03d) ", data);
      }
      shift += word_length;
    }    
    sb_fprintf(stdout, "\n");
  }

  sb_fprintf(stdout, "\nInitial state of Slow Memory 2:\n");
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
  i = 0;
  while (true) {
    wait();

    buffer = read_frame(i);

    data_temp = (buffer[0] + buffer[1] + buffer[2] + buffer[3] + buffer[4] + buffer[5] + buffer[6] + buffer[7] + buffer[8]) / 9.0;
    data = floor(data_temp + 0.5);

    status = bus_port->burst_write(m_unique_priority, &data, addr_mem_2 + i*word_length, 1, m_lock);
    if (status == SIMPLE_BUS_ERROR)
      sb_fprintf(stdout, "%s %s : blocking-write failed at address %x\n", sc_time_stamp().to_string().c_str(), name(), addr_mem_2 + shift);

    wait(m_timeout, SC_NS);
    i++;

    // If finished the process
    if (i == num_items) {
      sb_fprintf(stdout, "SWAP FINISHED: %s\n", sc_time_stamp().to_string().c_str() );
      sb_fprintf(stdout, "\nFinal state of Slow Memory 2:\n");

      i = 0;
      j = 0;
      shift = 0;

      for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
          status = bus_port->burst_read(m_unique_priority, &data, addr_mem_2 + shift, 1, m_lock);

          if (status == SIMPLE_BUS_ERROR) {
            sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n", sc_time_stamp().to_string().c_str(), name(), addr_mem_1 + shift);
          } else {     
            sb_fprintf(stdout, "(%03d) ", data);
          }
          shift += word_length;
        }
        sb_fprintf(stdout, "\n");
      }
      break;
    }
  }
}
