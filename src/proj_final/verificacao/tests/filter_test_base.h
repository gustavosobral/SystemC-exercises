#include <filter_define.h>
#include <filter_sequence.h>
#include <filter_environment.h>

//+--------------------------------------------------------------------------
//| CLASS: filter_test_base
//+--------------------------------------------------------------------------
class filter_test_base {

public :
  //+--------------------------------------------------------------------------
  //| Data Members
  //+--------------------------------------------------------------------------
  const char*  name;
  int          NI; // Number of interactions
  unsigned int seed; //Seed used in randomization and PRBS
  string testname;

  //+--------------------------------------------------------------------------
  //| Components Members
  //+--------------------------------------------------------------------------
  filter_environment* filter_env;

  //+--------------------------------------------------------------------------
  //| FUNCTION: constructor
  //+--------------------------------------------------------------------------
  filter_test_base(filter_environment* in_filter_env,
                   const char* _name,
                   test_config*       tst_cfg) {
    INFO(_name, "Constructor", MEDIUM);
    filter_env = in_filter_env;
    // filter_env = new filter_environment("filter_env", sc_rst_if, test_sc_if, rm_test_sc_if);
    name = _name;
    testname = tst_cfg->testname;
    NI   = tst_cfg->NI;
    seed = tst_cfg->seed;
    srand(seed);
  }

  //+--------------------------------------------------------------------------
  //| FUNCTION: reset_phase
  //+--------------------------------------------------------------------------
  //! Virtual Function to implementation of reset phase
  //+--------------------------------------------------------------------------
  virtual void reset_phase() {
    INFO(name, "Start Reset Phase", MEDIUM);
    filter_env->filter_reset->async_reset();
    filter_env->filter_reset->wait_posedge(10);
  }

  // //+--------------------------------------------------------------------------
  //  //| FUNCTION: configure_phase
  //  //+--------------------------------------------------------------------------
  //  //! Virtual Function to implementation of configure phase
  //  //+--------------------------------------------------------------------------
  virtual void configure_phase() {
  }

  //  //+--------------------------------------------------------------------------
  //  //| FUNCTION: run_phase
  //  //+--------------------------------------------------------------------------
  //  //! Virtual Function to implementation of run phase
  //  //+--------------------------------------------------------------------------
  virtual void run_phase() {
    INFO(name, "Start Run Phase", MEDIUM);
  }

  //+--------------------------------------------------------------------------
  //| FUNCTION: end_of_run_phase
  //+--------------------------------------------------------------------------
  //! Virtual Function to wait time to end of simfiltertion
  //+--------------------------------------------------------------------------
  virtual void end_of_run_phase() {
    filter_env->filter_reset->wait_posedge(100);
  }

  //+--------------------------------------------------------------------------
  //| FUNCTION: report_phase
  //+--------------------------------------------------------------------------
  //! Virtual Function to show the result of simfiltertion
  //+--------------------------------------------------------------------------
  virtual void report_phase() {
    stringstream msg;
    int errors;

    //Get errors from server
    errors = report_server::report::get_errors();

    if (errors) {
      INFO(name, "                                          ", LOW);
      INFO(name, "#########   #######   #########  ##       ", LOW);
      INFO(name, "##         ##     ##     ##      ##       ", LOW);
      INFO(name, "##         ##     ##     ##      ##       ", LOW);
      INFO(name, "######     #########     ##      ##       ", LOW);
      INFO(name, "##         ##     ##     ##      ##       ", LOW);
      INFO(name, "##         ##     ##     ##      ##       ", LOW);
      INFO(name, "##         ##     ##  #########   ########", LOW);
      INFO(name, "                                          ", LOW);
      msg << "Simfiltertion completed with " << errors << " errors!";
      ERROR(name, msg.str().c_str(), LOW);
    }
    else {
      INFO(name, "                                          ", LOW);
      INFO(name, "########    #######     ######     ###### ", LOW);
      INFO(name, "##     ##  ##     ##  ##     ##  ##     ##", LOW);
      INFO(name, "##     ##  ##     ##  ##         ##       ", LOW);
      INFO(name, "########   #########    ######     ###### ", LOW);
      INFO(name, "##         ##     ##         ##         ##", LOW);
      INFO(name, "##         ##     ##  ##     ##  ##     ##", LOW);
      INFO(name, "##         ##     ##    ######     ###### ", LOW);
      INFO(name, "                                          ", LOW);
      INFO(name, "Simfiltertion completed without errors!", LOW);
    }
  }

  //+--------------------------------------------------------------------------
  //| FUNCTION: finish_phase
  //+--------------------------------------------------------------------------
  //! Virtual Function to finish simfiltertion
  //+--------------------------------------------------------------------------
  virtual void finish_phase() {
    INFO(name, "Start Finish Phase", MEDIUM);
    sc_stop(); // sc_stop triggers end of simfiltertion
  }

};

