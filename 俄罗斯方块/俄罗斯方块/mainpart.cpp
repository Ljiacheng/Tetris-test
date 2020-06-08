#define _CRT_SECURE_NO_WARNINGS
#include"block.h"
#include<easyx.h>
#include<conio.h>

int Topgrade = 0;//��߷�
void showtop();//��ʾ��߷�
void showgrade(int grade);//��ʾ��ǰ����,������ʱ���úͳ�ʼʱ����,ͬʱ������߷�
void shownextb(Block nextb);//��ʾ�¸��������ҷ�
void gamepage();//��Ϸ����
void startgame();//��ʼҳ��
int  checkcrush(Block& curb, Backblock backblock[][10]);//�����ײ,����1������ײ������0����δ��ײ
int checkfullline(int& Topgrade, int& grade, Backblock backblock[][10]);//������У�����1�������У�����0����δ����
void kbdoing(Block& curb, Backblock backblock[][10]);//���̰�������


int main() {
	initgraph(500, 660);//�򿪴���
	setorigin(30, 30);//��������ԭ��
	Backblock backblock[20][10];//��������
	Block nextb, curb;//��һ������͵�ǰ����
	int grade;//����
	int newb;//�����ж���һ��ѭ���Ƿ��������µķ���
rq:	startgame();//��ʼ���漰��ѡ��
rr:	gamepage();//��Ϸ�����ӡ
	for (int i = 0;i < 20;i++)//��ʼ������20��10�ĸ��ӣ�����������
		for (int j = 0;j < 10;j++)
		{
			backblock[i][j].rol = i;
			backblock[i][j].col = j;
			backblock[i][j].ispour = 0;
		}
	grade = 0;
	newb = 0;
	curb.randblock();//������ɷ���
	nextb.randblock();
	shownextb(nextb);//����һ��������ʾ���ұ�
	curb.showblock();//������ʾ��һ������
	showtop();//��ʾ��߷�
	showgrade(grade);//��ʾ����
	while (1) {//��ѭ��
		if (newb) {
			newb = 0;
			nextb.randblock();//������һ������
			shownextb(nextb);//����һ��������ʾ���ұ�
			curb.showblock();//����������Ϸ�
			if (checkcrush(curb, backblock)) {
				newb = 1;
			    if(checkfullline(Topgrade,grade,backblock)){//���в�������Ӧ����
					continue;
			    }
				else{//�����в���ͷ
					settextcolor(RED);
					outtextxy(180, 250, _T("��Ϸ������"));//��Ϸ����ҳ��
					outtextxy(90, 330, _T("�� r ���¿�ʼ���� q ���ؿ�ʼ����"));
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
		kbdoing(curb,backblock);//����ָ������ƶ�����ת
		if(checkcrush(curb,backblock)){			//�ж���ײ
		    checkfullline(Topgrade,grade,backblock);//���м�⴦��
			newb = 1;
			curb = nextb;
			continue;
		}
		curb.moveblock(2,backblock);//ÿ�̶�ʱ���Զ������ƶ�һ��
	 	if(checkcrush(curb,backblock)){			//�ж���ײ
			checkfullline(Topgrade,grade, backblock);//���м�⴦��
			newb=1;
			curb = nextb;
			continue;
		}
	}
	_getch();
	closegraph();
	return 0;
}

void showtop()//��ʾ��߷�
{
	settextcolor(WHITE);
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(340, 240, 500, 260);
	setlinecolor(RGB(215, 222, 214));
	outtextxy(325, 220, _T("��߷֣�"));
	FILE* fp = fopen("score.txt", "r");
	char s1[50];
	fscanf(fp, "%s", s1);
	Topgrade = atoi(s1);
	TCHAR s[20];
	swprintf_s(s, _T("%d"), Topgrade);
	outtextxy(340, 240, s);
	fclose(fp);
}
void showgrade(int grade)//��ʾ��ǰ����,������ʱ���úͳ�ʼʱ����,ͬʱ������߷�
{
	settextcolor(WHITE);
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(340, 280, 500, 300);
	outtextxy(325, 260, _T("��ǰ������"));
	TCHAR s[20];
	if (grade > Topgrade)//�����ļ��е����ֵ
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
		showtop();//������ʾ��߷�
	}
	swprintf_s(s, _T("%d"), grade);
	outtextxy(340, 280, s);
}
void shownextb(Block nextb)//��ʾ�¸��������ҷ�
{
	setfillcolor(BLACK);
	fillrectangle(310, 30, 460, 150);
	setfillcolor(nextb.color);
	int mir = min(nextb.rol[0], min(nextb.rol[1], min(nextb.rol[2], nextb.rol[3])));//�ҳ���С����
	int mic = min(nextb.col[0], min(nextb.col[1], min(nextb.col[2], nextb.col[3])));
	setlinecolor(RGB(215, 222, 214));
	BeginBatchDraw();
	for (int i = 0;i < 4;i++)
		fillrectangle((nextb.col[i] - mic) * 30 + 320, (nextb.rol[i] - mir) * 30 + 60,
		(nextb.col[i] - mic) * 30 + 350, (nextb.rol[i] - mir) * 30 + 90);
	FlushBatchDraw();//
	EndBatchDraw();//
}

void gamepage()//��Ϸ����
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
	outtextxy(360, 380, _T("w   ��ת"));
	outtextxy(360, 400, _T("a   ����"));
	outtextxy(360, 420, _T("d   ����"));
	outtextxy(360, 440, _T("s   ����"));
	outtextxy(360, 460, _T("�ո񵽵�"));
}

void startgame()//��ʼҳ��
{
start:	
	setfillcolor(BLACK);
	fillrectangle(-30, -30, 500, 660);
	settextcolor(WHITE);
	settextstyle(20, 0, _T("����"));
	outtextxy(160, 230, _T("����˹���飡"));
	outtextxy(90, 310, _T("�� e ��ʼ��Ϸ���� q �˳���Ϸ"));
	char kbin = 0;
	kbin = _getch();
	if (kbin == 'q')//�˳���Ϸ
		exit(0);
	else if (kbin != 'e')
		goto start;//�ص���ҳ��
}
int  checkcrush(Block& curb, Backblock backblock[][10])//�����ײ,����1������ײ������0����δ��ײ
{
	for (int i = 0;i < 4;i++) {
		if (backblock[curb.rol[i] + 1][curb.col[i]].ispour == 1 || curb.rol[i] + 1 > 19) {//�����ײ��
			curb.color = RGB(242, 226, 167);
			for (int j = 0;j < 4;j++) { //�������״̬
				backblock[curb.rol[j]][curb.col[j]].ispour = 1;
				curb.showblock();
			}
			return 1;
		}
	}
	return 0;
}

int checkfullline(int& Topgrade, int& grade, Backblock backblock[][10]) {//������У�����1�������У�����0����δ����
//�������ܣ�������У��������У��������ƣ��������ӣ���ʾ����
	int flag = 0, lines = 0;
	for (int i = 19;i >= 0;i--) {//���ÿһ��
		int f = 0;
		for (int j = 0;j < 10;j++) {//�����е�ÿ������
			if (backblock[i][j].ispour == 0) {//���в���
				break;
			}
			else
				f++;
		}
		if (f == 10) {//������
			flag = 1;
			lines++;
			for (int b = i;b >= 1;b--) {//�Ϸ�ÿ����������
				for (int c = 0;c < 10;c++) {//����һ��
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
			i++;//�ص���ǰ�м�����
			for (int c = 0;c < 10;c++) {//���Ϸ�һ�����״̬
				backblock[0][c].ispour = 0;
				setfillcolor(BLACK);
				fillrectangle(c * 30, 0, c * 30 + 30, 30);
			}
		}
	}
	if (flag == 0) return 0;
	else {
		grade += lines;//���·���
		showgrade(grade);//��ʾ����
		return 1;
	}
}

void kbdoing(Block& curb, Backblock backblock[][10])//���̰�������
{
	char kbin = 0;
	int t = 0;
	while (kbin != 'q')
	{
		if (_kbhit())
			kbin = _getch();
		if (kbin == 'w')
			curb.rotateblock(backblock);//��ת����
		else if (kbin == 'a')//����
			curb.moveblock(1, backblock);
		else if (kbin == 's')//����
			curb.moveblock(2, backblock);
		else if (kbin == 'd')//����
			curb.moveblock(3, backblock);
		else if (kbin == VK_SPACE)//����
			curb.moveblock(4, backblock);
		kbin = 0;//ˢ�°���
		Sleep(80);//���̽�����Ϣ���mm�������е���
		t++;
		if (t == 10) break;//t*100�����Զ�����һ��,�����е���
	}
}