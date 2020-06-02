# Tetris-test
这是一个简单实现俄罗斯方块的程序，共有500行左右。
该程序是c++程序，使用的是vs2019，并且使用了EasyX图形库。
关于图形库详情请搜索easyx了解，该图形库适合初学者使用。
在进行试玩本游戏时请先将输入法调整为英文。

该程序适合c++初学者观看，需要的知识有：
    基本的c++语法知识
    EasyX图形库（可以看中文文档）

本游戏中的方块共有七种，主要思路是将七种方块的构成及其旋转情况都依次罗列出来，因此有很大一部分的重复代码，
理解这一点后就基本不影响阅读了，因为源码中有着大量的备注。


目前缺点：

          1、在方块旋转方面，因为各种方块旋转后所占的空间不同，因此暂时考虑将所有方块以左上到右下填充的原则填充。
             因此导致有些方块在靠右时无法旋转。
             比如一字型的方块如果是竖着的，此时若右边只有小于等于2格的空间，则无法旋转为横一字。
             更优的方法有待考虑。
             
          2、此代码只注重基本玩法的实现，其余视觉上的界面效果等没有详细设计。
