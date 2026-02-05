#ifndef RECORD_H_
#define RECORD_H_

#include <stdio.h>
#include <stdlib.h>//
#include <string.h>//strncpy() strncpm() strcat()
#include <time.h>//time() ctime()
#include <unistd.h>//sleep()

#define UID_START 10001
#define SCORE_MAX 100
#define SCORE_MIN 0 
#define SLEEP_SEC 2 
#define FAIL_SCORE 90

typedef struct Record{
	int user_id;
	char name[20];
	int score;
	time_t time;
//	Subject curr_subject;
//	ExamStatus curr_status;
	struct Record *next;
	
} Record; 

//=====================基础功能函数声明========================
void safe_input_int(int *p,int min,int max);
void free_linkList(Record *head);
int empty(Record *head);
int get_linkList_len(Record *head);
int get_uid(Record *head); 

//=====================添加功能函数声明========================
Record *batch_add_node(Record *head);

//=====================删除功能函数声明========================
Record *batch_delete_node(Record *head);

//=====================修改功能函数声明========================
void modify_by_uid(Record *head);

//=====================查询功能函数=声明=======================
void inquire_all(Record *head); 
void inquire_by_uid(Record *head);
void inquire_range(Record *head);

//=====================文件操作功能函数声明========================
void save_to_file(Record *head);
Record *load_from_file(); 

//=====================数据分析功能函数======================== 
void statistic_analysis(Record *head);
void bubble_sort_score(struct Record *head);

//=====================用户交互功能函数======================== 
struct Record* menu(struct Record* head); 



#endif
