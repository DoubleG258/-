// 别踩白块.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<vector>
#include <graphics.h>
#include<time.h>

#define N 5
std::vector<int> Map(5);//定义了一个数组，存储黑块的位置

int MapX, MapY,Score=0;

//随机产生黑块的坐标
void InitBlack() {
	for (int i = 0; i < N - 1; i++) {
		Map[i] = rand() % N;

	}
}

//绘制黑块
void DrawBlack() {
	for (int i = 0; i < N; i++) {
		fillrectangle(Map[i] * 100, i * 120, Map[i] * 100+100, i * 120+120);
	}
 }

//绘制界面
void Draw() {
	BeginBatchDraw();
	cleardevice();//清屏
	//设置线条的颜色
	setlinecolor(BLACK); 
	setfillcolor(WHITE);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			fillrectangle(j * 100, i * 120, (j + 1) * 100, (i + 1) * 120); //绘制一个填充的矩形左上角的点和右上角的点
		}
	}
	setfillcolor(BLACK);
	DrawBlack();
	EndBatchDraw();

}

bool Play() {
	MOUSEMSG msg;
	msg = GetMouseMsg();
	switch (msg.uMsg) {
	case WM_LBUTTONDOWN:
		MapY = msg.y / 120;
		MapX = msg.x / 100;
		if (Map[3] == MapX && MapY == 3) {//点击最后一行的块并且是黑块
			for (int i = 3; i > 0; i--) {// 擦除被点击的格子
				Map[i] = Map[i - 1];
			}
			Map[0] = rand() % N;
			Score += 10;
			printf("你点击到了黑块！\n");
		}
		else {
			printf("未点击到黑块！\n");
			return true;

		}
		break;
	}
	return false;
}

int main()
{	
	srand((unsigned)time(NULL));//通过时间做随机数的种子
	//1.创建界面

	initgraph(500,480,SHOWCONSOLE);
	//四行五列宽度100高度120


	InitBlack();//初始化
	while (1) {
		Draw();//绘制方块
		if (Play()) {
			char str[128];
			sprintf(str, "总计消除格子%d,总计得分%d", Score / 10, Score);
			MessageBox(GetHWnd(),str,"Game Over",MB_OK);
			exit(0);//结束程序
		}
	}

	//卡屏
	getchar();
	return 0;
}


