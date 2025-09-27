#!/bin/bash

clang++ -o2 -g ffdb.cpp -o ffdb

# Remove -g if debugger not needed
# Will need to create an interactive script.