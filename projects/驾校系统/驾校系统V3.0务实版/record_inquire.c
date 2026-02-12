#include "record.h" 
//====================================================================================
//=====================查询功能函数========================

//=========================================================
// 显示一个学员所有科目详情
void show_student_progress(Record *student){
	if(student == NULL){
		printf("学员不存在\n");
		return;
	}
	
	printf("\n【UID:%d】%s的科目进度总览：\n",student->user_id,student->name);
	printf("===================================\n");
	int passed_count = 0;
	for(int j = 0;j<SUBJECT_COUNT;j++){
		printf(" %s: 分数：%d  ,状态：%s\n",SubjectNames[j],student->scores[j],StatusNames[student->statuses[j]]);
		if(student->statuses[j]==3)passed_count++; 
	}
	printf("===================================\n");
	printf("进度：%d/%d 科目已经通过\n",passed_count,SUBJECT_COUNT);
	if(passed_count==SUBJECT_COUNT){
		printf("恭喜，该学员已经通过所有项目!\n"); 
	}
	printf("\n");
	return ;
}
//=========================================================

//=========================================================
// 显示所有学员的所有科目详情
void show_all_progress(Record *head){
	while(empty(head))return ;
	
	Record *p=head->next;
	while(p){
		show_student_progress(p);
		p=p->next;
	}
	
	return ;
}
//=========================================================


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
			show_student_progress(p->next);
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
	
	printf("请输入你要查询分数段的科目：\n");
	printf("科目一（1） 科目二（2） 科目三（3） 科目四（4）：");
	int subject_choice = 0;
	safe_input_int(&subject_choice,1,4);
	subject_choice--; 
	
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
		if(p->next->scores[subject_choice] >= min && p->next->scores[subject_choice] <=max){			
			printf("找到【UID:%d】姓名：[%s]  分数：%d 时间：%s",p->next->user_id,p->next->name,p->next->scores[subject_choice],ctime(&(p->next->time)));
			is_found = 1;
		}
		p=p->next;
	}
	
	if(is_found == 0)printf("无学员在此分数段\n");
	
	return ;
}
//=========================================================


