#include <filter_environment.h>

//+--------------------------------------------------------------------------
//| SC_MODULE: filter_test
//+--------------------------------------------------------------------------
SC_MODULE (filter_test) {
  //+--------------------------------------------------------------------------
  //| Input
  //+--------------------------------------------------------------------------
  sc_in<bool> clock;
  string t_name;

  //+--------------------------------------------------------------------------
  //| Running test
  //+--------------------------------------------------------------------------
  filter_test_base* t;

  //+--------------------------------------------------------------------------
  //| Function Members
  //+--------------------------------------------------------------------------
  void select_phase();

  //+--------------------------------------------------------------------------
  //| FUNCTION: constructor
  //+--------------------------------------------------------------------------
  SC_HAS_PROCESS(filter_test);
  filter_test(filter_environment * filter_env,
              sc_module_name name,
              test_config *       tst_cfg)
    : sc_module(sc_module_name("filter_test"))
  {
    t_name = string(name);
    if (string(name) == "filter_test_sanity") {
      t = new filter_test_sanity(filter_env, name, tst_cfg);
    }
    else if (string(name) == "filter_test_random") {
      t = new filter_test_random(filter_env, name, tst_cfg);
    }
    else  {
      SC_REPORT_FATAL(name, "Test not register");
    }

    SC_CTHREAD(select_phase, clock.pos());
  }
};

//+--------------------------------------------------------------------------
//| FUNCTION: select_phase
//+--------------------------------------------------------------------------
//! Function responsible to call the phases of the test
//+-------------------------------------------------------------------------
void filter_test::select_phase() {
  //Call Reset Phase
  t->reset_phase();

  //Call Configure Phase
  t->configure_phase();

  //Call Run Phase
  t->run_phase();

  //Call End of Run Phase
  t->end_of_run_phase();

  //Call Report Phase
  t->report_phase();

  //Call Finish Phase
  t->finish_phase();
}
