#include "record.h" 
//====================================================================================
//=====================查询功能函数========================

//=========================================================
//查询所有学员信息 
void inquire_all(Record *head){
	if(empty(head))return ;
	
	Record *p = head->next;
	 
	while(p){
		printf("【UID:%d】\t姓名：[%s]\t分数：%d\t时间：%s",p->user_id,p->name,p->score,ctime(&(p->time)));
		p=p->next;
	}
	
	return;
} 


//=========================================================
//按uid查询学员信息 
void inquire_by_uid(Record *head){
	if(empty(head))return;
	
	int uid = 0;
	printf("请输入要查询的学员的id:");
	safe_input_int(&uid,UID_START,get_uid(head)-1);
	
	Record *p = head; 
	int is_found = 0;
	printf("正在查询中...\n");
	sleep(SLEEP_SEC);
	while(p->next){
		if(uid==p->next->user_id){			
			printf("找到【UID:%d】姓名：[%s]  分数：%d 时间：%s",p->next->user_id,p->next->name,p->next->score,ctime(&(p->next->time)));
			is_found = 1;
			break;
		}
		p=p->next;
	}
	
	if(is_found == 0)printf("查无此人，请检查输入\n");
	
	return ;
}


//=========================================================
//查询某个分数段的学员信息

void inquire_range(Record *head){
	if(empty(head))return;
	
	printf("请输入你要查询的分数段：");
	int min=0,max=0;
	while(1){
		if(scanf("%d %d",&min,&max)!=2){
			printf("类型错误，请输入两个整数\n");
			while(getchar()!='\n');
			continue;
		}
		while(getchar()!='\n');
		if(max<min){
			printf("输入错误,%d比%d却在后面\n",max,min);
			continue; 
		}
		else if(max>100||min<0||max<0||min>100){
			printf("请输入正确的范围\n");
			continue;
		}
		break;
	} 
	Record *p = head; 
	int is_found = 0;
	printf("正在查询中...\n");
	sleep(SLEEP_SEC);
	while(p->next){
		if(p->next->score >= min && p->next->score <=max){			
			printf("找到【UID:%d】姓名：[%s]  分数：%d 时间：%s",p->next->user_id,p->next->name,p->next->score,ctime(&(p->next->time)));
			is_found = 1;
		}
		p=p->next;
	}
	
	if(is_found == 0)printf("无学员在此分数段\n");
	
	return ;
}
//=========================================================


