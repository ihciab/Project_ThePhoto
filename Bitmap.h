#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
using namespace std;

void Bitmap(const char File[])
{
	//��ȡͼ���ļ�
	
	FILE* fp = fopen(File, "rb");//������ļ�
	if (!fp) {
		cout << "�ļ�δ�򿪣�\n";
		exit(0);
	}
	long width, height;
	BITMAPFILEHEADER fileHead;//λͼ�ļ�ͷ
	fread(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);//��fp�ж�ȡBITMAPFILEHEADER��Ϣ��fileHead��,ͬʱfp��ָ���ƶ�
	BITMAPINFOHEADER infoHead;//λͼ��Ϣͷ
	fread(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);//��fp�ж�ȡBITMAPINFOHEADER��Ϣ��infoHead��,ͬʱfp��ָ���ƶ�
	width = infoHead.biWidth;
	height = infoHead.biHeight;

	cout << "width = " << width << endl << "height = " << height << endl;

	char* bmpBuf = new char[width * height * 3];
	fseek(fp, long(sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)), 0);//��λ����ʼλ��
	fread(bmpBuf, sizeof(char), width * height * 3, fp);
	fclose(fp);

	//д���ļ���Ϣ
	FILE* outFile = fopen(File, "wb");//����ļ�
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, outFile);
	fwrite(&infoHead, sizeof(BITMAPINFOHEADER), 1, outFile);
	char* tmp = bmpBuf;
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width * 3; i++)
			fwrite(tmp++, 1, 1, outFile);
	fclose(outFile);

	//��ʾͼ��
	HWND hwnd = GetForegroundWindow();//���ھ��
	HDC hdc = GetDC(hwnd);//��ͼ���
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