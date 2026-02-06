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
		//先写入基本信息和！科目数量 !
		fprintf(fp,"%d %s %ld %d ",p->user_id,p->name,(long)(p->time),SUBJECT_COUNT);
		
		//写入所有科目的分数和状态 
		for(int i=0;i<SUBJECT_COUNT;i++){
			fprintf(fp,"%d %d ",p->scores[i],(int)p->statuses[i]);
		}
		fprintf(fp,"\n");
		
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
	int subject_count;
	long t;
	
	while(fscanf(fp,"%d %s %ld %d ",&uid,name,&t,&subject_count)==4){
		Record *newNode = (Record*)malloc(sizeof(Record));
		if(newNode==NULL){
			printf("内存分配失败,请重试\n");
			return NULL;
		}
		
		strcpy(newNode->name,name);
		newNode->user_id = uid;
		newNode->time = t;
		newNode->next = NULL;
		
		//读取科目数据
		for(int i = 0;i<subject_count;i++){
			int score,status;
			if(fscanf(fp,"%d %d",&score,&status)!=2){
				newNode->scores[i] = 0;
				newNode->statuses[i] = STATUS_UNREGISTERED; 
			}
			else{
				newNode->scores[i] = score;
				newNode->statuses[i] = (ExamStatus)status; 
			}
		} 
		
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

