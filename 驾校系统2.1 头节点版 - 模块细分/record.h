#ifndef RECORD_H
#define RECORD_H

//位置错放，应该放在最后面 
//现在没报错是因为头文件只包含一次后续如果还要拓展功能的话，就会连编译都过不了
// #endif


#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<string.h> 
#include<stdlib.h>

// record.h 新增宏定义
#define NAME_MAX_LEN 19  // 留1位给'\0'
#define SCORE_MIN 0
#define SCORE_MAX 100
#define FAIL_SCORE 90
#define SLEEP_SEC 2

//定义一个用于记录的结构体
//包含姓名，分数，实际，
//用链表来实现 

struct Record{
	char name[20];
	int score;
	time_t time;
	int user_id;
	struct Record *next;
};
//==========================================================
				//安全功能 
void safe_input_int(int *p,int min,int max);
int empty(struct Record *head);
int check_malloc(struct Record *node); 
//=============================================================
struct Record * create_linkList();//创建链表 头节点 

struct Record *batch_add_node(struct Record *head);//批量加节点 
struct Record * batch_delete_node(struct Record *head);//批量删除 
void find_and_modify(struct Record *head);//查找并且修改成绩 
void inquire_info(struct Record *head);//查询个人信息 
void show(struct Record *head);//展示学员信息，全部 
void save_to_file(struct Record *head);//保存学员信息到文件"students.txt" 
struct Record* load_from_file();//从文件"students.txt"中读取信息 
void bubble_sort_score(struct Record *head);//冒泡排序从高到低 
void statistic_analysis(struct Record *head);//数据分析 
void free_linkList(struct Record *head);//释放链表，避免内存泄漏 
struct Record* menu(struct Record *head);//主菜单，用于与用户交互 

#endif 

