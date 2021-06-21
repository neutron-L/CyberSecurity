#pragma once
#include <string>
#include<iostream>
#include<fstream>
using namespace std;

//解密类
class RC4_decryption {
public:

    //构造函数，参数为密钥流文件和密文文件
    RC4_decryption(const string ks, const string ct) :keystream(ks), ciphertext(ct) {}
    //解密，参数为解密文件名
    void decryption(const string& filename);

private:
    string ciphertext, keystream;
};
