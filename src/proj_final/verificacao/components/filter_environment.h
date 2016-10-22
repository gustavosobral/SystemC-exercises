#ifndef _ENV_H_
#define _ENV_H_

#include <systemc.h>
#include <filter_pkg.h>
#include <filter_checker.h>
#include <filter_rst_interface.h>
#include <filter_rst.h>

SC_MODULE(filter_environment)
{
public:

  //+--------------------------------------------------------------------------
  //| Components Members
  //+--------------------------------------------------------------------------
  filter_driver*   filter_drv;
  filter_monitor*  filter_dut_mon;
  filter_monitor*  filter_rm_mon;
  filter_checker*  filter_chk;

  filter_rst*      filter_reset;

  //+--------------------------------------------------------------------------
  //| FUNCTION: config_checker
  //+--------------------------------------------------------------------------
  //! Select the type of check for:
  //!   1 - Select compare_in_out
  //+--------------------------------------------------------------------------
  void config_checker(int config_checker) {
    filter_chk->select_checker = config_checker;
  }

  //+--------------------------------------------------------------------------
  //| FUNCTION: constructor
  //+--------------------------------------------------------------------------
  SC_HAS_PROCESS(filter_environment);
  filter_environment(sc_module_name name,
                     filter_rst_interface * sc_rst_if,
                     filter_interface *     filter_vif,
                     filter_interface *     filter_rm_vif): sc_module(name)
  {
    INFO(this->name(), "constructor");

    filter_reset = new filter_rst("filter_reset", sc_rst_if);
    filter_reset->clock(sc_rst_if->clk);
    filter_reset->clock2(sc_rst_if->clk2);

    filter_drv = new filter_driver("filter_drv", filter_vif);
    filter_drv->clk(sc_rst_if->clk);
    filter_drv->async_reset(sc_rst_if->reset_n);

    filter_dut_mon = new filter_monitor("filter_dut_mon", filter_vif);
    filter_dut_mon->clk(sc_rst_if->clk);
    filter_dut_mon->async_reset(sc_rst_if->reset_n);

    filter_rm_mon = new filter_monitor("filter_rm_mon", filter_rm_vif);
    filter_rm_mon->clk(sc_rst_if->clk);
    filter_rm_mon->async_reset(sc_rst_if->reset_n);

    filter_chk = new filter_checker("filter_chk");
    filter_chk->clk(sc_rst_if->clk);
    filter_chk->clk2(sc_rst_if->clk2);
    filter_chk->async_reset(sc_rst_if->reset_n);

    filter_drv->drv_port.bind(filter_chk->chk_drv_port);
    filter_dut_mon->mon_port.bind(filter_chk->chk_port);
    filter_rm_mon->mon_port.bind(filter_chk->chk_rm_port);
  }

};

#endif /* VIP_SC_ENV_H_ */
