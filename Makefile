# a proper simple Makefile

# set the  compiler variable
CC := clang 

# set the compiler flags var
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm


# add header files here
HDRS := defs.h common.h structs.h


# add source files here
SRCS := main.c

# generate name of object files
OBJS := $(SRCS:.c=.o)

# name of executable
EXEC := myPong

# default recipe
all: $(EXEC)

# recipe for building the final exe
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building the object files
#$(OBJS): $(@:.o=.c) $(HDRS) Makefile
#	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)



# recipe to clean the workspace
clean: 
	rm -f $(EXEC) $(OBJS)


.PHONY: all clean

