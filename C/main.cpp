#include <iostream>
#include "RC4_encryption.h"
#include "RC4_decryption.h"

int main() {
    RC4_encryption rc4(32); //密钥长32字节
    rc4.encryption("明文.txt", "密钥流.txt", "密文.txt");

    RC4_decryption decrypt("密钥流.txt", "密文.txt");
    decrypt.decryption("解密结果.txt");

}