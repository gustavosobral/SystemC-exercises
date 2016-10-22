#include "rm_filter.h"

SC_HAS_PROCESS(rm_filter);
rm_filter::rm_filter(sc_module_name nm):
  sc_module   (nm),
  clock       ("clock"),
  in_data_en  ("in_data_en"),
  reset_n     ("reset_n"),
  out_data_rdy("out_data_rdy")
{
  SC_CTHREAD(func, clock.pos());
  async_reset_signal_is(reset_n, false);
}

void rm_filter::func()
{
  int iA1, iA2, iA3, iA4, iA5, iA6, iA7, iA8, iA9, iF;
  // reset
  while (true)
  {
    if (reset_n.read() == false) {
      out_data_rdy.write(0);
    }
    else if (in_data_en.read() == 1) {
      iA1 = A1.read();
      iA2 = A2.read();
      iA3 = A3.read();
      iA4 = A4.read();
      iA5 = A5.read();
      iA6 = A6.read();
      iA7 = A7.read();
      iA8 = A8.read();
      iA9 = A9.read();

      iF = (iA1 + iA2 + iA3 + iA4 + iA5 + iA6 + iA7 + iA8 + iA9 );

      // std::cout << "Soma = " << iA1 << " + " << iA2 << " + " << iA3 << " + " << iA4 << " + " << iA5 << " + "
      // << iA6 << " + " << iA7 << " + " << iA8 << " + " << iA9 << " = "<< iF;

      iF = iF / 9;
      // std::cout << " | Media = " << iF << std::endl;

      F.write(iF);
      out_data_rdy.write(1);
    }
    wait(1);
  }
}
