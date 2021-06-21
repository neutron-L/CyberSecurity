#include "RC4_encryption.h"

RC4_encryption::RC4_encryption(int kl):keylen(kl) {
    //随机生产长度为keylen字节的密钥
    srand((unsigned)time(NULL));
    for (int i = 0; i < kl; ++i) {
        int tmp = rand() % 256;
        K.push_back(char(tmp));
    }

    //初始化状态向量S和临时向量T，供keyStream方法调用
    for (int i = 0; i < 256; ++i) {
        S[i] = i;
        T[i] = K[i % keylen];//K的长度不可能超过S和T，T被初始化为K的循环排列
    }

    //初始排列状态向量S
    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + S[i] + T[i]) % 256;
        //cout<<"j="<<j<<endl;
        swap(S[i], S[j]);//差不多就是让S根据K随机排列。
    }
}

//生成密钥流
void RC4_encryption::CreateKeyStream(int len) {
    int i = 0, j = 0, t;
    while (len--) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        swap(S[i], S[j]);

        t = (S[i] + S[j]) % 256;
        k.push_back(S[t]);
    }
}
//加密
//plaintext明文 ks密钥流（输出变量） ciphertext密文（输出变量）
void RC4_encryption::encryption(const string& plaintext, const string& ks, const string& ciphertext) {
    ifstream in;
    ofstream out, outks;

    in.open(plaintext);
    //获取输入流的长度
    in.seekg(0, ios::end);
    int lenFile = in.tellg();
    in.seekg(0, ios::beg);

    //生产密钥流并输出到文件
    CreateKeyStream(lenFile);
    outks.open(ks);
    for (int i = 0; i < lenFile; ++i) {
        outks << (k[i]);
    }
    outks.close();

    //明文内容读入bits中
    unsigned char* bits = new unsigned char[lenFile];
    in.read((char*)bits, lenFile);
    in.close();


    out.open(ciphertext);
    //将明文按字节依次与密钥流 异或 后就得到密文，然后把密文输出到密文文件中
    for (int i = 0; i < lenFile; ++i) {
        out << (unsigned char)(bits[i] ^ k[i]);//^表示异或
    }
    out.close();

    delete[]bits;
}