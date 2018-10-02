#!/bin/sh

rm -f sem_tab
g++ semantic_tableau.cpp -o sem_tab
clear
./sem_tab
