
#include "tool.h"

// 用于画图的工具


int GameData[LINE_X][LINE_Y];             // 游戏区 作为判断胜负的依据

Player GameAreaPoint[GAMEDATA];           // 存每个放棋子的坐标点。
int BackMove[BACKMOVE] ;                  // 存放悔棋的步数


// 存放悔棋的步数
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
        GameAreaPoint[i].Point_X = QIPANFRISTPOINT + k*BLOCK_SIZE ;                  // 存x坐标
        GameAreaPoint[i].Point_Y = QIPANFRISTPOINT + (i%LINE_X)*BLOCK_SIZE ;         // 存y坐
    }

}
// 图片
void DrawPic(void)
{
    PIMAGE img;
    img = newimage(640 , 480);
    getimage(img, "2.jpg");
    //四种贴图比较
    //EGEAPI::resize(img , 640, 480);
    putimage(0, 0, img);
    setcaption("五子棋");
//    putimage_alphablend(NULL, img, 160, 0, 0x80); //半透明度为0x80
//    putimage_transparent(NULL, img, 0, 80, BLACK);        //透明贴图，关键色为BLACK，源图为这个颜色的地方会被忽略
//    putimage_alphatransparent(NULL, img, 160, 80, BLACK, 0xA0); //同时使用透明和半透明
    //delimage(img);
}

// 写文字
void PrintText(int x , int y ,char *ch)
{
    setcolor(YELLOW);    // 设置文字颜色
    //文字背景色（注意setbkcolor函数也会同时改变文字背景色）
    //setfontbkcolor(EGERGB(0x80, 0x00, 0x80));
    //设置字体，第一个参数是字体的高度（像素），第二个参数是字体的宽度，第二个参数如果为0，就使用默认比例值
    //如果高度为12，即相当于小五号字，或者9磅字，实际的换算就自己完成吧
    setfont(24, 0, "宋体");
    //写文字，注意：outtextxy不支持\t \n这类格式化用的特殊字符，这类字符会被忽略
    //要使用特殊格式化字符请用outtextrect
    //outtextxy(x, y, "11");
    //outtextrect(100, 120, 200, 100, "\tHello EGE Graphics\nHere is the next line.");
    //设置文字背景填充方式为透明，默认为OPAQUE不透明
    setbkmode(TRANSPARENT);
    outtextxy(x, y, ch );
}

// 画一个矩形框 白色的矩形
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
// tool 按键
void ToolKey(void)
{
    for (int i = 0 ; i < 3;i++)
    {
        DrawsBar(FRISTKEY_X , FRISTKEY_Y*i+TOOLKEYSPASE , FRISTKEY_X+TOOLKEYSIZE_X ,FRISTKEY_Y*i+TOOLKEYSIZE_Y+TOOLKEYSPASE);
        DrawsBar(FRISTKEY_X+2 , FRISTKEY_Y*i+2+TOOLKEYSPASE , FRISTKEY_X+TOOLKEYSIZE_X-2 ,FRISTKEY_Y*i+TOOLKEYSIZE_Y-2+TOOLKEYSPASE);
    }
    PrintText(FRISTKEY_X+10 , TOOLKEYSPASE+10 ,   "新 游 戏");
    PrintText(FRISTKEY_X+10 , TOOLKEYSPASE+10+FRISTKEY_Y, "悔    棋");
    PrintText(FRISTKEY_X+10 , TOOLKEYSPASE+10+FRISTKEY_Y*2 , "  EXIT! ");
}
void PlayerOne(int num)
{
//    setfillcolor(BLACK);
//    bar(FRISTKEY_X+10 , 5 , FRISTKEY_X+10+100 ,40);
    PrintText(FRISTKEY_X ,20 ,"执棋者：");
    if(num ==1)
    {
        DrawPoint(FRISTKEY_X+100 , 30 , 0);
    }
    else if(num == 2)
    {
        DrawPoint(FRISTKEY_X+100 , 30 , 1);
    }
}
// 初始化游戏区
void InitGameArea(void)
{
    for(int j=0 ; j < LINE_X; j++)
        for(int i = 0 ; i <LINE_Y ; i++)
            GameData[j][i] = 0;
}
// 画游戏区的网格s
void FiveBlock(void)
{
    setcolor(RED);
    setbkcolor(SKYBLUE);
    for(int i = 0 ; i< LINE_Y ; i++)
        line(QIPANFRISTPOINT+BLOCK_SIZE*i, QIPANFRISTPOINT, QIPANFRISTPOINT+BLOCK_SIZE*i, BLOCK_SIZE*LINE_X);
    for(int i = 0 ; i < LINE_X ;i++)
        line(QIPANFRISTPOINT, QIPANFRISTPOINT+BLOCK_SIZE*i, BLOCK_SIZE*LINE_Y, QIPANFRISTPOINT+BLOCK_SIZE*i);
}

