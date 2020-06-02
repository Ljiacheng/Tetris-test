#include"block.h"

Block::Block(){}
Block::Block(Block& b)
{
	this->type = b.type;
	this->color = b.color;
	this->state = b.state;
	for (int i = 0;i < 4;i++)
	{
		this->rol[i] = b.rol[i];
		this->col[i] = b.col[i];
	}
}
void Block::operator=(Block& b)
{
	this->type = b.type;
	this->color = b.color;
	this->state = b.state;
	for (int i = 0;i < 4;i++)
	{
		this->rol[i] = b.rol[i];
		this->col[i] = b.col[i];
	}
}

void Block::randblock()//�����������
{
	srand((unsigned)time(0));
	int t = rand()%7;
	this->state = 1;
	this->type = t;
	//this->color = RGB(242, 226, 167);
	switch (t)
	{
	case 0: {
		this->rol[0] = 0;this->rol[1] = 0;this->rol[2] = 1;this->rol[3] = 1;
		this->col[0] = 4;this->col[1] = 5;this->col[2] = 5;this->col[3] = 4;
		this->color = RED;
		break;
	}
	case 1: {
		this->rol[0] = 0;this->rol[1] = 1;this->rol[2] = 1;this->rol[3] = 1;
		this->col[0] = 4;this->col[1] = 4;this->col[2] = 5;this->col[3] = 6;
		this->color = YELLOW;
		break;
	}
	case 2: {
		this->rol[0] = 1;this->rol[1] = 1;this->rol[2] = 1;this->rol[3] = 0;
		this->col[0] = 4;this->col[1] = 5;this->col[2] = 6;this->col[3] = 6;
		this->color = GREEN;
		break;
	}
	case 3: {
		this->rol[0] = 0;this->rol[1] = 1;this->rol[2] = 1;this->rol[3] = 1;
		this->col[0] = 5;this->col[1] = 4;this->col[2] = 5;this->col[3] = 6;
		this->color = BLUE;
		break;
	}
	case 4: {
		this->rol[0] = 0;this->rol[1] = 0;this->rol[2] = 0;this->rol[3] = 0;
		this->col[0] = 3;this->col[1] = 4;this->col[2] = 5;this->col[3] = 6;
		this->color = RGB(200,147,206);
		break;
	}
	case 5: {
		this->rol[0] = 0;this->rol[1] = 0;this->rol[2] = 1;this->rol[3] = 1;
		this->col[0] = 4;this->col[1] = 5;this->col[2] = 5;this->col[3] = 6;
		this->color = RGB(130,240,180);
		break;
	}
	case 6: {
		this->rol[0] = 1;this->rol[1] = 1;this->rol[2] = 0;this->rol[3] = 0;
		this->col[0] = 4;this->col[1] = 5;this->col[2] = 5;this->col[3] = 6;
		this->color = RGB(180,240,169);
		break;
	}
	}
}
void Block::clearblock() {//��������
	setlinecolor(RGB(215, 222, 214));
	setfillcolor(BLACK);
	BeginBatchDraw();
	for (int i = 0;i < 4;i++){
		fillrectangle(this->col[i] * 30, this->rol[i] * 30, this->col[i] * 30 + 30, this->rol[i] * 30 + 30);
	}
	FlushBatchDraw();
	EndBatchDraw();
}
void Block::showblock()//��䷽��
{
	setlinecolor(RGB(215, 222, 214));
	setfillcolor(this->color);
	BeginBatchDraw();//��Ϻ�����BatchDraw����ʵ��������ͼ����ֹ��˸������Ȥ���԰�94,98,99��ע�͵����Ƿ���˸
	for (int i = 0;i < 4;i++){
		fillrectangle(this->col[i] * 30, this->rol[i] * 30, this->col[i] * 30 + 30, this->rol[i] * 30 + 30);
	}
	FlushBatchDraw();
	EndBatchDraw();
}
void Block::moveblock(int n,Backblock backblock[][10])//���������ƶ����������������ƶ��������ƶ���ֱ�ӵ�������״̬
{//n�� 1����    2����    3����   4������
	int flag = 0;
	if (n == 1) {
		int mic = min(this->col[0], min(this->col[1], min(this->col[2], this->col[3])));
		for (int i = 0;i < 4;i++)//�ж��Ƿ��������
			if (backblock[this->rol[i]][this->col[i]-1].ispour == 1 || mic-1<0)
				flag = 1;//��������
		if (flag == 0) {
			this->clearblock();
			for (int i = 0;i < 4;i++)//����һ��
				this->col[i]--;
			setfillcolor(this->color);
			this->showblock();
		}
	}
	else if (n == 2) {
		int n = 4;
		int mar = max(this->rol[0], max(this->rol[1], max(this->rol[2], this->rol[3])));
		for (int i = 0;i < 4;i++)//�ж��Ƿ��������
			if (backblock[this->rol[i] + 1][this->col[i]].ispour == 1 || mar + 1 > 19) {
				flag = 1;//��������
				break;
			}
		if (flag == 0) {
			this->clearblock();
			for (int i = 0;i < 4;i++)//����һ��
				this->rol[i]++;
			this->showblock();
		}
	}
	else if (n == 3) {
		int mac = max(this->col[0], max(this->col[1], max(this->col[2], this->col[3])));
		for (int i = 0;i < 4;i++)//�ж��Ƿ��������
			if (backblock[this->rol[i]][this->col[i]+1].ispour == 1 || mac+1>9)
				flag = 1;//��������
		if (flag == 0) {
			this->clearblock();
			for (int i = 0;i < 4;i++)//����һ��
				this->col[i]++;
			this->showblock();
		}
	}
	else if (n == 4) {
		int count = 0;
		while ((max(this->rol[0],max(this->rol[1],max(this->rol[2], this->rol[3])))+count)<20) {
			if (backblock[this->rol[0] + count+1][this->col[0]].ispour == 1)
				break;
			if (backblock[this->rol[1] + count+1][this->col[1]].ispour == 1)
				break;
			if (backblock[this->rol[2] + count+1][this->col[2]].ispour == 1)
				break;
			if (backblock[this->rol[3] + count+1][this->col[3]].ispour == 1)
				break;
			count++;
		}
		count--;
		this->clearblock();
		for (int i = 0;i < 4;i++)//����count��
			this->rol[i]+=count;
		this->showblock();
	}
}

