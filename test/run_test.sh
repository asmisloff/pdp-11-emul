#!/bin/bash

g++ -g $1.cpp -o $1

if [ $? -eq 0 ]
then
    ./$1
    rm ./$1
fi

if [ $? -eq 0 ]
then
    echo PASSED
fi