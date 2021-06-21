#pragma once
#include <time.h>
#include <xmemory>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//RC4���̣��ȸ�����Կ����S���ٸ���S������������Կ������Կ�������İ�λ����������ģ���������Կ����λ����������ġ�


//������
class RC4_encryption {
public:
    //���캯��������Ϊ��Կ����    
    RC4_encryption(int klen);
    //���ܣ������Ĳ�������
    void encryption(const string&, const string&, const string&);

private:
    unsigned char S[256]; //״̬��������256�ֽ�
    unsigned char T[256]; //��ʱ��������256�ֽ�
    int keylen;        //��Կ���ȣ�keylen���ֽڣ�ȡֵ��ΧΪ1-256
    vector<char> K;      //�ɱ䳤����Կ
    vector<char> k;      //��Կ��

    
    //������Կ��
    //len:����Ϊlen���ֽ�
    void CreateKeyStream(int len);

};
