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
	struct Record *next;
};

void safe_input_int(int *p,int min,int max);
struct Record * create_linkList();
struct Record *batch_add_node(struct Record *head);
struct Record * batch_delete_node(struct Record *head);
void find_and_modify(struct Record *head);
void inquire_info(struct Record *head);
void show(struct Record *head);
void save_to_file(struct Record *head);
struct Record* load_from_file();
void bubble_resort_score(struct Record *head);
void statistic_analysis(struct Record *head);
void free_linkList(struct Record *head);
struct Record* menu(struct Record *head);

#endif 

