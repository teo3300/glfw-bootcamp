target	:= main

CC			:= gcc
CFLAG		:= -O2 -Wall -Werror -m64
DEFINES		:= LOG_LEVEL=LOG_LEVEL_DEBUG
LIBRARIES	:= pthread GL glfw dl
PKG 		:= 

SRC := src
LIB := lib
OBJ := obj
BLD := build

MAKEFLAGS += --no-print-directory

#------------------------------------------------------------------------------#

#	suppress make printing directory while calling other makefiles
#	MAKEFLAGS += -no-print-directory

#	include packages
#CFLAG += $(shell pkg-config --cflags --libs $(PKG))
#	include libraries
CFLAG +=-I$(LIB) $(LIBRARIES:%=-l%) $(DEFINES:%=-D%)

#------------------------------------------------------------------------------#

#	set default target
target := $(BLD)/$(target)
default: $(target)

#------------------------------------------------------------------------------#

BASE	:= $(SRC) $(LIB) $(OBJ) $(BLD)
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
	@make default	$(MAKEFLAGS) > /dev/null
	@echo DONE

clean:
	@rm -rf $(OBJ)
	@rm -rf $(BLD)

#------------------------------------------------------------------------------#

#	generate dependencies alongside objects
DEPS := $(shell find $(OBJ) -name "*.d" 2> /dev/null)
-include $(DEPS)
DEPFLAG_O = -MMD -MF $(@:.o=.d) -MT $@
#------------------------------------------------------------------------------#

#	build target with all objects
$(target): $(DEPS:.d=.o)
	$(CC) -o $@ $^ $(CFLAG)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -o $@ -c $< $(CFLAG) $(DEPFLAG_O)
