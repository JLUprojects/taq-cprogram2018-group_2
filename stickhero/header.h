#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib") //����Ϸ�������Ҫ�õ���


#define STICK_SPEED 5//���ӱ䳤���ٶȣ���ֵԽ�󣬹��ӱ䳤���ٶ�Խ��
#define MOVE_SPEED 10//�����ƶ����ٶȣ���ֵԽ�������ڹ������ƶ��ٶ�Խ��
#define G 9.8//�������ٶ�


typedef struct 
{
	int left;
	int top;
	int right;
	int bottom;
}PILLAR;


PILLAR pillar1 = {10, 370, 60, 600};
PILLAR pillar2;


void UI(IMAGE *p_start);
void Login(int *p_score,int *p_length,IMAGE *p_background,IMAGE *p_hero,IMAGE *p_over);
void game(int *p_score,int *p_length,IMAGE *p_background,IMAGE *p_hero,IMAGE *p_over);
PILLAR pillar_rnd();
void draw_pillar(PILLAR pillar);
void lengthen(int *p_length);
int Judge(int *p_length,IMAGE *p_background,IMAGE *p_hero);
void move(int *p_length,IMAGE *p_background,IMAGE *p_hero);
void free_fall(int *p_length,IMAGE *p_background,IMAGE *p_hero);
int maximum();
void change_maximum(int *p_score);
void game_over(int *p_length,int *p_score,IMAGE *p_background,IMAGE *p_hero,IMAGE *p_over);