#!/bin/bash
set -e  # exit with none zero

# test files have ending of CRLF, so need to truncate the string read from them
# use ${str%?}

# compile the cpp 
g++ -o main check_brackets.cpp -lm 

inputs=$(ls tests | grep -v .a)
for f in ${inputs}
do
  should=$(cat tests/${f}.a)
  real=$(./main < tests/${f})
  if [ "${should%?}" != "${real}" ]; then  # use %? to filter out the last character
    echo "tests/${f} -> |${real}||, should be |||${should}|"
    exit 1
  fi
done
