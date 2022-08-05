#include<stdio.h>
#include<easyx.h>
#include<time.h>
#include<conio.h>

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define STAR_NUM 500
#define METEOR_NUM 50
struct Star {
	int x, y, r;
	int speed;		//速度
	COLORREF color;	//颜色
};
struct Meteor {
	int x;
	int y;
	int speed;
};
struct Star star[STAR_NUM];
struct Meteor meteor[METEOR_NUM];

//小星星
//初始化
void initStar(int i) {
	star[i].x = rand() % getwidth();
	star[i].y = rand() % getheight();
	star[i].r = rand() % 3 ;
	star[i].speed = rand() % 5;//0 1 2 3 4
	star[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
}
//绘制星星
void drawStar() {
	for (size_t i = 0; i < STAR_NUM; i++) {
		//putpixel(star[i].x, star[i].y, star[i].color);
		setfillcolor(star[i].color);
		solidcircle(star[i].x, star[i].y, star[i].r);
	}
}
//移动星星
void moveStar() {
	for (size_t i = 0; i < STAR_NUM; i++)
	{
		star[i].x+=star[i].speed;
		if (star[i].x > getwidth()) {
			star[i].x = 0;
		}
	}
}
//流星
IMAGE img[2];
IMAGE bk;
void loadImg() {
	loadimage(img + 0, _T("./images/1.png"),50,50);
	loadimage(img + 1, _T("./images/2.png"),50,50);
}
//初始化流星
void initMeteor(int i) {
	//[0,2400)
	//[-1200,1200)
	meteor[i].x = rand() % (2 * getwidth()) - getwidth();//[-1200,1200)
	meteor[i].y = 20 - 200;
	meteor[i].speed = rand() % 9 + 1;
}
//绘制流星：贴图
void drawMeteor() {
	for (size_t i = 0; i < METEOR_NUM; i++)
	{
		putimage(meteor[i].x, meteor[i].y, img + rand() % 2,SRCPAINT);
	}
}
//移动流星
void moveMeteor() {
	for (size_t i = 0; i < METEOR_NUM; i++)
	{
		meteor[i].x += meteor[i].speed;
		meteor[i].y += meteor[i].speed;
		if (meteor[i].x >= getwidth() || meteor[i].y >= getheight())
		{
			initMeteor(i);
		}
	}
}

void welcome() {
	//播放音乐
	mciSendString(_T("open ./images/浪漫空气.mp3"), NULL, 0, NULL);
	mciSendString(_T("play ./images/浪漫空气.mp3"), NULL, 0, NULL);

	//设置随机数种子
	srand((unsigned)time(NULL));

	//设置背景模式
	setbkmode(TRANSPARENT);

	//设置文字样式
	settextstyle(40, 0, _T("华文行楷"));
	//输出文字

	//如果没有按键按下，就一直循环
	while (!_kbhit()) {
		cleardevice();
		putimage(0, 0, &bk);

		//设置文字颜色
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));

		int tx = (getwidth() - textwidth(_T("淼捷Love"))) / 2;
		outtextxy(tx, 50, _T("淼捷Love"));
		outtextxy(200, 100, _T("    我一生很短，只够喜欢你一人"));
		outtextxy(200, 150, _T("    只有你在身边才会感觉到温暖，所以亲爱"));
		outtextxy(200, 200, _T("的，请每时每刻带在我的身边。"));
		outtextxy(200, 250, _T("    我虽然没有生动的语言去描绘我对你的感"));
		outtextxy(200, 300, _T("情，但是我有一颗真挚的心，只要你愿意感受，"));
		outtextxy(200, 350, _T("就能感觉到我的爱。"));
		outtextxy(200, 400, _T("    你是我的心是我的全部在我的世界里没有"));
		outtextxy(200, 450, _T("你怎么能叫幸福呢? "));
		outtextxy(200, 500, _T("    你知道吗?和你第1次牵手就已经注定了我们"));
		outtextxy(200, 550, _T("以后的缘分，直到带上结婚戒指的那一天你都"));
		outtextxy(200, 600, _T("是我的。 "));
		outtextxy(200, 650, _T("                   ------------------淼捷Love"));

		for (size_t i = 0; i < 10; i++) {
			settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
			outtextxy(rand() % getwidth(), rand() % getheight(), _T("♥"));
		}

		Sleep(1000);
	}
}

int main() {
	//1.创建图形窗口
	initgraph(1200, 800);
	//设置背景颜色
	/*setbkcolor(RGB(99, 99, 99));
	cleardevice();*/
	
	loadimage(&bk, _T("./images/bk.jpg"), getwidth(), getheight());

	for (size_t i = 0; i < STAR_NUM; i++)
	{
		initStar(i);
	}
	for (size_t i = 0; i < METEOR_NUM; i++)
	{
		initMeteor(i);
	}
	loadImg();
	welcome();

	//双缓冲绘图
	BeginBatchDraw();
	while (true) {
		cleardevice();
		putimage(0, 0, &bk);

		drawStar();
		moveStar();

		drawMeteor();
		moveMeteor();

		FlushBatchDraw();
	}
	EndBatchDraw();

	getchar();
	return 0;
}
