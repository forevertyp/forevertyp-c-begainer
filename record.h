#ifndef RECORD_H
#define RECORD_H

#endif

#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<string.h> 
#include<stdlib.h>

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
void menu(struct Record *head);
