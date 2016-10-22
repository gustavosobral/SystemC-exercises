#include "systemc.h"
#include "mem_swap.h"

int sc_main(int, char **)
{
  mem_swap top("top");

  sc_start(500000, SC_NS);

  return 0;
}
