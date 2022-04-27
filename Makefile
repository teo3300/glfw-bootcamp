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
OBJECTS := $(if $(OBJECTS),$(OBJECTS),_do_nothing)
STRUCT	:= $(sort $(dir $(OBJECTS)))

base:
	@echo "> making project base folders..."
	@mkdir $(BASE) 2> /dev/null || :

struct:
	@echo "> replicating project structure..."
	@mkdir $(STRUCT) 2> /dev/null || :

objects:
	@echo "> making objects..."
	@make $(OBJECTS) $(MAKEFLAGS)

project:
	@echo "> making structure..."
	@make base		$(MAKEFLAGS)
	@make struct	$(MAKEFLAGS)
	@echo "> compiling..."
	@make objects	$(MAKEFLAGS) > /dev/null
	@make $(target)	$(MAKEFLAGS) > /dev/null

clean:
	@echo "> cleaning project..."
	@rm -rf $(OBJ)
	@rm -rf $(BLD)
	
rebuild:
	@echo "> rebuilding project..."
	@make clean 	$(MAKEFLAGS)
	@make project	$(MAKEFLAGS)

_do_nothing:
	@true
#------------------------------------------------------------------------------#

#	generate dependencies alongside objects
DEPS := $(shell find $(OBJ) -name "*.d" 2> /dev/null)
-include $(DEPS)
DEPFLAG_O = -MMD -MF $(@:.o=.d) -MT $@
#------------------------------------------------------------------------------#

#	build target with all objects
$(target): $(DEPS:.d=.o) $(DEFDEPS)
	@echo "building target: $@"
	$(CC) -o $@ $(filter-out $(DEFDEPS), $^) $(CFLAG)

$(OBJ)/%.o: $(SRC)/%.c $(DEFDEPS)
	@echo "building object: $@"
	$(CC) -o $@ -c $(filter-out $(DEFDEPS), $<) $(CFLAG) $(DEPFLAG_O)

#------------------------------------------------------------------------------#

#	testing
test:
	valgrind $(TESTFLAGS) ./build/main