#include "shared_library.h"
#include "rc4.h"

RC4 rc4;

int set_key(char* key, int len) {
    return rc4.key(reinterpret_cast<char*>(key), len);
}

char g(void) {
    return rc4.prga();
}

void fin(void) {
    rc4.reset();
}