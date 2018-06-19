#include "header.h"

void main()
{
	int length = 0;
	int score = 1;
	int *p_length = NULL;
	int *p_score = NULL;
	IMAGE start,background,hero,over;
	IMAGE *p_start = NULL;
	IMAGE *p_background = NULL;
	IMAGE *p_hero = NULL;
	IMAGE *p_over = NULL;
	
	p_length = &length;
	p_score = &score;
	
	loadimage(&start, _T("C:\\Users\\Lenovo\\Desktop\\source\\start.jpg"));
	loadimage(&background,_T("C:\\Users\\Lenovo\\Desktop\\source\\bg.jpg"));
	loadimage(&hero,_T("C:\\Users\\Lenovo\\Desktop\\source\\hero.jpg"));
	loadimage(&over,_T("C:\\Users\\Lenovo\\Desktop\\source\\over.jpg"));

	p_start = &start;
	p_background = &background;
	p_hero = &hero;
	p_over = &over;

	UI(p_start);
	Login(p_score,p_length,p_background,p_hero,p_over);
	closegraph();
}


void UI(IMAGE *p_start) 
{
	initgraph(350, 600);

	IMAGE start = *p_start;

	putimage(0,0,&start);
	settextcolor(LIGHTRED);
	settextstyle(20, 0, _T("NewRoman"));
	outtextxy(10,450, "Playing Strategy£º");
	settextcolor(WHITE);
	outtextxy(10, 490, "press space to lengthen the stick");
	outtextxy(10, 520, "press enter to fall the stick");
}


void Login(int *p_score,int *p_length,IMAGE *p_background,IMAGE *p_hero,IMAGE *p_over) 
{	
	MOUSEMSG n;
	while(true)
	{
		n = GetMouseMsg();
		if(n.x >= 95 && n.x <= 235 && n.y >= 160 && n.y <= 275)
		{
			setlinecolor(LIGHTRED);
			setlinestyle(PS_SOLID , 3);
			circle(175, 230, 65);

			if(n.uMsg == WM_LBUTTONDOWN )
			{
				cleardevice();
				game(p_score,p_length,p_background,p_hero,p_over);
			}
		}
		else 
		{
			setlinecolor(LIGHTGRAY);
			setlinestyle(PS_SOLID , 3);
			circle(175, 230, 65);
		}
	}
}


void game(int *p_score,int *p_length,IMAGE *p_background,IMAGE *p_hero,IMAGE *p_over) 
{
	PlaySound(NULL,NULL,SND_FILENAME);
	PlaySound("C:\\Users\\Lenovo\\Desktop\\source\\±³¾°ÒôÀÖ.wav",NULL,SND_FILENAME|SND_ASYNC);
	IMAGE background = *p_background;
	IMAGE hero = *p_hero;
	int m;
	int score = *p_score;
	char score_now[10];
	while(1) 
	{
		cleardevice();

		sprintf(score_now, "%d", score);
		putimage(0,0,&background);
		putimage(25,340,&hero);
		setbkmode(TRANSPARENT);
		settextstyle(34, 0, _T("NewRoman"));
		outtextxy(175, 200, score_now);
		pillar2 = pillar_rnd();
		draw_pillar(pillar1);
		draw_pillar(pillar2);
		lengthen(p_length);
		m = Judge(p_length,p_background,p_hero);
		if(m)
		{
			score += 1;
			*p_score = score;
			move(p_length,p_background,p_hero);
		}
		else 
		{
			move(p_length,p_background,p_hero);
			free_fall(p_length,p_background,p_hero);
			game_over(p_length,p_score,p_background,p_hero,p_over);
		}
	}
}


PILLAR pillar_rnd() 
{
	srand((unsigned int) time(NULL));
	PILLAR pillar;
	pillar.left = rand() % 181 + 100;
	pillar.right = rand() % 91 + 10 + pillar.left;
	pillar.top = 370;
	pillar.bottom = 600;
	return pillar;
}


void draw_pillar(PILLAR pillar) 
{
	setfillcolor(BLACK);
	solidrectangle(pillar.left, pillar.top, pillar.right, pillar.bottom);
}


void lengthen(int *p_length) 
{
	char ch;
	int l = 370;
	int length = *p_length;

	while(1)
	{
		if(kbhit())
		{
			ch = getch();
			if(ch == ' ')
			{
				setlinecolor(BLACK);
				setlinestyle(PS_SOLID , 2);
				line(60, 370, 60, l -= STICK_SPEED);
			}
			else
			{
				settextcolor(WHITE);
				settextstyle(22, 0, _T("NewRoman"));
				outtextxy(85,150, "Please press space");
			}
			if(ch == '\r') 
			{
				break;
			}
		}
	}

	if(l < 0)
	length = 370;
	else
	length = 370 - l;

	*p_length = length;
}


