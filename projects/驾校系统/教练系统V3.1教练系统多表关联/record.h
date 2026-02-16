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
#define SUBJECT_COUNT 4
#define STATUS_COUNT 5 
//====教练相关=======
#define CID_START 2001
#define MAX_STU_NUM 5

typedef enum{
	SUBJECT_1,
	SUBJECT_2,
	SUBJECT_3,
	SUBJECT_4 
}Subject; 

typedef enum{
	STATUS_UNREGISTERED,
	STATUS_REGISTERED,
	STATUS_WAITING_EXAM,
	STATUS_PASSED,
	STATUS_FAILED
}ExamStatus;

static const char* subject_names[] ={
	"科目一（理论）",
	"科目二（场地）",
	"科目三（路考）",
	"科目四（安全文明）" 
};

static const char* status_names[] = {
	"未报名",
	"已报名",
	"待考试",
	"已通过",
	"未通过" 
};


//================教练链表========================
typedef struct Coach{
	int coach_id;
	char coach_name[20];
	int student_count;
	int student[MAX_STU_NUM];
	struct Coach *next; 
}Coach;
//================================================ 


typedef struct Record{
	int user_id;
	int coach_id;
	char name[20];
	int scores[SUBJECT_COUNT];//每科的成绩 
	time_t time;
	ExamStatus statuses[SUBJECT_COUNT];//每科的状态 
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
void update_subject_score(Record *head);
void process_subject_progress(Record *head);

//=====================查询功能函数=声明=======================
void show_student_progress(Record *student);
void show_all_progress(Record *head);
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
