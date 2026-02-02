#include "record.h"
				//创建链表
//创建 //其他值可以不赋值 
struct Record * create_linkList(){
	struct Record * head = (struct Record*)malloc(sizeof(struct Record));
	if(check_malloc(head)){
		printf("头节点创建失败\n"); 
		 return NULL;
	}
	head->next = NULL;
	return head;
}	
