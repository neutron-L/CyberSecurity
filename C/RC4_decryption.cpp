#include "RC4_decryption.h"
//根据密文和密钥流进行解密
void RC4_decryption::decryption(const string& res) {
    ifstream inks, incp;
    ofstream out;

    inks.open(keystream);
    incp.open(ciphertext);

    //计算密文长度
    inks.seekg(0, ios::end);
    const int lenFile = inks.tellg();
    inks.seekg(0, ios::beg);
    //读入密钥流
    unsigned char* bitKey = new unsigned char[lenFile];
    inks.read((char*)bitKey, lenFile);
    inks.close();
    //读入密文
    unsigned char* bitCip = new unsigned char[lenFile];
    incp.read((char*)bitCip, lenFile);
    incp.close();

    //解密：将密文与密钥流按位异或//解密后结果输出到解密文件
    out.open(res);
    for (int i = 0; i < lenFile; ++i)
        out << (unsigned char)(bitKey[i] ^ bitCip[i]);

    out.close();
}

