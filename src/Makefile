# suffixes used in implicit rules (first line clears default ones)
.SUFFIXES:
.SUFFIXES: .cpp .o

# flags used in implicit rules
CC=g++
CPPFLAGS=-g -Wall -O2
CXXFLAGS=-std=c++11

# instance generator variables
INSTANCE_GENERATOR_EXECUTABLE=instance_generator
INSTANCE_GENERATOR_OBJECT=$(addsuffix .o, $(INSTANCE_GENERATOR_EXECUTABLE))

# excercise variables
EXECUTABLES_BASE=ej2 ej3 ej4 ej5 ej6 ej7

EXECUTABLES=$(addsuffix _solver, $(EXECUTABLES_BASE))
MAIN_OBJECT=main.o
OTHER_OBJECTS=solver.o experimentation.o test.o
OTHER_OBJECTS_DIR=$(foreach exe,$(EXECUTABLES_BASE),$(addprefix $(exe)/,$(OTHER_OBJECTS)))

# framework variables
FRAMEWORK_DIR=framework
FRAMEWORK_FOLDERS=experiments experiments/input structures utils
FRAMEWORK_EXPERIMENTS_HEADERS=experiment.h incremental_experiment.h experiment_suite.h \
                              incremental_experiment_input.h incremental_experiment_input_int.h \
                              incremental_experiment_input_float.h quality_experiment.h
FRAMEWORK_STRUCTURES_HEADERS=graph.h adj_list_graph.h
FRAMEWORK_UTILS_HEADERS=chronometer.h graph_factory.h io.h \
                        element_generator.h element_generator_int.h
FRAMEWORK_OBJECTS=utils/chronometer.o utils/element_generator_int.o \
                  utils/io.o experiments/quality_experiment.o experiments/experiment_suite.o
FRAMEWORK_OBJECTS_DIR=$(addprefix $(FRAMEWORK_DIR)/,$(FRAMEWORK_OBJECTS))
FRAMEWORK_OTHER_OBJECTS=test.o
FRAMEWORK_OTHER_OBJECTS_DIR=$(addprefix $(FRAMEWORK_DIR)/,$(FRAMEWORK_OTHER_OBJECTS))
FRAMEWORK_MAIN_OBJECT=$(FRAMEWORK_DIR)/main.o
FRAMEWORK_EXECUTABLE=$(FRAMEWORK_DIR)/main

# exact algorithm variables
EXACT_DIR=exact
EXACT_HEADER=exact.h
EXACT_OBJECTS=backtracking.o cograph_vs_complete.o
EXACT_OBJECTS_DIR=$(addprefix $(EXACT_DIR)/,$(EXACT_OBJECTS))

# heuristics variables
HEURISTICS_DIR=heuristics
HEURISTICS_HEADER=heuristics.h
HEURISTICS_OBJECTS=greedy.o local_search.o tabu.o
HEURISTICS_OBJECTS_DIR=$(addprefix $(HEURISTICS_DIR)/,$(HEURISTICS_OBJECTS))

VPATH=$(addprefix $(FRAMEWORK_DIR)/,$(FRAMEWORK_FOLDERS)) $(EXACT_DIR) $(HEURISTICS_DIR)

# targets that aren't file names
.PHONY: all clean test

all: $(EXECUTABLES)

clean:
	rm -rf $(EXECUTABLES) $(MAIN_OBJECT) $(addsuffix /*.o,$(EXECUTABLES_BASE)) \
           $(FRAMEWORK_EXECUTABLE) $(FRAMEWORK_MAIN_OBJECT) $(FRAMEWORK_OBJECTS_DIR) \
           $(FRAMEWORK_OTHER_OBJECTS_DIR) $(EXACT_OBJECTS_DIR) $(HEURISTICS_OBJECTS_DIR) \
           $(INSTANCE_GENERATOR_EXECUTABLE) $(INSTANCE_GENERATOR_OBJECT)

framework: $(FRAMEWORK_EXECUTABLE)

instance-generator: $(INSTANCE_GENERATOR_EXECUTABLE)

# any change to the framework or the test header forces rebuilding
$(FRAMEWORK_MAIN_OBJECT): $(subst .o,.h,$(FRAMEWORK_MAIN_OBJECT)) \
                          $(FRAMEWORK_UTILS_HEADERS) $(FRAMEWORK_STRUCTURES_HEADERS) \
                          $(FRAMEWORK_EXPERIMENTS_HEADERS)

$(FRAMEWORK_OTHER_OBJECTS_DIR): $(FRAMEWORK_UTILS_HEADERS) $(FRAMEWORK_STRUCTURES_HEADERS) \
                                $(FRAMEWORK_EXPERIMENTS_HEADERS)

$(FRAMEWORK_OBJECTS_DIR): $(FRAMEWORK_UTILS_HEADERS) $(FRAMEWORK_STRUCTURES_HEADERS) \
                          $(FRAMEWORK_EXPERIMENTS_HEADERS)

$(FRAMEWORK_EXECUTABLE): $(FRAMEWORK_OBJECTS_DIR) $(FRAMEWORK_OTHER_OBJECTS_DIR) \
                         $(FRAMEWORK_MAIN_OBJECT)
	$(CC) $(CFLAGS) -o $@ $^

$(INSTANCE_GENERATOR_EXECUTABLE): $(INSTANCE_GENERATOR_OBJECT) $(FRAMEWORK_OBJECTS_DIR) $(EXACT_OBJECTS_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(MAIN_OBJECT): $(subst .o,.h,$(MAIN_OBJECT))

$(EXACT_OBJECTS_DIR): $(EXACT_HEADER) $(subst .o,.h,$(MAIN_OBJECT))

$(HEURISTICS_OBJECTS_DIR): $(HEURISTICS_HEADER)

$(INSTANCE_GENERATOR_OBJECT): $(subst .o,.h,$(MAIN_OBJECT))

.SECONDEXPANSION:

# any change to the framework or the exercise header forces rebuilding
$(OTHER_OBJECTS_DIR): $$(dir $$@)/$$(subst /,.h,$$(dir $$@)) \
                      $(FRAMEWORK_UTILS_HEADERS) $(FRAMEWORK_STRUCTURES_HEADERS) $(FRAMEWORK_EXPERIMENTS_HEADERS)

$(EXECUTABLES): $(MAIN_OBJECT) $(FRAMEWORK_OBJECTS_DIR) $(EXACT_OBJECTS_DIR) $(HEURISTICS_OBJECTS_DIR) \
                $$(addprefix $$(subst _solver,,$$@)/,$(OTHER_OBJECTS))
	$(CC) $(CXXFLAGS) -o $@ $^
