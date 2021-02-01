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

assert 0 0
assert 5 '2+4-1'
assert 13 '6+6+1'
assert 60 '30+40-10'

echo "OK"
