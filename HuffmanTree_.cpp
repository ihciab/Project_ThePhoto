#include "HuffmanTree_.h"
//HT指向HuffmanTree end为保存树数组所需搜寻的末尾，s1，s2分别指向最小和次小结点在树数组中下标
void select(HuffTree HT, int end, int* s1, int* s2) {
    int min1, min2;
    int i = 0;

    while (HT[i].parent != 0 && i <= end) {
        //找到第一个无双亲结点
        i++;
    }

    min1 = HT[i].weight;
    *s1 = i;

    i++;
    while (HT[i].parent != 0 && i <= end) {
        //第二个无双亲结点
        i++;
    }

    if (HT[i].weight < min1) {
        min2 = min1;
        min1 = HT[i].weight;
        *s2 = *s1;
        *s1 = i;
    }
    else {
        min2 = HT[i].weight;
        *s2 = i;
    }

    for (int j = i + 1; j <= end; j++) {
        //两结点与后续无双亲结点比较
        if (HT[j].parent != 0) {
            continue;
        }
        if (HT[j].weight < min1) {
            //新结点小于min1
            min2 = min1;
            *s2 = *s1;
            min1 = HT[j].weight;
            *s1 = j;
        }
        else if (HT[j].weight >= min1 && HT[j].weight < min2) {
            //新结点介于min1，min2 之间
            min2 = HT[j].weight;
            *s2 = j;
        }
    }
}

void InitTrie(int* w, HuffTree& HT) {
    HT = (HuffTree)malloc(sizeof(HTNode) * NODES);
    for (int i = 0; i < SIZE; i++) {
        //0-255 叶子结点
        HT[i].parent = 0;
        HT[i].rChild = 0;
        HT[i].lChild = 0;
        HT[i].weight = w[i];
        HT[i].ch = i;
    }
    for (int i = SIZE; i < NODES; i++) {
        //256-510 内部结点
        HT[i].parent = 0;
        HT[i].lChild = 0;
        HT[i].rChild = 0;
        HT[i].weight = 0;
        HT[i].ch = 0;
    }
}

