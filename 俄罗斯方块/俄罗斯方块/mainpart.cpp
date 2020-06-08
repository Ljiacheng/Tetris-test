#define _CRT_SECURE_NO_WARNINGS
#include"block.h"
#include<easyx.h>
#include<conio.h>

int Topgrade = 0;//最高分
void showtop();//显示最高分
void showgrade(int grade);//显示当前分数,被满行时调用和初始时调用,同时更新最高分
void shownextb(Block nextb);//显示下个方块在右方
void gamepage();//游戏界面
void startgame();//开始页面
int  checkcrush(Block& curb, Backblock backblock[][10]);//检查碰撞,返回1代表碰撞，返回0代表未碰撞
int checkfullline(int& Topgrade, int& grade, Backblock backblock[][10]);//检查满行，返回1代表满行，返回0代表未满行
void kbdoing(Block& curb, Backblock backblock[][10]);//键盘按键操作


int main() {
	initgraph(500, 660);//打开窗口
	setorigin(30, 30);//重新设置原点
	Backblock backblock[20][10];//背景方块
	Block nextb, curb;//下一个方块和当前方块
	int grade;//分数
	int newb;//用于判断下一次循环是否是运行新的方块
rq:	startgame();//开始界面及其选择
rr:	gamepage();//游戏界面打印
	for (int i = 0;i < 20;i++)//初始化背景20乘10的格子，并标记无填充
		for (int j = 0;j < 10;j++)
		{
			backblock[i][j].rol = i;
			backblock[i][j].col = j;
			backblock[i][j].ispour = 0;
		}
	grade = 0;
	newb = 0;
	curb.randblock();//随机生成方块
	nextb.randblock();
	shownextb(nextb);//把下一个方块提示在右边
	curb.showblock();//初次显示第一个方块
	showtop();//显示最高分
	showgrade(grade);//显示分数
	while (1) {//主循环
		if (newb) {
			newb = 0;
			nextb.randblock();//生产下一个方块
			shownextb(nextb);//把下一个方块提示在右边
			curb.showblock();//方块出现在上方
			if (checkcrush(curb, backblock)) {
				newb = 1;
			    if(checkfullline(Topgrade,grade,backblock)){//满行并进行相应处理
					continue;
			    }
				else{//不满行并到头
					settextcolor(RED);
					outtextxy(180, 250, _T("游戏结束！"));//游戏结束页面
					outtextxy(90, 330, _T("按 r 重新开始，按 q 返回开始界面"));
					char cc = 0;
					while (cc != 'r' && cc != 'q') { cc = _getch(); }
					if (cc == 'r')
						goto rr;
					else if(cc== 'q')
						goto rq;
					break;
				}
			}
		}
		kbdoing(curb,backblock);//接收指令，方块移动或旋转
		if(checkcrush(curb,backblock)){			//判断碰撞
		    checkfullline(Topgrade,grade,backblock);//满行检测处理
			newb = 1;
			curb = nextb;
			continue;
		}
		curb.moveblock(2,backblock);//每固定时间自动向下移动一次
	 	if(checkcrush(curb,backblock)){			//判断碰撞
			checkfullline(Topgrade,grade, backblock);//满行检测处理
			newb=1;
			curb = nextb;
			continue;
		}
	}
	_getch();
	closegraph();
	return 0;
}

void showtop()//显示最高分
{
	settextcolor(WHITE);
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(340, 240, 500, 260);
	setlinecolor(RGB(215, 222, 214));
	outtextxy(325, 220, _T("最高分："));
	FILE* fp = fopen("score.txt", "r");
	char s1[50];
	fscanf(fp, "%s", s1);
	Topgrade = atoi(s1);
	TCHAR s[20];
	swprintf_s(s, _T("%d"), Topgrade);
	outtextxy(340, 240, s);
	fclose(fp);
}
void showgrade(int grade)//显示当前分数,被满行时调用和初始时调用,同时更新最高分
{
	settextcolor(WHITE);
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(340, 280, 500, 300);
	outtextxy(325, 260, _T("当前分数："));
	TCHAR s[20];
	if (grade > Topgrade)//更新文件中的最大值
	{
		FILE* fp = fopen("score.txt", "r+");
		char s1[20];
		fscanf(fp, "%s", s1);
		int l = strlen(s1);
		Topgrade = grade;
		sprintf_s(s1, 4, "%d", Topgrade);
		fseek(fp, -l, SEEK_CUR);
		fprintf(fp, "%s", s1);
		fclose(fp);
		showtop();//重新显示最高分
	}
	swprintf_s(s, _T("%d"), grade);
	outtextxy(340, 280, s);
}
void shownextb(Block nextb)//显示下个方块在右方
{
	setfillcolor(BLACK);
	fillrectangle(310, 30, 460, 150);
	setfillcolor(nextb.color);
	int mir = min(nextb.rol[0], min(nextb.rol[1], min(nextb.rol[2], nextb.rol[3])));//找出最小行列
	int mic = min(nextb.col[0], min(nextb.col[1], min(nextb.col[2], nextb.col[3])));
	setlinecolor(RGB(215, 222, 214));
	BeginBatchDraw();
	for (int i = 0;i < 4;i++)
		fillrectangle((nextb.col[i] - mic) * 30 + 320, (nextb.rol[i] - mir) * 30 + 60,
		(nextb.col[i] - mic) * 30 + 350, (nextb.rol[i] - mir) * 30 + 90);
	FlushBatchDraw();//
	EndBatchDraw();//
}

