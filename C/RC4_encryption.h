#pragma once
#include <time.h>
#include <xmemory>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//RC4流程：先根据密钥生成S，再根据S和明文生成密钥流，密钥流与明文按位异或生成密文，密文与密钥流按位异或生成明文。


//加密类
class RC4_encryption {
public:
    //构造函数，参数为密钥长度    
    RC4_encryption(int klen);
    //加密，由明文产生密文
    void encryption(const string&, const string&, const string&);

private:
    unsigned char S[256]; //状态向量，共256字节
    unsigned char T[256]; //临时向量，共256字节
    int keylen;        //密钥长度，keylen个字节，取值范围为1-256
    vector<char> K;      //可变长度密钥
    vector<char> k;      //密钥流

    
    //生成密钥流
    //len:明文为len个字节
    void CreateKeyStream(int len);

};
