#include "record.h"
//修改功能 ======================================
void find_and_modify(struct Record *head){
	if(empty(head))return;
	
	char target_name[20];
	printf("请输入你要修改的学员的姓名：");
	scanf("19s",target_name);
	
	struct Record *p = head; 
	int flag = 1;
	//p->next;
	while(p->next){
		if(strcmp(target_name,p->next->name)==0){
			printf("找到[%s] 当前分数为 %d \n",target_name,p->next->score);
			
			printf("请输入新的分数：");
			safe_input_int(&p->next->score,SCORE_MIN,SCORE_MAX);
			
			//忘记加更新时间戳
			p->next->time = time(NULL); 
			
			printf("修改中.....\n");
			sleep(SLEEP_SEC);
			printf("修改成功！姓名：%s  分数：%d\n",target_name,p->next->score);
			flag = 0;
		}
		p = p->next;
	}
	
	if(flag == 1)printf("查无此人\n");	
} 
//===============================================
//查询功能 ======================================
void inquire_info(struct Record *head){
	if(empty(head))return;
	
	char target_name[20];
	printf("请输入你要查找的学员的姓名：");
	scanf("%19s",target_name);
	
	struct Record *p = head; 
	int flag = 1;
	while(p->next){
		if(strcmp(target_name,p->next->name)==0){

			printf("查找中.....\n");
			sleep(SLEEP_SEC);
			printf("查找成功！姓名：%s  分数：%d  时间：%s",target_name,p->next->score,ctime(&(p->next->time)));
			flag = 0;
		}
		p = p->next;
	}
	
	if(flag == 1)printf("查无此人\n");	
} 
//===============================================
