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
const Second animationTime = 0.05f;

struct POS {
	int x, y;
};

const POS positions[5] = {
	{95, 390},{95, 340},{95, 290},{95, 240},{95, 190} };

int y[5] = {190,240,290,340,390};
int y1[5] = { 1,1,1,1,1 };
int y2[5] = { 0,0,0,0,0 };
int y3[5] = { 0,0,0,0,0 };

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

int check1()
{
	for (int i = 0; i < 5; i++)
	{
		if (y1[i] == 0)
		y1[i] = 1;
		return i;
	}
}
int check2()
{
	for (int i = 0; i < 5; i++)
	{
		if (y2[i] == 0)
		y2[i] = 1;
		return i;
	}
}
int check3()
{
	for (int i = 0; i < 5; i++)
	{
		if (y3[i] == 0)
		y3[i] = 1;
		return i;
	}
}

void check11()
{
	for (int i = 4; i >= 0; i--)
	{
		if (y1[i] == 1)
		y1[i] = 0;
		return;
	}
}
void check22()
{
	for (int i = 4; i >= 0; i--)
	{
		if (y2[i] == 1)
		y2[i] = 0;
		return;
	}
}
void check33()
{
	for (int i = 4; i >= 0; i--)
	{
		if (y3[i] == 1)
		y3[i] = 0;
		return;
	}
}

	void move( int n, int* a, int* b, int* c)
{	
		int i,k;
	if (n == 1) {
		//printf("원판1 - %c to %c\n", a, b);
		locateObject(initObjects[0], scene1, *b, 190);
	}
	else {	
	    move(n - 1, a, c, b);
		if (*b == 95)  i = check1();
		if (*b == 395) i = check2();
		if (*b == 695) i = check3();
		if (*a == 95)  check11();
		if (*a == 395) check22();
		if (*a == 695) check33();
		locateObject(initObjects[n-1], scene1, *b, y[i]);
		//printf("원판%d - %c to %c\n", n, a, b);
		move(n - 1, c, b, a);
	}
	setTimer(timerMixing, animationTime);
	startTimer(timerMixing);
}

int n=5, a = 95, b = 395, c = 695;

void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
	int a = 95, b = 395, c = 695;
	if (object == start) {
		timerMixing = createTimer();
		move(n, &a, &b, &c);
	}
}

void timerCallback(TimerID timer)
{
	if (mixCount > 0) {
		--mixCount;	
		move(n, &c, &b, &a);
	}
	setTimer(timerMixing, animationTime);
	startTimer(timerMixing);
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