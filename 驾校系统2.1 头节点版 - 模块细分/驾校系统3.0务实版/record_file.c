#include "record.h"
//====================================================================================
//=====================文件操作功能函数========================

//=========================================================
//保存所有学员信息到文件

void save_to_file(Record *head){
	if(empty(head))return;
	
	FILE *fp = fopen("students.txt","w");
	if(fp==NULL){
		printf("未能找到文件，请重试\n");
		return;
	}
	
	Record *p = head->next;
	
	while(p){
		fprintf(fp,"%d %s %d %ld\n",p->user_id,p->name,p->score,(long)(p->time));
		p=p->next;
	}
	
	printf("成功将%d条学员信息转入硬盘\n",get_linkList_len(head));
	fclose(fp);
	
	return;
} 
//=========================================================

//=========================================================
//从文件读取学员信息
Record *load_from_file(){
	FILE *fp = fopen("students.txt","r");
	if(fp==NULL){
		printf("未能找到文件，请重试\n");
		return NULL; 
	}
	
	Record *head = (Record*)malloc(sizeof(Record));
	if(head == NULL){
		printf("初始化不成功，请重试\n");
		return NULL; 
	}
	head->next = NULL;
	Record *tail = head->next;
	
	int uid;
	char name[20];
	int score;
	long t;
	
	while(fscanf(fp,"%d %s %d %ld",&uid,name,&score,&t)!=EOF){
		Record *newNode = (Record*)malloc(sizeof(Record));
		if(newNode==NULL){
			printf("内存分配失败,请重试\n");
			return NULL;
		}
		
		strcpy(newNode->name,name);
		newNode->score = score;
		newNode->user_id = uid;
		newNode->time = t;
		newNode->next = NULL;
		
		if(tail==NULL){
			head->next = newNode;
			tail = head->next;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
	
	}
	printf("从硬盘中读取%d条数据。\n",get_linkList_len(head));
	fclose(fp);
	
	return head;
} 
//=========================================================

