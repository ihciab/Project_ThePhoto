#pragma once
#ifndef HUFFMANCOMPRESSCPRO1_HUFFMANTREE_H
#define HUFFMANCOMPRESSCPRO1_HUFFMANTREE_H
#include <string>
#include <iostream>
#include "BitlO.h"
#define SIZE 256
#define NODES 2*SIZE - 1

//各种各样的编码方法
//取出index位，若取出的index位为0，则GET_BYTE值为假，否则为真
#define GET_BYTE(vByte, index) (((vByte) & (1 << ((index) ^ 7))) != 0)
//把index位设置为‘1’
#define SET_BYTE(vbyte, index) ((vbyte) |= (1 << ((index) ^ 7)))
//把index位设置为‘0’
#define CLR_BYTE(vbyte, index) ((vbyte) &= (~(1 << ((index) ^ 7))))

//n个叶子结点的哈夫曼树共有2n-1个结点
//一个字节8位 读取文件的char可以从0-255 用weight[]数组记录每个char出现的频率
//HuffmanTree 保存在HTNode[2n-1]的数组中
struct Node {
    bool isLeaf();
    int ch = 0;
    int weight = 0;
    int lChild = 0, rChild = 0, parent = 0;
};
typedef Node HTNode, * HuffTree;

struct HEAD {
    char type[4];
    int length;
    int weight[256];
};

void expand();
void select(HuffTree HT, int end, int* s1, int* s2);
void buildCode(std::string st[], Node x, std::string s, HuffTree HT);
std::string* buildCode(Node root, HuffTree HT);
void testBuildCode(std::string* st);
void InitTrie(int* w, HuffTree& HT);
void buildTrie(int* w, HuffTree& HT);
void testBuildTrie(int* w, HuffTree HT);
int InitHead(const char* Filename, HEAD& sHead);
unsigned char Str2Byte(char* BinStr);
void writeTrie(Node x, FILE* fpo, HuffTree& HT);
void encode(FILE* fpi, FILE* fpo, std::string* st);
void writeHead(FILE* fpo, HEAD& head);
void Extract(char EFLIE[256]);

#endif //HUFFMANCOMPRESSCPRO1_HUFFMANTREE_H

