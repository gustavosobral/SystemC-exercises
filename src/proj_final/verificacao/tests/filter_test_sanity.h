
//+--------------------------------------------------------------------------
//| CLASS: filter_test_sanity
//+--------------------------------------------------------------------------
class filter_test_sanity : public filter_test_base {
  public :
    //+--------------------------------------------------------------------------
    //| FUNCTION: constructor
    //+--------------------------------------------------------------------------
    filter_test_sanity(filter_environment* filter_env,
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
      filter_env->config_checker(0);
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: run_phase
    //+--------------------------------------------------------------------------
    //! Implement the test run
    //---------------------------------------------------------------------------
    void run_phase(){
      INFO(name, " Starting test...");
      filter_env->filter_drv->set_seed(seed);
      
      filter_env->filter_reset->wait_posedge(1);
      
      INFO(name, " Finished test!!!");
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: end_of_run_phase
    //+--------------------------------------------------------------------------
    //! Wait time to end of silmuation
    //+--------------------------------------------------------------------------
    virtual void end_of_run_phase(){
      filter_env->filter_reset->wait_posedge(100);  
    }
};
