#pragma once
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <Windows.h>
#include<graphics.h>
#include<easyx.h>
#include <conio.h>
#include <iostream>
#include "Compress.h"
#include "HuffmanTree.h"
#define PI 3.14159265
#define pi acos(-1.0)
using namespace std;
void newswap(DWORD& a, DWORD& b)
{
	DWORD tem;
	tem = a;
	a = b;
	b = tem;
}
void BubbleSort(int* arr, int n)
{
	int end = n;
	while (end)
	{
		int flag = 0;
		for (int i = 1; i < end; ++i)
		{
			if (arr[i - 1] > arr[i])
			{
				int tem = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = tem;
				flag = 1;
			}
		}
		if (flag == 0)
		{
			break;
		}
		--end;
	}
}
#pragma region 颜色的分解与合成
void other()
{//绘制像素点

	RGB(255, 25, 30);
	//颜色的分解与合成
	DWORD red = RGB(255, 25, 30);
	int r = (UCHAR)red;
	int g = (UCHAR)(red >> 8);
	int b = (UCHAR)(red >> 16);
	//若给定一个数组（128，63，77） 则在putpixel中填入第三个参数为（（63<<8|125)|(77<<16));
};
#pragma  endregion
UCHAR r(DWORD a)//返回r
{
	UCHAR r = (UCHAR)a;
	return r;
}

UCHAR g(DWORD a)//返回g
{
	UCHAR g = (UCHAR)(a >> 8);
	return g;
}

UCHAR b(DWORD a)//返回b
{
	UCHAR b = (UCHAR)(a >> 16);
	return b;
}
void toGray_s(IMAGE* srcimg)
{
	DWORD* psrc = GetImageBuffer(srcimg);//一个一维数组 获取了src所有像素点;
	for (int i = 0; i < srcimg->getwidth() * srcimg->getheight(); i++)
	{
		UCHAR arv = (r(psrc[i]) + g(psrc[i]) + b(psrc[i])) / 3;
		psrc[i] = RGB(arv, arv, arv);
	}

}


void drawImg_s(int x, int y, IMAGE* img)
{
	DWORD* pwin = GetImageBuffer();     //获取窗口缓冲区指针;
	DWORD* pimg = GetImageBuffer(img);  //获取图片缓冲区指针
	int win_w = getwidth();
	int win_h = getheight();
	int img_w = img->getwidth();
	int img_h = img->getheight();
	//判断x，y坐标是否超出了窗口范围
	int real_w = (x + img_w > win_w) ? win_w - x : img_w;//超出右边界
	int real_h = (x + img_h > win_h) ? win_h - x : img_h;//超出下边界
	if (x < 0)
	{//处理超出左边界
		pimg += -x;//让指针向后偏移
		real_w -= -x;
		x = 0;
	}
	if (y < 0)
	{//处理超出上边界
		pimg += (img_w) * -y;//让指针向下偏移
		real_h -= -y;
		y = 0;
	}
	pwin += (win_w * y + x);

	for (int iy = 0; iy < real_h; iy++)
	{
		for (int ix = 0; ix < real_w; ix++)
		{

			UCHAR alpha = pimg[ix] >> 24;
			if (alpha > 200)
			{
				pwin[ix] = pimg[ix];
			}
			//换到下一行

		}
		pwin += win_w;
		pimg += img_w;
	}
}
//图片的翻转
void turnImg(IMAGE* img)
{
	DWORD* pimg = GetImageBuffer(img);
	int img_w = img->getwidth();
	int img_h = img->getheight();
	for (int i = 0; i < (img_w * img_h + 1) / 2; ++i)
	{
		newswap(pimg[i], pimg[img_w * img_h - i - 1]);
	}


}
//转灰度
void  toGray(IMAGE* detimg, IMAGE* srcimg)
{
	//设置目标图片大小
	detimg->Resize(srcimg->getwidth(), srcimg->getheight());
	//2获取srcimg图片缓冲区数组指针
	DWORD* psrc = GetImageBuffer(srcimg);//一个一维数组 获取了src所有像素点;
	DWORD* pdst = GetImageBuffer(detimg);
	for (int i = 0; i < srcimg->getwidth() * srcimg->getheight(); i++)
	{
		//彩色像素转成灰度像素  原理  ARGB(0,255,0,0)->(0,X/3,X/3,X/3);
		DWORD color = psrc[i];

		//颜色的分解与合成

		UCHAR r = (UCHAR)color;
		UCHAR g = (UCHAR)(color >> 8);
		UCHAR b = (UCHAR)(color >> 16);
		UCHAR a = (UCHAR)(color >> 24);
		DWORD arv = (r + g + b + a) / 4;
		pdst[i] = RGB(arv, arv, arv);

	}
	
	

}
//图片的反色
void turncolor(IMAGE* img, IMAGE* target)
{
	DWORD* newimg = GetImageBuffer(img);
	DWORD* pdst = GetImageBuffer(target);

	int img_w = img->getwidth();
	int img_h = img->getheight();
	for (int i = 0; i < (img_w * img_h); i++)
	{
		DWORD color = newimg[i];
		UCHAR r = (UCHAR)color;
		UCHAR g = (UCHAR)(color >> 8);
		UCHAR b = (UCHAR)(color >> 16);
		DWORD new_r = 255 - r;
		DWORD new_g = 255 - g;
		DWORD new_b = 255 - b;
		pdst[i] = RGB(new_r, new_g, new_b);

	}
	saveimage(_T("D:/Cstudy/C++study/Project_Thephoto/targetturn.bmp"), target);

}

