#include "record.h" 
//====================================================================================
//=====================修改功能函数========================

//=========================================================
//修改姓名，分数
void modify_by_uid(Record *head){
	if(empty(head))return;
	
	int uid = 0;
	printf("请输入要修改信息的学员的id:");
	safe_input_int(&uid,UID_START,get_uid(head)-1);
	
	Record *p = head; 
	int is_found = 0;
	printf("正在查询中...\n");
	sleep(SLEEP_SEC);
	while(p->next){
		if(uid==p->next->user_id){			
			printf("找到【UID:%d】姓名：[%s]  分数：%d 时间：%s",p->next->user_id,p->next->name,p->next->score,ctime(&(p->next->time)));
			printf("请输入你要修改的内容：姓名（1） 分数（2） 姓名和分数（3）：");
			int choice = 2;
			safe_input_int(&choice,1,3);
			switch(choice){
				case 1:
					printf("请输入新的姓名：");
					scanf("%19s",p->next->name);
					while(getchar()!='\n');
					break;
				case 2:
					printf("请输入新的分数：");
					safe_input_int(&p->next->score,SCORE_MIN,SCORE_MAX);
					break;
				case 3:
					printf("请输入新的姓名和分数：\n");
					printf("姓名：");
					scanf("%19s",p->next->name);
					while(getchar()!='\n');
					printf("分数：");
 					safe_input_int(&p->next->score,SCORE_MIN,SCORE_MAX);
 					break;	
			} 
			
			is_found = 1;
			break;
		}
		p=p->next;
	}
	
	if(is_found == 0)printf("查无此人，请检查输入\n");
	
	return ;
}
//=========================================================

 

