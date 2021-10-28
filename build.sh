#!/bin/bash

R='\033[0;31m' # Red
G='\033[0;32m' # Green
B='\033[0;34m' # Blue
LG='\033[0;37m' # Light Grey
NC='\033[0m'   # No Color

FILE="sbre_template"

# Clear the console and go to the build dir
clear
cd build

# Check if an exe exist, if it does delete it
if [[ -f "$FILE" ]]; then
	printf "${B}Deleted the old exetuable.${B}\n"
	rm sbre_template
fi

# Compile the program
cmake --build .

# If the compilation succeeded run the program, otherwise abort
if [[ -f "$FILE" ]]; then
	printf "${G}Compilation succeeded. Executing the program.${NC}\n"
	printf "${LG}=============================================${NC}\n"
	./sbre_template
else
	printf "${R}Compilation failed.${NC}\n"
fi
