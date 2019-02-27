C_COMPILER_FLAGS = -Iinc -O2 -Wall -Wextra -std=gnu11 -ggdb
CC = clang
LD = $(CC)

LIBDIR = -Llib/linux64/ 
LIBS = -pthread -lm -ldl -lfreetype -lGL -lSDL2 -lfmod

BINFOLDER = ./bin
BINARY = test

include ./src/Makefile

all: $(BINARY)

$(BINARY): $(OBJS)
	@echo LD $(BINARY)
	$(LD) $(OBJS) -o $(BINFOLDER)/$(BINARY) $(LIBDIR) $(LIBS)

%.o: %.c
	@echo CC $<
	$(CC) $(C_COMPILER_FLAGS) -c $< -o $@

.PHONY : clean multi

multi:
	$(MAKE) -j8 all

clean:
	@echo RM $(OBJS)
	rm -rf $(OBJS)

$(V).SILENT: