# RetroSnaker

C语言 贪吃蛇小游戏

操作
---

awsd控制蛇的转向

更新日志
---

2018.12.9

* 增加了欢迎界面和结束页面，可以重新游戏。
* 可以显示最高分（注意要创建一个“SnakeScore.txt”放在RetroSnaker.c的根目录下。
* 新版本中蛇不能回头，防止误触。
* 分数提高后，速度会逐渐加快。
* 修正了食物出现在墙里的bug。

2018.12.10

* 增加了以下功能：按Esc键暂停，再按任意键继续游戏。按F1加速，同时每个食物加分变高。按F2减速，同时每个食物加分变低。
* 修复了结束界面按任意键重新游戏的bug，增加了按键提示。
* 修复了蛇可以在左右墙中行走的bug。
* 存在的问题：F1,F2键的部分还有许多问题：滞后变速，加分不变。读取最高分有时异常。
* 经验：变量声明应放在goto语句的lable之前，否则会报错：[Error] a label can only be part of a statement and a declaration is not a statement
