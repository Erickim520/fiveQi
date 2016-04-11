#include <graphics.h>
#include <iostream>
#include "main.h"
//typedef unsigned int color_t ;

// ��ɫRGB
#define WHITE   EGERGB(0xFF, 0xFF, 0xF0)
#define YELLOW  EGERGB(0xFF, 0xFF, 0x00)
#define BLUE    EGERGB(0x00, 0xCD, 0x00)
#define RED     EGERGB(220,20,60)       // ������crimson���Ⱥ죩
#define ORCHID  EGERGB(218,112,214)     // ������orchid�������ϣ�
#define SKYBLUE EGERGB(0,191,255)       // ������deepskyblue����������
#define GREEN   EGERGB(0,255,127)       // ������springgreen�������̣�
#define BLACK   EGERGB(0,0,0)              // ������black���ڣ�
// ���ڴ�С
#define WIN_H   640
#define WIN_W   480
#define QIPANFRISTPOINT     20
#define LINE_X  20                       // ����x����
#define LINE_Y  20                       // ����y����
#define GAMEDATA       LINE_X*LINE_Y     // ��Ϸ����С
#define BLOCK_SIZE     20                // ÿ�����ӵı߳�
#define FRISTKEY_X     500               // ���ܼ��ĵ�һ��λ�õ�����
#define FRISTKEY_Y     80
#define TOOLKEYSIZE_X  120               // ���ܼ��Ĵ�С
#define TOOLKEYSIZE_Y  50                // ���ܼ��Ĵ�С
#define TOOLKEYSPASE   50                // ���ܼ��ļ��

#define BACKMOVE    10                    // ����Ĳ���

typedef struct Player
{
    unsigned int Flag ;
    unsigned int Point_X;
    unsigned int Point_Y;
};
extern unsigned int BackNum ;
extern Player GameAreaPoint[GAMEDATA];   // ��ÿ�������ӵ�����㡣
extern int GameData[LINE_X][LINE_Y];
extern void DrawsBar(int x ,int y , int x1 , int y1 );
extern void PrintText(int x , int y , char *ch);

void NewGame(void);
void TakeBack(int er);
void ToolKey(void);
bool StdJugleWin(int er);
void InitGameArea(void);
void FiveBlock(void);
void InitWin(void);
void DrawPoint(int x , int y , int player);
void SavePointX_Y(void);
void DrawPic(void);
bool StdDrawPoint(int x , int y , int player);
void PlayerOne(int num);
void SaveBackMove(int x , int y);
