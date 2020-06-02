#pragma once
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<random>
//此处定义两种类，Backblock是作为背景板，背景共有20*10个方块

//第二种是Block类，这是七种方块的基础类，每种方块都有4个小格子组成，
//不同的方块有其特殊的类型和颜色坐标等，由内部的randblock函数随机生成。
class Backblock
{
public:
	int rol, col;//行和列坐标
	int ispour;//是否填充该格，作为之后的碰撞判断依据。
};
class Block//方块类型
{
public:
	Block();
	Block(Block &b);//拷贝构造
	void operator=(Block& b);//拷贝
	void randblock();//随机定义此方块类型
	void clearblock();//消除方块
	void showblock();//打印方块
	void moveblock(int n,Backblock backblock[][10]);//方块向下移动函数，包括左，右，下，直接到底四种状态
	void rotateblock(Backblock backblock[][10]);//本方块的旋转
	int type;//0-6共七种类型的方块
	COLORREF color;//方块颜色
	int rol[4],col[4];//四个小方块的行和列
	int state;//该方块的方向，有的有4种，有的有两种，田字格只有一种不考虑
};

