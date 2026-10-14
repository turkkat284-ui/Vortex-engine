# Vortex Engine Build System

CC = gcc
RUSTC = rustc
GO = go

CORE_DIR = core/src
RUST_CORE_DIR = core/rust-core
CMD_DIR = cmd/vortex

# Build flags
CFLAGS = -O3 -Wall -Icore/include
RUSTFLAGS = -C opt-level=3

all: rust-core core cli

core:
	$(CC) $(CFLAGS) -c $(CORE_DIR)/*.c -o $(CORE_DIR)/core.o
	$(CC) $(CFLAGS) $(CORE_DIR)/core.o -L$(RUST_CORE_DIR)/target/release -lrust_core -o core/vortex_core_native

rust-core:
	cd $(RUST_CORE_DIR) && cargo build --release

cli:
	cd $(CMD_DIR) && $(GO) build -o ../../../vortex main.go

clean:
	rm -f core/vortex_core_native core/src/*.o
	cd $(RUST_CORE_DIR) && cargo clean
	rm -f vortex