void gamepage()//游戏界面
{
	setfillcolor(BLACK);
	fillrectangle(-30, -30, 470, 630);
	setlinecolor(RGB(215, 222, 214));
	for (int i = 0;i < 11;i++)
		line(i * 30, 0, i * 30, 600);
	for (int i = 0;i < 21;i++)
		line(0, i * 30, 300, i * 30);
	line(310, 30, 460, 30);
	line(310, 150, 460, 150);
	line(310, 30, 310, 150);
	line(460, 30, 460, 150);
	outtextxy(360, 380, _T("w   旋转"));
	outtextxy(360, 400, _T("a   左移"));
	outtextxy(360, 420, _T("d   右移"));
	outtextxy(360, 440, _T("s   下移"));
	outtextxy(360, 460, _T("空格到底"));
}

void startgame()//开始页面
{
start:	
	setfillcolor(BLACK);
	fillrectangle(-30, -30, 500, 660);
	settextcolor(WHITE);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(160, 230, _T("俄罗斯方块！"));
	outtextxy(90, 310, _T("按 e 开始游戏，按 q 退出游戏"));
	char kbin = 0;
	kbin = _getch();
	if (kbin == 'q')//退出游戏
		exit(0);
	else if (kbin != 'e')
		goto start;//回到该页面
}
int  checkcrush(Block& curb, Backblock backblock[][10])//检查碰撞,返回1代表碰撞，返回0代表未碰撞
{
	for (int i = 0;i < 4;i++) {
		if (backblock[curb.rol[i] + 1][curb.col[i]].ispour == 1 || curb.rol[i] + 1 > 19) {//如果碰撞了
			curb.color = RGB(242, 226, 167);
			for (int j = 0;j < 4;j++) { //更新填充状态
				backblock[curb.rol[j]][curb.col[j]].ispour = 1;
				curb.showblock();
			}
			return 1;
		}
	}
	return 0;
}

int checkfullline(int& Topgrade, int& grade, Backblock backblock[][10]) {//检查满行，返回1代表满行，返回0代表未满行
//函数功能：检查满行，消除满行，上面下移，分数增加，显示分数
	int flag = 0, lines = 0;
	for (int i = 19;i >= 0;i--) {//检测每一行
		int f = 0;
		for (int j = 0;j < 10;j++) {//检测该行的每个方块
			if (backblock[i][j].ispour == 0) {//该行不满
				break;
			}
			else
				f++;
		}
		if (f == 10) {//该行满
			flag = 1;
			lines++;
			for (int b = i;b >= 1;b--) {//上方每行依次下移
				for (int c = 0;c < 10;c++) {//对于一行
					if (backblock[b - 1][c].ispour == 0) {
						backblock[b][c].ispour = 0;
						setfillcolor(BLACK);
						fillrectangle(c * 30, b * 30, c * 30 + 30, b * 30 + 30);
					}
					else {
						backblock[b][c].ispour = 1;
						setfillcolor(RGB(242, 226, 167));
						fillrectangle(c * 30, b * 30, c * 30 + 30, b * 30 + 30);
					}
				}
			}
			i++;//回到当前行继续查
			for (int c = 0;c < 10;c++) {//最上方一行清空状态
				backblock[0][c].ispour = 0;
				setfillcolor(BLACK);
				fillrectangle(c * 30, 0, c * 30 + 30, 30);
			}
		}
	}
	if (flag == 0) return 0;
	else {
		grade += lines;//更新分数
		showgrade(grade);//显示分数
		return 1;
	}
}

void kbdoing(Block& curb, Backblock backblock[][10])//键盘按键操作
{
	char kbin = 0;
	int t = 0;
	while (kbin != 'q')
	{
		if (_kbhit())
			kbin = _getch();
		if (kbin == 'w')
			curb.rotateblock(backblock);//旋转方块
		else if (kbin == 'a')//左移
			curb.moveblock(1, backblock);
		else if (kbin == 's')//下移
			curb.moveblock(2, backblock);
		else if (kbin == 'd')//右移
			curb.moveblock(3, backblock);
		else if (kbin == VK_SPACE)//到底
			curb.moveblock(4, backblock);
		kbin = 0;//刷新按键
		Sleep(80);//键盘接收信息间隔mm，可自行调整
		t++;
		if (t == 10) break;//t*100毫秒自动下移一格,可自行调整
	}
}