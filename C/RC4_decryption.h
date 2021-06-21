#pragma once
#include <string>
#include<iostream>
#include<fstream>
using namespace std;

//������
class RC4_decryption {
public:

    //���캯��������Ϊ��Կ���ļ��������ļ�
    RC4_decryption(const string ks, const string ct) :keystream(ks), ciphertext(ct) {}
    //���ܣ�����Ϊ�����ļ���
    void decryption(const string& filename);

private:
    string ciphertext, keystream;
};