//怀旧图片
void turn_old(IMAGE* detimg, IMAGE* srcimg)
{
	detimg->Resize(srcimg->getwidth(), srcimg->getheight());
	DWORD* psrc = GetImageBuffer(srcimg);
	DWORD* pdet = GetImageBuffer(detimg);
	for (int i = 0; i < srcimg->getwidth() * srcimg->getheight(); i++)
	{
		DWORD newr = 0.393 * r(psrc[i]) + 0.769 * g(psrc[i]) + 0.189 * b(psrc[i]);
		DWORD newg = 0.349 * r(psrc[i]) + 0.686 * g(psrc[i]) + 0.168 * b(psrc[i]);
		DWORD newb = 0.272 * r(psrc[i]) + 0.534 * g(psrc[i]) + 0.131 * b(psrc[i]);
		if (newr > 255) { newr = 255; }
		if (newg > 255) { newg = 255; }
		if (newb > 255) { newb = 255; }
		pdet[i] = RGB(newb, newg, newr);
	}

}
//均值滤波
void average(IMAGE* srcimg)
{
	//2获取srcimg图片缓冲区数组指针
	DWORD* psrc = GetImageBuffer(srcimg);//一个一维数组 获取了src所有像素点;
	DWORD* pdst = new DWORD[srcimg->getwidth() * srcimg->getheight()];
	for (int i = 0; i < srcimg->getwidth() * srcimg->getheight(); i++)
	{
		if ((i + 1) % srcimg->getwidth() == 0 || (i + 1) % srcimg->getheight() == 1 || i< getwidth() || i>srcimg->getwidth() * srcimg->getheight() - srcimg->getwidth() - 1)//判断点是否在边界上
		{
		}
		else
		{
			DWORD centre = psrc[i];
			DWORD centre_left = psrc[i - 1];
			DWORD centre_right = psrc[i + 1];
			DWORD centre_up = psrc[i - srcimg->getwidth()];
			DWORD centre_down = psrc[i + srcimg->getwidth()];
			DWORD centre_45 = psrc[i - srcimg->getwidth() + 1];
			DWORD centre_135 = psrc[i - srcimg->getwidth() - 1];
			DWORD centre_minus45 = psrc[i + srcimg->getwidth() + 1];
			DWORD centre_minus135 = psrc[i + srcimg->getwidth() - 1];
			//获取一个3*3的数组用于处理；
			UCHAR newr = ((r(centre_left) + r(centre_right) + r(centre_up) + r(centre_down) + r(centre_45) + r(centre_135) + r(centre_minus45) + r(centre_minus135)) / 8);
			UCHAR newg = ((g(centre_left) + g(centre_right) + g(centre_up) + g(centre_down) + g(centre_45) + g(centre_135) + g(centre_minus45) + g(centre_minus135)) / 8);
			UCHAR newb = ((b(centre_left) + b(centre_right) + b(centre_up) + b(centre_down) + b(centre_45) + b(centre_135) + b(centre_minus45) + b(centre_minus135)) / 8);
			pdst[i] = RGB(newr, newg, newb);
		}

	}
	for (int i = 0; i < srcimg->getwidth() * srcimg->getheight(); i++)
	{
		psrc[i] = pdst[i];
	}
}
void Addnoise_point(IMAGE* srcimg, int num)
{
	DWORD* psrc = GetImageBuffer(srcimg);//一个一维数组 获取了src所有像素点;
	int x = 0;
	int y = 0;
	int type;
	for (int j = 0; j < num; j++)
	{

		type = rand() % 2;
		x = rand() % srcimg->getwidth();
		y = rand() % srcimg->getheight();
		int i = y * srcimg->getwidth() + x;
		int width = srcimg->getwidth(); int height = srcimg->getheight();

		if (i < width * height && type == 1)
		{
			psrc[i] = RGB(0, 0, 0);

		}
		if (i < width * height && type == 0)
		{
			psrc[i] = RGB(255, 255, 255);
		}
	}
}
//反色
void turncolor_s(IMAGE* img)
{
	DWORD* newimg = GetImageBuffer(img);
	int img_w = img->getwidth();
	int img_h = img->getheight();
	for (int i = 0; i < (img_w * img_h); ++i)
	{
		DWORD color = newimg[i];
		UCHAR r = (UCHAR)color;
		UCHAR g = (UCHAR)(color >> 8);
		UCHAR b = (UCHAR)(color >> 16);
		DWORD new_r = 255 - r;
		DWORD new_g = 255 - g;
		DWORD new_b = 255 - b;
		newimg[i] = RGB(new_r, new_g, new_b);

	}
}
//哈夫曼压缩
int  _Huffman(char filename[256])
{
	cout << "==== 哈夫曼压缩 ====" << endl;
	cout << "filename: ";
	/*char filename[256];*/
	/*cin >> filename;*/
	Compress(filename);//解压函数也在这里运行了

	return 0;
}
//镜像
void Mirror(IMAGE* img)
{

	DWORD* pimg = GetImageBuffer(img);

	int img_w = img->getwidth();
	int img_h = img->getheight();



	for (int iy = 0; iy < (img_h - 1); iy++)
	{
		for (int ix = 0; ix < (img_w - 1) / 2; ix++)
		{

			newswap(pimg[ix + iy * img_h], pimg[(img_w - ix) + iy * img_h]);

			//换到下一行

		}

	}



}
//高斯滤波 
void gauss(IMAGE* srcimg, double sigma = 10.50, int size = 9)//----------第二代
{
	if (size % 2 != 0)
	{
		DWORD* psrc = GetImageBuffer(srcimg);//一个一维数组 获取了src所有像素点;
		DWORD** img = new DWORD * [srcimg->getheight()];
		for (int i = 0; i < srcimg->getheight(); i++)
		{
			*(img + i) = new DWORD[srcimg->getwidth()];
		}
		for (int i = 0; i < srcimg->getheight(); i++)
		{
			for (int j = 0; j < srcimg->getwidth(); j++)
			{
				img[i][j] = psrc[i * srcimg->getwidth() + j];

			}
		}
		DWORD* pdst = new DWORD[srcimg->getwidth() * srcimg->getheight()];
		//-------------------------------------------构建一个二维数组来承载高斯核桃
		double** core = new double* [size];
		for (int i = 0; i < size; i++)
		{
			*(core + i) = new double[size];
		}
		//-------------------------------------------计算权重并且使权重之和为1
		double sum = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				double dist_2 = (double)((i - size / 2) * (i - size / 2) + (j - size / 2) * (j - size / 2));
				core[i][j] = (exp(-dist_2 / (2 * sigma * sigma))) / (2 * pi * sigma * sigma);
				sum += core[i][j];
			}
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				core[i][j] = core[i][j] / sum;
			}
		}
		//-----------------------------------------------
		for (int i = 0; i < srcimg->getwidth() * srcimg->getheight(); i++)
		{
			if (i < (size / 2) * srcimg->getwidth() || i >= (srcimg->getwidth() * srcimg->getheight() - (size / 2) * srcimg->getwidth()) || (i % srcimg->getwidth()) < (size / 2) || ((i + size / 2) % srcimg->getwidth()) < (size / 2))
			{
			}//去除边界点
			else
			{
				UCHAR newr = 0;
				UCHAR newg = 0;
				UCHAR newb = 0;
				int centre_x = i / srcimg->getwidth();
				int centre_y = i % srcimg->getwidth();
				int p = 0;
				for (int m = centre_x - (size / 2); m <= centre_x + (size / 2); m++)
				{
					if (p < size)
					{
						int q = 0;
						for (int n = centre_y - (size / 2); n <= centre_y + (size / 2); n++)
						{
							if (q < size)
							{
								newr += r(img[m][n]) * core[p][q];
								newg += g(img[m][n]) * core[p][q];
								newb += b(img[m][n]) * core[p][q];
								q++;
							}
						}
						p++;
					}
				}
				pdst[i] = RGB(newr, newg, newb);
			}
		}
		for (int i = 0; i < srcimg->getwidth() * srcimg->getheight(); i++)
		{
			psrc[i] = pdst[i];
		}
		delete[]pdst;
	}
	else { cout << "请输入一个奇数作为高斯核的大小"; }
}
//边缘化
void edge(IMAGE* srcimg)
{
	int width = srcimg->getwidth();
	int height = srcimg->getheight();
	DWORD* psrc = GetImageBuffer(srcimg);
	DWORD** img = new DWORD * [height];
	for (int i = 0; i < height; i++)
	{
		*(img + i) = new DWORD[width];
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int n = i * width + j;
			img[i][j] = (r(psrc[n]) + g(psrc[n]) + b(psrc[n])) / 3;//构建一个二维数组用来承载灰度信息
		}
	}
	for (int i = 1; i < height - 1; i++)//便利二维数组的每一个点（除开边界点）
	{
		for (int j = 1; j < width - 1; j++)
		{
			DWORD Gx = (-1) * img[i - 1][j - 1] + (-2) * img[i][j - 1] + (-1) * img[i + 1][j - 1] + (1) * img[i - 1][j + 1] + (2) * img[i][j + 1] + (1) * img[i + 1][j + 1];
			DWORD Gy = (-1) * img[i - 1][j - 1] + (-2) * img[i - 1][j] + (-1) * img[i - 1][j + 1] + (1) * img[i + 1][j - 1] + (2) * img[i + 1][j] + (1) * img[i + 1][j + 1];
			DWORD G = sqrt(Gx * Gx + Gy * Gy);
			psrc[i * width + j] = RGB(255 - G, 255 - G, 255 - G);
		}
	}
}
DWORD  LineGet(DWORD left, DWORD right)
{
	DWORD target;
	UCHAR lr = (UCHAR)left;
	UCHAR lg = (UCHAR)(left >> 8);
	UCHAR lb = (UCHAR)(left >> 16);
	UCHAR rr = (UCHAR)right;
	UCHAR rg = (UCHAR)(right >> 8);
	UCHAR rb = (UCHAR)(right >> 16);
	UCHAR mr = (lr + rr) / 2;
	UCHAR mg = (lg + rg) / 2;
	UCHAR mb = (lb + rb) / 2;
	target = RGB(mr, mg, mb);
	return target;

}
void Enlarge_X(IMAGE* srcimg, int bill)
{
	int img_w = srcimg->getwidth();
	int img_h = srcimg->getheight();
	DWORD* psrc = GetImageBuffer(srcimg);
	DWORD* pdst = new DWORD[img_w * bill * img_h];
	for (int y = 0; y < img_h; ++y)
	{
		for (int x = 0; x < img_w * bill; ++x)
		{
			int position = y * img_w * bill + x;
			if (position % bill == 0)
			{
				pdst[position] = psrc[position / bill];
			}
			else if (position % bill != 0)
			{

				pdst[position] = LineGet(psrc[position / bill], psrc[(position / bill)]);
			}

		}

	}
	srcimg->Resize(img_w * bill, img_h);
	DWORD* npsrc = GetImageBuffer(srcimg);
	for (int y = 0; y < img_h; ++y)
		for (int x = 0; x < img_w * bill; ++x)
		{

			npsrc[y * img_w * bill + x] = pdst[y * img_w * bill + x];


		}
}
void Enlarge_Y(IMAGE* srcimg, int bill)
{

	int img_w = srcimg->getwidth();
	int img_h = srcimg->getheight();
	DWORD* psrc = GetImageBuffer(srcimg);
	DWORD* pdst = new DWORD[img_w * bill * img_h];
	for (int y = 0; y < img_h * bill; ++y)
	{
		for (int x = 0; x < img_w; ++x)
		{
			int position = y * img_w + x;
			if (y % bill == 0)
			{
				pdst[position] = psrc[((y/bill * img_w) + x)];
			}
			else if (y % bill != 0)
			{

				pdst[position] = LineGet(psrc[(y /bill* img_w + x) ], psrc[(y/bill * img_w + x )]);
			}

		}

	}
	srcimg->Resize(img_w, img_h * bill);
	DWORD* npsrc = GetImageBuffer(srcimg);
	for (int y = 0; y < img_h * bill; ++y)
		for (int x = 0; x < img_w; ++x)
		{

			npsrc[y * img_w + x] = pdst[y * img_w + x];


		}

}
//---------------------------------------------------------------------------
void multiply(double* a, double* b, double* c, int m, int n, int l)
{
	int i, j, k;
	double t;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < l; j++)
		{
			t = 0;
			for (k = 0; k < n; k++)
			{
				t += a[i * n + k] * b[k * l + j];
			}
			c[i * l + j] = t;
		}
	}
}
//---------------------------------------------------------------------------
void Mosaic(IMAGE* srcimg, int size = 11)
{
	int halfsize = size / 2;
	int width = srcimg->getwidth();
	int height = srcimg->getheight();
	DWORD* psrc = GetImageBuffer(srcimg);
	DWORD** img = new DWORD * [height];
	for (int i = 0; i < height; i++)
	{
		*(img + i) = new DWORD[width];
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int n = i * width + j;
			img[i][j] = psrc[i * width + j];
		}
	}
	for (int i = halfsize; i < height + halfsize; i = i + size)
	{
		for (int j = halfsize; j < width + halfsize; j = j + size)
		{
			for (int m = i - halfsize; m <= i + halfsize; m++)
			{
				for (int n = j - halfsize; n <= j + halfsize; n++)
				{
					if (m < height && n < width)
						img[m][n] = img[i - halfsize][j - halfsize];
				}
			}

		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			psrc[i * width + j] = img[i][j];
		}
	}
}
void RotateImage(IMAGE* pTo, IMAGE* pFrom, double rad)
{
	IMAGE* pWorking = GetWorkingImage();
	SetWorkingImage(pFrom);
	int iWidth = getwidth();
	int iHeight = getheight();												// 获取原图长宽

	while (rad > 2 * PI)													// 化简弧度
		rad -= 2 * PI;

	double pad = rad;														// 处理弧度
	if (pad > PI / 2 && pad <= PI)
	{
		pad -= PI / 2;
		pad = PI / 2 - pad;
	}
	else if (pad > PI && pad <= PI / 2 * 3)
	{
		pad -= PI;
	}
	else if (pad > PI / 2 * 3 && pad <= PI * 2)
	{
		pad -= PI / 2 * 3;
		pad = PI / 2 - pad;
	}

	int	tWidth = int(iWidth * cos(pad) + iHeight * sin(pad));
	int	tHeight = int(iHeight * cos(pad) + iWidth * sin(pad));				// 计算新图大小

	int iMinX = -(iWidth / 2), iMinY = -(iHeight / 2);
	int iMaxX = iMinX + iWidth, iMaxY = iMinY + iHeight;					// 计算原图最小（大）坐标

	int tMinX = -(tWidth / 2), tMinY = -(tHeight / 2);
	int tMaxX = tMinX + tWidth, tMaxY = tMinY + tHeight;					// 计算新图最小（大）坐标

	setorigin(-iMinX, -iMinY);												// 设置图片中心为原点

	SetWorkingImage(NULL);
	pTo->Resize(tWidth, tHeight);											// 初始化新图

	DWORD* dst = GetImageBuffer(pTo);
	DWORD* src = GetImageBuffer(pFrom);										// 获取新图、原图的缓冲区

	SetWorkingImage(pTo);
	for (int y1 = 0; y1 < tHeight; y1++)
	{
		for (int x1 = 0; x1 < tWidth; x1++)
			dst[x1] = 0x00000000;
		dst += tWidth;
	}
	SetWorkingImage(pWorking);
	for (int y1 = 0; y1 < tHeight; y1++)									// 初始化新图
		dst -= tWidth;

	for (int y1 = tMinY; y1 < tMaxY; y1++)
	{
		for (int x1 = tMinX; x1 < tMaxX; x1++)
		{
			int x = int(x1 * cos(rad) - y1 * sin(rad));
			int y = int(x1 * sin(rad) + y1 * cos(rad));						// 计算变换后坐标

			int sxy = (iHeight - (y - iMinY) - 1) * iWidth + (x - iMinX);
			int dxy = (tHeight - (y1 - tMinY) - 1) * tWidth + (x1 - tMinX);	// 计算坐标在缓冲区的位置

			if (x >= iMinX && x < iMaxX && y >= iMinY && y < iMaxY)			// 越界特判
				dst[dxy] = src[sxy];
		}
	}

	SetWorkingImage(pFrom);
	setorigin(0, 0);
	SetWorkingImage(pWorking);												// 还原原图坐标
}
IMAGE RotateImage2(IMAGE img, double radian)
{
	int WIDTH = img.getwidth();
	int HEIGHT = img.getheight();
	int max_x = WIDTH * cos(radian) + HEIGHT * sin(radian);
	int max_y = WIDTH * sin(radian) + HEIGHT * cos(radian);
	IMAGE Rimg(max_x, max_y);
	DWORD* P_data = GetImageBuffer(&img);
	IMAGE* myimg;
	myimg = new IMAGE();
	*myimg = img;
	DWORD* p_data = GetImageBuffer(myimg);		
	DWORD* my_data = GetImageBuffer(&Rimg);		
	double F[3][3];
	F[0][0] = 1;
	F[0][1] = 0;
	F[0][2] = 0;
	F[1][0] = 0;
	F[1][1] = -1;
	F[1][2] = 0;
	F[2][0] = -0.5 * max_x;
	F[2][1] = 0.5 * max_y;
	F[2][2] = 1;

	double nB[3][3];
	nB[0][0] = cos(radian);
	nB[0][1] = sin(radian);
	nB[0][2] = 0;
	nB[1][0] = -sin(radian);
	nB[1][1] = cos(radian);
	nB[1][2] = 0;
	nB[2][0] = 0;
	nB[2][1] = 0;
	nB[2][2] = 1;

	double nC[3][3];
	nC[0][0] = 1;
	nC[0][1] = 0;
	nC[0][2] = 0;
	nC[1][0] = 0;
	nC[1][1] = -1;
	nC[1][2] = 0;
	nC[2][0] = 0.5 * WIDTH;
	nC[2][1] = 0.5 * HEIGHT;
	nC[2][2] = 1;
	for (int j = 0; j < max_y; j++)
	{
		for (int i = 0; i < max_x; i++)
		{
			// 将图像反算
			double XY_3[3];
			XY_3[0] = i;
			XY_3[1] = j;
			XY_3[2] = 1;
			double XY2F[3];
			double XY2G[3];
			double needxy[3];
			multiply(XY_3, *F, XY2F, 1, 3, 3);
			multiply(XY2F, *nB, XY2G, 1, 3, 3);
			multiply(XY2G, *nC, needxy, 1, 3, 3);
			double db_x = needxy[0];
			double db_y = needxy[1];

			// 两种情况
			// 1.反算回去在矩阵中则双线性内插
			// 2.反算回去不在矩阵中则给它白色
			double gr;
			double gg;
			double gb;

			if (0 <= db_x && db_x <= WIDTH && 0 <= db_y && db_y <= HEIGHT)
			{
				// 这里进行双线性内插法
				if (((int(db_y) + 1) * WIDTH + int(db_x)) > (WIDTH - 1) * (HEIGHT - 1) || ((int(db_y) + 1) * WIDTH + int(db_x) + 1) > (WIDTH - 1) * (HEIGHT - 1))
				{
					continue;
				}
				else
				{
					double d_x = db_x - int(db_x);
					double d_y = db_y - int(db_y);
					//上下左右
					int gr11 = GetRValue(p_data[(int(db_y) * WIDTH + int(db_x))]);
					int gr12 = GetRValue(p_data[((int(db_y) + 1) * WIDTH + int(db_x))]);
					int gr21 = GetRValue(p_data[((int(db_y)) * WIDTH + int(db_x)) + 1]);
					int gr22 = GetRValue(p_data[((int(db_y) + 1) * WIDTH + int(db_x) + 1)]);
					gr = (1 - d_x) * (1 - d_y) * gr11 + (1 - d_x) * d_y * gr12 + d_x * (1 - d_y) * gr21 + d_x * d_y * gr22;

					int gg11 = GetGValue(p_data[(int(db_y) * WIDTH + int(db_x))]);
					int gg12 = GetGValue(p_data[((int(db_y) + 1) * WIDTH + int(db_x))]);
					int gg21 = GetGValue(p_data[((int(db_y)) * WIDTH + int(db_x)) + 1]);
					int gg22 = GetGValue(p_data[((int(db_y) + 1) * WIDTH + int(db_x) + 1)]);
					gg = (1 - d_x) * (1 - d_y) * gg11 + (1 - d_x) * d_y * gg12 + d_x * (1 - d_y) * gg21 + d_x * d_y * gg22;

					int gb11 = GetBValue(p_data[(int(db_y) * WIDTH + int(db_x))]);
					int gb12 = GetBValue(p_data[((int(db_y) + 1) * WIDTH + int(db_x))]);
					int gb21 = GetBValue(p_data[((int(db_y)) * WIDTH + int(db_x)) + 1]);
					int gb22 = GetBValue(p_data[((int(db_y) + 1) * WIDTH + int(db_x) + 1)]);
					gb = (1 - d_x) * (1 - d_y) * gb11 + (1 - d_x) * d_y * gb12 + d_x * (1 - d_y) * gb21 + d_x * d_y * gb22;

				}
			}
			else
			{
				gr = 255;
				gg = 255;
				gb = 255;
			}
			my_data[j * max_x + i] = RGB(gr, gg, gb);
		}
	}
	return Rimg;
}
void shrink(IMAGE* srcimg, double xrate, double yrate)
{
	int width = srcimg->getwidth();
	int height = srcimg->getheight();
	DWORD* psrc = GetImageBuffer(srcimg);//一个一维数组 获取了src所有像素点;
	DWORD** img = new DWORD * [height];
	DWORD** img2 = new DWORD * [height];

	for (int i = 0; i < height; i++)
	{
		*(img + i) = new DWORD[width];
		*(img2 + i) = new DWORD[width];
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			img[i][j] = psrc[i * width + j];
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int m = i / xrate;
			int n = j / yrate;
			img2[m][n] = img[i][j];
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			psrc[i * width + j] = img2[i][j];
		}
	}



}

