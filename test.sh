
touch result result2 result3 result4 total2 total
for element in TESTS/*
do
	./ft_nm $element > result
	nm $element > result2
	./ft_otool $element > result3
	otool -t $element > result4
	diff result result2 > total
	diff result result2 > total2
	if [ -s "total" ]
	then
		printf "\033[31m"
		cat $element
		printf "\033[0m\n"
		cat total
	fi
	if [ -s "total2" ]
	then
		printf "\033[31m"
		cat $element
		printf "\033[0m\n"
		cat total
	fi
done