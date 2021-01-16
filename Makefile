compile:
	g++ -g -std=c++11 -Wall -DNDEBUG *.cpp

val:
	valgrind --leak-check=full --track-origins=yes ./a.out < segel_tests/in$(v).txt > segel_tests/myout$(v).txt

valv:
	valgrind --leak-check=full --track-origins=yes -v ./a.out < segel_tests/in$(v).txt > segel_tests/myout$(v).txt

test:
	./a.out < segel_tests/in$(v).txt > segel_tests/myout$(v).txt
	diff segel_tests/out$(v).txt segel_tests/myout$(v).txt > segel_tests/mydiff$(v).txt

try:
	number=1 ; while [[ $$number -le 10 ]] ; do \
	make test v=$$number ; \
	((number = number + 1)) ; \
	done

try_val:
	number=1 ; while [[ $$number -le 10 ]] ; do \
	make val v=$$number ; \
	((number = number + 1)) ; \
	done

try_valv:
	number=1 ; while [[ $$number -le 10 ]] ; do \
	make valv v=$$number ; \
	((number = number + 1)) ; \
	done
	
make full_test:
	make try
	make try_val