#    g++ -c -o lib.o rc4.cpp
#	g++ -shared -o librc4.so lib.o
# Определим имена файлов

# Обязательно прописать export LD_LIBRARY_PATH=$PWD
make:
	g++ -Wall -Wextra -O2 -c -o rc4.o rc4.cpp -fPIC
	g++ -Wall -Wextra -O2 -shared -o rc4.so rc4.o
	g++ -Llib/ -Wall -Wextra -O2 -o main main.cpp rc4.so

# Чистка
clean:
	rm -f *.o *.so
