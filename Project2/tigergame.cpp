#include"acllib.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
const int winWidth = 600, winHeight = 620;
const int imgWidth = 200, imgHeight = 200;
int Rank = 1, maxRank = 5;
int x = 0, y = 20, n = 1;
ACL_Image img[4];
ACL_Sound music;
char name[] = "1.jpg";
char Song[] = "Music.mp3";
char str[10];
int pos[3][3];
void init();
void paint();
void timerEvent(int id);
void keyEvent(int key, int n);
int Setup()
{
	srand((unsigned)time(NULL));
	initWindow("Tiger Game", 0, 0, winWidth, winHeight);
	init();
	registerTimerEvent(timerEvent);
	startTimer(0, 1);//进入游戏时一秒钟就行啦，不用startTimer（0,1200）,这样会白屏一段时间；
	registerKeyboardEvent(keyEvent);
	return 0;
}
void init()
{
	for (int i = 0; i < 4; i++)
	{
		name[0] = i + 1 + '0';
		loadImage(name, &img[i]);
	}
	loadSound(Song, &music);
	for (int j = 0; j < 3; j++)
	{
		for (int s = 0; s < 3; s++)
		{
			pos[j][s] = rand() % 4;
		}
	}
}
void paint()
{
	beginPaint();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			putImageScale(&img[pos[i][j]], j*200, i*200+y, imgWidth, imgHeight);
			//putImageScale(&img[pos[i][j]], i * 200, j * 200+y, imgWidth, imgHeight);
		}
	}
	endPaint();
}
void timerEvent(int id)
{
	playSound(music, 1);
	switch (Rank)
	{
	case 1:startTimer(0, 1200);
		break;
	case 2:startTimer(0, 1000);
		break;
	case 3:startTimer(0, 800);
		break;
	case 4:startTimer(0, 600);
		break;
	case 5:startTimer(0, 400);
		break;
	default:
		break;
	}
	if (id == 0)
	{
		int i, j;
		for (i = 2; i>0;--i)
		{
			for (j = 0; j < 3; j++)
			{
				pos[i][j] = pos[i-1][j];
			}
		}
		for (j = 0; j < 3; ++j)
		{
			pos[0][j] = rand() % 4;
		}
		paint();
		sprintf_s(str, "Rank:%d", Rank);
		beginPaint();
		setTextSize(20);
		paintText(winWidth / 2-30, 0, str);
		line(1, imgHeight+y, winWidth-1, imgHeight + y);
		line(winWidth - 1, imgHeight + y, winWidth - 1, 2 * imgHeight + y);
		line(winWidth - 1, 2 * imgHeight + y, 1, 2 * imgHeight + y);
		line(1, 2 * imgHeight + y, 1, imgHeight + y);
		endPaint();
	}
}
void keyEvent(int key, int n)
{
	char s[50];
	if (n != KEY_DOWN)return;
	if (key == VK_SPACE)
	{
		if (Rank <= maxRank)
		{
			if (Rank == maxRank)
			{
				if (pos[1][0] == pos[1][1] && pos[1][1] == pos[1][2])
				{
					sprintf_s(s, "%s", "You win!", 50);
				}
				else
					sprintf_s(s, "%s", "You lost!", 50);
				cancelTimer(0);
				beginPaint();
				setTextSize(40);
				paintText(winWidth / 2 - 100, winHeight / 2 - 20, s);
				endPaint();
			}
			else
			{
				if (pos[1][0] == pos[1][1] && pos[1][1] == pos[1][2])
				{
					Rank++;
					sprintf_s(s, "%s", "Go on!", 50);
					cancelTimer(1);
					beginPaint();
					setTextSize(40);
					paintText(winWidth / 2 - 100, winHeight / 2 - 20, s);
					endPaint();
				}
				else
				{
					sprintf_s(s, "%s", "You lost!", 50);
					beginPaint();
					setTextSize(40);
					paintText(winWidth / 2 - 100, winHeight / 2 - 20, s);
					endPaint();
					cancelTimer(0);
				}
			}
		}
	}
}