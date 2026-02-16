#include "record.h"
//====================================================================================
//=====================添加功能函数========================

//=========================================================
//初始化一个节点
//输入：new_node
//输出：成员变量初始化成功的new_node 
void assignment_node(Record *new_node){
	//输入姓名 分数 
	printf("请输入要添加的学员的姓名:");
	while(scanf("%19s",new_node->name)!=1) {
		printf("请输入正确的姓名："); 
		while(getchar()!='\n');
	}
	
	//成绩与状态 
	for(int i=0;i<SUBJECT_COUNT;i++){
		new_node->scores[i] = 0;
		new_node->statuses[i] = STATUS_UNREGISTERED; 
	}
	
	//时间戳
	new_node->time = time(NULL);
	
	//分配教练,初始化为没有分配 
	new_node->coach_id = -1; 
	
	//指针域置空
	new_node->next = NULL; 
	
	printf("正在录入中....\n");
	sleep(SLEEP_SEC);
	
	return;
} 
//=========================================================

//=========================================================
//在链表末尾加一个节点 
//输入：链表头节点
//输出：加上一个新节点在末尾的链表头节点 
Record * tail_add_node(Record *head){
	//申请内存
	Record *new_node = (Record*)malloc(sizeof(Record));
	if(new_node==NULL){
		printf("内存分配失败，无法添加学员信息\n");
		return NULL;
	} 
	
	//赋值 and uid的添加
	assignment_node(new_node);
	new_node->user_id = get_uid(head);
	
	//挂载
	Record *p = head;
	while(p->next)
		p=p->next;
	p->next = new_node;
	
	
	return head;
}
//=========================================================

//=========================================================
//批量增加节点
//输入：链表头节点
//输出：添加了选择个数的节点的链表头节点 
Record *batch_add_node(Record *head){
	if(head==NULL){
		printf("初始化不成功\n");
		return NULL;
	}
	int information_number = 0;
	printf("请输入你要添加的学员的个数：");
	safe_input_int(&information_number,0,100);
	 
	for(int i=0;i<information_number;i++){
		head = tail_add_node(head); 
		Record *p = head;
		while(p->next)p=p->next; 
		printf("添加中...\n");
		sleep(SLEEP_SEC); 
		printf("\n===================================\n");
		printf("【UID:%d】姓名：[%s]\n",p->user_id,p->name);
		printf("各科目初始状态：\n");
		for(int j = 0;j<SUBJECT_COUNT;j++){
			printf(" %s: 分数：%d  ,状态：%s\n",subject_names[j],p->scores[j],status_names[p->statuses[j]]); 
		}
		printf("添加时间：%s",ctime(&(p->time)));
   		printf("===================================\n");
	}
	
	return head; 
} 

