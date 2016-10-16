/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2014 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.accellera.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************
 
  simple_bus_master_blocking.cpp : The master using the blocking BUS interface.
 
  Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11
 
 *****************************************************************************/
 
/*****************************************************************************
 
  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.
 
      Name, Affiliation, Date:
  Description of Modification:
 
 *****************************************************************************/

#include "simple_bus_master_blocking.h"

void simple_bus_master_blocking::main_action()
{
  int mydata;
  unsigned int i = 0;
  unsigned int shift = 0;
  const int num_items = 1000;
  const unsigned int mylength = 0x04; 
  unsigned int addr_mem_1 = 0x00;
  unsigned int addr_mem_2 = 0xFA0;
  simple_bus_status status;

  while (true)
  {
    wait();
    status = bus_port->burst_read(m_unique_priority, &mydata, 
                                  addr_mem_1 + shift, 1, m_lock);
    if (status == SIMPLE_BUS_ERROR)
        sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
                   sc_time_stamp().to_string().c_str(), name(), addr_mem_1 + shift);

    status = bus_port->burst_write(m_unique_priority, &mydata, 
                                   addr_mem_2 + shift, 1, m_lock);
    if (status == SIMPLE_BUS_ERROR)
      sb_fprintf(stdout, "%s %s : blocking-write failed at address %x\n",
                 sc_time_stamp().to_string().c_str(), name(), addr_mem_2 + shift);

    wait(m_timeout, SC_NS);

    i++;
    shift += mylength;

    if (i == num_items) {
      sb_fprintf(stdout, "SWAP FINISHED: %s\n", sc_time_stamp().to_string().c_str() );

      i = 0;
      shift = 0;

      while(i < num_items) {
        status = bus_port->burst_read(m_unique_priority, &mydata, 
                                      addr_mem_2 + shift, 1, m_lock);
        if (status == SIMPLE_BUS_ERROR) {
            sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
                       sc_time_stamp().to_string().c_str(), name(), addr_mem_2 + shift);
        } else {
          sb_fprintf(stdout, "%d|", mydata);
        }

        shift += mylength;
        i++;
      }
      
      sb_fprintf(stdout, "\n");
      break;
    }
  }
}
