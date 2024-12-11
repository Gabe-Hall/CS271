# Makefile for Hack Assembler

# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -I.

# Linker Flags
LDFLAGS =

# Source Files
SRCS = main.c parser.c symtable.c error.c

# Object Files
OBJS = $(SRCS:.c=.o)

# Executable Name
TARGET = assembler

# Default Target
all: $(TARGET)

# Link Object Files to Create Executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile Source Files into Object Files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Up Generated Files
clean:
	rm -f $(OBJS) $(TARGET) *~ 
