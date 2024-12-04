#!/bin/bash

g++ -g -Wall -Wextra $1Test.cpp $2 -o $1

if [ $? -eq 0 ]
then
    ./$1
    rm ./$1
fi

if [ $? -eq 0 ]
then
    echo PASSED
fi