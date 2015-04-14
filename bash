#!/bin/bash
yacc -d -v $1.y
lex $1.l
gcc lex.yy.c y.tab.c -ly -ll -o $1
./$1
