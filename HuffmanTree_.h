#pragma once
#ifndef HUFFMANCOMPRESSCPRO1_HUFFMANTREE_H
#define HUFFMANCOMPRESSCPRO1_HUFFMANTREE_H
#include <string>
#include <iostream>
#include "BitlO.h"
#define SIZE 256
#define NODES 2*SIZE - 1

//���ָ����ı��뷽��
//ȡ��indexλ����ȡ����indexλΪ0����GET_BYTEֵΪ�٣�����Ϊ��
#define GET_BYTE(vByte, index) (((vByte) & (1 << ((index) ^ 7))) != 0)
//��indexλ����Ϊ��1��
#define SET_BYTE(vbyte, index) ((vbyte) |= (1 << ((index) ^ 7)))
//��indexλ����Ϊ��0��
#define CLR_BYTE(vbyte, index) ((vbyte) &= (~(1 << ((index) ^ 7))))

//n��Ҷ�ӽ��Ĺ�����������2n-1�����
//һ���ֽ�8λ ��ȡ�ļ���char���Դ�0-255 ��weight[]�����¼ÿ��char���ֵ�Ƶ��
//HuffmanTree ������HTNode[2n-1]��������
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

