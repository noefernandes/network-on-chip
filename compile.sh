#!/bin/bash


export SYSTEMC_HOME=/home/noe/systemc-2.3.1a

g++ -I. -std=c++11 -o roteador src/main.cpp -I include/  -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -lsystemc -lm
