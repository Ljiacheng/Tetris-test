#pragma once
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<random>
//�˴����������࣬Backblock����Ϊ�����壬��������20*10������

//�ڶ�����Block�࣬�������ַ���Ļ����࣬ÿ�ַ��鶼��4��С������ɣ�
//��ͬ�ķ���������������ͺ���ɫ����ȣ����ڲ���randblock����������ɡ�
class Backblock
{
public:
	int rol, col;//�к�������
	int ispour;//�Ƿ����ø���Ϊ֮�����ײ�ж����ݡ�
};
class Block//��������
{
public:
	Block();
	Block(Block &b);//��������
	void operator=(Block& b);//����
	void randblock();//�������˷�������
	void clearblock();//��������
	void showblock();//��ӡ����
	void moveblock(int n,Backblock backblock[][10]);//���������ƶ��������������ң��£�ֱ�ӵ�������״̬
	void rotateblock(Backblock backblock[][10]);//���������ת
	int type;//0-6���������͵ķ���
	COLORREF color;//������ɫ
	int rol[4],col[4];//�ĸ�С������к���
	int state;//�÷���ķ����е���4�֣��е������֣����ָ�ֻ��һ�ֲ�����
};

