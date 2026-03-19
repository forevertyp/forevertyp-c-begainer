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

extern SSTUD student[STUDNUM];
extern SBOOK book[BOOKNUM];

//===============用户登录模块=====================
void ManagerLogin(int *pbn,int *psn);
void StudentLogin(int bn,int sn); 

//==============图书信息管理模块==================
void InputOnebook(int i);
int LoadBooks(void);
void SaveOnebook(int i); 
void SaveAllbooks(int bn);
int OriginalBook(void);
void ModifyBook(int bn);
int AddBook(int bn);
int DelBook(int bn);
void OutputOnebook(int i);
void OutputAllbooks(int bn);
void OutputBrief(int bn); 

//==============学生信息管理模块===================
void InputOnestud(int i);
int LoadStuds(void);
void SaveOnestud(int i);
void SaveAllstuds(int sn);
int OriginalStud(void);
void ModifyStud(int sn);
int AddStud(int sn);
int DelStud(int sn);
void OutputOnestud(int i);
void OutputAllstuds(int sn); 


//==============图书查询模块=======================
void SearchMenu(int bn);
void SearchBname(int bn);
void SearchAuthor(int bn);
void SearchBclass(int bn);
void SearchPublisher(int bn);
void SearchPubtime(int bn); 

//===============图书借阅模块========================
void BorrowBook(int bn,int m);
void ReturnBook(int bn,int m); 

#endif 
