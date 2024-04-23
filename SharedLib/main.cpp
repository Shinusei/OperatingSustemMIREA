#include <iostream>
#include <vector>
#include "rc4.h"

int main() {
    std::string key = "Thisvhjvu";
    std::string plain_text = "fbyvbhs";
    std::cin>>key;
    std::cin>>plain_text;

    // Генерация ключа
    std::vector<unsigned char> key_vec(key.begin(), key.end());
    set_key(key_vec);

    // Кодирование текста
    std::vector<unsigned char> cipher_text;
    for (unsigned char c : plain_text) {
        //std::cout<<(static_cast<int>(c))<<" ";
        cipher_text.push_back(static_cast<unsigned char >(c ^ g()));
    }
    std::cout<<std::endl;
    // Вывод закодированного текста
    //std::cout << "Закодированный текст: " << cipher_text << std::endl;
    for(unsigned char elem : cipher_text)
    {
        std::cout<<static_cast<unsigned char>(elem)<< " ";
    }
    std::cout<<std::endl;
    // Очистка памяти
    fin();
////////////////////////////////////////////////////////////////////////////////////////////
    //Проверка при помощи Декодирование текста

    // Генерация ключа
    set_key(key_vec);

    // Кодирование текста
    std::vector<unsigned char> uncipher_text;
    for (unsigned char c : cipher_text) {
        //std::cout<<(static_cast<int>(c))<<" ";
        //std::cout<<static_cast<int>(g())<< " ";
        uncipher_text.push_back(static_cast<unsigned char >(c ^ g()));
    }
    for(unsigned char elem : uncipher_text)
    {
        std::cout<<static_cast<unsigned char >(elem)<< " ";
    }
    std::cout<<std::endl;

//////////////////////////////////////////////////////////////////////////////////////////////////
    // Очистка памяти
    fin();

    return 0;
}