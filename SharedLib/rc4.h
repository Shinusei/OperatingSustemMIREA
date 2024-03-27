#ifndef RC4_H
#define RC4_H

class RC4 {
private:
    char S[256];
    int i;
    int j;

public:
    RC4();
    int key(char* key, int len);
    char prga();
    void reset();
};

#endif