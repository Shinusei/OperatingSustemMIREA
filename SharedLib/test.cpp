#include <iostream>
#include <vector>
#include "shared_library.h"

int main() {
    char key[] = "secret_key";
    char data[] = "Hello, World!";
    std::vector<char> encrypted;

    set_key(key, sizeof(key) - 1);

    for (int i = 0; i < sizeof(data) - 1; ++i) {
        encrypted.push_back(g() ^ data[i]);
    }

    for (auto &&i : encrypted)
    {
        std::cout << i;
    }

    fin();

    return 0;
}