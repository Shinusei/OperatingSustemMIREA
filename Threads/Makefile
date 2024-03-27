
#launch without library
#test: test.cpp rc4.cpp shared_library.cpp
#	gcc -lstdc++ test.cpp rc4.cpp shared_library.cpp -o test -I.
matrix: matrix.cpp clean
	g++  matrix.cpp

changed: matrix.cpp clean
	g++ -DC=3 -DX=3 matrix.cpp

clean:
	rm -f *.o *~ matrix.out


#launch by: LD_LIBRARY_PATH=. ./test