
t: mtest test









mtest: mytest.cpp Array.hpp
	g++ -std=c++1z -g -Wall -Wextra -pedantic -o mytest mytest.cpp

mrun: clear mtest
	./mytest

mclang: mytest.cpp Array.hpp 
	clang++ -std=c++1z -g -Wall -Wextra -pedantic -o mytest mytest.cpp

mval: mytest.cpp Array.hpp clear
	valgrind -v --track-origins=yes --leak-check=full \
			--show-leak-kinds=all ./mytest
mgdb: clear
	gdb mytest







 



test: test_Array-new.cpp
	g++ -std=c++1z -g -Wall -Wextra -pedantic -o test_Array-new test_Array-new.cpp

run: clear test 
	./test_Array-new

clang: test_Array-new.cpp Array.hpp
	clang++ -std=c++1z -g -Wall -Wextra -pedantic -o test_Array-new test_Array-new.cpp

val: test_Array-new Array.hpp clear
	valgrind -v --track-origins=yes --leak-check=full \
			--show-leak-kinds=all ./test_Array-new
gdb: clear
	gdb test_Array-new






clean:
	rm -f *.o test_Array-new mytest

clear:
	clear && clear
	


