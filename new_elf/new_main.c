#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

void __attribute__((section(".upx"))) hello_world() {
    printf("Hello, world\n");
}

extern char upx_end;
extern char upx_start;


void rc4_init(unsigned char *key, unsigned char *state, size_t keylen) {
    unsigned char j = 0;
    for (size_t i = 0; i < 256; i++) {
        state[i] = i;
    }
    for (size_t i = 0; i < 256; i++) {
        j = (j + state[i] + key[i % keylen]) % 256;
        unsigned char temp = state[i];
        state[i] = state[j];
        state[j] = temp;
    }
}


unsigned char rc4_output(unsigned char *state, size_t *i, size_t *j) {
    *i = (*i + 1) % 256;
    *j = (*j + state[*i]) % 256;
    unsigned char temp = state[*i];
    state[*i] = state[*j];
    state[*j] = temp;
    return state[(state[*i] + state[*j]) % 256];
}

int main(int argc, char *argv[]) {
    unsigned char text[] = "Hello, world";
    unsigned char key[] = "IKBO_25_22";
    unsigned char state[256];
    size_t keylen = strlen(key);
    rc4_init(key, state, keylen);

    size_t i = 0, j = 0;

    char *ptr = &upx_start;
    while (ptr != &upx_end) {
        unsigned char decrypted_byte = rc4_output(state, &i, &j);
        *ptr ^= decrypted_byte;
        ptr++;
    }
    
    unsigned char decrypted_string[100];
    
    strncpy(decrypted_string, &upx_start, sizeof(decrypted_string));
    decrypted_string[sizeof(decrypted_string) - 1] = '\0';
    
    printf("Decoded text: ", decrypted_string);
    hello_world();

    return 0;
}
