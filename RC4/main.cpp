//#include <iostream>
//#include <vector>
//#include <string>
//#include <fstream>
//
//using namespace std;
//
///*
//    加密类
//*/
//class RC4 {
//public:
//    /*
//        构造函数，参数为密钥长度
//    */
//    RC4(int kl) : keylen(kl) {
//        srand((unsigned) time(NULL));
//        for (int i = 0; i < kl; ++i) {  //随机生产长度为keylen字节的密钥
//            int tmp = rand() % 256;
//            K.push_back(char(tmp));
//        }
//    }
//
//    /*
//        由明文产生密文
//    */
//    void encryption(const string &, const string &, const string &);
//
//private:
//    unsigned char S[256]; //状态向量，共256字节
//    unsigned char T[256]; //临时向量，共256字节
//    int keylen;        //密钥长度，keylen个字节，取值范围为1-256
//    vector<char> K;      //可变长度密钥
//    vector<char> k;      //密钥流
//
//    /*
//        初始化状态向量S和临时向量T，供keyStream方法调用
//    */
//    void initial() {
//        for (int i = 0; i < 256; ++i) {
//            S[i] = i;
//            T[i] = K[i % keylen];
//        }
//    }
//
//    /*
//        初始排列状态向量S，供keyStream方法调用
//    */
//    void rangeS() {
//        int j = 0;
//        for (int i = 0; i < 256; ++i) {
//            j = (j + S[i] + T[i]) % 256;
//            //cout<<"j="<<j<<endl;
//            S[i] = S[i] + S[j];
//            S[j] = S[i] - S[j];
//            S[i] = S[i] - S[j];
//        }
//    }
//
//    /*
//        生成密钥流
//        len:明文为len个字节
//    */
//    void keyStream(int len);
//
//};
//
//void RC4::keyStream(int len) {
//    initial();
//    rangeS();
//
//    int i = 0, j = 0, t;
//    while (len--) {
//        i = (i + 1) % 256;
//        j = (j + S[i]) % 256;
//
//        S[i] = S[i] + S[j];
//        S[j] = S[i] - S[j];
//        S[i] = S[i] - S[j];
//
//        t = (S[i] + S[j]) % 256;
//        k.push_back(S[t]);
//    }
//}
//
//void RC4::encryption(const string &plaintext, const string &ks, const string &ciphertext) {
//    ifstream in;
//    ofstream out, outks;
//
//    in.open(plaintext);
//    //获取输入流的长度
//    in.seekg(0, ios::end);
//    int lenFile = in.tellg();
//    in.seekg(0, ios::beg);
//
//    //生产密钥流
//    keyStream(lenFile);
//    outks.open(ks);
//    for (int i = 0; i < lenFile; ++i) {
//        outks << (k[i]);
//    }
//    outks.close();
//
//    //明文内容读入bits中
//    unsigned char *bits = new unsigned char[lenFile];
//    in.read((char *) bits, lenFile);
//    in.close();
//
//
//    out.open(ciphertext);
//    //将明文按字节依次与密钥流异或后输出到密文文件中
//    for (int i = 0; i < lenFile; ++i) {
//        out << (unsigned char) (bits[i] ^ k[i]);
//    }
//    out.close();
//
//    delete[]bits;
//}
//
///*
//    解密类
//*/
//class RC4_decryption {
//public:
//    /*
//        构造函数，参数为密钥流文件和密文文件
//    */
//    RC4_decryption(const string ks, const string ct) : keystream(ks), ciphertext(ct) {}
//
//    /*
//        解密方法，参数为解密文件名
//    */
//    void decryption(const string &);
//
//private:
//    string ciphertext, keystream;
//};
//
//void RC4_decryption::decryption(const string &res) {
//    ifstream inks, incp;
//    ofstream out;
//
//    inks.open(keystream);
//    incp.open(ciphertext);
//
//    //计算密文长度
//    inks.seekg(0, ios::end);
//    const int lenFile = inks.tellg();
//    inks.seekg(0, ios::beg);
//    //读入密钥流
//    unsigned char *bitKey = new unsigned char[lenFile];
//    inks.read((char *) bitKey, lenFile);
//    inks.close();
//    //读入密文
//    unsigned char *bitCip = new unsigned char[lenFile];
//    incp.read((char *) bitCip, lenFile);
//    incp.close();
//
//    //解密后结果输出到解密文件
//    out.open(res);
//    for (int i = 0; i < lenFile; ++i)
//        out << (unsigned char) (bitKey[i] ^ bitCip[i]);
//
//    out.close();
//}
//
//
//int main() {
//    RC4 rc4(16); //密钥长16字节
//    rc4.encryption("plaintext.txt", "cipher.txt", "ciphertext.txt");
//
//    RC4_decryption decrypt("cipher.txt", "ciphertext.txt");
//    decrypt.decryption("decodefile.txt");
//
//
//    return 0;
//}

//程序开始
#include<stdio.h>
#include<string.h>
typedef unsigned longULONG;

/*初始化函数*/
void rc4_init(unsigned char*s, unsigned char*key, unsigned long Len)
{
    int i = 0, j = 0;
    char k[256] = { 0 };
    unsigned char tmp = 0;
    for (i = 0; i<256; i++)
    {
        s[i] = i;
        k[i] = key[i%Len];
    }
    for (i = 0; i<256; i++)
    {
        j = (j + s[i] + k[i]) % 256;
        tmp = s[i];
        s[i] = s[j];//交换s[i]和s[j]
        s[j] = tmp;
    }
}


/*加解密*/
void rc4_crypt(unsigned char*s, unsigned char*Data, unsigned long Len)
{
    int i = 0, j = 0, t = 0;
    unsigned long k = 0;
    unsigned char tmp;
    for (k = 0; k<Len; k++)
    {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        tmp = s[i];
        s[i] = s[j];//交换s[x]和s[y]
        s[j] = tmp;
        t = (s[i] + s[j]) % 256;
        Data[k] ^= s[t];
    }
}

int main()
{
    unsigned char s[256] = { 0 }, s2[256] = { 0 };//S-box
    char key[256] = { "justfortest" };
    char pData[512] = "这是明文:今天的天气很好";
    unsigned long len = strlen(pData);
    int i;

    printf("pData=%s\n", pData);
    printf("key=%s,length=%d\n\n", key, strlen(key));
    rc4_init(s, (unsigned char*)key, strlen(key));//已经完成了初始化
    printf("完成对S[i]的初始化，如下：\n\n");
    for (i = 0; i<256; i++)
    {
        printf("%02X", s[i]);
        if (i && (i + 1) % 16 == 0)putchar('\n');
    }
    printf("\n\n");
    for (i = 0; i<256; i++)//用s2[i]暂时保留经过初始化的s[i]，很重要的！！！
    {
        s2[i] = s[i];
    }
    printf("已经初始化，现在加密:\n\n");
    rc4_crypt(s, (unsigned char*)pData, len);//加密
    printf("pData=%s\n\n", pData);
    printf("已经加密，现在解密:\n\n");
    //rc4_init(s,(unsignedchar*)key,strlen(key));//初始化密钥
    rc4_crypt(s2, (unsigned char*)pData, len);//解密
    printf("pData=%s\n\n", pData);
    return 0;
}

//程序完