#include <report_server.h>

#define FILTER_SEED          1
#define FILTER_TIMEOUT       50000
#define FILTER_TIMEUNIT      SC_NS

#define DATA_NUMBER_BITS  8

#ifndef  FILTER_TEST_CONFIG
#define FILTER_TEST_CONFIG
struct test_config {
  int          NI;    // Number of interactions
  unsigned int seed;  // Seed used in randomization and PRBS
  string testname;
};
#endif

typedef sc_uint<DATA_NUMBER_BITS> dut_data_t;
