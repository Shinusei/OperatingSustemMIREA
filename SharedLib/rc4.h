#ifndef RC4_H
#define RC4_H

#include <vector>

// Максимальная длина ключа
const int RC4_MAX_KEY_LEN = 256;

// Функция генерации ключа и инициализации внутреннего состояния шифратора
int set_key(const std::vector<unsigned char>& key);

// Функция генерации одного элемента псевдослучайной последовательности (гаммы)
unsigned char g(void);

// Функция очистки памяти после использования библиотеки
void fin(void);

#endif // RC4_H