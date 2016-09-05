#!/bin/bash
set -e  # exit with none zero

# compile the cpp 
g++ -o main check_brackets.cpp -lm 

inputs=$(ls tests | grep -v .a)
for f in ${inputs}
do
  should=$(cat tests/${f}.a)
  real=$(./main < tests/${f})
  if [ "${should}" != "${real}" ]; then
    echo "tests/${f} -> |${real}||, should be |||${should}|"
    exit 1
  fi
done