INT CheckValue(INT value)
{
	return (value & ~0xff) == 0 ? value : value > 255 ? 255 : 0;
}

// 线性亮度/对比度调整
void HightLight(IMAGE* date, INT bright, INT contrast, BYTE threshold)
{

	DWORD* pdst = GetImageBuffer(date);
	if (bright == 0 && contrast == 0)
		return;

	FLOAT bv = bright <= -255 ? -1.0f : bright / 255.0f;
	if (bright > 0 && bright < 255)
		bv = 1.0f / (1.0f - bv) - 1.0f;

	FLOAT cv = contrast <= -255 ? -1.0f : contrast / 255.0f;
	if (contrast > 0 && contrast < 255)
		cv = 1.0f / (1.0f - cv) - 1.0f;

	BYTE values[256];
	for (INT i = 0; i < 256; i++)
	{
		INT v = contrast > 0 ? CheckValue(i + (INT)(i * bv + 0.5f)) : i;
		if (contrast >= 255)
			v = v >= threshold ? 255 : 0;
		else
			v = CheckValue(v + (INT)((v - threshold) * cv + 0.5f));
		values[i] = contrast <= 0 ? CheckValue(v + (INT)(v * bv + 0.5f)) : v;
	}



	for (int y = 0; y < date->getheight(); y++)
	{
		for (int x = 0; x < date->getwidth(); x++)
		{
			DWORD color = pdst[y * date->getheight() + x];
			int r = (UCHAR)color;
			int g = (UCHAR)(color >> 8);
			int b = (UCHAR)(color >> 16);
			int a = (UCHAR)(color >> 24);

			UCHAR r_ = values[r];
			UCHAR g_ = values[g];
			UCHAR b_ = values[b];
			pdst[y * date->getheight() + x] = RGB(r_, g_, b_);

		}
	}
}
//---------------------------------------------------------------------------

