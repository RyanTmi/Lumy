#!/bin/bash

# Cmake files
find . -type f \( -name "*.cmake" -o -name "CMakeLists.txt" \) -exec rm -f {} +

# Xcode files
# find . -type d \( -name "*.xcodeproj" -o -name "*.xcworkspace" \) -exec rm -rf {} +
