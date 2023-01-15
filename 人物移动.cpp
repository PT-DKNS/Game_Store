#include <graphics.h>
#include <time.h>
#include <conio.h>
#define SPEED 8

struct People {
	int x;
	int y;
	int dx;
	int dy;
	int towards;
};

struct People man = { 300,300,SPEED,SPEED,1 };

int Timer(int duration, int id) {
	static int startTime[10];
	int endTime = clock();
	if (endTime - startTime[id] > duration) {
		startTime[id] = endTime;
		return 1;
	}
	return 0;
}

void Move() {
	int userkey = _getch();
	switch (userkey) {
	case 'w':
	case 'W':
	case 72:
		man.y -= man.dy;
		man.towards = 0;
		break;
	case 's':
	case 'S':
	case 80:
		man.y += man.dy;
		man.towards = 1;
		break;
	case 'a':
	case 'A':
	case 75:
		man.x -= man.dx;
		man.towards = 2;
		break;
	case 'd':
	case 'D':
	case 77:
		man.x += man.dx;
		man.towards = 3;
		break;
	/*
	default:
		man.towards = 1;
		break;
	*/
	}
}

void DrawPeople(IMAGE* people,int pos) {
	switch (man.towards) {
	case 0:
		putimage(man.x, man.y, &people[6 + pos%3 * 2], SRCPAINT);
		putimage(man.x, man.y, &people[7 + pos%3 * 2], SRCAND);
		break;
	case 1:
		putimage(man.x, man.y, &people[pos % 3 * 2], SRCPAINT);
		putimage(man.x, man.y, &people[1+ pos % 3 * 2], SRCAND);
		break;
	case 2:
		putimage(man.x, man.y, &people[12 + pos % 2 * 2], SRCPAINT);
		putimage(man.x, man.y, &people[13 + pos % 2 * 2], SRCAND);
		break;
	case 3:
		putimage(man.x, man.y, &people[16 + pos % 2 * 2], SRCPAINT);
		putimage(man.x, man.y, &people[17 + pos % 2 * 2], SRCAND);
		break;
	}
}


int main() {
	initgraph(1000, 500);
	int pos=0;
	IMAGE bk;
	IMAGE people[20];
	loadimage(&bk, "./Photo/bk.jpg", 1000, 500);
	loadimage(&people[0], "./Photo/Front_stand_b.jpg", 100, 120);
	loadimage(&people[1], "./Photo/Front_stand_w.jpg", 100, 120);
	loadimage(&people[2], "./Photo/Front_left_b.jpg", 100, 120);
	loadimage(&people[3], "./Photo/Front_left_w.jpg", 100, 120);
	loadimage(&people[4], "./Photo/Front_right_b.jpg", 100, 120);
	loadimage(&people[5], "./Photo/Front_right_w.jpg", 100, 120);
	loadimage(&people[6], "./Photo/Back_stand_b.jpg", 100, 120);
	loadimage(&people[7], "./Photo/Back_stand_w.jpg", 100, 120);
	loadimage(&people[8], "./Photo/Back_left_b.jpg", 100, 120);
	loadimage(&people[9], "./Photo/Back_left_w.jpg", 100, 120);
	loadimage(&people[10], "./Photo/Back_right_b.jpg", 100, 120);
	loadimage(&people[11], "./Photo/Back_right_w.jpg", 100, 120);
	loadimage(&people[12], "./Photo/Left_low_b.jpg", 100, 120);
	loadimage(&people[13], "./Photo/Left_low_w.jpg", 100, 120);
	loadimage(&people[14], "./Photo/Left_high_b.jpg", 100, 120);
	loadimage(&people[15], "./Photo/Left_high_w.jpg", 100, 120);
	loadimage(&people[16], "./Photo/Right_low_b.jpg", 100, 120);
	loadimage(&people[17], "./Photo/Right_low_w.jpg", 100, 120);
	loadimage(&people[18], "./Photo/Right_high_b.jpg", 100, 120);
	loadimage(&people[19], "./Photo/Right_high_w.jpg", 100, 120);
	BeginBatchDraw();
	while (1) {
		cleardevice();
		putimage(0, 0, &bk);
		if (Timer(100, 0)) {
			Move();
			pos++;
		}
		DrawPeople(people,pos);
		if (pos > 1000) {
			pos -= 1000;
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
	return 0;
}
