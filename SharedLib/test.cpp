#include <iostream>
#include <vector>
#include "shared_library.h"
#include <fstream>

int main() {
    char key[] = "secret_key";
    char data[] = "Hello, World!";
    std::vector<char> encrypted;
    set_key(key, sizeof(key) - 1);

    for (int i = 0; i < sizeof(data) - 1; ++i) {
        encrypted.push_back(g() ^ data[i]);
    }
    //std::cout << g() << '\n';
    for (auto i : encrypted)
    {
        std::cout << char(int(i)) << '\n';
    }
    fin();

    return 0;
}