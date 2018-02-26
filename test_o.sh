#!/bin/bash

if [ -n "$1" ]
then
	make;
	./ft_otool $1 > test1;
	otool -t $1 > test2;
	diff test1 test2 > total;
else
	printf "usage: sh test.sh [file]\n"
fi