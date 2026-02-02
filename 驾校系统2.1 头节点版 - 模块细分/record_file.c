#include "record.h"
//保存数据至文件 ================================
	
void save_to_file(struct Record *head){
	if(empty(head))return;
	
	FILE *fp = fopen("students.txt","w");
	if(fp==NULL){
		printf("未找到文件\n");
		return ;
	}
	
	struct Record *p = head;
	int cnt = 0;
	//老问题：我还是用了while(p) 到最后 p->next = NULL, 程序会对NULL 解引用，直接崩溃
	//为什么我会觉得while(p)可以呢，因为我觉得p可遍历地更多，而我程序内用的又是p->next,我以为是没错的 
	while(p->next!= NULL){
		fprintf(fp,"姓名：%s   | 分数：%d    |时间：%ld\n",p->next->name,p->next->score,(long)p->next->time);
		cnt++;
		p=p->next;
	}
	
	printf("已经将%d条信息存入硬盘\n",cnt);
	fclose(fp);
	
}
//===============================================
//从文件中读取数据 ==============================

struct Record* load_from_file(){
	FILE *fp = fopen("students.txt","r");
	if(fp==NULL){
		printf("未找到文件\n");
		return NULL; 
	}
	
	char name[20];
	int score;
	long t;
	int cnt = 0;
	
	//建议改成现有的函数 head = create_linkList() 
	struct Record *head = (struct Record *)malloc(sizeof(struct Record));
	//bug1:没有给head->next赋值，出现野指针bug 
	head->next = NULL;
	
	if(check_malloc(head))return NULL;
	
	struct Record *tail = NULL;
	//fscanf()的内容要与fprintf()的一致 
	while(fscanf(fp,"姓名：%s   | 分数：%d    |时间：%ld\n",name,&score,&t)!=EOF){
		
		struct Record *newNode = (struct Record*)malloc(sizeof(struct Record));
		//bug2这里没有检查malloc分配
		if(check_malloc(newNode))return NULL; 
		
		strcpy(newNode->name,name);
		newNode->score = score;
		newNode->time = t;
		newNode->next = NULL;
		
		if(head->next==NULL){
			head->next = newNode;
			tail = newNode;
		}else{
			tail->next = newNode;
			tail = newNode;
		}
		
		cnt++;
	}
	
	printf("已从硬盘读取%d条数据\n",cnt);
	fclose(fp);
	
	return head;
}
//================================================
