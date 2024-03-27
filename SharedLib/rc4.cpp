#include "rc4.h"
#include <algorithm>

RC4::RC4() {
    i = 0;
    j = 0;
    for (int i = 0; i < 256; ++i) {
        S[i] = i;
    }
}

int RC4::key(char* key, int len) {
    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + S[i] + static_cast<char>(key[i % len])) % 256;
        std::swap(S[i], S[j]);
    }
    return 1;
}

char RC4::prga() {
    i = (i + 1) % 256;
    j = (j + S[i]) % 256;
    std::swap(S[i], S[j]);
    return S[(S[i] + S[j]) % 256];
}

void RC4::reset() {
    i = 0;
    j = 0;
    for (int i = 0; i < 256; ++i) {
        S[i] = i;
    }
}