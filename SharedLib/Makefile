
test: test.o libprint.so 
	gcc -lstdc++ test.cpp -L. -lprint -o test -I.

libprint.so:
	gcc -c -fPIC rc4.cpp shared_library.cpp
	gcc -shared -o libprint.so rc4.o shared_library.o

clean:
	rm *.o *.so test output.txt


#launch by: LD_LIBRARY_PATH=. ./test