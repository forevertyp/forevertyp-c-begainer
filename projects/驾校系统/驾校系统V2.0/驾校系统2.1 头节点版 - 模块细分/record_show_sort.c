#include "record.h"
//显示功能 ======================================
void show(struct Record *head){
	if(empty(head))return ;
	struct Record *p = head;
	//bug3:不能是while(p)当走到最后p->next = NULL;与无头结点的不同 
	while(p->next){
		printf("【UID:%d】：姓名：%s\t\t|分数：%d \t|时间：%s",p->next->user_id,p->next->name,p->next->score,ctime(&(p->next->time)));
		p =p->next; 
	}
} 
//=============================================================
				//数据利用

//分析数据========================================
void swap_node_info(struct Record *p,struct Record *q){
	char temp_name[20];
	strcpy(temp_name,p->name);
	strcpy(p->name,q->name);
	strcpy(q->name,temp_name);
	
	int temp_score;
	temp_score = p->score;
	p->score = q->score;
	q->score = temp_score;
	
	long temp_time;
	temp_time = p->time;
	p->time = q->time;
	q->time = temp_time;
	
} 

void bubble_sort_score(struct Record *head){
	if(empty(head))return ;
	
	struct Record *p,*q;
	for(p=head;p->next;p=p->next){
		int swapped = 0;
		for(q=head;q->next->next;q=q->next){
			if(q->next->score < q->next->next->score ){
				swap_node_info(q->next,q->next->next);
				swapped = 1; 
			} 
		}
		if(swapped == 0)break;
	}
	
	printf("学员信息已按成绩（由高到低）排好序\n");
} 
