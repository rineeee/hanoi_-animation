#include<bangtal.h>
#include<stdio.h>
#include<windows.h>
#include <stdlib.h>
#include <time.h>

SceneID scene1;
ObjectID start;
ObjectID initObjects[5];
TimerID timerMixing;
int mixCount = 31;
const Second animationTime = 0.1f;

int i = 0;
int  k = 0;
int a_k[40], b_k[40], c_k[40];
int p = 0;
//각 'a' 'b' 'c' 열에 칸이 있는지 없는지 여부 파악용 
int y[5] = { 190,240,290,340,390 };
int y1[5] = { 1,1,1,1,1 };
int y2[5] = { 0,0,0,0,0 };
int y3[5] = { 0,0,0,0,0 };

//사진 지정을 위한 구조체
struct POS {
	int x, y;
};

const POS positions[5] = {
	{95, 390},{95, 340},{95, 290},{95, 240},{95, 190} };

//사진을 intitObjects에 넣고 show
void put()
{
	char image[25];
	for (int i = 0; i < 5; i++) {
		sprintf_s(image, "%d.png", i + 1);
		initObjects[i] = createObject(image);
		locateObject(initObjects[i], scene1, positions[i].x, positions[i].y);
		showObject(initObjects[i]);
	}
}

//check1~check33 각 열에 칸여부 파악 및 변경
int check1()
{
	for (int i = 0; i < 5; i++)
	{
		if (y1[i] == 0)
		{
			y1[i] = 1;
			return i;
		} 
		
	}
}
int check2()
{
	for (int i = 0; i < 5; i++)
	{
		if (y2[i] == 0)
		{
			y2[i] = 1;
			return i;
		}
	}
}
int check3()
{
	for (int i = 0; i < 5; i++)
	{
		if (y3[i] == 0)
		{
			y3[i] = 1;
			return i;
		}
	}
}

void check11()
{
	for (int i = 4; i >= 0; i--)
	{
		if (y1[i] == 1)
		{
			y1[i] = 0;
			return;
		}
	}
}
void check22()
{
	for (int i = 4; i >= 0; i--)
	{
		if (y2[i] == 1)
		{
			y2[i] = 0;
			return;
		}
	}
}
void check33()
{
	for (int i = 4; i >= 0; i--)
	{
		if (y3[i] == 1)
		{
			y3[i] = 0;
			return;
		}
	}
}
void mix() {
	locateObject(initObjects[a_k[p] - 1], scene1, b_k[p], y[c_k[p]]);
	setTimer(timerMixing, animationTime);
	startTimer(timerMixing);
}

//하노이 함수
void move(int n, int a, int b, int c)
{	
	if (n == 1) {
		//printf("원판1 - %c to %c\n", a, b);
		if (b == 95)  i = check1();
		if (b == 395) i = check2();
		if (b == 695) i = check3();
		if (a == 95)  check11();
		if (a == 395) check22();
		if (a == 695) check33();
		a_k[k] = n;
		b_k[k] = b;
		c_k[k] = i;
		k++;
		//locateObject(initObjects[0], scene1, b, y[i]);

	}
	else {
		move(n - 1, a, c, b);
		if (b == 95)  i = check1();
		if (b == 395) i = check2();
		if (b == 695) i = check3();
		if (a == 95)  check11();
		if (a == 395) check22();
		if (a == 695) check33();
		a_k[k] = n;
		b_k[k] = b;
		c_k[k] = i;
		k++;
		//locateObject(initObjects[n - 1], scene1, b, y[i]);
		//printf("원판%d - %c to %c\n", n, a, b);
		move(n - 1, c, b, a);

	}

}


void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{

	if (object == start) {
		move(5, 95, 395, 695);
		timerMixing = createTimer();
		setTimer(timerMixing, animationTime);
		startTimer(timerMixing);
	}
}

void timerCallback(TimerID timer)
{

	if (mixCount > 0) {
		--mixCount;
		mix();
		p++;
	}

}


ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown)
{
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);

	if (shown) {
		showObject(object);
	}

	return object;
}


int main()
{
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);

	scene1 = createScene("하노이탑", "main.png");
	start = createObject("start.png", scene1, 100, 25, true);
	put();

	startGame(scene1);
}