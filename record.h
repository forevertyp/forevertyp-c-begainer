#ifndef RECORD_H 
#define RECORD_H
#endif

#include<stdio.h>     //printf() scanf()
#include<unistd.h>   //sleep()
#include<time.h>	//time() ctime()
#include<string.h>  //strcmp() 
#include<stdlib.h> //用于引入malloc()函数 

//用于记录学生成绩的结构体 
struct Record{
	int score;  //成绩 
	char name[20];  //姓名 
	time_t time;  //时间戳 
	struct Record *next;  //链表指针域 
}; 

struct Record *add_one_node(struct Record *head);//添加一个节点头插 
struct Record *get_info(struct Record *head);   //录入信息函数头 
struct Record *delete_node(struct Record *head);//删除一个对应学员 
struct Record *delete_info(struct Record *head);//删除学员 
void save_to_file(struct Record *head);  //将信息保存到文件函数头 
struct Record* load_from_file();//从文件中读取信息函数头 
void find_and_modify(struct Record *head);//修改成绩函数头 
void show(struct Record *head);//展示函数头 
void free_list(struct Record *head);//清除内存 
void statistic_analysis(struct Record *head); //统计并分析信息 函数头 
void bubbleSort_records(struct Record *head);//把数据进行排序 
void find_fail_student(struct Record *head);//查找不合格的学员，并打印 
void search_by_name(struct Record *head);//按名字查找学员记录 
void menu(struct Record *head);//菜单函数头 
