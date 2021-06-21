#include "RC4_decryption.h"
//�������ĺ���Կ�����н���
void RC4_decryption::decryption(const string& res) {
    ifstream inks, incp;
    ofstream out;

    inks.open(keystream);
    incp.open(ciphertext);

    //�������ĳ���
    inks.seekg(0, ios::end);
    const int lenFile = inks.tellg();
    inks.seekg(0, ios::beg);
    //������Կ��
    unsigned char* bitKey = new unsigned char[lenFile];
    inks.read((char*)bitKey, lenFile);
    inks.close();
    //��������
    unsigned char* bitCip = new unsigned char[lenFile];
    incp.read((char*)bitCip, lenFile);
    incp.close();

    //���ܣ�����������Կ����λ���//���ܺ�������������ļ�
    out.open(res);
    for (int i = 0; i < lenFile; ++i)
        out << (unsigned char)(bitKey[i] ^ bitCip[i]);

    out.close();
}

