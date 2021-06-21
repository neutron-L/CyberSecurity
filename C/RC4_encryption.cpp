#include "RC4_encryption.h"

RC4_encryption::RC4_encryption(int kl):keylen(kl) {
    //�����������Ϊkeylen�ֽڵ���Կ
    srand((unsigned)time(NULL));
    for (int i = 0; i < kl; ++i) {
        int tmp = rand() % 256;
        K.push_back(char(tmp));
    }

    //��ʼ��״̬����S����ʱ����T����keyStream��������
    for (int i = 0; i < 256; ++i) {
        S[i] = i;
        T[i] = K[i % keylen];//K�ĳ��Ȳ����ܳ���S��T��T����ʼ��ΪK��ѭ������
    }

    //��ʼ����״̬����S
    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + S[i] + T[i]) % 256;
        //cout<<"j="<<j<<endl;
        swap(S[i], S[j]);//��������S����K������С�
    }
}

//������Կ��
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
//����
//plaintext���� ks��Կ������������� ciphertext���ģ����������
void RC4_encryption::encryption(const string& plaintext, const string& ks, const string& ciphertext) {
    ifstream in;
    ofstream out, outks;

    in.open(plaintext);
    //��ȡ�������ĳ���
    in.seekg(0, ios::end);
    int lenFile = in.tellg();
    in.seekg(0, ios::beg);

    //������Կ����������ļ�
    CreateKeyStream(lenFile);
    outks.open(ks);
    for (int i = 0; i < lenFile; ++i) {
        outks << (k[i]);
    }
    outks.close();

    //�������ݶ���bits��
    unsigned char* bits = new unsigned char[lenFile];
    in.read((char*)bits, lenFile);
    in.close();


    out.open(ciphertext);
    //�����İ��ֽ���������Կ�� ��� ��͵õ����ģ�Ȼ�����������������ļ���
    for (int i = 0; i < lenFile; ++i) {
        out << (unsigned char)(bits[i] ^ k[i]);//^��ʾ���
    }
    out.close();

    delete[]bits;
}