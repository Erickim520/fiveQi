
#include "tool.h"

// ���ڻ�ͼ�Ĺ���


int GameData[LINE_X][LINE_Y];             // ��Ϸ�� ��Ϊ�ж�ʤ��������

Player GameAreaPoint[GAMEDATA];           // ��ÿ�������ӵ�����㡣
int BackMove[BACKMOVE] ;                  // ��Ż���Ĳ���


// ��Ż���Ĳ���
unsigned int BackNum = 0 ;
void SaveBackMove(int x , int y)
{
    if(BackNum >= 10)
    {
        memmove(BackMove , &BackMove[2] ,8*sizeof(int));
        BackNum -= 2 ;
    }
    BackMove[BackNum++] = x ;
    BackMove[BackNum++] = y ;
}

void SavePointX_Y(void)
{
    int k = 0;
    for(int i = 0 ; i < GAMEDATA ; i++)
    {
        if(i >= (k+1)*LINE_Y)
        {
            k++ ;
        }
        GameAreaPoint[i].Point_X = QIPANFRISTPOINT + k*BLOCK_SIZE ;                  // ��x����
        GameAreaPoint[i].Point_Y = QIPANFRISTPOINT + (i%LINE_X)*BLOCK_SIZE ;         // ��y��
    }

}
// ͼƬ
void DrawPic(void)
{
    PIMAGE img;
    img = newimage(640 , 480);
    getimage(img, "2.jpg");
    //������ͼ�Ƚ�
    //EGEAPI::resize(img , 640, 480);
    putimage(0, 0, img);
    setcaption("������");
//    putimage_alphablend(NULL, img, 160, 0, 0x80); //��͸����Ϊ0x80
//    putimage_transparent(NULL, img, 0, 80, BLACK);        //͸����ͼ���ؼ�ɫΪBLACK��ԴͼΪ�����ɫ�ĵط��ᱻ����
//    putimage_alphatransparent(NULL, img, 160, 80, BLACK, 0xA0); //ͬʱʹ��͸���Ͱ�͸��
    //delimage(img);
}

// д����
void PrintText(int x , int y ,char *ch)
{
    setcolor(YELLOW);    // ����������ɫ
    //���ֱ���ɫ��ע��setbkcolor����Ҳ��ͬʱ�ı����ֱ���ɫ��
    //setfontbkcolor(EGERGB(0x80, 0x00, 0x80));
    //�������壬��һ������������ĸ߶ȣ����أ����ڶ�������������Ŀ�ȣ��ڶ����������Ϊ0����ʹ��Ĭ�ϱ���ֵ
    //����߶�Ϊ12�����൱��С����֣�����9���֣�ʵ�ʵĻ�����Լ���ɰ�
    setfont(24, 0, "����");
    //д���֣�ע�⣺outtextxy��֧��\t \n�����ʽ���õ������ַ��������ַ��ᱻ����
    //Ҫʹ�������ʽ���ַ�����outtextrect
    //outtextxy(x, y, "11");
    //outtextrect(100, 120, 200, 100, "\tHello EGE Graphics\nHere is the next line.");
    //�������ֱ�����䷽ʽΪ͸����Ĭ��ΪOPAQUE��͸��
    setbkmode(TRANSPARENT);
    outtextxy(x, y, ch );
}

