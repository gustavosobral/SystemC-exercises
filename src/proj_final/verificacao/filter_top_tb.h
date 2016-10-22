SC_MODULE(filter_top_tb) {
  //+--------------------------------------------------------------------------
  //| Members
  //+--------------------------------------------------------------------------
  // Interface
  filter_rst_interface *rst_if;
  filter_interface     *filter_if;
  filter_interface     *rm_out_if;
  filter_environment   *filter_env;

  // DUT Module
  filter    DUT;
  rm_filter RM;

  // Test Module
  filter_test *test;

#ifdef _TRACE_
  sc_trace_file *tf;
  string        trace_fname;
#endif
  //+--------------------------------------------------------------------------
  //| FUNCTION: constructor
  //+--------------------------------------------------------------------------

  filter_top_tb(sc_module_name name, string _testname, string _trace_fname, test_config * tst_cfg)
    : DUT("DUT"),
      RM("RM"),
      sc_module(name)
  {
    // Interface
    rst_if     = new filter_rst_interface();   //reset
    filter_if     = new filter_interface();
    rm_out_if  = new filter_interface();

    //-----------------------------
    // DUT Module
    //-----------------------------
    //Input signals
    DUT.clock   (rst_if->clk);
    DUT.reset_n (rst_if->reset_n);

    DUT.in_data_en  (filter_if->in_data_en);
    DUT.A1   (filter_if->A1);
    DUT.A2   (filter_if->A2);
    DUT.A3   (filter_if->A3);
    DUT.A4   (filter_if->A4);
    DUT.A5   (filter_if->A5);
    DUT.A6   (filter_if->A6);
    DUT.A7   (filter_if->A7);
    DUT.A8   (filter_if->A8);
    DUT.A9   (filter_if->A9);


    //Output signals
    DUT.F    (filter_if->F);
    DUT.out_data_rdy(filter_if->out_data_rdy);

    //-----------------------------
    // Reference Module
    //-----------------------------
    //Input signals
    RM.clock   (rst_if->clk);
    RM.reset_n (rst_if->reset_n);

    RM.in_data_en  (filter_if->in_data_en);
    RM.A1   (filter_if->A1);
    RM.A2   (filter_if->A2);
    RM.A3   (filter_if->A3);
    RM.A4   (filter_if->A4);
    RM.A5   (filter_if->A5);
    RM.A6   (filter_if->A6);
    RM.A7   (filter_if->A7);
    RM.A8   (filter_if->A8);
    RM.A9   (filter_if->A9);


    //Output signals
    RM.F    (rm_out_if->F);
    RM.out_data_rdy(rm_out_if->out_data_rdy);


    //-----------------------------
    // Environment
    //-----------------------------
    filter_env = new filter_environment("filter_env", rst_if, filter_if, rm_out_if);

    //-----------------------------
    // Test Module
    //-----------------------------
    test = new filter_test(filter_env,
                           _testname.c_str(),
                           tst_cfg);
    test->clock(rst_if->clk);

#ifdef _TRACE_
    tf = 0;
    trace_fname = _trace_fname;
#endif

  }

  //+--------------------------------------------------------------------------
  //| FUNCTION: before_end_of_elaboration
  //+--------------------------------------------------------------------------
  //! Used to create the trace file
  //+--------------------------------------------------------------------------
  void before_end_of_elaboration() {
#ifdef _TRACE_
    tf = sc_create_vcd_trace_file(trace_fname.c_str());
    tf->set_time_unit(0.5, SC_PS);
#endif
  }

  //+--------------------------------------------------------------------------
  //| FUNCTION: end_of_elaboration
  //+--------------------------------------------------------------------------
  //! Used to connect the interface signals to trace file
  //+--------------------------------------------------------------------------
  void end_of_elaboration() {
#ifdef _TRACE_
    sc_trace(tf, rst_if->clk, "clk");
    sc_trace(tf, rst_if->reset_n, "reset_n");

    sc_trace(tf, filter_if->in_data_en, "in_data_en");
    sc_trace(tf, filter_if->in_data_a,  "in_data_a");
    sc_trace(tf, filter_if->in_data_b,  "in_data_b");
    sc_trace(tf, filter_if->in_sel ,    "in_sel");

    sc_trace(tf, filter_if->out_data    , "out_data");
    sc_trace(tf, filter_if->out_data_rdy, "out_data_rdy");
    sc_trace(tf, filter_if->out_sel, "out_sel");

    sc_trace(tf, rm_out_if->out_data    , "rm_out_data");
    sc_trace(tf, rm_out_if->out_data_rdy, "rm_out_data_rdy");
    sc_trace(tf, rm_out_if->out_sel, "rm_out_sel");

#endif
  }

  //+--------------------------------------------------------------------------
  //| FUNCTION: end_of_simfiltertion
  //+--------------------------------------------------------------------------
  //! Used to close the trace file
  //+--------------------------------------------------------------------------
  void end_of_simfiltertion() {
#ifdef _TRACE_
    sc_close_vcd_trace_file(tf);
#endif
  }
};

