#include "record.h"
//====================================================================================
//=====================添加功能函数========================

//=========================================================
//初始化一个节点
void assignment_node(Record *newNode){
	//输入姓名 分数 
	printf("请输入要添加的学员的姓名:");
	while(scanf("%19s",newNode->name)!=1) {
		printf("请输入正确的姓名："); 
		while(getchar()!='\n');
	}
	
	
	printf("请输入该学员的成绩：");
	safe_input_int(&newNode->score,SCORE_MIN,SCORE_MAX);
	
	//时间戳
	newNode->time = time(NULL);
	
	//指针域置空
	newNode->next = NULL; 
	
	printf("正在录入中....\n");
	sleep(SLEEP_SEC);
	
	return;
} 
//=========================================================

//=========================================================
//在链表末尾加一个节点 
Record * tail_add_node(Record *head){
	//申请内存
	Record *newNode = (Record*)malloc(sizeof(Record));
	if(newNode==NULL){
		printf("内存分配失败，无法添加学员信息\n");
		return NULL;
	} 
	
	//赋值 and uid的添加
	assignment_node(newNode);
	newNode->user_id = get_uid(head);
	
	//挂载
	Record *p = head;
	while(p->next)
		p=p->next;
	p->next = newNode;
	
	
	return head;
}
//=========================================================

//=========================================================
//批量增加节点
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
		printf("找到【UID:%d】姓名：[%s]  分数：%d 时间：%s",p->user_id,p->name,p->score,ctime(&(p->time)));

	}
	
	return head; 
} 

