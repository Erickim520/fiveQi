#include <iostream>
#include <graphics.h>
#include "main.h"
#include "tool.h"
#include <stdio.h>
#include <time.h>
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) //隐藏控制台用,注掉后控制台和窗口一起出现
using namespace std;

void GameInit(void)
{
    initgraph(WIN_H, WIN_W);
    setbkcolor(BLACK);
    DrawPic();
    InitGameArea();         //初始化游戏区
    FiveBlock();            //初始化游戏网格
    SavePointX_Y();         //初始化棋盘坐标
    ToolKey();

}

// 调用结果函数
void Result(int er)
{
    int num = 0 ;
    num = rand()%5 ;
    setfont(36, 0,"宋体");
    switch(num){
    case 0:
        setcolor(RED);
        break;
    case 1:
        setcolor(YELLOW);
        break;
    case 2:
        setcolor(ORCHID);
        break;
    case 3:
        setcolor(GREEN);
        break;
    case 4:
        setcolor(BLUE);
        break;
    }
    if(er == 0)
        xyprintf(150 , 120 ,"执白棋者胜利！");
    else if(er ==1)
        xyprintf(150 , 120 ,"执黑棋者胜利！");
}

void GameMainWIN(void)
{
    int stop = 0 ;
    int Playerflag = 0 ;
    mouse_msg msg = {0};
    PlayerOne(Playerflag+1);
    for ( ; is_run(); delay_fps(60))
    {
        //获取鼠标消息，这个函数会等待，等待到有消息为止
        //类似地，有和kbhit功能相近的函数MouseHit，用于检测有没有鼠标消息
        while (mousemsg())
        {
            msg = getmouse();
        }
        //格式化输出为字符串，用于后面输出
        //msg和flag常数请参考文档或者mouse_msg_e, mouse_flag_e的声明
        //cleardevice();
        if(stop)
        {
            Result(Playerflag);
        }
        if((int)msg.is_left()&&(int)msg.is_down())          //按下
        {
            if(!stop)
            {
                if(StdDrawPoint(msg.x, msg.y , Playerflag))
                {
                    if(StdJugleWin(Playerflag))                 //放下棋子后判断是否有五子相连的情况
                    {
                        Result(Playerflag);
                        stop = 1;
                        continue ;
                    }
                    Playerflag = !Playerflag ;
                    PlayerOne(Playerflag+1);
                }
                // 悔棋功能
                if(msg.x > FRISTKEY_X+10 && msg.x<FRISTKEY_X+TOOLKEYSIZE_X\
                   &&msg.y>TOOLKEYSPASE+5+FRISTKEY_Y && msg.y<TOOLKEYSPASE+FRISTKEY_Y+TOOLKEYSIZE_Y)
                {
                    if(BackNum>=2)
                    {
                        TakeBack(Playerflag);
                        Playerflag = !Playerflag ;
                        PlayerOne(Playerflag+1);
                    }
                }
            }
             // 在新游戏按键区按下了键
            if(msg.x > FRISTKEY_X+10 && msg.x<FRISTKEY_X+TOOLKEYSIZE_X\
               && msg.y>TOOLKEYSPASE+5 && msg.y<TOOLKEYSPASE+TOOLKEYSIZE_Y )
               {
                   stop = 0 ;
                   Playerflag = 0 ;
                   NewGame();                   // 新游戏
               }
            if(msg.x > FRISTKEY_X+10 && msg.x<FRISTKEY_X+TOOLKEYSIZE_X\
                &&msg.y>TOOLKEYSPASE+5+FRISTKEY_Y*2 && msg.y<TOOLKEYSPASE+FRISTKEY_Y*2+TOOLKEYSIZE_Y)
                {
                    break ;
                }
            msg = {0};
        }
    }
    closegraph();
 }


int WinMain()
{
    InitWin();
    DrawPic();
    GameInit();
    GameMainWIN();
    return 0;
}
