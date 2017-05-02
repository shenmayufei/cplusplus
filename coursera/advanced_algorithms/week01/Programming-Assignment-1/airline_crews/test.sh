#!/bin/bash
set -e  # exit with none zero

# test files have ending of CRLF, so need to truncate the string read from them
# use ${str%?}

# compile the cpp 
g++ -o main airline_crews.cpp -lm 

inputs=$(ls tests | grep -v .a)
for f in ${inputs}
do
  should=$(cat tests/${f}.a | tr '\n' ' ')
  real=$(./main < tests/${f})
  echo "tests/${f}"
  echo "${should}"
  echo "${real}"
  echo ""
done
