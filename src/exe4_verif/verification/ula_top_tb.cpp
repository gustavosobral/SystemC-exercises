//-----------------------------
// SystemC defines and includes
//-----------------------------
#define SC_INCLUDE_FX
#include <systemc.h>
#include "tlm.h"

using namespace tlm;
using namespace std;


//-----------------------------
// C++ includes
//-----------------------------
#include <getopt.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string>
using namespace std;

#include <report_server.h>

//-----------------------------
// Log, Trace and Module ID
//-----------------------------
const char* main_ID  = "ula_MAIN";
const char* log_name = "ula_tb.log";
const char* vcd_name = "ula_trace";
string result_path;
int number_clock;


//-----------------------------
// DUT Instantiation
//-----------------------------

#include <ula.h>
#include <rm_ula.h>

//-----------------------------
// Sub-Modules Include
//-----------------------------

#include <ula_define.h>
#include <ula_pkg.h>
#include <ula_subscriber.h>
#include <ula_test_list.h>

// Reset
#include <ula_rst_interface.h>
#include <ula_rst.h>

#include <ula_top_tb.h>

using namespace report_server;
verbosity_type report_server::report::verbosity;

int sc_main(int argc, char *argv[])
{
  //-----------------------------
  // Initial Time
  //-----------------------------
  int startTime;
  startTime = time(NULL);

  //-------------------------
  // Connection Signals
  //--------------------------
  //sc_signal<bool> reset("arst_n");
  //is_rst=0;


  // +--------------------------------------------------------------------------
  // | RECEIVEING INPUT ARGUMENTS
  // +--------------------------------------------------------------------------
  int opt;
  string input_argv = "Running command line: ";

  //Setup to dumping the log file
  char* pwd = getenv("PWD");
  string log_fname;
  string result_path_tmp(pwd);
  result_path = result_path_tmp + "/results/";

  string testname  = "ula_test_sanity";
  string seed_input = "1";
  string verbosity_input = "MEDIUM";
  string NI_str = "50";

  verbosity_type verbosity_simulation;
  bool quiet = 0;

  //Setup test configuration
  test_config tst_cfg;

  //Set long options
  static struct option long_options[] =
  {
    /* These options set a flag. */
    //   {"quiet", no_argument,       &quiet, 1},
    /* These options don¿t set a flag.
       We distinguish them by their indices. */
    {"quiet",       no_argument,       0, 'q'},
    {"testname",    required_argument, 0, 't'},
    {"result_path", required_argument, 0, 'r'},
    {"seed"       , required_argument, 0, 's'},
    {"log_str",     required_argument, 0, 'l'},
    {"verbosity",   required_argument, 0, 'v'},
    {0, 0, 0, 0}
  };
  //!Get input from prompt to select the options: testname, result_path and the seed.
  while ((opt = getopt(argc, argv, "t:l:s:v:q n:")) != -1)
  {
    switch (opt)
    {
    case 't':
      testname = optarg;
      break;
    case 'l':
      result_path = optarg;
      break;
    case 's':
      seed_input = optarg;
      break;
    case 'v':
      verbosity_input = optarg;
      break;
    case 'q':
      quiet = 1;
      break;
    case 'n':
      NI_str = optarg;
      break;
    default:
      break;
    }
  }

  for (int i = 0; i < argc; i++ ) {
    input_argv = input_argv + argv[i] + " ";
  }
  //Convert input from prompt string2double
  istringstream convert(NI_str);
  if (!(convert >> tst_cfg.NI)) {tst_cfg.NI = 10;}
  convert.clear();

  convert.str(seed_input);
  if (!(convert >> tst_cfg.seed)) {tst_cfg.seed = 1;}
  convert.clear();

  //set testname
  tst_cfg.testname = testname;

  //set verbosity
  if ( verbosity_input == "HIGH") { verbosity_simulation = HIGH; }
  else if ( verbosity_input == "MEDIUM") { verbosity_simulation = MEDIUM; }
  else if ( verbosity_input == "LOW") { verbosity_simulation = LOW; }
  else { SC_REPORT_FATAL("ula_top_tb", "Vebosity format not specify!");}

  log_fname = result_path + "/" + testname + "_" + seed_input + ".log";

  report_server::report::set_log_file_name(log_fname.c_str());
  report_server::report::set_verbosity(verbosity_simulation, quiet);
  INFO("main", input_argv.c_str());

  //Used to generated VCD file
  string trace_fname;
  trace_fname = result_path + testname;

  //-------------------------
  // Conect and call Tests
  //--------------------------
  ula_top_tb ula_top_tb("ula_top_tb", testname, trace_fname, &tst_cfg);

  //-----------------------------
  // Start Simulation
  //-----------------------------
  SC_REPORT_INFO(main_ID, "Start Simulation...");
  sc_start(ULA_TIMEOUT, ULA_TIMEUNIT);
  SC_REPORT_INFO(main_ID, "End Simulation...");

  return 0;
}