// ��һ�����ο� ��ɫ�ľ���
void DrawsBar(int x ,int y , int x1 , int y1)
{
    //setfillcolor(WHITE);
    //bar(x,y,x1,y1);
    setcolor(WHITE);
    line(x , y , x1 , y);
    line(x , y1 , x1 , y1);
    line(x , y , x , y1);
    line(x1 , y , x1 , y1);
}
// tool ����
void ToolKey(void)
{
    for (int i = 0 ; i < 3;i++)
    {
        DrawsBar(FRISTKEY_X , FRISTKEY_Y*i+TOOLKEYSPASE , FRISTKEY_X+TOOLKEYSIZE_X ,FRISTKEY_Y*i+TOOLKEYSIZE_Y+TOOLKEYSPASE);
        DrawsBar(FRISTKEY_X+2 , FRISTKEY_Y*i+2+TOOLKEYSPASE , FRISTKEY_X+TOOLKEYSIZE_X-2 ,FRISTKEY_Y*i+TOOLKEYSIZE_Y-2+TOOLKEYSPASE);
    }
    PrintText(FRISTKEY_X+10 , TOOLKEYSPASE+10 ,   "�� �� Ϸ");
    PrintText(FRISTKEY_X+10 , TOOLKEYSPASE+10+FRISTKEY_Y, "��    ��");
    PrintText(FRISTKEY_X+10 , TOOLKEYSPASE+10+FRISTKEY_Y*2 , "  EXIT! ");
}
void PlayerOne(int num)
{
//    setfillcolor(BLACK);
//    bar(FRISTKEY_X+10 , 5 , FRISTKEY_X+10+100 ,40);
    PrintText(FRISTKEY_X ,20 ,"ִ���ߣ�");
    if(num ==1)
    {
        DrawPoint(FRISTKEY_X+100 , 30 , 0);
    }
    else if(num == 2)
    {
        DrawPoint(FRISTKEY_X+100 , 30 , 1);
    }
}
// ��ʼ����Ϸ��
void InitGameArea(void)
{
    for(int j=0 ; j < LINE_X; j++)
        for(int i = 0 ; i <LINE_Y ; i++)
            GameData[j][i] = 0;
}
// ����Ϸ��������s
void FiveBlock(void)
{
    setcolor(RED);
    setbkcolor(SKYBLUE);
    for(int i = 0 ; i< LINE_Y ; i++)
        line(QIPANFRISTPOINT+BLOCK_SIZE*i, QIPANFRISTPOINT, QIPANFRISTPOINT+BLOCK_SIZE*i, BLOCK_SIZE*LINE_X);
    for(int i = 0 ; i < LINE_X ;i++)
        line(QIPANFRISTPOINT, QIPANFRISTPOINT+BLOCK_SIZE*i, BLOCK_SIZE*LINE_Y, QIPANFRISTPOINT+BLOCK_SIZE*i);
}

// ������Ϸ�Ľ���
void InitWin(void)
{
    //string ch = "hhllll" ;
    initgraph(WIN_H, WIN_W);                    //��ʼ��Ϊ640*480��С
    setbkcolor(ORCHID);                         //���ñ�����ɫ
    setcaption("������");
    setcolor(BLACK);    // ����������ɫ
    setfont(36, 0, "����");
    setbkmode(TRANSPARENT);
    outtextxy(180, 120, "��     ��     ��");

    setcolor(YELLOW);    // ����������ɫ
    setfont(16, 0, "����");
    setbkmode(TRANSPARENT);
    outtextxy(220, 250, "Please press enter key");

    getch();
    closegraph();
}

// ������
void DrawPoint(int x , int y , int player)
{
    if(player == 0)
    {
        setcolor(WHITE);
        setfillcolor(WHITE);            //��ɫ��ʾ���1
    }
    else
    {
        setcolor(BLACK);
        setfillcolor(BLACK);            //��ɫ��ʾ���2
    }
    //circle(x, y, BLOCK_SIZE/2-1);     // Բ�β������ֻ�����û���Բ�ĺ������
    fillellipse(x, y, BLOCK_SIZE/2-1, BLOCK_SIZE/2-1);
}

// ÿ�����ӵ����� ��player��ʾ���  player = 0 ��1
//  ���Ӻ󱣴���������
bool StdDrawPoint(int x , int y , int player)
{
    if(player == 0 || player == 1)
    {
        for(int i = 0 ; i < GAMEDATA ; i++)
        {
            if( x > GameAreaPoint[i].Point_X - BLOCK_SIZE/2 + 2 && x < GameAreaPoint[i].Point_X + BLOCK_SIZE/2 -2 \
               && y > GameAreaPoint[i].Point_Y - BLOCK_SIZE/2 +2 && y < GameAreaPoint[i].Point_Y + BLOCK_SIZE/2 -2 )
            {
                int point_x = GameAreaPoint[i].Point_X/20 -1;
                int point_y = GameAreaPoint[i].Point_Y/20 -1;
                if(GameData[point_x][point_y] == 0)
                {
                    DrawPoint(GameAreaPoint[i].Point_X , GameAreaPoint[i].Point_Y , player);        // ����
                    GameData[point_x][point_y] = player +1  ;
                    SaveBackMove(point_x ,point_y );                                    //  ���ڻ���Ĵ��
                    return true ;       // ������ ���һ��1 ����Ҷ���2
                }
            }
        }
        return false ;
    }
    return false ;
}

