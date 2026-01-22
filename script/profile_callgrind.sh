#!/bin/bash
# Profile build/debug/main with Valgrind Callgrind and open results in KCachegrind

set -e

if [ ! -f "build/debug/main" ]; then
  echo "Error: build/debug/main not found. Build your project first."
  exit 1
fi

# Run main with Valgrind Callgrind, passing all arguments to main
valgrind --tool=callgrind build/debug/main "$@"

# Find the latest callgrind output file
CALLGRIND_OUT=$(ls -t callgrind.out.* | head -n1)

if [ -z "$CALLGRIND_OUT" ]; then
  echo "Error: No callgrind output file found."
  exit 2
fi

# Open in KCachegrind
kcachegrind "$CALLGRIND_OUT"
