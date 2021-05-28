#!/bin/bash

# create 3rd party libs dir if non exists
mkdir -p lib/
cd lib/

# fetch the catch2 unit test framework
wget https://raw.githubusercontent.com/catchorg/Catch2/v2.x/single_include/catch2/catch.hpp
