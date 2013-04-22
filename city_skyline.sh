#!/bin/bash

# ADHOC_LIB_PATH=/home/mark/local/boost_1_52_0/lib:/home/mark/local/gcc-4.7.1/lib ./city_skyline.sh

LD_LIBRARY_PATH=$ADHOC_LIB_PATH:$LD_LIBRARY_PATH

./city_skyline
