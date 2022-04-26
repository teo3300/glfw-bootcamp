target	:= main

CC			:= gcc
CFLAG		:= -O2 -Wall -Werror -g # -m64
DEFINES		:= LOG_LEVEL=LOG_LEVEL_DEBUG
LIBRARIES	:= pthread GL glfw dl m
PKG 		:= 

SRC := src
OBJ := obj
BLD := build

DEFDEPS := Makefile

MAKEFLAGS += --no-print-directory

TESTFLAGS = --leak-check=yes

#------------------------------------------------------------------------------#

#	suppress make printing directory while calling other makefiles
#	MAKEFLAGS += -no-print-directory

#	include packages
#CFLAG += $(shell pkg-config --cflags --libs $(PKG))
#	include libraries
CFLAG +=-I$(SRC) $(LIBRARIES:%=-l%) $(DEFINES:%=-D%)

#------------------------------------------------------------------------------#

#	set default target
target := $(BLD)/$(target)
default: project

#------------------------------------------------------------------------------#

BASE	:= $(SRC) $(OBJ) $(BLD)
OBJECTS := $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(shell find $(SRC) -name "*.c"))
STRUCT	:= $(sort $(dir $(OBJECTS)))

base:
	@echo -n "making project base folders..."
	@mkdir $(BASE) 2> /dev/null || :
	@echo DONE

struct:
	@echo -n "replicating project structure..."
	@mkdir $(STRUCT) 2> /dev/null || :
	@echo DONE

objects:
	@make $(OBJECTS) $(MAKEFLAGS) > /dev/null

project:
	@make base		$(MAKEFLAGS)
	@make struct	$(MAKEFLAGS)
	@echo -n "compiling..."
	@make objects	$(MAKEFLAGS)
	@make $(target)	$(MAKEFLAGS) > /dev/null
	@echo DONE

clean:
	@rm -rf $(OBJ)
	@rm -rf $(BLD)
	
rebuild:
	@make clean 	$(MAKEFLAGS)
	@make project	$(MAKEFLAGS)
#------------------------------------------------------------------------------#

#	generate dependencies alongside objects
DEPS := $(shell find $(OBJ) -name "*.d" 2> /dev/null)
-include $(DEPS)
DEPFLAG_O = -MMD -MF $(@:.o=.d) -MT $@
#------------------------------------------------------------------------------#

#	build target with all objects
$(target): $(DEPS:.d=.o) $(DEFDEPS)
	$(CC) -o $@ $(filter-out $(DEFDEPS), $^) $(CFLAG)

$(OBJ)/%.o: $(SRC)/%.c $(DEFDEPS)
	$(CC) -o $@ -c $(filter-out $(DEFDEPS), $<) $(CFLAG) $(DEPFLAG_O)

#------------------------------------------------------------------------------#

#	testing
test:
	valgrind $(TESTFLAGS) ./build/main