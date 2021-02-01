#!/bin/bash

assert() {
    expected="$1"
    input="$2"
    ./pcc "$input" > tmp.s
    cc -o tmp tmp.s
    ./tmp
    actual="$?"
    
    if [ "$actual" == "$expected" ]; then
        echo "$input => $actual"
    else
        echo "$input => $expected, but got $actual"
        exit 1
    fi 
}

assert 1 '2-1'
assert 47 '5+6*7'
assert 8 '5+3'
assert 5 '(2+4)-1'
assert 13 '6+(6+1)'
assert 60 '30+40-10'
assert 12 '(2+1)*(3+1)'
assert 43 '-7+50/1'

echo "OK"
