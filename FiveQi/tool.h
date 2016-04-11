#include <graphics.h>
#include <iostream>
#include "main.h"
//typedef unsigned int color_t ;

// 颜色RGB
#define WHITE   EGERGB(0xFF, 0xFF, 0xF0)
#define YELLOW  EGERGB(0xFF, 0xFF, 0x00)
#define BLUE    EGERGB(0x00, 0xCD, 0x00)
#define RED     EGERGB(220,20,60)       // ■★●◆crimson（腥红）
#define ORCHID  EGERGB(218,112,214)     // ■★●◆orchid（兰花紫）
#define SKYBLUE EGERGB(0,191,255)       // ■★●◆deepskyblue（深天蓝）
#define GREEN   EGERGB(0,255,127)       // ■★●◆springgreen（春天绿）
#define BLACK   EGERGB(0,0,0)              // ■★●◆black（黑）
// 窗口大小
#define WIN_H   640
#define WIN_W   480
#define QIPANFRISTPOINT     20
#define LINE_X  20                       // 棋盘x线数
#define LINE_Y  20                       // 棋盘y线数
#define GAMEDATA       LINE_X*LINE_Y     // 游戏区大小
#define BLOCK_SIZE     20                // 每个格子的边长
#define FRISTKEY_X     500               // 功能键的第一个位置的坐标
#define FRISTKEY_Y     80
#define TOOLKEYSIZE_X  120               // 功能键的大小
#define TOOLKEYSIZE_Y  50                // 功能键的大小
#define TOOLKEYSPASE   50                // 功能键的间隔

#define BACKMOVE    10                    // 悔棋的步数

typedef struct Player
{
    unsigned int Flag ;
    unsigned int Point_X;
    unsigned int Point_Y;
};
extern unsigned int BackNum ;
extern Player GameAreaPoint[GAMEDATA];   // 存每个放棋子的坐标点。
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