//双边滤波
void Bilateral_filters(IMAGE* srcimg, double sigma, int size)//----------第二代
{
	int halfsize = size / 2;
	int width = srcimg->getwidth();
	int height = srcimg->getheight();
	if (size % 2 != 0)
	{
		DWORD* psrc = GetImageBuffer(srcimg);//一个一维数组 获取了src所有像素点;
		DWORD** img = new DWORD * [height];
		for (int i = 0; i < height; i++)
		{
			*(img + i) = new DWORD[width];
		}
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				img[i][j] = psrc[i * width + j];
			}
		}
		DWORD* pdst = new DWORD[width * height];
		//-------------------------------------------构建一个二维数组来承载高斯核桃
		double** core = new double* [size];
		for (int i = 0; i < size; i++)
		{
			*(core + i) = new double[size];
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				double dist_2 = (i - halfsize) * (i - halfsize) + (j - halfsize) * (j - halfsize);
				core[i][j] = exp(-dist_2 / (2 * sigma * sigma));
			}
		}
		//-----------------------------------------------
		for (int i = 0; i < width * height; i++)
		{
			if (i < halfsize * width || i >= (width * height - halfsize * width) || (i % width) < halfsize || ((i + halfsize) % width) < halfsize)
			{
			}//去除边界点
			else
			{
				UCHAR newr = 0;
				UCHAR newg = 0;
				UCHAR newb = 0;
				double** Bilateralcore = new double* [size];
				for (int i = 0; i < size; i++)
				{
					*(Bilateralcore + i) = new double[size];//创建一个二维数组用来承载双边滤波核。
				}
				int centre_x = i / width;
				int centre_y = i % width;
				double centregery = (r(img[centre_x][centre_y]) + g(img[centre_x][centre_y]) + b(img[centre_x][centre_y])) / 3;
				double bsum = 0;
				int p = 0;
				for (int m = centre_x - halfsize; m <= centre_x + halfsize; m++)
				{
					if (p < size)
					{
						int q = 0;
						for (int n = centre_y - halfsize; n <= centre_y + halfsize; n++)
						{
							if (q < size)
							{
								double grey = (r(img[m][n]) + g(img[m][n]) + b(img[m][n])) / 3;
								double distcore_2 = (grey - centregery) * (grey - centregery);
								Bilateralcore[p][q] = exp(-distcore_2 / (2 * sigma * sigma)) * core[p][q];
								bsum += Bilateralcore[p][q];
								q++;
							}
						}
						p++;
					}
				}
				for (int i = 0; i < size; i++)
				{
					for (int j = 0; j < size; j++)
					{
						Bilateralcore[i][j] = Bilateralcore[i][j] / bsum;//归化，使权重和为1；
					}
				}
				int w = 0;
				for (int m = centre_x - halfsize; m <= centre_x + halfsize; m++)
				{
					if (w < size)
					{
						int v = 0;
						for (int n = centre_y - halfsize; n <= centre_y + halfsize; n++)
						{
							if (v < size)
							{
								newr += r(img[m][n]) * Bilateralcore[w][v];
								newg += g(img[m][n]) * Bilateralcore[w][v];
								newb += b(img[m][n]) * Bilateralcore[w][v];
								v++;
							}
						}
						w++;
					}
				}
				pdst[i] = RGB(newr, newg, newb);
			}
		}
		for (int i = 0; i < width * height; i++)
		{
			psrc[i] = pdst[i];
		}
		delete[]pdst;

	}
	else { cout << "请输入一个奇数作为高斯核的大小"; }
}

