#include "record.h"
//====================================================================================
//=====================基础功能函数========================

//=========================================================
//功能：输入合法验证，包括验证范围 ，核心在于清理输入缓存区 
void safe_input_int(int *p,int min,int max){
	while(1){
		if(scanf("%d",p)!=1){
			printf("非法输入，请输入整数:"); 
			while(getchar()!='\n');
			continue;
		}
		//if the previous if statement's judgement fails,it is necessary to 
		//chaek once again and clear the input buffer once
		while(getchar()!='\n');
		
		if(*p>max||*p<min){
			printf("输入超出范围，请输入%d到%d的整数:",min,max);
			continue;
		}
		break;
	}
}
//=========================================================

//=========================================================
//清除链表所占的内存，避免内存泄漏 
void free_linkList(Record *head){
	if(head==NULL){
		printf("初始化未成功\n");
		return;
	}
	Record *p;
	while(head){
		p=head;
		head = head->next;
		free(p);
		p = NULL;
	} 
	return;
}
//=========================================================

//=========================================================
//检查空链表以及链表是否存在
int empty(Record *head){
	int ret=1;
	if(head==NULL){
		printf("初始化未成功\n");
	}
	else if(head->next == NULL){
		printf("没有学员数据"); 
	}
	else ret = 0;
	
	return ret; 
} 
//=========================================================

//=========================================================
//获得链表长度
int get_linkList_len(Record *head){
	int cnt = 0;
	Record *p = head->next;
	while(p){
		cnt++;
		p=p->next;
	}
	return cnt;
} 
//=========================================================

//=========================================================
//为每个学员加上独一无二的id,id要自增,这个函数是给id的，等到
//加成员的时候再赋值 
int get_uid(Record *head){
	if(head==NULL){
		printf("初始化不成功\n");
		return 0;	
	}
	if(head->next==NULL) return UID_START;
	
	int max_uid = UID_START - 1;
	Record *p = head->next;
	while(p){
		if(p->user_id>max_uid)max_uid = p->user_id;
		p=p->next;
	}
	return max_uid+1;
}
//=========================================================


