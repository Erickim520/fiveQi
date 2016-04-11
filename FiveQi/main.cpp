#include <iostream>
#include <graphics.h>
#include "main.h"
#include "tool.h"
#include <stdio.h>
#include <time.h>
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) //���ؿ���̨��,ע�������̨�ʹ���һ�����
using namespace std;

void GameInit(void)
{
    initgraph(WIN_H, WIN_W);
    setbkcolor(BLACK);
    DrawPic();
    InitGameArea();         //��ʼ����Ϸ��
    FiveBlock();            //��ʼ����Ϸ����
    SavePointX_Y();         //��ʼ����������
    ToolKey();

}

// ���ý������
void Result(int er)
{
    int num = 0 ;
    num = rand()%5 ;
    setfont(36, 0,"����");
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
        xyprintf(150 , 120 ,"ִ������ʤ����");
    else if(er ==1)
        xyprintf(150 , 120 ,"ִ������ʤ����");
}

void GameMainWIN(void)
{
    int stop = 0 ;
    int Playerflag = 0 ;
    mouse_msg msg = {0};
    PlayerOne(Playerflag+1);
    for ( ; is_run(); delay_fps(60))
    {
        //��ȡ�����Ϣ�����������ȴ����ȴ�������ϢΪֹ
        //���Ƶأ��к�kbhit��������ĺ���MouseHit�����ڼ����û�������Ϣ
        while (mousemsg())
        {
            msg = getmouse();
        }
        //��ʽ�����Ϊ�ַ��������ں������
        //msg��flag������ο��ĵ�����mouse_msg_e, mouse_flag_e������
        //cleardevice();
        if(stop)
        {
            Result(Playerflag);
        }
        if((int)msg.is_left()&&(int)msg.is_down())          //����
        {
            if(!stop)
            {
                if(StdDrawPoint(msg.x, msg.y , Playerflag))
                {
                    if(StdJugleWin(Playerflag))                 //�������Ӻ��ж��Ƿ����������������
                    {
                        Result(Playerflag);
                        stop = 1;
                        continue ;
                    }
                    Playerflag = !Playerflag ;
                    PlayerOne(Playerflag+1);
                }
                // ���幦��
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
             // ������Ϸ�����������˼�
            if(msg.x > FRISTKEY_X+10 && msg.x<FRISTKEY_X+TOOLKEYSIZE_X\
               && msg.y>TOOLKEYSPASE+5 && msg.y<TOOLKEYSPASE+TOOLKEYSIZE_Y )
               {
                   stop = 0 ;
                   Playerflag = 0 ;
                   NewGame();                   // ����Ϸ
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