// �ж�Ŀǰ�������Ƿ������������
// ÿ���Ӷ��ж�Ȼ����ÿ���㶼�����ĵ�չ�����ж��Ƿ����
bool StdJugleWin(int er)
{
    for(int i = 2 ; i < LINE_X-2 ; i++)
    {
        for(int j = 2 ; j < LINE_Y-2 ; j++)
        {
             if(er+1 == GameData[i][j])
             {
                //  \�����ж��Ƿ������������
                if(GameData[i+1][j+1] == er+1 && GameData[i+2][j+2] == er+1 && GameData[i-1][j-1] == er+1 && GameData[i-2][j-2] == er+1)
                    return true ;
                //  /�������ж��Ƿ������������
                if(GameData[i+1][j-1] == er+1 && GameData[i+2][j-2] == er+1 && GameData[i-1][j+1] == er+1 && GameData[i-2][j+2] == er+1)
                    return true ;
                // x �᷽���ж��Ƿ����������
                if(GameData[i+1][j] == er+1 && GameData[i+2][j] == er+1 && GameData[i-1][j] == er+1 && GameData[i-2][j] == er+1)
                    return true ;
                // y �᷽���ж��Ƿ����������
                if(GameData[i][j+1] == er+1 && GameData[i][j+2] == er+1 && GameData[i][j-1] == er+1 && GameData[i][j-2] == er+1)
                    return true ;
             }
        }
    }
    // �� i ����0 ���� 1 ����19 20 ��ʱ�� ֻ�ж�x����û�����ӳ�5����
    for(int i = 2 ;i<LINE_X-2 ;i++)      //
    {
         if(er+1 == GameData[i][0])      //��y������
         {
             if(GameData[i+1][0] == er+1 && GameData[i+2][0] == er+1 && GameData[i-1][0] == er+1 && GameData[i-2][0] == er+1)
                 return true ;
         }
         if(er+1 == GameData[i][1])      //��y����1
         {
             if(GameData[i+1][1] == er+1 && GameData[i+2][1] == er+1 && GameData[i-1][1] == er+1 && GameData[i-2][1] == er+1)
                 return true ;
         }
         if(er+1 == GameData[i][18])      //��y����18
         {
             if(GameData[i+1][18] == er+1 && GameData[i+2][18] == er+1 && GameData[i-1][18] == er+1 && GameData[i-2][18] == er+1)
                 return true ;
         }
         if(er+1 == GameData[i][19])      //��y����19
         {
             if(GameData[i+1][19] == er+1 && GameData[i+2][19] == er+1 && GameData[i-1][19] == er+1 && GameData[i-2][19] == er+1)
                 return true ;
         }
    }

     // �� j ����0 ���� 1 ����19 20 ��ʱ�� ֻ�ж�y����û�����ӳ�5����
    for(int j = 2 ;j<LINE_Y-2 ;j++)      //
    {
         if(er+1 == GameData[0][j])      //��y������
         {
             if(GameData[0][j+1] == er+1 && GameData[0][j+2] == er+1 && GameData[0][j-1] == er+1 && GameData[0][j-2] == er+1)
                 return true ;
         }
         if(er+1 == GameData[1][j])      //��y����1
         {
             if(GameData[1][j+1] == er+1 && GameData[1][j+2] == er+1 && GameData[1][j-1] == er+1 && GameData[1][j-2] == er+1)
                 return true ;
         }
         if(er+1 == GameData[18][j])      //��y����18
         {
             if(GameData[18][j+1] == er+1 && GameData[18][j+2] == er+1 && GameData[18][j-1] == er+1 && GameData[18][j-2] == er+1)
                 return true ;
         }
         if(er+1 == GameData[19][j])      //��y����19
         {
             if(GameData[19][j+1] == er+1 && GameData[19][j+2] == er+1 && GameData[19][j-1] == er+1 && GameData[19][j-2] == er+1)
                 return true ;
         }
    }
    return false ;
}

// ����Ϸ
void NewGame(void)
{
    cleardevice();
    DrawPic();
    InitGameArea();         //��ʼ����Ϸ��
    FiveBlock();            //��ʼ����Ϸ����
    SavePointX_Y();         //��ʼ����������
    PlayerOne(1);           //�������
    ToolKey();
}


// ���ڻ��幦�ܣ�����������
void ChangeGameAreaData(void)
{
    if(BackNum >= 2)
    {
        GameData[BackMove[BackNum-2]][BackMove[BackNum-1]] = 0 ;
        BackNum -= 2 ;
    }
}
// ���ڻ��幦�� �� ������������������
void TakeBack(int er)
{
    cleardevice();
    DrawPic();
    FiveBlock();            //��ʼ����Ϸ����
    ChangeGameAreaData();
    PlayerOne(er);           //�������
    ToolKey();
    for(int i = 0 ; i < GAMEDATA ; i++)
    {
        int point_x = GameAreaPoint[i].Point_X/20 -1 ;
        int point_y = GameAreaPoint[i].Point_Y/20 -1;
        if(GameData[point_x][point_y] != 0)
        {
            DrawPoint(GameAreaPoint[i].Point_X , GameAreaPoint[i].Point_Y , GameData[point_x][point_y]-1);        // ����
        }
    }
}