void buildTrie(int* w, HuffTree& HT) {
    //每次搜寻两棵频率最小的树合并
    int s1, s2;
    for (int i = SIZE; i < NODES; i++) {
        //从256开始填树结点，一直到把根结点510填满 NODES = 511
        select(HT, i - 1, &s1, &s2);
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lChild = s1;
        HT[i].rChild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}
bool Node::isLeaf() { return lChild == 0 && rChild == 0; }
void buildCode(std::string st[], Node x, std::string s, HuffTree HT) {
    if (x.isLeaf()) {
        st[x.ch] = s;
        return;
    }
    buildCode(st, HT[x.lChild], s + '0', HT);
    buildCode(st, HT[x.rChild], s + '1', HT);
}

void testBuildTrie(int* w, HuffTree HT) {
    std::cout << "字节ASCII " << "频率" << std::endl;
    //文件中出现的字节对应的ASCII（十六进制）和 出现的频率
    for (int i = 0; i < SIZE; i++) {
        printf("0x%02X %d\n", i, w[i]);
    }
    //哈夫曼树中所有结点
    printf("结点下标\t频率\t双亲下标\t左孩子下标\t右孩子下标\n");
    for (int i = 0; i < NODES; i++) {
        printf("HT[%d]\t%d\t%d  \t%d  \t\t%d\t%d\n", i, HT[i].weight, HT[i].parent, HT[i].lChild, HT[i].rChild, HT[i].ch);
    }
}
std::string* buildCode(Node root, HuffTree HT) {
    std::string st[SIZE];
    buildCode(st, root, "", HT);
    std::cout << "HuffmanCode: " << std::endl;
    std::cout << "Bytes \t Codes" << std::endl;
    for (int i = 0; i < SIZE; i++) {
        printf("0x%02X :", i);
        printf("%s\n", st[i].c_str());
    }
    return st;
}

void testBuildCode(std::string* st) {
    std::cout << "HuffmanCode: " << std::endl;
    std::cout << "Bytes \t Codes" << std::endl;
    for (int i = 0; i < SIZE; i++) {
        printf("0x%02X :", i);
        printf("%s\n", (st + i)->c_str());
    }
}

int InitHead(const char* Filename, HEAD& sHead) {
    //初始化文件头
    char* t = (char*)malloc(sizeof(char) * strlen(Filename));
    strcpy(t, const_cast<char*>(Filename));
    char* token = std::strtok(t, ".");
    std::string str[4];
    int it = 0;
    while (token != nullptr) {
        str[it++] = token;
        token = strtok(NULL, ".");
    }
    char t2[8] = { '\0' };
    for (int k = 0; k < str[it - 1].size(); k++) {
        t2[k] = str[it - 1].at(k);
    }
    strcpy(sHead.type, t2);
    sHead.length = 0;
    for (int i = 0; i < 256; i++) {
        sHead.weight[i] = 0;
    }

    //以二进制流打开文件
    FILE* in = fopen(Filename, "rb");
    int ch;
    while ((ch = fgetc(in)) != EOF) {
        sHead.weight[ch]++;
        sHead.length++;//原文件长度多少字节
    }
    fclose(in);
    in = nullptr;
    return 1;
}

//将8位char变成一个char 即把 char数组 中的 char01 变成 一个char 中的 位01
unsigned char Str2Byte(char* BinStr) {
    unsigned char b = 0x00;
    for (int i = 0; i < 8; i++)
    {
        b = b << 1;
        if (BinStr[i] == '1')
        {
            b = b | 0x01;
        }
    }
    return b;
}

//可以将编码好的单词查找树写在文件开头，代价是文件变大， 也可以利用文件头(上述HEAD)中的weight数组在解压时重新构建树
//按位写入查找树
void writeTrie(Node x, FILE* fpo, HuffTree& HT) {
    char ch;
    if (x.isLeaf()) {
        bool t = true;
        fwrite(&t, sizeof(bool), 1, fpo);
        ch = (char)x.ch;
        fwrite(&ch, sizeof(char), 1, fpo);
        return;
    }
    bool t = false;
    fwrite(&t, sizeof(bool), 1, fpo);
    writeTrie(HT[x.lChild], fpo, HT);
    writeTrie(HT[x.rChild], fpo, HT);
}

//原文件编码后写入压缩文件
void encode(FILE* fpi, FILE* fpo, std::string* st) {
    int ch;
    char cd[SIZE] = { 0 };
    int pos = 0;
    //unsigned char pBuffer[1000] = {0}; //debug
    if (!fpo) {
        std::cerr << "解压失败" << std::endl;
        exit(EXIT_FAILURE);
    }
    while ((ch = fgetc(fpi)) != EOF) {
        std::string code = st[ch];
        strcat(cd, code.c_str());

        while (strlen(cd) >= 8) {
            unsigned char w = Str2Byte(cd);
            //pBuffer[pos++] = w;
            fwrite(&w, sizeof(char), 1, fpo);//写入文件
            for (int i = 0; i < SIZE - 8; i++) {
                //cd整体向左偏移8位
                cd[i] = cd[i + 8];
            }
        }
    }
    //处理可能剩余不足8位
    if (strlen(cd) > 0) {
        unsigned char w = Str2Byte(cd);
        fwrite(&w, sizeof(char), 1, fpo); //最后不足8位的位都为0
    }
}

void writeHead(FILE* fpo, HEAD& head) {
    fwrite(&head, sizeof(head), 1, fpo);
}

void Extract(char efile[256]) {
    std::cout << "解压文件路径: ";
    /*char efile[256];*/
    /*std::cin >> efile;*/
    FILE* in = fopen(efile, "rb");
    if (!in) {
        std::cerr << "File opening failed" << std::endl;
        return ;
    }
    HEAD head;
    fread(&head, sizeof(HEAD), 1, in);
    char file[SIZE] = { '\0' };
    char* t = (char*)malloc(sizeof(char) * strlen(efile));
    strcpy(t, const_cast<char*>(efile));
    char* token = strtok(t, ".");
    strcpy(file, token);
    strcat(file, "_解压文件.");
    strcat(file, head.type);
    FILE* out = fopen(file, "wb");

    fseek(in, 0L, SEEK_END);
    long filesize = ftell(in);

    HuffTree HT;
    InitTrie(head.weight, HT);
    buildTrie(head.weight, HT);
    std::string st[SIZE];
    buildCode(st, HT[NODES - 1], "", HT);

    fseek(in, 1032, SEEK_SET);
    long curLoc = ftell(in);

    unsigned char outValue;
    int index = 0;
    int root = NODES - 1;
    unsigned char ch = fgetc(in);
    fseek(out, 0, SEEK_SET);
    while (true) {
        if (HT[root].lChild == 0 && HT[root].rChild == 0) {
            outValue = (char)HT[root].ch;
            fwrite(&outValue, sizeof(char), 1, out);
            if (curLoc >= filesize) {
                break;
            }
            root = NODES - 1;
        }
        if (!(ch & (1 << (index ^ 7)))) {
            root = HT[root].lChild;
        }
        else {
            root = HT[root].rChild;
        }

        if (++index >= 8) {
            index = 0;
            ch = fgetc(in);
            curLoc = ftell(in);
        }
    }

    fclose(in);
    fclose(out);
  
}

