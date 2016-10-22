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
    //filter_test_base *t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7;

    //+--------------------------------------------------------------------------
    //| Function Members
    //+--------------------------------------------------------------------------
    void select_phase();
  
    //+--------------------------------------------------------------------------
    //| FUNCTION: constructor
    //+--------------------------------------------------------------------------
    SC_HAS_PROCESS(filter_test);
     filter_test(filter_environment* filter_env,
              sc_module_name name, 
              test_config*       tst_cfg)
   : sc_module(sc_module_name("filter_test"))
   {
      t_name = string(name);
      if (string(name) == "filter_test_sanity") {
        t = new filter_test_sanity(filter_env, name, tst_cfg);
      }
      // else if (string(name) == "test_all") {
      //   t0 = new t_operation_0(filter_env, name, tst_cfg);
      //   t1 = new t_operation_1(filter_env, name, tst_cfg);
      //   t2 = new t_operation_2(filter_env, name, tst_cfg); 
      //   t3 = new t_operation_3(filter_env, name, tst_cfg); 
      //   t4 = new t_operation_4(filter_env, name, tst_cfg); 
      //   t5 = new t_operation_5(filter_env, name, tst_cfg); 
      //   t6 = new t_operation_6(filter_env, name, tst_cfg); 
      //   t7 = new t_operation_7(filter_env, name, tst_cfg); 

      // }      
      // else if (string(name) == "t_operation_0") {
      //   t = new t_operation_0(filter_env, name, tst_cfg);
      // }
      //  else if (string(name) == "t_operation_1") {
      //   t = new t_operation_1(filter_env, name, tst_cfg);
      // }
      //  else if (string(name) == "t_operation_2") {
      //   t = new t_operation_2(filter_env, name, tst_cfg);
      // }
      //  else if (string(name) == "t_operation_3") {
      //   t = new t_operation_3(filter_env, name, tst_cfg);
      // }
      //  else if (string(name) == "t_operation_4") {
      //   t = new t_operation_4(filter_env, name, tst_cfg);
      // }
      //  else if (string(name) == "t_operation_5") {
      //   t = new t_operation_5(filter_env, name, tst_cfg);
      // }
      //  else if (string(name) == "t_operation_6") {
      //   t = new t_operation_6(filter_env, name, tst_cfg);
      // }
      // else if (string(name) == "t_operation_7") {
      //   t = new t_operation_7(filter_env, name, tst_cfg);
      // }
      else if (string(name) == "filter_test_random") {
        t = new filter_test_random(filter_env, name, tst_cfg);
      }
      else  {
        SC_REPORT_FATAL(name, "Test not register");
      }

      SC_CTHREAD(select_phase,clock.pos());
    }
}; 

//+--------------------------------------------------------------------------
//| FUNCTION: select_phase
//+--------------------------------------------------------------------------
//! Function responsible to call the phases of the test
//+-------------------------------------------------------------------------
void filter_test::select_phase() {

  // if (t_name == "test_all") {
  //  t0->reset_phase();
  //  t0->configure_phase();
  //  t0->run_phase();
  //  t0->end_of_run_phase();
  //  t0->report_phase();

  //  t1->reset_phase();
  //  t1->configure_phase();
  //  t1->run_phase();
  //  t1->end_of_run_phase();
  //  t1->report_phase();

  //  t2->reset_phase();
  //  t2->configure_phase();
  //  t2->run_phase();
  //  t2->end_of_run_phase();
  //  t2->report_phase();

  //  t3->reset_phase();
  //  t3->configure_phase();
  //  t3->run_phase();
  //  t3->end_of_run_phase();
  //  t3->report_phase();

  //  t4->reset_phase();
  //  t4->configure_phase();
  //  t4->run_phase();
  //  t4->end_of_run_phase();
  //  t4->report_phase();

  //  t5->reset_phase();
  //  t5->configure_phase();
  //  t5->run_phase();
  //  t5->end_of_run_phase();
  //  t5->report_phase();

  //  t6->reset_phase();
  //  t6->configure_phase();
  //  t6->run_phase();
  //  t6->end_of_run_phase();
  //  t6->report_phase();

  //  t7->reset_phase();
  //  t7->configure_phase();
  //  t7->run_phase();
  //  t7->end_of_run_phase();
  //  t7->report_phase();
  //  t7->finish_phase();


  // }
  // else {

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
