SET_WAVEFORM = 0

BLOCK_PATH = $$PWD/..
BLOCK_TB = $(BLOCK_PATH)/verification

CC=g++

CPPFLAGS = -lsystemc -lm -pthread

SYSTEMC_LIB = $$SYSTEMC_HOME/lib-linux64/libsystemc.a
LIBS =  $(SYSTEMC_LIB)

SYSTEMCFLAGS += -DSC_INCLUDE_DYNAMIC_PROCESSES
SYSTEMCFLAGS += -I$$SYSTEMC_HOME/include
SYSTEMCLIBS += -L$$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$$SYSTEMC_HOME/lib-linux64

#TESTBENCH
INC_COMP   = -I$(BLOCK_TB)/components
INC_TESTS  = -I$(BLOCK_TB)/tests
CPP_TOP_TB := $(BLOCK_TB)/filter_top_tb.cpp

#TRACE
ifeq ($(SET_WAVEFORM),1) 
  DEFINES += -D_TRACE_ 
endif

#REFERENCE MODEL
PATH_RM = $(BLOCK_PATH)/reference_model
ARCH_RM = $(PATH_RM)/rm_filter.cpp 

#DUT
PATH_DUT = $(BLOCK_PATH)/design
TARGET = run_verification
ARCH_DUT = $(PATH_DUT)/filter.cpp 
 
all: 
	$(CC) $(SYSTEMCFLAGS) $(CPPFLAGS) $(DEFINES) -I. -I$(PATH_DUT) -I$(PATH_RM) $(INC_COMP) $(INC_TESTS) $(ARCH_DUT) $(ARCH_RM) $(CPP_TOP_TB) $(SYSTEMCLIBS) $(LIBS) -D_SYSTEMC_ -o $(TARGET) 

clean:
	@rm -rf $(TARGET) *.vcd logs *.log results/*