int check(Backblock &back)//���Ŀ�ı������Ƿ������
{
	if (back.ispour == 0)
		return 1;
	else return 0;
}

void Block::rotateblock(Backblock backblock[][10])//���������ת.��ת֮ǰ�ж���ת�������Ƿ�Խ�磬top�������ϣ���ת���Ƿ���ײ��Խ��������ת��
{
	//���ڵ�0�����ָ����ת���عܣ�1-3����������״̬��4-6����������״̬
	//�˴�ֻ�Ե�һ�ַ���ĵ�һ��״̬�жϸ�����ע����������ͬ
	if (this->type == 1) {//��һ�ַ���
		if (this->state == 1) {//��һ��״̬
			if ((this->rol[0]+2 )< 20 //��ת����һ�����򳬳�һ�������жϼ���Ƿ�Խ��
				&& check(backblock[this->rol[0]][this->col[0] + 1]) //�����հ׷���Ҫ��䣬�鿴�Ƿ��Ѿ������
				&& check(backblock[this->rol[0] + 2][this->col[0]]))
			{
				this->clearblock();
				this->col[0]++;
				this->rol[1]--;
				this->col[2]--;
				this->rol[3]++;col[3] -= 2;
				this->showblock();
				this->state = 2;
			}	
		}
		else if (this->state == 2) {
			if (this->col[0] + 1 < 10 
				&& check(backblock[this->rol[0]][this->col[0] + 1])
				&& check(backblock[this->rol[0] + 1][this->col[0] + 1]))
			{
				this->clearblock();
				this->rol[0]++;this->col[0]++;
				this->col[1]+=2;
				this->rol[2]--;this->col[2]++;
				this->rol[3]-=2;
				this->showblock();
				this->state = 3;
			}
		}
		else if (this->state == 3) {
			if (this->rol[0]+1<20
				&& check(backblock[this->rol[0]][this->col[0] - 1]) 
				&& check(backblock[this->rol[0] + 1][this->col[0] - 1])
				&& check(backblock[this->rol[0] + 1][this->col[0] - 2]))
			{
				this->clearblock();
				this->rol[0]++;this->col[0] -= 2;
				this->rol[1] += 2;this->col[1]--;
				this->rol[2]++;
				this->col[3]++;
				this->showblock();
				this->state = 4;
			}
		}
		else if (this->state == 4) {
			if (this->col[0] +2 < 10 
				&& check(backblock[this->rol[0] -2][this->col[0]])
				&& check(backblock[this->rol[0] -1][this->col[0]])
				&& check(backblock[this->rol[0] -1][this->col[0] + 2]))
			{
				this->clearblock();
				this->rol[0] -= 2;
				this->rol[1]--;this->col[1]--;
				this->rol[3]++;this->col[3]++;
				this->showblock();
				this->state = 1;
			}
		}
	}
	if (this->type == 2) {
		if (this->state == 1) {
			if ((this->rol[0]+2 )< 20
				&& check(backblock[this->rol[0] -1][this->col[0]])
				&& check(backblock[this->rol[0] +1][this->col[0]])
				&& check(backblock[this->rol[0] + 1][this->col[0] + 1]))
			{
				this->clearblock();
				this->rol[0] --;
				this->col[1]--;
				this->rol[2]++;this->col[2]-=2;
				this->rol[3] += 2;this->col[3] -= 1;
				this->showblock();
				this->state = 2;
			}
		}
		else if (this->state == 2) {
			if (this->col[0] + 2 < 10
				&& check(backblock[this->rol[0]][this->col[0]+1])
				&& check(backblock[this->rol[0]][this->col[0]+2]))
			{
				this->clearblock();
				this->col[0] +=2;
				this->rol[1]--;this->col[1]++;
				this->rol[2] -= 2;
				this->rol[3]--;this->col[3]--;
				this->showblock();
				this->state = 3;
			}
		}
		else if (this->state == 3) {
			if (this->rol[0] + 2 < 20
				&& check(backblock[this->rol[0] + 1][this->col[0] - 1])
				&& check(backblock[this->rol[0] + 2][this->col[0] - 1]))
			{
				this->clearblock();
				this->rol[0] += 2;this->col[0] --;
				this->rol[1]++;
				this->col[2]++;
				this->rol[3]--;
				this->showblock();
				this->state = 4;
			}
		}
		else if (this->state == 4) {
			if (this->col[0] +1 < 10
				&& check(backblock[this->rol[0] - 1][this->col[0]-1])
				&& check(backblock[this->rol[0] - 1][this->col[0]+1])
				&& check(backblock[this->rol[0] -2][this->col[0] +1]))
			{
				this->clearblock();
				this->rol[0] --;this->col[0]--;
				this->rol[2]++;this->col[2]++;
				this->col[3] += 2;
				this->showblock();
				this->state = 1;
			}
		}
	}
	if (this->type == 3) {
		if (this->state == 1) {
			if ((this->rol[0] + 2) < 20
				&& check(backblock[this->rol[0]][this->col[0] - 1])
				&& check(backblock[this->rol[0] + 2][this->col[0] - 1]))
			{
				this->clearblock();
				this->rol[0]++;
				this->rol[1]--;
				this->col[2]--;
				this->rol[3]++;this->col[3] -= 2;
				this->showblock();
				this->state = 2;
			}
		}
		else if (this->state == 2) {
			if (this->col[0] +1 < 10
				&& check(backblock[this->rol[0]-1][this->col[0]])
				&& check(backblock[this->rol[0]-1][this->col[0]+ 1]))
			{
				this->clearblock();
				this->col[1]+=2;
				this->rol[2]--;this->col[2]++;
				this->rol[3]-=2;
				this->showblock();
				this->state = 3;
			}
		}
		else if (this->state == 3) {
			if (this->rol[0] + 1 < 20
				&& check(backblock[this->rol[0]][this->col[0] - 1])
				&& check(backblock[this->rol[0] +1][this->col[0]]))
			{
				this->clearblock();
				this->col[0]--;
				this->rol[1] += 2;this->col[1]--;
				this->rol[2]++;
				this->col[3]++;
				this->showblock();
				this->state = 4;
			}
		}
		else if (this->state == 4) {
			if (this->col[0] + 2 < 10
				&& check(backblock[this->rol[0]][this->col[0]+2]))
			{
				this->clearblock();
				this->rol[0]--;this->col[0]++;
				this->rol[1]--;this->col[1]--;
				this->rol[3]++;this->col[3]++;
				this->showblock();
				this->state = 1;
			}
		}
	}
	if (this->type == 4) {
		if (this->state == 1) {
			if ((this->rol[0] + 3 )< 20
				&& check(backblock[this->rol[0] + 1][this->col[0]])
				&& check(backblock[this->rol[0] + 2][this->col[0]])
				&& check(backblock[this->rol[0] + 3][this->col[0]]))
			{
				this->clearblock();
				this->rol[1]++;this->col[1]--;
				this->rol[2] += 2;this->col[2] -= 2;
				this->rol[3] += 3;this->col[3] -= 3;
				this->showblock();
				this->state = 2;
			}
		}
		else if (this->state == 2) {
			if ((this->col[0] + 3 )< 10
				&& check(backblock[this->rol[0]][this->col[0] + 1])
				&& check(backblock[this->rol[0]][this->col[0] + 2])
				&& check(backblock[this->rol[0]][this->col[0] + 3]))
			{
				this->clearblock();
				this->rol[1]--;this->col[1]++;
				this->rol[2] -= 2;this->col[2] += 2;
				this->rol[3] -= 3;this->col[3] += 3;
				this->showblock();
				this->state = 1;
			}
		}
	}
	if (this->type == 5) {
		if (this->state == 1) {
			if ((this->rol[0] + 2) < 20
				&& check(backblock[this->rol[0] + 1][this->col[0]])
				&& check(backblock[this->rol[0] + 2][this->col[0]]))
			{
				this->clearblock();
				this->col[0] += 1;
				this->rol[1] += 1;
				this->col[2] -= 1;
				this->rol[3] += 1;this->col[3] -= 2;
				this->showblock();
				this->state = 2;
			}
		}
		else if (this->state == 2) {
			if ((this->col[0] + 1) < 10
				&& check(backblock[this->rol[0]][this->col[0]-1])
				&& check(backblock[this->rol[0] + 1][this->col[0]+1]))
			{
				this->clearblock();
				this->col[0] -= 1;
				this->rol[1] -= 1;
				this->col[2] += 1;
				this->rol[3] -= 1;this->col[3] += 2;
				this->showblock();
				this->state = 1;
			}
		}
	}
	if (this->type == 6) {
		if (this->state == 1) {
			if ((this->rol[0] + 1) < 20
				&& check(backblock[this->rol[0] - 1][this->col[0]])
				&& check(backblock[this->rol[0] + 1][this->col[0]+1]))
			{
				this->clearblock();
				this->rol[0]--;
				this->col[1]--;
				this->rol[2]++;
				this->rol[3]+=2;this->col[3]--;
				this->showblock();
				this->state = 2;
			}
		}
		else if (this->state == 2) {
			if (this->col[0] + 2 < 10
				&& check(backblock[this->rol[0]][this->col[0] + 1])
				&& check(backblock[this->rol[0]][this->col[0] + 2]))
			{
				this->clearblock();
				this->rol[0]++;
				this->col[1]++;
				this->rol[2]--;
				this->rol[3] -= 2;this->col[3]++;
				this->showblock();
				this->state = 1;
			}
		}
	}
}