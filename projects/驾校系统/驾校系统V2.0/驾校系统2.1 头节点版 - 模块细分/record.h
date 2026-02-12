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
#define UID_START 1001
#define SUBJECT_COUNT 4
#define STATUS_COUNT 4 

//定义一个用于记录的结构体
//包含姓名，分数，实际，
//用链表来实现 

//教学科目 (4个) 
typedef enum{
	SUBJECT_1, //科目一（理论） 
	SUBJECT_2, //科目二（场地） 
	SUBJECT_3, //科目三（路考） 
	SUBJECT_4, //科目四（安全文明） 
}Subject; 

//学员状态：单科目 
typedef enum{
	STATUS_UNREGISTERED,//未报考
	STATUS_WAIT_EXAM, //待考试
	STATUS_PASSD,  //已通过 
	STATUS_FAILED //挂科待补考 
}ExamStatus;



//科目名称数组（索引对于Subject枚举值
const char* SubjectNames[]={
	"科目一（理论）",
	"科目二（场地）",
	"科目三（路考）",
	"科目四（安全文明）" 
}; 

//科目状态名称对应数组 
const char* StatusNames[]={
	"未报考",
	"待考试",
	"已通过",
	"挂科待补考" 
}; 


struct Record{
	char name[20];
	int score;
	time_t time;
	int user_id;//【唯一UID】 
	Subject curr_subject;
	ExamStatus curr_status;
	struct Record *next;
};
//==========================================================
				//安全&基础功能 
void safe_input_int(int *p,int min,int max);
int empty(struct Record *head);
int check_malloc(struct Record *node); 
int assignment_user_id(struct Record *head);//给学员编号 
int get_linkList_len(struct Record *head);//获取链表长度（不包括头节点） 
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

