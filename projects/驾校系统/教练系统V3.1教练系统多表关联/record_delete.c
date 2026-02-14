#include "record.h"
//====================================================================================
//=====================删除功能函数========================

//=========================================================
//头删法 
//输入：链表头节点
//输出：删除首元节点后的新链表的头节点 
Record * head_delete_node(Record *head){
	if(empty(head))return NULL;
	
	Record *p = head->next;
	head->next = p->next;
	
	free(p);
	p=NULL;
	
	return head; 
} 
//=========================================================

//=========================================================
//尾删法 
//输入：链表头节点
//输出：删除最后节点后的新链表的头节点 
Record *tail_delete_node(Record *head){
	if(empty(head))return NULL;
	
	Record *p = head;
	while(p->next->next){
		p=p->next;
	}
	Record *q=p->next;
	p->next = q->next;//指针域置空 
	
	free(q);
	q = NULL;
	
	return head;
} 
//=========================================================

//=========================================================
//按照uid删除
//输入：uid
//输出：按要求删除后的新链表的头节点 
Record *uid_delete_node(Record *head,int *is_found){
	if(empty(head))return NULL;
	
	int uid = 0;
	printf("请输入要删除的学员的id:");
	safe_input_int(&uid,UID_START,get_uid(head)-1);
	
	Record *p = head; 
	*is_found = 0;
	while(p->next){
		if(uid==p->next->user_id){
			printf("找到【UID:%d】姓名：[%s]",uid,p->next->name);
			Record *q = p->next;
			p->next = q->next;
			printf("正在删除中...\n");
			sleep(SLEEP_SEC);
			free(q);
			q = NULL;
			*is_found = 1;
			break;
		}
		p=p->next;
	}
	
	if(*is_found == 0)printf("查无此人，请检查输入\n");
	
	return head; 
}  
//=========================================================

//=========================================================
//批量删除
//输入：删除方式 删除个数
//输出：按要求删除后的新链表的头节点  
Record *batch_delete_node(Record *head){
	if(empty(head))return NULL;
	
	//选择输入方式
	int choice = 3;
	printf("请选择删除方式：头删（1） 尾删（2） 按id删（3)：");
	safe_input_int(&choice,1,3);
	
	//删除个数
	int len = get_linkList_len(head);
	int delete_times = 0;
	printf("请输入要删除的学员的个数(0-%d)",len);
	safe_input_int(&delete_times,0,len);
	
	int is_found = 0;
	for(int i=0;i<delete_times;){
		switch(choice){
			case 1:
				head = head_delete_node(head);
				i++;
				break;
			case 2:
				head = tail_delete_node(head);
				i++;
				break;
			case 3:
				head = uid_delete_node(head,&is_found);
				if(is_found==1)i++;
				break;
			default:
				printf("请输入有效的选项\n");
				break;
		}
	}
	
	return head;
	
} 
//=========================================================
