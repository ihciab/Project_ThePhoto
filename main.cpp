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
#include "HuffmanTree_.h"
#include "Compress.h"
#include"Picture.h"
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
int button[19][4] = { {30,20,130,60},{170,20,220,60},{260,20,360,60} ,{400,20,500,60},{400,120,500,160},{400,220,500,260},
	{500,20,600,60},{500,120,600,160},{500,220,600,260},
	{600,20,700,60},{600,120,650,160},{600,220,700,260},
	{400,60,500,120},{500,60,550,120},{600,60,650,90} ,{600,60,650,120}, {650,60,700,120},
	 {650,120,700,160},{550,60,600,120} };          //按钮的二维数组
MOUSEMSG m1, m2, m3, m4, m5;
int button_judge(int x, int y)
{
	if (x > button[0][0] && x<button[0][2] && y>button[0][1] && y < button[0][3])return 1;
	if (x > button[1][0] && x<button[1][2] && y>button[1][1] && y < button[1][3])return 2;
	if (x > button[2][0] && x<button[2][2] && y>button[2][1] && y < button[2][3])return 3;
	if (x > button[3][0] && x<button[3][2] && y>button[3][1] && y < button[3][3])return 4;
	if (x > button[4][0] && x<button[4][2] && y>button[4][1] && y < button[4][3])return 5;
	if (x > button[5][0] && x<button[5][2] && y>button[5][1] && y < button[5][3])return 6;
	if (x > button[6][0] && x<button[6][2] && y>button[6][1] && y < button[6][3])return 7;
	if (x > button[7][0] && x<button[7][2] && y>button[7][1] && y < button[7][3])return 8;
	if (x > button[8][0] && x<button[8][2] && y>button[8][1] && y < button[8][3])return 9;
	if (x > button[9][0] && x<button[9][2] && y>button[9][1] && y < button[9][3])return 10;
	if (x > button[10][0] && x<button[10][2] && y>button[10][1] && y < button[10][3])return 11;
	if (x > button[11][0] && x<button[11][2] && y>button[11][1] && y < button[11][3])return 12;
	if (x > button[12][0] && x<button[12][2] && y>button[12][1] && y < button[12][3])return 13;
	if (x > button[13][0] && x<button[13][2] && y>button[13][1] && y < button[13][3])return 14;
	if (x > button[14][0] && x<button[14][2] && y>button[14][1] && y < button[14][3])return 15;
	if (x > button[15][0] && x<button[15][2] && y>button[15][1] && y < button[15][3])return 16;
	if (x > button[16][0] && x<button[16][2] && y>button[16][1] && y < button[16][3])return 17;
	if (x > button[17][0] && x<button[17][2] && y>button[17][1] && y < button[17][3])return 18;
	if (x > button[18][0] && x<button[18][2] && y>button[18][1] && y < button[18][3])return 19;
	return 0;
}





