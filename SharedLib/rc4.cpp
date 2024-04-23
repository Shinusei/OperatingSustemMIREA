
#include "rc4.h"

// S-блок
std::vector<unsigned char> S(256);

// Текущий индекс в S-блоке
int i, j;

// Инициализация S-блока
void init_sbox() {
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }
}

// Перемешивание S-блока
void mix_sbox(const std::vector<unsigned char>& key, int key_len) {
    unsigned char t;
    for (int i = 0, j = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key_len]) % 256;
        t = S[i];
        S[i] = S[j];
        S[j] = t;
    }
}

// Функция генерации ключа и инициализации
int set_key(const std::vector<unsigned  char>& key) {
    if (key.size() > RC4_MAX_KEY_LEN) {
        return -1;
    }

    init_sbox();
    mix_sbox(key, key.size());

    i = 0;
    j = 0;

    return 0;
}

// Функция генерации одного элемента псевдослучайной последовательности (гаммы)
unsigned char g(void) {
    i = (i + 1) % 256;
    j = (j + S[i]) % 256;

    unsigned char t = S[i];
    S[i] = S[j];
    S[j] = t;

    return S[(S[i] + S[j]) % 256];
}

// Функция очистки памяти
void fin(void) {
    // Очистка S-блока
    for (int i = 0; i < 256; i++) {
        S[i] = 0;
    }

    // Обнуление индексов
    i = 0;
    j = 0;
}