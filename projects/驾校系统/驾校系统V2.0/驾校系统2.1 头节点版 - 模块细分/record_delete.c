#include "record.h"
//删除功能 ======================================
	//删除一个节点
		//头删 

struct Record * head_delete_one_node(struct Record *head){
	if(empty(head))return NULL; 
	struct Record *p;
	
	p = head->next;
	head->next = p->next;
	
	free(p);
	p=NULL;
	return head;
}
		//尾删 
struct Record *tail_delete_one_node(struct Record *head){
	if(empty(head))return NULL; 	
	struct Record *p=head;
	while(p->next->next!=NULL) p = p->next;
	struct Record *q;
	q = p->next;
	p->next = q->next;
	
	free(q);
	q=NULL;
	
	return head;
}

		//按名字删
struct Record* delete_one_node_by_name(struct Record *head,int *is_found){
	if(empty(head))return NULL; 
	char target_name[20];
	printf("请输入要删除学员的姓名：");
	//不能NAME_MAX_LENs不能识别字符串，会出隐形错误 
	scanf("%19s",target_name);
	//加上
	 while(getchar() != '\n'); 
	
	struct Record *p = head;
	
	*is_found = 0; 
	while(p->next){
		if(strcmp(p->next->name,target_name)==0){
			struct Record *q = p->next;
			
			printf("找到姓名：[%s]   分数：%d\n",target_name,q->score);
			
			p->next = q->next;
			printf("删除中...\n");
			sleep(SLEEP_SEC);
			
			free(q);
			q=NULL;//free(p->next) p->next = NULL 
			*is_found = 1;
			break;
		}
		p=p->next;
	}
	if(*is_found==0) printf("查无此人\n");
	
	return head;
}

		//按UID删
struct Record* delete_one_node_by_userId(struct Record *head){
	if(empty(head))return NULL; 
	
	struct Record *p = head;
	int uid = 0;
	printf("请输入你要删除的学员的id:\n");
	safe_input_int(&uid,1001,1000+get_linkList_len(head));
	int is_found = 0;
	while(p->next){
		if(p->next->user_id==uid){
			struct Record *q = p->next;
			
			printf("找到【UID:%d】 姓名：[%s]   分数：%d\n",p->next->user_id,p->next->name,q->score);
			
			p->next = q->next;
			printf("删除中...\n");
			sleep(SLEEP_SEC);
			
			free(q);
			q=NULL;//free(p->next) p->next = NULL 
			is_found = 1;
			break;			
		}
		p=p->next;
	}
	if(is_found==0) printf("查无此人\n");	
	
	return head;
} 
		//批量删除 
struct Record * batch_delete_node(struct Record *head){
	if(empty(head))return NULL;
	
	int choice = 1;
	printf("请输入你的删除方式：""头删（1） 尾删（2） 按名字删（3） 按ID删(4)\n");
	safe_input_int(&choice,1,4);
	
	struct Record *p = head;
	
	int cnt = get_linkList_len(head);
	
	int delete_times;
	printf("请输入你要删除学员的人数(0-%d)：",cnt); 
	safe_input_int(&delete_times,0,cnt);
	
	int is_found = 0;
	switch(choice){
		case 1:
			//把choice改成cnt才对，写快了//cnt 也不对 是delete_time才对太急了 
			for(int i=0;i<delete_times;i++)head = head_delete_one_node(head);
			break;
		case 2:
			for(int i=0;i<delete_times;i++)head = tail_delete_one_node(head);
			break;
		case 3:
			//添加一个名字输入错误后，不计入删除的数的实现 
			for(int i=0;i<delete_times;){
				head = delete_one_node_by_name(head,&is_found);
				//查无此人后，i也会+1，我需要做到，i不变 ,我就需要一个
				//能确定是否查询到信息的参数来确定i，也就是is_found,我决定传入指针 
				if(is_found==1) i++;
			}
			break;	
		case 4:
			for(int i=0;i<delete_times;i++)head = delete_one_node_by_userId(head);
			break;					
	}
	/*
	for(int i=0;i<delete_times;i++){
		switch(choice){
			case 1: head = head_delete_one_node(head); break;
			case 2: head = tail_delete_one_node(head); break;
			case 3: head = delete_one_node_by_name(head,is_found); break;
			case 4: head = delete_one_node_by_userId(head); break; 
			
		}
	}
	*/
	return head;
}
//===============================================