int _tmain(int argc, char* argv[])
{


	int TEST_X = 50;
	int TEST_Y = 320;
	int event = 0;
	int i;
	//创建窗口
	initgraph(1000, 800, EW_SHOWCONSOLE);//可显示出两块屏幕
	//设置窗口背景颜色;
	setbkcolor(WHITE);
	cleardevice();
	//保存图片
	IMAGE TEST;
	IMAGE gray;
	IMAGE Light;
	IMAGE oldimg;
	IMAGE OrImage;
	IMAGE Roatimg;
	//加载图片


	//使用前一定要重新写自己的路径！
	char _FILE[256] = "D:/Cstudy/C++study/Project_Thephoto/target.bmp";
	char e_FILE[256] = "D:/Cstudy/C++study/Project_Thephoto/target.bmp.huf";
	LPCTSTR  FILE = _T("D:/Cstudy/C++study/Project_Thephoto/target.bmp");
	//使用前一定要重新写自己的路径！






	loadimage(&TEST, FILE, 320, 320);
	loadimage(&OrImage, FILE, 320, 320);
	/*loadimage(&Limg, FILE);*/

	int img_w = TEST.getwidth();
	int img_h = TEST.getheight();




	int huf_flag = 3;
	MOUSEMSG m;//鼠标指针
	while (true)
	{
	Case1:
#pragma region 按钮界面
		RECT R1 = { button[0][0],button[0][1],button[0][2],button[0][3] };
		RECT R2 = { button[1][0],button[1][1],button[1][2],button[1][3] };
		RECT R3 = { button[2][0],button[2][1],button[2][2],button[2][3] };
		RECT R4 = { button[3][0],button[3][1],button[3][2],button[3][3] };
		RECT R5 = { button[4][0],button[4][1],button[4][2],button[4][3] };
		RECT R6 = { button[5][0],button[5][1],button[5][2],button[5][3] };
		RECT R7 = { button[6][0],button[6][1],button[6][2],button[6][3] };
		RECT R8 = { button[7][0],button[7][1],button[7][2],button[7][3] };
		RECT R9 = { button[8][0],button[8][1],button[8][2],button[8][3] };
		RECT R10 = { button[9][0],button[9][1],button[9][2],button[9][3] };
		RECT R11 = { button[10][0],button[10][1],button[10][2],button[10][3] };
		RECT R12 = { button[11][0],button[11][1],button[11][2],button[11][3] };
		RECT R13 = { button[12][0],button[12][1],button[12][2],button[12][3] };
		RECT R14 = { button[13][0],button[13][1],button[13][2],button[13][3] };
		RECT R15 = { button[14][0],button[14][1],button[14][2],button[14][3] };
		RECT R16 = { button[15][0],button[15][1],button[15][2],button[15][3] };
		RECT R17 = { button[16][0],button[16][1],button[16][2],button[16][3] };
		RECT R18 = { button[17][0],button[17][1],button[17][2],button[17][3] };
		RECT R19 = { button[18][0],button[18][1],button[18][2],button[18][3] };
		LOGFONT f;
		gettextstyle(&f);					                                      //获取字体样式
		_tcscpy(f.lfFaceName, _T("宋体"));	                                      //设置字体为宋体
		f.lfQuality = ANTIALIASED_QUALITY;                                        // 设置输出效果为抗锯齿  
		settextstyle(&f);                                                         // 设置字体样式
		settextcolor(BLACK);                                                      //BLACK在graphic.h头文件里面被定义为黑色的颜色常量
		drawtext(_T("画图/复原"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);        //在矩形区域R1内输入文字，水平居中，垂直居中，单行显示
		drawtext(_T("压缩"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);        //在矩形区域R2内输入文字，水平居中，垂直居中，单行显示
		drawtext(_T("解压缩"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);      //在矩形区域R3内输入文字，水平居中，垂直居中，单行显示
		drawtext(_T("反色"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("转灰度"), &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("高斯滤波"), &R6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("镜像"), &R7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("翻转"), &R8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("双边滤波"), &R9, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("复古"), &R10, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("旋"), &R11, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("中值滤波"), &R12, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("高亮"), &R13, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("边缘化"), &R14, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("X"), &R15, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("Y"), &R16, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("缩小"), &R17, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("转"), &R18, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("马赛克"), &R19, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		setlinecolor(BLACK);
		rectangle(button[0][0], button[0][1], button[0][2], button[0][3]);
		rectangle(button[1][0], button[1][1], button[1][2], button[1][3]);
		rectangle(button[2][0], button[2][1], button[2][2], button[2][3]);
		rectangle(button[3][0], button[3][1], button[3][2], button[3][3]);
		rectangle(button[4][0], button[4][1], button[4][2], button[4][3]);
		rectangle(button[5][0], button[5][1], button[5][2], button[5][3]);
		rectangle(button[6][0], button[6][1], button[6][2], button[6][3]);
		rectangle(button[7][0], button[7][1], button[7][2], button[7][3]);
		rectangle(button[8][0], button[8][1], button[8][2], button[8][3]);
		rectangle(button[9][0], button[9][1], button[9][2], button[9][3]);
		rectangle(button[10][0], button[10][1], button[10][2], button[10][3]);
		rectangle(button[11][0], button[11][1], button[11][2], button[11][3]);
		rectangle(button[12][0], button[12][1], button[12][2], button[12][3]);
		rectangle(button[13][0], button[13][1], button[13][2], button[13][3]);
		rectangle(button[14][0], button[14][1], button[14][2], button[14][3]);
		rectangle(button[15][0], button[15][1], button[15][2], button[15][3]);
		rectangle(button[16][0], button[16][1], button[16][2], button[16][3]);
		rectangle(button[17][0], button[17][1], button[17][2], button[17][3]);
		rectangle(button[18][0], button[18][1], button[18][2], button[18][3]);
		m = GetMouseMsg();//获取一条鼠标消息

		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
			setfillcolor(WHITE);//填充颜色为白色
			if (button_judge(m.x, m.y) != 0)
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//记录这一次触发的按钮
					fillrectangle(button[event - 1][0], button[event - 1][1], button[event - 1][2], button[event - 1][3]);//有框填充矩形（X1,Y1,X2,Y2）
				}
			}
			else
			{
				if (event != 0)//上次触发的按钮未被修正为原来的颜色
				{
					fillrectangle(button[event - 1][0], button[event - 1][1], button[event - 1][2], button[event - 1][3]);//两次同或为原来颜色
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);           //二元光栅——NOT(屏幕颜色 XOR 当前颜色)

			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				Sleep(30);//停顿30ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}

#pragma endregion
			//画图&复原
			if (button_judge(m.x, m.y) == 1)
			{
				TEST = OrImage;
				drawImg_s(TEST_X, TEST_Y, &OrImage);

			}
			//压缩
			if (button_judge(m.x, m.y) == 2)
			{
				_Huffman(_FILE);
				huf_flag = 1;
			}
			//解压缩
			if (button_judge(m.x, m.y) == 3)
			{
				if (huf_flag == 1)
				{
					Compress(_FILE, e_FILE);

				}
				else if (huf_flag != 1)
				{
					cout << "尚未进行压缩" << endl;
					goto Case1;
				}

			}
			//反色
			if (button_judge(m.x, m.y) == 4)
			{

				turncolor_s(&TEST);
				putimage(TEST_X, TEST_Y, &TEST);
				saveimage(_T("D:/Cstudy/C++study/Project_Thephoto/targetturn.bmp"), &TEST);
				goto Case1;
			}
			//转灰度
			if (button_judge(m.x, m.y) == 5)
			{

				toGray(&gray, &TEST);
				putimage(TEST_X, TEST_Y, &gray);
				goto Case1;

			}

			//高斯滤波
			if (button_judge(m.x, m.y) == 6)
			{

				gauss(&TEST);
				putimage(TEST_X, TEST_Y, &TEST);
				goto Case1;
			}

			//镜像

			if (button_judge(m.x, m.y) == 7)
			{

				Mirror(&TEST);
				putimage(TEST_X, TEST_Y, &TEST);
				goto Case1;

			}
			//翻转 
			if (button_judge(m.x, m.y) == 8)
			{

				turnImg(&TEST);
				putimage(TEST_X, TEST_Y, &TEST);
				goto Case1;

			}
			//双边滤波
			if (button_judge(m.x, m.y) == 9)
			{
				//缺省调用 可自行添加参数
				double sigma = 21.00;


				Bilateral_filters(&TEST, sigma, 9);
				putimage(TEST_X, TEST_Y, &TEST);



			}
			//复古
			if (button_judge(m.x, m.y) == 10)
			{
				turn_old(&oldimg, &TEST);
				putimage(TEST_X, TEST_Y, &oldimg);
			}
			// 旋转左右键  
			if (button_judge(m.x, m.y) == 11)
			{

				while (1)
				{
					m5 = GetMouseMsg();
					IMAGE NewImg;
					if (m5.uMsg == WM_LBUTTONDOWN)
					{
						RotateImage(&NewImg, &TEST, (PI / 48.00));
						TEST = NewImg;
						saveimage(_T("D:/Cstudy/C++study/Project_Thephoto/target_turn.bmp"), &NewImg);
						
						putimage(TEST_X, TEST_Y, &NewImg);
					}
					if (m5.uMsg == WM_RBUTTONDOWN)
					{
						RotateImage(&NewImg, &TEST, 2 * PI - (PI / 48.00));
						TEST = NewImg;
						saveimage(_T("D:/Cstudy/C++study/Project_Thephoto/target_turn.bmp"), &NewImg);

						putimage(TEST_X, TEST_Y, &NewImg);
					}
					else if (m5.uMsg == WM_MBUTTONDOWN)
					{

						cleardevice();
						break;

					}
				}
			}
			//中值滤波
			if (button_judge(m.x, m.y) == 18)
			{

				Roatimg = RotateImage2(TEST, PI / 48.00);
				putimage(TEST_X, TEST_Y, &Roatimg);
				TEST = Roatimg;

			}

			if (button_judge(m.x, m.y) == 12)
			{

				Midfilter(&TEST, 9);
				putimage(TEST_X, TEST_Y, &TEST);
				goto Case1;

			}
			//高亮
			if (button_judge(m.x, m.y) == 13)
			{
				int light = -20;
				while (1)
				{
					m1 = GetMouseMsg();
					if (m1.uMsg == WM_MOUSEWHEEL)
					{

						light += 1;
						HightLight(&TEST, light, 0, 121);
						putimage(TEST_X, TEST_Y, &TEST);
						if (light > 120)
							break;
					}
					else if (m1.uMsg == WM_MBUTTONDOWN)
						break;
				}

			}
			//边缘化
			if (button_judge(m.x, m.y) == 14)
			{
				edge(&TEST);
				putimage(TEST_X, TEST_Y, &TEST);


			}
			//粗糙的放大缩小
			if (button_judge(m.x, m.y) == 15)
			{
				Enlarge_X(&TEST, 2);


				putimage(TEST_X, TEST_Y, &TEST);

			}
			//旋转
			if (button_judge(m.x, m.y) == 16)
			{
				Enlarge_Y(&TEST, 2);
				putimage(TEST_X, TEST_Y, &TEST);
				;
			}
			/*Mosaic(&TEST);
			putimage(TEST_X, TEST_Y, &TEST);*/
			if (button_judge(m.x, m.y) == 17)
			{

				shrink(&TEST, 2, 2);
				putimage(TEST_X, TEST_Y, &TEST);
			}
			if (button_judge(m.x, m.y) == 19)
			{

				Mosaic(&TEST);
				putimage(TEST_X, TEST_Y, &TEST);
			}
		}
	}

	goto Case1;
	getchar();//延长窗口时间
	return 0;

}