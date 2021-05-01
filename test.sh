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
assert 0 '0==1'
assert 1 '5==5'
assert 1 '10>=5'
assert 0 '8>=10'
assert 1 '1>0'
assert 1 '9<19'
assert 1 '6>-1'
assert 47 '5+6*7'
assert 8 '5+3'
assert 5 '(2+4)-1'
assert 13 '6+(6+1)'
assert 60 '30 + 40-10'
assert 12 '(2+1)*(3+1)'
assert 10 '- - +10'
assert 10 '-10+20'
assert 10 '// sample comment
9+1git '

echo "OK"
