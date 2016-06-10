CC=g++
CFLAGS=-g -Wall -O2 -std=c++11
EXECUTABLES_BASE=#UnaNuevaEsperanza ElImperioContraataca ElRetornoDelJedi
EXECUTABLES=$(addsuffix Solver, $(EXECUTABLES_BASE))
FRAME_WORK_TEST=framework/test
MAIN_OBJECT=main.o
OTHER_OBJECTS=solver.o performance.o test.o

.PHONY: all clean test $(addsuffix test, $(EXECUTABLES_BASE))

all: $(EXECUTABLES)

$(FRAME_WORK_TEST): $(addsuffix .o, $(FRAME_WORK_TEST)) framework/graph.h framework/ady_list_graph.h
	$(CC) $(CFLAGS) $(addsuffix .o, $(FRAME_WORK_TEST)) -o $@

test: $(addprefix test,$(EXECUTABLES_BASE)) $(FRAME_WORK_TEST)

clean:
	rm -rf $(EXECUTABLES) $(MAIN_OBJECT) $(addsuffix /*.o,$(EXECUTABLES_BASE)) $(FRAME_WORK_TEST) $(addsuffix .o, $(FRAME_WORK_TEST))

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@

.SECONDEXPANSION:

$(EXECUTABLES): $(MAIN_OBJECT) $$(addprefix $$(subst Solver,,$$@)/,$(OTHER_OBJECTS))
	$(CC) $(CFLAGS) -o $@ $^
