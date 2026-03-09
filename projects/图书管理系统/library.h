#ifndef LIBRARY_H_
#define LIBRARY_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>

typedef struct date{
	short year;
	short month;
	short day;
}SDATE;

typedef struct library_card{
	short flag;
	char ISBN[20];
	SDATE bor_time;
}SLCARD;

typedef struct stud{
	char num[15];
	char name[20];
	SLCARD card[5];
}SSTUD;

typedef struct book{
	char ISBN[20];
	char bookname[40];
	char author[20];
	char publisher[30];
	char bookclass[20];
	short total_num,stock_num;
	float price;
	SDATE publish_time; 
}SBOOK;


#define SDATE_LEN sizeof(SDATE)
#define SLCARD_LEN sizeof(SLCARD)
#define SSTUD_LEN sizeof(SSTUD)
#define SBOOK_LEN sizeof(SBOOK)
#define BOOKNUM 1000
#define STUDNUM 100

SSTUD student[STUDNUM] = {0};//设置为零表示什么嘛
SBOOK book[BOOKNUM] = {0};

//===============用户登录模块=====================
void ManagerLogin(int *pbn,int *psn);
void StudentLogin(int bn,int sn); 

//==============图书信息管理模块==================
void InputOneBook(int i);
int LoadBooks(void);
void Saveonebook(int i); 
void SaveAllbooks(int bn);
int originalBook(void);
void ModifyBook(int bn);
int AddBook(int bn);
int DelBook(int bn);
void OutputOnebook(int i);
void OutputAllbooks(int bn);
void OutputBrief(int bn);  

#endif 
