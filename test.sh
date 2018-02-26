#!/bin/bash

if [ -n "$1" ]
then
	make;
	./ft_nm $1 > test1;
	nm $1 > test2;
	diff test1 test2 > total;
else
	printf "usage: sh test.sh [file]\n"
fi