//中值滤波
void Midfilter(IMAGE* srcimg, int size)//----------第二代
{
	int S = size * size;
	int halfsize = size / 2;
	int width = srcimg->getwidth();
	int height = srcimg->getheight();
	if (size % 2 != 0)
	{
		DWORD* psrc = GetImageBuffer(srcimg);//一个一维数组 获取了src所有像素点;
		DWORD* pdst = new DWORD[width * height];
		DWORD* data = new DWORD[S];
		for (int i = 0; i < width * height; i++)
		{
			if (i < halfsize * width || i >= (width * height - halfsize * width) || (i % width) < halfsize || ((i + halfsize) % width) < halfsize)
			{
			}//去除边界点
			else
			{
				int* datar = new int[S];
				int* datag = new int[S];
				int* datab = new int[S];
				UCHAR newr = 0;
				UCHAR newg = 0;
				UCHAR newb = 0;
				int p = 0;
				for (int m = i - (width + 1) * halfsize; m <= i - (width + 1) * halfsize + (size - 1) * width; m = m + width)
				{
					for (int j = m; j <= m + size - 1; j++)
					{
						datar[p] = (int)r(psrc[j]);
						datag[p] = (int)g(psrc[j]);
						datab[p] = (int)b(psrc[j]);
						p++;
					}
				}
				BubbleSort(datar, S);
				BubbleSort(datag, S);
				BubbleSort(datab, S);
				newr = (UCHAR)datar[S / 2];
				newg = (UCHAR)datag[S / 2];
				newb = (UCHAR)datab[S / 2];
				pdst[i] = RGB(newr, newg, newb);
			}
		}
		for (int i = 0; i < width * height; i++)
		{
			psrc[i] = pdst[i];
		}
		delete[]pdst;

	}
	else { cout << "请输入一个奇数"; }
}
//噪点添加
void gaussnoise(IMAGE* srcimg, int num)
{
	DWORD* psrc = GetImageBuffer(srcimg);//一个一维数组 获取了src所有像素点;
	double x;
	double y;
	for (int j = 0; j < num; j++)
	{
		x = rand() % srcimg->getwidth();
		y = rand() % srcimg->getheight();
		int i = y * srcimg->getwidth() + x;

		UCHAR r = rand() % 255;
		UCHAR g = rand() % 255;
		UCHAR b = rand() % 255;
		psrc[i] = RGB(r, g, b);
	}
}


