# === Compiler settings ===
CC ?= clang
CFLAGS ?= -Wall -Wextra -pedantic -std=c11

# === Build directories ===
BUILDDIR ?= dist
OBJDIR := $(BUILDDIR)/obj
DIST_LINUX := $(BUILDDIR)/linux
DIST_WINDOWS := $(BUILDDIR)/windows
DIST_MAC := $(BUILDDIR)/macos
TARGET ?= launcher

# === Cross-compilers ===
WCC ?= x86_64-w64-mingw32-gcc  # Windows cross-compiler
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    OSX_CC ?= clang
endif

# === Source files ===
SRCS := $(wildcard *.c src/*.c)
OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# === Build flags per platform ===
LINUX_FLAGS := $(CFLAGS) -DLINUX_BUILD
WINDOWS_FLAGS := $(CFLAGS) -DWINDOWS_BUILD
MAC_FLAGS := $(CFLAGS) -DMAC_BUILD

# === Default target ===
.PHONY: all clean help
all: linux windows mac

# === Linux build ===
linux: $(DIST_LINUX)/$(TARGET)

$(DIST_LINUX)/$(TARGET): $(SRCS)
	mkdir -p $(DIST_LINUX)
	$(CC) $(LINUX_FLAGS) -o $@ $(SRCS)

# === Windows build ===
windows: $(DIST_WINDOWS)/$(TARGET).exe

$(DIST_WINDOWS)/$(TARGET).exe: $(SRCS)
	mkdir -p $(DIST_WINDOWS)
	@if command -v $(WCC) >/dev/null 2>&1; then \
		$(WCC) $(WINDOWS_FLAGS) -o $@ $(SRCS); \
	else \
		printf "Skipping Windows build: $(WCC) not found\n"; \
	fi

# === macOS build (only builds if on mac or OSX_CC is set) ===
mac: $(DIST_MAC)/$(TARGET)

$(DIST_MAC)/$(TARGET): $(SRCS)
	mkdir -p $(DIST_MAC)
	@if [ "$(UNAME_S)" = "Darwin" ] || [ -n "$(OSX_CC)" ]; then \
		$(OSX_CC) $(MAC_FLAGS) -o $@ $(SRCS); \
	else \
		printf "Skipping macOS build: not on macOS and no cross-compiler set\n"; \
	fi

# === Clean ===
clean:
	rm -rf $(BUILDDIR)

# === Help ===
help:
	@printf "Targets:\n  all - build Linux, Windows, macOS\n  linux - build Linux\n  windows - build Windows\n  mac - build macOS\n  clean - remove build artifacts\n"
