#!/bin/bash

#-----------------------------------------------------------------------------------------------------------------------------
# 
# The Script to compile and install the Denial-of-Service implementation
# Author: Giovani Ferreira
#
#-----------------------------------------------------------------------------------------------------------------------------

# The directory to store the binary file 
DIR="/usr/local/bin/"

echo ":: Warning: Execute this script in the root directory of DoS project"

if [ "$EUID" -ne 0 ]; then 
    echo ":: Error: Please run as superuser"
    exit
fi

echo "==> Compiling the source"
make

echo "==> Installing denial to $DIR"
cp ./build/denial.bin ./build/denial
mv ./build/denial $DIR

if [ $? -eq 0 ]; then
    echo "==> Successfully installed denial"
else
    echo ":: Error: Failed to install denial"
fi
