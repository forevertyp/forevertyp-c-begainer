#include "record.h"
//==========================================================
				//安全功能 
	//安全输入int
void safe_input_int(int *p,int min,int max){
	while(1){
		if(scanf("%d",p)!=1){
			printf("非法输入，请输入整数");
			while(getchar()!='\n');
			continue; 
		}
		//改进 
		while(getchar()!='\n');
		if(*p<min || *p > max){
			printf("输入超出范围（%d-%d)\n",min,max);
			//while(getchar()!='\n');// 只清除了换行符，但可能还有其他字符
			continue;
		}
		break;
	}
} 

	//检查链表是否为空//看哨兵节点是否指向空节点 
int empty(struct Record *head){
	int ret = 0; 
	if(head->next==NULL) //:1 ?0;//！！！！！忘记：？ 
	{
		ret = 1;
		printf("链表为空\n"); 
	}
	return ret;
}

	//检查malloc内存分配是否成功
int check_malloc(struct Record *node){
	int ret = 0;
	if(node==NULL){
		printf("内存未分配成功\n");
		ret = 1;
	}
	return ret; 
} 

	//释放内存 //无需改动 
void free_linkList(struct Record *head){
	if(head==NULL){
		printf("无链表\n"); 
	}
	struct Record *p;
	while(head){
		p = head;
		head = head->next;
		free(p);
		p=NULL;
	}
	free(head);
} 

//写一个函数为每个学员加上id
int assignment_user_id(struct Record *head){
	//空链表时 
	if(head==NULL){
		printf("无链表\n");
		return 0;
	}
	if(empty(head))return UID_START;  //先返回，添加节点时再赋值 
	
	int max_uid = UID_START - 1;
	struct Record *temp = head->next;
	while(temp != NULL){
		if(temp->user_id > max_uid){
			max_uid = temp->user_id;
		}
		temp = temp->next; 
	}
	
	return max_uid+1;
} 

//获取链表长度（不包括头节点）
int get_linkList_len(struct Record *head){
	struct Record *p = head;
	int cnt = 0;
	while(p->next){
		p=p->next;
		cnt++;
	}
	return cnt;
}
 
//=============================================================
