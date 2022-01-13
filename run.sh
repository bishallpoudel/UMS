#! /bin/bash
g++ `wx-config --cxxflags` -o myapp *.cpp `wx-config --libs` -l sqlite3
./myapp