#include "HuffmanTree_.h"
//HTָ��HuffmanTree endΪ����������������Ѱ��ĩβ��s1��s2�ֱ�ָ����С�ʹ�С��������������±�
void select(HuffTree HT, int end, int* s1, int* s2) {
    int min1, min2;
    int i = 0;

    while (HT[i].parent != 0 && i <= end) {
        //�ҵ���һ����˫�׽��
        i++;
    }

    min1 = HT[i].weight;
    *s1 = i;

    i++;
    while (HT[i].parent != 0 && i <= end) {
        //�ڶ�����˫�׽��
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
        //������������˫�׽��Ƚ�
        if (HT[j].parent != 0) {
            continue;
        }
        if (HT[j].weight < min1) {
            //�½��С��min1
            min2 = min1;
            *s2 = *s1;
            min1 = HT[j].weight;
            *s1 = j;
        }
        else if (HT[j].weight >= min1 && HT[j].weight < min2) {
            //�½�����min1��min2 ֮��
            min2 = HT[j].weight;
            *s2 = j;
        }
    }
}

void InitTrie(int* w, HuffTree& HT) {
    HT = (HuffTree)malloc(sizeof(HTNode) * NODES);
    for (int i = 0; i < SIZE; i++) {
        //0-255 Ҷ�ӽ��
        HT[i].parent = 0;
        HT[i].rChild = 0;
        HT[i].lChild = 0;
        HT[i].weight = w[i];
        HT[i].ch = i;
    }
    for (int i = SIZE; i < NODES; i++) {
        //256-510 �ڲ����
        HT[i].parent = 0;
        HT[i].lChild = 0;
        HT[i].rChild = 0;
        HT[i].weight = 0;
        HT[i].ch = 0;
    }
}

void buildTrie(int* w, HuffTree& HT) {
    //ÿ����Ѱ����Ƶ����С�����ϲ�
    int s1, s2;
    for (int i = SIZE; i < NODES; i++) {
        //��256��ʼ������㣬һֱ���Ѹ����510���� NODES = 511
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
    std::cout << "�ֽ�ASCII " << "Ƶ��" << std::endl;
    //�ļ��г��ֵ��ֽڶ�Ӧ��ASCII��ʮ�����ƣ��� ���ֵ�Ƶ��
    for (int i = 0; i < SIZE; i++) {
        printf("0x%02X %d\n", i, w[i]);
    }
    //�������������н��
    printf("����±�\tƵ��\t˫���±�\t�����±�\t�Һ����±�\n");
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
    //��ʼ���ļ�ͷ
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

    //�Զ����������ļ�
    FILE* in = fopen(Filename, "rb");
    int ch;
    while ((ch = fgetc(in)) != EOF) {
        sHead.weight[ch]++;
        sHead.length++;//ԭ�ļ����ȶ����ֽ�
    }
    fclose(in);
    in = nullptr;
    return 1;
}

//��8λchar���һ��char ���� char���� �е� char01 ��� һ��char �е� λ01
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

//���Խ�����õĵ��ʲ�����д���ļ���ͷ���������ļ���� Ҳ���������ļ�ͷ(����HEAD)�е�weight�����ڽ�ѹʱ���¹�����
//��λд�������
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

//ԭ�ļ������д��ѹ���ļ�
void encode(FILE* fpi, FILE* fpo, std::string* st) {
    int ch;
    char cd[SIZE] = { 0 };
    int pos = 0;
    //unsigned char pBuffer[1000] = {0}; //debug
    if (!fpo) {
        std::cerr << "��ѹʧ��" << std::endl;
        exit(EXIT_FAILURE);
    }
    while ((ch = fgetc(fpi)) != EOF) {
        std::string code = st[ch];
        strcat(cd, code.c_str());

        while (strlen(cd) >= 8) {
            unsigned char w = Str2Byte(cd);
            //pBuffer[pos++] = w;
            fwrite(&w, sizeof(char), 1, fpo);//д���ļ�
            for (int i = 0; i < SIZE - 8; i++) {
                //cd��������ƫ��8λ
                cd[i] = cd[i + 8];
            }
        }
    }
    //�������ʣ�಻��8λ
    if (strlen(cd) > 0) {
        unsigned char w = Str2Byte(cd);
        fwrite(&w, sizeof(char), 1, fpo); //�����8λ��λ��Ϊ0
    }
}

void writeHead(FILE* fpo, HEAD& head) {
    fwrite(&head, sizeof(head), 1, fpo);
}

void Extract(char efile[256]) {
    std::cout << "��ѹ�ļ�·��: ";
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
    strcat(file, "_��ѹ�ļ�.");
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

