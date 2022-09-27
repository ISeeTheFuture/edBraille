#!/bin/bash

g++-10 -c ../src/brailleConv.cpp
g++-10 -c ../src/htmlDoc.cpp -I/usr/include/libxml2/
g++-10 -c ../src/main.cpp
g++-10 ./main.o ./htmlDoc.o ./brailleConv.o -o ../bin/edBraille_exe -lxml2