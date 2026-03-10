#include "library.h"
//以下为学生信息管理模块的函数定义
//==========================================
//功能：输入一个学生信息
//参数：i表示对对第i个学生进行输入操作
//返回：无
//主要思路：用gets函数输入学生的学号和姓名
//==========================================
void InputOnestud(int i){
	printf("\n");
	printf("学号：");	gets(student[i].num);
	printf("姓名：");   gets(student[i].name);
} 