// 进入游戏的界面
void InitWin(void)
{
    //string ch = "hhllll" ;
    initgraph(WIN_H, WIN_W);                    //初始化为640*480大小
    setbkcolor(ORCHID);                         //设置背景颜色
    setcaption("五子棋");
    setcolor(BLACK);    // 设置文字颜色
    setfont(36, 0, "宋体");
    setbkmode(TRANSPARENT);
    outtextxy(180, 120, "五     子     棋");

    setcolor(YELLOW);    // 设置文字颜色
    setfont(16, 0, "宋体");
    setbkmode(TRANSPARENT);
    outtextxy(220, 250, "Please press enter key");

    getch();
    closegraph();
}

// 画棋子
void DrawPoint(int x , int y , int player)
{
    if(player == 0)
    {
        setcolor(WHITE);
        setfillcolor(WHITE);            //白色表示玩家1
    }
    else
    {
        setcolor(BLACK);
        setfillcolor(BLACK);            //黑色表示玩家2
    }
    //circle(x, y, BLOCK_SIZE/2-1);     // 圆形不能填充只能先用画椭圆的函数替代
    fillellipse(x, y, BLOCK_SIZE/2-1, BLOCK_SIZE/2-1);
}

// 每个棋子的坐标 ，player表示玩家  player = 0 或1
//  落子后保存棋盘数据
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
                    DrawPoint(GameAreaPoint[i].Point_X , GameAreaPoint[i].Point_Y , player);        // 画点
                    GameData[point_x][point_y] = player +1  ;
                    SaveBackMove(point_x ,point_y );                                    //  用于悔棋的存放
                    return true ;       // 存数据 玩家一存1 ；玩家二存2
                }
            }
        }
        return false ;
    }
    return false ;
}

