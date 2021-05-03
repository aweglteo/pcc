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

assert 1 '1;'
assert 1 '3-2;'
assert 0 '0==1;'
assert 1 '5==5;'
assert 1 '10>=5;'
assert 0 '8>=10;'
assert 1 '1>0;'
assert 1 '9<19;'
assert 1 '6>-1;'
assert 47 '5+6*7;'
assert 5 '(2+4)-1;'
assert 13 '6+(6+1);'
assert 60 '30 + 40-10;'
assert 12 '(2+1)*(3+1);'
assert 10 '- - +10;'
assert 10 '-10+20;'
assert 10 '// sample comment
9+1;'
assert 4 '5;1+2;1+3;'
assert 4 '4+2;10-6;'
assert 3 'a=3; a;'
assert 8 'a=3; z=5; a+z;'
assert 6 'a=b=3; a+b;'
assert 10 'a=12; b=2; c=a-b; c;'

echo "OK"
