#pragma once
#ifndef HUFFMANCOMPRESSCPRO1_BITIO_H
#define HUFFMANCOMPRESSCPRO1_BITIO_H

#include <iostream>
#define BITBUFFSIZE 1024
#define SHIFT 3
struct BIT {
    char b[BITBUFFSIZE];//位数组 bit数组
    int p; //指示数组填到哪一位的下一位
};

//向位数组栈顶推入一位
bool pushBit(BIT* buffer, const bool istrue);

//从文件加载多位
int fPushBit(BIT* buffer, FILE* fp);

//修改position位置的一位
int changeBit(BIT* buffer, const int istrue, const int position);

//读取一位
int readBit(BIT* buffer, const int position);

//栈顶弹出一位
int popBit(BIT* buffer);

#endif //HUFFMANCOMPRESSCPRO1_BITIO_H
