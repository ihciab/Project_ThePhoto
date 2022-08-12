#pragma once
#ifndef HUFFMANCOMPRESSCPRO1_BITIO_H
#define HUFFMANCOMPRESSCPRO1_BITIO_H

#include <iostream>
#define BITBUFFSIZE 1024
#define SHIFT 3
struct BIT {
    char b[BITBUFFSIZE];//λ���� bit����
    int p; //ָʾ�������һλ����һλ
};

//��λ����ջ������һλ
bool pushBit(BIT* buffer, const bool istrue);

//���ļ����ض�λ
int fPushBit(BIT* buffer, FILE* fp);

//�޸�positionλ�õ�һλ
int changeBit(BIT* buffer, const int istrue, const int position);

//��ȡһλ
int readBit(BIT* buffer, const int position);

//ջ������һλ
int popBit(BIT* buffer);

#endif //HUFFMANCOMPRESSCPRO1_BITIO_H
