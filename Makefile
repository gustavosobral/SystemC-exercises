CC      := g++
CCFLAGS := -lsystemc -Wall

SYSTEMC := /home/gustavo/Applications/systemc-2.3.1

INCS := -I$(SYSTEMC)/include
LIBS := -L$(SYSTEMC)/lib-linux64
FILES := *.cpp

all: main.cpp
	$(CC) $(INCS) $(LIBS) -Wl,-rpath=$(SYSTEMC)/lib-linux64 $(CCFLAGS) -o main $(FILES)

clean:
	rm -rf main traces.vcd
