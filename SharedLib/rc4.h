#ifndef RC4_H
#define RC4_H

class RC4 {
private:
    unsigned char S[256];
    int i;
    int j;

public:
    RC4();
    int key(unsigned char* key, int len);
    unsigned char prga();
    void reset();
};

#endif