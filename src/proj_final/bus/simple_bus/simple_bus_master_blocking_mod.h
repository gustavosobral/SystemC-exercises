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

  simple_bus_master_blocking.h : The master using the blocking BUS interface.

  Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#ifndef __simple_bus_master_blocking_h
#define __simple_bus_master_blocking_h

#include <systemc.h>

#include "simple_bus_types.h"
#include "simple_bus_blocking_if.h"

SC_MODULE(simple_bus_master_blocking)
{
  // ports
  sc_in_clk clock;
  sc_port<simple_bus_blocking_if> bus_port;

  SC_HAS_PROCESS(simple_bus_master_blocking);

  // constructor
  simple_bus_master_blocking(sc_module_name name_
                             , unsigned int unique_priority
                             , bool lock
                             , int timeout
                             , int num_items
                             , unsigned int word_length
                             , unsigned int addr_mem_1
                             , unsigned int addr_mem_2
                             , unsigned int width
                             , unsigned int height
                             )
    : sc_module(name_)
    , m_unique_priority(unique_priority)
    , m_lock(lock)
    , m_timeout(timeout)
    , num_items(num_items)
    , word_length(word_length)
    , addr_mem_1(addr_mem_1)
    , addr_mem_2(addr_mem_2)
    , width(width)
    , height(height)
  {
    SC_THREAD(main_action);
    sensitive << clock.pos();
  }

  // process
  void main_action();
  int * read_frame(unsigned int shift);

private:
  unsigned int m_unique_priority;
  bool m_lock;
  int m_timeout;
  const unsigned int num_items;
  const unsigned int word_length; 
  unsigned int addr_mem_1;
  unsigned int addr_mem_2;
  unsigned int width;
  unsigned int height;

}; // end class simple_bus_master_blocking

#endif
