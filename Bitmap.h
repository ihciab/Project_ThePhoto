#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
using namespace std;

void Bitmap(const char File[])
{
	//读取图像文件
	
	FILE* fp = fopen(File, "rb");//读入的文件
	if (!fp) {
		cout << "文件未打开！\n";
		exit(0);
	}
	long width, height;
	BITMAPFILEHEADER fileHead;//位图文件头
	fread(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);//从fp中读取BITMAPFILEHEADER信息到fileHead中,同时fp的指针移动
	BITMAPINFOHEADER infoHead;//位图信息头
	fread(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);//从fp中读取BITMAPINFOHEADER信息到infoHead中,同时fp的指针移动
	width = infoHead.biWidth;
	height = infoHead.biHeight;

	cout << "width = " << width << endl << "height = " << height << endl;

	char* bmpBuf = new char[width * height * 3];
	fseek(fp, long(sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)), 0);//定位到起始位置
	fread(bmpBuf, sizeof(char), width * height * 3, fp);
	fclose(fp);

	//写入文件信息
	FILE* outFile = fopen(File, "wb");//输出文件
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, outFile);
	fwrite(&infoHead, sizeof(BITMAPINFOHEADER), 1, outFile);
	char* tmp = bmpBuf;
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width * 3; i++)
			fwrite(tmp++, 1, 1, outFile);
	fclose(outFile);

	//显示图像
	HWND hwnd = GetForegroundWindow();//窗口句柄
	HDC hdc = GetDC(hwnd);//绘图句柄
	BYTE b, g, r, rgb;
	tmp = bmpBuf;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			b = *tmp++;
			g = *tmp++;
			r = *tmp++;
			SetPixel(hdc, i, 150 + height - j, RGB(r, g, b));
		}
	}
}