int Judge(int *p_length,IMAGE *p_background,IMAGE *p_hero) 
{
	int a,b;
	int length = *p_length,c = 370 - length;
	IMAGE background = *p_background;
	IMAGE hero = *p_hero;

	BeginBatchDraw();

	for(a = 60; a <= 300; a++) 
	{
		for(b = c; b <= 350; b++)
		{
			if((c - 370) * (c - 370) == (a - 60) * (a - 60) + (b - 370) * (b - 370))
			{
				putimage(0,0,&background);
				putimage(25, 340, &hero);
				draw_pillar(pillar1);
				draw_pillar(pillar2);
				setlinecolor(BLACK);
				line(60, 370, a, b);
				FlushBatchDraw();
				Sleep(80);
				cleardevice();
			}
		}
	}
	setlinecolor(BLACK);
	line(60, 370, 60 + length, 370);
	if((length + 60) >= pillar2.left && (length + 60) <= pillar2.right)
	return 1;
	else 
	return 0;
}


void move(int *p_length,IMAGE *p_background,IMAGE *p_hero) 
{
	BeginBatchDraw();

	int length = *p_length;
	int i;
	IMAGE background = *p_background;
	IMAGE hero = *p_hero;

	for(i = 25; i <= 60 + length; i += MOVE_SPEED) 
	{
		putimage(0,0,&background);
		putimage(i, 340, &hero);
		draw_pillar(pillar1);
		draw_pillar(pillar2);
		line(60, 370, 60 + length, 370);
		FlushBatchDraw();
		Sleep(50);
		cleardevice();
	}
	EndBatchDraw();
}


void free_fall(int *p_length,IMAGE *p_background,IMAGE *p_hero) 
{
	BeginBatchDraw();
	double h = 340.0;
	double t = 0.05;
	int length = *p_length;
	IMAGE background = *p_background;
	IMAGE hero = *p_hero;

	for(; h <= 600; h += 0.5 * G * t * t) 
	{
		putimage(0,0,&background);
		putimage(length + 60, h, &hero);
		draw_pillar(pillar1);
		draw_pillar(pillar2);
		line(60, 370, 60 + length, 370);
		FlushBatchDraw();
		Sleep(50);
		t += 0.10;
		cleardevice();
	}
	Sleep(1000);
	EndBatchDraw();
}


int maximum()
{
	FILE *fp;
	int max_score;
	if((fp = fopen("maximum.txt", "a+")) == NULL) 
	{
		printf("Open fail!");
		exit(1);
	}
	fscanf(fp, "%d", &max_score);
	fclose(fp);
	return max_score;
}


void change_maximum(int *p_score) 
{
	int score = *p_score;
	FILE *fp;
	fp = fopen("maximum.txt", "w");
	if((fp = fopen("maximum.txt", "w")) == NULL)
	{
		printf("Open fail!");
		exit(1);
	}
	fprintf(fp, "%d", score);
	fclose(fp);
}


void game_over(int *p_length,int *p_score,IMAGE *p_background,IMAGE *p_hero,IMAGE *p_over) 
{
	void game(int *p_length,int *p_score,IMAGE *p_background,IMAGE *p_hero,IMAGE *p_over);

	PlaySound(NULL,NULL,SND_FILENAME);
	PlaySound("C:\\Users\\Lenovo\\Desktop\\source\\½áÊøÒôÀÖ.wav",NULL,SND_FILENAME|SND_ASYNC);

	IMAGE over = *p_over;

	putimage(0,0,&over);
	Sleep(1000);
	char current_score[20];
	char max[20];
	int max_score;
	int score = *p_score;
	int length = *p_length;
	max_score = maximum();

	if(score > max_score) 
	{
		change_maximum(p_score);
	}
	max_score = maximum();
	settextcolor(WHITE);
	settextstyle(32, 0, _T("»ªÎÄÐÂÎº"));
	sprintf(current_score, "%d", score);
	sprintf(max, "%d", max_score);
	outtextxy(20, 240, "Current Score£º");
	outtextxy(220, 240, current_score);
	outtextxy(20, 350, "Highest Score£º");
	outtextxy(220, 350, max);
	outtextxy(110, 500, "Play Again");
	FlushMouseMsgBuffer();
	MOUSEMSG m;
	Sleep(3000);
	while(true)
	{
		m = GetMouseMsg();
		if(m.x >= 87 && m.x <= 212 && m.y >= 415 && m.y <= 550) 
		{
			if(m.uMsg == WM_LBUTTONDOWN ) 
			{
				cleardevice();
				score = 1;
				length = 0;
				*p_score = score;
				*p_length = length;
				game(p_score,p_length,p_background,p_hero,p_over);
			}
		}
	}
}

