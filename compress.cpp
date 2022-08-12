#include "compress.h"
#include "HuffmanTree_.h"

void Compress(char* Filename, char* ExFilename )
{
    
    if (ExFilename == nullptr)
    {
        int weight[SIZE] = { 0 };
        FILE* fin = fopen(Filename, "rb");
        if (!fin) {
            std::cerr << "文件打开失败" << std::endl;
            exit(EXIT_FAILURE);
        }
        int ch;
        while ((ch = fgetc(fin)) != EOF) {
            weight[ch]++;
        }
        fclose(fin);

        HuffTree HT;
        InitTrie(weight, HT);
        buildTrie(weight, HT);
        testBuildTrie(weight, HT);

        std::string st[SIZE];
        buildCode(st, HT[NODES - 1], "", HT);
        std::cout << "HuffmanCode: " << std::endl;
        std::cout << "Bytes \t Codes" << std::endl;
        for (int i = 0; i < SIZE; i++) {
            printf("0x%02X :", i);
            printf("%s\n", st[i].c_str());
        }
        //testBuildCode(str);
    //    std::cout<<"HuffmanCode: "<<std::endl;
    //    std::cout<<"Bytes \t Codes"<<std::endl;
    //    for(int i= 0; i < SIZE; i++){
    //        printf("0x%02X :", i);
    //        printf("%s\n",str[i].c_str());
    //    }

        HEAD head;
        InitHead(Filename, head);

        char filename[256] = { '\0' };
        strcpy(filename, Filename);
        strcat(filename, ".huf");

        FILE* out = fopen(filename, "wb");
        writeHead(out, head);

        fin = fopen(Filename, "rb");
        encode(fin, out, st);

        fclose(fin);
        fclose(out);
        
    }
    else  if(ExFilename!=nullptr)
    Extract(ExFilename);
}
