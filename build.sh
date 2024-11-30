#!/bin/bash

SRC="main.cpp"
OUTPUT="svd"

EIGEN_PATH="/usr/include/eigen3"  # Modify if needed
OPENCV_FLAGS=$(pkg-config --cflags --libs opencv4)  # Modify if you're using a different version

echo "Compiling project..."
clang++ -std=c++20 $SRC -o $OUTPUT -I$EIGEN_PATH $OPENCV_FLAGS -Wno-deprecated -O3

if [ $? -eq 0 ]; then
    echo "Compilation successful!"
    echo "Running the project..."
else
    echo "Compilation failed!"
fi
