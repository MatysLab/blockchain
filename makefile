# === Compiler settings ===
CC ?= gcc
CFLAGS ?= -Wall -Wextra -pedantic -std=c11 -Iincludes -DLINUX_BUILD

# === Build directories ===
BUILDDIR ?= dist
OBJDIR := $(BUILDDIR)/obj
DIST_LINUX := $(BUILDDIR)/linux
TARGET ?= launcher

# === Source files ===
SRCS := $(shell find src -name '*.c')
OBJS := $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))

# === Default target ===
.PHONY: all clean
all: $(DIST_LINUX)/$(TARGET)

# === Compile object files ===
$(OBJDIR)/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# === Link executable ===
$(DIST_LINUX)/$(TARGET): $(OBJS)
	mkdir -p $(DIST_LINUX)
	$(CC) $(OBJS) -o $@

# === Clean ===
clean:
	rm -rf $(BUILDDIR)
