#--------------------------------------------------------------------------------------
# ANNOTATION
#--------------------------------------------------------------------------------------

# Makefile for task2
# version 1.2
#		author: Starchenko Ivan

#--------------------------------------------------------------------------------------
# SETTINGS
#--------------------------------------------------------------------------------------

# project name
PROJECT = task2

# choose release, debug, fastest mode
LAUNCH_MD = debug

Q = @  
E = $(Q) echo

# source
BIN = $(PROJECT).out
HDR =              graph.h graph_settings.h queue.h queue_settings.h parser_stdio.h
SRC = $(PROJECT).c graph.c                  queue.c                  parser_stdio.c
OBJ = $(SRC:%.c=%.o)

DOXYFILE = Doxyfile

# compiler settings
CXX      = gcc 
WARNINGS = -Wall -Wextra -std=c11
CXXFLAGS = 

DBG_MD   = -g3 -O0
RLS_MD   = -g0 -O3
FSTST_MD = $(RLS_MD) -flto -fwhole-program

ifeq ($(LAUNCH_MODE),debug)
	CXXFLAGS += $(DBG_MD)
else ifeq ($(LAUNCH_MODE), release)
	CXXFLAGS += $(RLS_MD)
else
	CXXFLAGS += $(FSTST_MD)
	WARNINGS += $(FSTST_MD)
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
	$(Q) ${CXX} -c $(CXXFLAGS) $< -o $@

task.o: task.c

#
## debug
strace: $(BIN)
	$(E) "    LAUNCH(DBG): " $(BIN)
	$(Q) strace $(BIN)

#
## additional features
clean:
	$(E) "    CLEAN"
	$(Q) rm -rf *.o $(BIN) *.dot *.jpeg *.txt Outs/* html 2> /dev/null

rebuild: clean default

docs:
	$(E) "    DOXYGEN"
	doxygen $(DOXYFILE)

#
## gdb
gdb: $(BIN)
	$(E) "    LAUNCH(DBG): " $(BIN)
	$(Q) gdb $(BIN)
