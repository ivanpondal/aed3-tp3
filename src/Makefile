# suffixes used in implicit rules (first line clears default ones)
.SUFFIXES:
.SUFFIXES: .cpp .o

# flags used in implicit rules
CC=g++
CPPFLAGS=-g -Wall -O2
CXXFLAGS=-std=c++11

# excercise variables
EXECUTABLES_BASE=#exercise1 excercise2 ... exerciseN
EXECUTABLES=$(addsuffix _solver, $(EXECUTABLES_BASE))
MAIN_OBJECT=main.o
OTHER_OBJECTS=solver.o experimentation.o test.o
OTHER_OBJECTS_DIR=$(foreach exe,$(EXECUTABLES_BASE),$(addprefix $(exe)/,$(OTHER_OBJECTS)))

# framework variables
FRAMEWORK_DIR=framework/
FRAMEWORK_FOLDERS=experiments experiments/input structures utils
FRAMEWORK_EXPERIMENTS_HEADERS=experiment.h incremental_experiment.h experiment_suite.h \
                              incremental_experiment_input.h incremental_experiment_input_int.h
FRAMEWORK_STRUCTURES_HEADERS=graph.h adj_list_graph.h
FRAMEWORK_UTILS_HEADERS=chronometer.h
FRAMEWORK_OBJECTS=utils/chronometer.o experiments/experiment_suite.o
FRAMEWORK_OBJECTS_DIR=$(addprefix $(FRAMEWORK_DIR),$(FRAMEWORK_OBJECTS))
FRAMEWORK_TEST_OBJECT=$(FRAMEWORK_DIR)test.o
FRAMEWORK_TEST_EXECUTABLE=$(FRAMEWORK_DIR)test_framework

VPATH=$(addprefix $(FRAMEWORK_DIR),$(FRAMEWORK_FOLDERS))

# targets that aren't file names
.PHONY: all clean test

all: $(EXECUTABLES)

clean:
	rm -rf $(EXECUTABLES) $(MAIN_OBJECT) $(addsuffix /*.o,$(EXECUTABLES_BASE)) \
           $(FRAMEWORK_TEST_EXECUTABLE) $(FRAMEWORK_TEST_OBJECT) $(FRAMEWORK_OBJECTS_DIR)

test: $(FRAMEWORK_TEST_EXECUTABLE)

# any change to the framework or the test header forces rebuilding
$(FRAMEWORK_TEST_OBJECT): $(subst .o,.h,$(FRAMEWORK_TEST_OBJECT)) \
                $(FRAMEWORK_UTILS_HEADERS) $(FRAMEWORK_STRUCTURES_HEADERS) $(FRAMEWORK_EXPERIMENTS_HEADERS)

$(FRAMEWORK_TEST_EXECUTABLE): $(FRAMEWORK_OBJECTS_DIR) $(FRAMEWORK_TEST_OBJECT)
	$(CC) $(CFLAGS) -o $@ $^

$(MAIN_OBJECT): $(subst .o,.h,$(MAIN_OBJECT))

.SECONDEXPANSION:

# any change to the framework or the exercise header forces rebuilding
$(OTHER_OBJECTS_DIR): $$(dir $$@)/$$(subst /,.h,$$(dir $$@)) \
                      $(FRAMEWORK_UTILS_HEADERS) $(FRAMEWORK_STRUCTURES_HEADERS) $(FRAMEWORK_EXPERIMENTS_HEADERS)

$(EXECUTABLES): $(MAIN_OBJECT) $(FRAMEWORK_OBJECTS_DIR) \
                $$(addprefix $$(subst _solver,,$$@)/,$(OTHER_OBJECTS))
	$(CC) $(CFLAGS) -o $@ $^