// 判断目前棋盘上是否有五个子相连
// 每个子都判断然后设每个点都是中心点展开来判断是否结束
bool StdJugleWin(int er)
{
    for(int i = 2 ; i < LINE_X-2 ; i++)
    {
        for(int j = 2 ; j < LINE_Y-2 ; j++)
        {
             if(er+1 == GameData[i][j])
             {
                //  \方向判断是否有五个相连的
                if(GameData[i+1][j+1] == er+1 && GameData[i+2][j+2] == er+1 && GameData[i-1][j-1] == er+1 && GameData[i-2][j-2] == er+1)
                    return true ;
                //  /方向来判断是否有五个相连的
                if(GameData[i+1][j-1] == er+1 && GameData[i+2][j-2] == er+1 && GameData[i-1][j+1] == er+1 && GameData[i-2][j+2] == er+1)
                    return true ;
                // x 轴方向判断是否有五个相连
                if(GameData[i+1][j] == er+1 && GameData[i+2][j] == er+1 && GameData[i-1][j] == er+1 && GameData[i-2][j] == er+1)
                    return true ;
                // y 轴方向判断是否有五个相连
                if(GameData[i][j+1] == er+1 && GameData[i][j+2] == er+1 && GameData[i][j-1] == er+1 && GameData[i][j-2] == er+1)
                    return true ;
             }
        }
    }
    // 当 i 等于0 或者 1 或者19 20 的时候 只判断x轴有没有连接成5个的
    for(int i = 2 ;i<LINE_X-2 ;i++)      //
    {
         if(er+1 == GameData[i][0])      //当y等于零
         {
             if(GameData[i+1][0] == er+1 && GameData[i+2][0] == er+1 && GameData[i-1][0] == er+1 && GameData[i-2][0] == er+1)
                 return true ;
         }
         if(er+1 == GameData[i][1])      //当y等于1
         {
             if(GameData[i+1][1] == er+1 && GameData[i+2][1] == er+1 && GameData[i-1][1] == er+1 && GameData[i-2][1] == er+1)
                 return true ;
         }
         if(er+1 == GameData[i][18])      //当y等于18
         {
             if(GameData[i+1][18] == er+1 && GameData[i+2][18] == er+1 && GameData[i-1][18] == er+1 && GameData[i-2][18] == er+1)
                 return true ;
         }
         if(er+1 == GameData[i][19])      //当y等于19
         {
             if(GameData[i+1][19] == er+1 && GameData[i+2][19] == er+1 && GameData[i-1][19] == er+1 && GameData[i-2][19] == er+1)
                 return true ;
         }
    }

     // 当 j 等于0 或者 1 或者19 20 的时候 只判断y轴有没有连接成5个的
    for(int j = 2 ;j<LINE_Y-2 ;j++)      //
    {
         if(er+1 == GameData[0][j])      //当y等于零
         {
             if(GameData[0][j+1] == er+1 && GameData[0][j+2] == er+1 && GameData[0][j-1] == er+1 && GameData[0][j-2] == er+1)
                 return true ;
         }
         if(er+1 == GameData[1][j])      //当y等于1
         {
             if(GameData[1][j+1] == er+1 && GameData[1][j+2] == er+1 && GameData[1][j-1] == er+1 && GameData[1][j-2] == er+1)
                 return true ;
         }
         if(er+1 == GameData[18][j])      //当y等于18
         {
             if(GameData[18][j+1] == er+1 && GameData[18][j+2] == er+1 && GameData[18][j-1] == er+1 && GameData[18][j-2] == er+1)
                 return true ;
         }
         if(er+1 == GameData[19][j])      //当y等于19
         {
             if(GameData[19][j+1] == er+1 && GameData[19][j+2] == er+1 && GameData[19][j-1] == er+1 && GameData[19][j-2] == er+1)
                 return true ;
         }
    }
    return false ;
}

// 新游戏
void NewGame(void)
{
    cleardevice();
    DrawPic();
    InitGameArea();         //初始化游戏区
    FiveBlock();            //初始化游戏网格
    SavePointX_Y();         //初始化棋盘坐标
    PlayerOne(1);           //落子玩家
    ToolKey();
}


// 用于悔棋功能：处理数据区
void ChangeGameAreaData(void)
{
    if(BackNum >= 2)
    {
        GameData[BackMove[BackNum-2]][BackMove[BackNum-1]] = 0 ;
        BackNum -= 2 ;
    }
}
// 用于悔棋功能 ： 根据数据区来画棋盘
void TakeBack(int er)
{
    cleardevice();
    DrawPic();
    FiveBlock();            //初始化游戏网格
    ChangeGameAreaData();
    PlayerOne(er);           //落子玩家
    ToolKey();
    for(int i = 0 ; i < GAMEDATA ; i++)
    {
        int point_x = GameAreaPoint[i].Point_X/20 -1 ;
        int point_y = GameAreaPoint[i].Point_Y/20 -1;
        if(GameData[point_x][point_y] != 0)
        {
            DrawPoint(GameAreaPoint[i].Point_X , GameAreaPoint[i].Point_Y , GameData[point_x][point_y]-1);        // 画点
        }
    }
}

