#--------------------------------------------------------------------------------------
# ANNOTATION
#--------------------------------------------------------------------------------------

# Makefile for task2
# version 1.0
#		author: Starchenko Ivan

#--------------------------------------------------------------------------------------
# SETTINGS
#--------------------------------------------------------------------------------------

# project name
PROJECT = task2

# choose release or debug mode
LAUNCH_MD = debug

Q = @  
E = $(Q) echo

# source
BIN = $(PROJECT).out
HDR =              graph.h graph_settings.h queue.h queue_settings.h parser_stdio.h
SRC = $(PROJECT).c graph.c                  queue.c                  parser_stdio.c
OBJ = $(SRC:%.c=%.o)

# compiler settings
CXX      = gcc 
WARNINGS = -Wall -Wextra
CXXFLAGS = 

DBG_MD = -g3 -O0
RLS_MD = -g0 -O2


ifeq ($(LAUNCH_MODE),debug)
	CXXFLAGS += $(DBG_MD)
else
	CXXFLAGS += $(RLS_MD)
endif

#--------------------------------------------------------------------------------------
# RULES
#--------------------------------------------------------------------------------------

default: $(BIN)

#
## launch
launch: $(BIN)
	$(E) "    LAUNCH:      " $(BIN)
	$(Q) ./$(BIN)

#
## linking
$(BIN): $(OBJ)
	$(E) "    LINK:        " $@
	$(Q) $(CXX) $(WARNINGS)  $^ -o $@ 

#
## compiling
%.o: %.c
	$(E) "    C:           " $@
	$(Q) ${CXX} -c $(DBG_MD) $< -o $@

task.o: task.c

#
## debug
strace: $(BIN)
	$(E) "    LAUNCH(DBG): " $(BIN)
	$(Q) strace $(BIN)

#
## additional features
clean:
	$(E) "  CLEAN"
	$(Q) rm *.o $(BIN) *.dot *.jpeg *.txt Outs/*

rebuild: clean default

#
## gdb
gdb: $(BIN)
	$(E) "    LAUNCH(DBG): " $(BIN)
	$(Q) gdb $(BIN)
