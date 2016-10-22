
//+--------------------------------------------------------------------------
//| CLASS: filter_test_random
//+--------------------------------------------------------------------------
class filter_test_random : public filter_test_base {
  public :
    //+--------------------------------------------------------------------------
    //| FUNCTION: constructor
    //+--------------------------------------------------------------------------
    filter_test_random(filter_environment* filter_env,
                  const char* _name,
                  test_config*       tst_cfg) : filter_test_base(filter_env, _name, tst_cfg){ 
  }

    //+--------------------------------------------------------------------------
    //| FUNCTION: configure_phase
    //+--------------------------------------------------------------------------
    //! Set the function of the checker for this test
    //---------------------------------------------------------------------------
    virtual void configure_phase(){
      INFO(name, "Configure Phase");
      filter_env->config_checker(1);
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: run_phase
    //+--------------------------------------------------------------------------
    //! Implement the test run
    //---------------------------------------------------------------------------
    void run_phase(){
      INFO(name, " Starting test...", MEDIUM);
      
      INFO(name, " Set seed");
      filter_env->filter_drv->set_seed(seed);
      
      
      for(int i = 0; i < NI; i++) {
	     //INFO(name, " Generate random data", MEDIUM);
	     filter_env->filter_drv->randomize();
      }
      
      //INFO(name, " Finished test!!!", MEDIUM);
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: end_of_run_phase
    //+--------------------------------------------------------------------------
    //! Wait time to end of silmuation
    //+--------------------------------------------------------------------------
    virtual void end_of_run_phase(){
      filter_env->filter_reset->wait_posedge(1);  
    }
};
