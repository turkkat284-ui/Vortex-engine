#!/bin/bash

# Vortex Engine Setup & Build Script
set -e

echo "🌪️  Starting Vortex Engine Setup..."

# 1. Check Dependencies
DEPENDENCIES=("gcc" "cargo" "go" "make")
for dep in "${DEPENDENCIES[@]}"; do
    if ! command -v "$dep" &> /dev/null; then
        echo "❌ Error: $dep is not installed. Please install it and try again."
        exit 1
    fi
done
echo "✅ System dependencies verified."

# 2. Go Modules
echo "📦 Setting up Go modules..."
cd cmd/vortex
go mod tidy
cd ../..

# 3. Build Rust Core (Static Library)
echo "🦀 Building Rust Core..."
cd core/rust-core
cargo build --release
cd ../..

# 4. Build C Core & Link with Rust
echo "⚙️  Compiling C Core..."
make all

# 5. Final Go Binary Build
echo "🚀 Building final Vortex binary..."
cd cmd/vortex
# Link against the Rust static library and C core
CGO_ENABLED=1 go build -o ../../vortex main.go
cd ../..

# 6. Privileges
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "🔐 Granting network capabilities..."
    sudo setcap cap_net_raw,cap_net_admin=eip ./vortex || echo "⚠️  Could not set capabilities, run with sudo."
fi

echo "🎯 Vortex Engine successfully installed! Run it with: ./vortex"
