#include "record.h"
//====================================================================================
//=====================数据分析功能函数======================== 

//=========================================================
//得出平均分，分数最高，最低以及不合格的人 
void statistic_analysis(Record *head){
	if(empty(head))return ;
	
	printf("请输入你要查询分数段的科目：\n");
	printf("科目一（1） 科目二（2） 科目三（3） 科目四（4）：");
	int subject_choice = 0;
	safe_input_int(&subject_choice,1,4);
	subject_choice--; 
	
	Record *p = head->next;
	int sum = 0;
	double average = 0;
	int max,min;
	max = min=p->scores[subject_choice];
	double cnt = 0;
	int number_failure = 0;
	
	for(;p;p=p->next){
		sum+=p->scores[subject_choice];
		cnt++;
		
		if(p->scores[subject_choice]>max)
			max = p->scores[subject_choice];
			
		if(p->scores[subject_choice]<min)
			min = p->scores[subject_choice];
		if(p->scores[subject_choice]<FAIL_SCORE)
			number_failure++;	
	}
	
	average = sum/cnt;
	
	printf("统计并分析数据结果如下：\n");
	
	printf("平均分：%lf\n",average);
	
	printf("最高分为：%d  ",max);
	printf("最高分获得者如下：\n");
	for(p=head->next;p;p=p->next){
		if(p->scores[subject_choice] == max)printf("|【UID:%d】  %s\t",p->user_id,p->name);
	}
	printf("\n"); 
	
	printf("最低分为：%d  ",min);
	printf("最低分获得者如下：\n");
	for(p=head->next;p;p=p->next){
		if(p->scores[subject_choice]==min)printf("|【UID:%d】  %s\t",p->user_id,p->name);
	}
	printf("\n");
	
	printf("不及格的有%d人：\n",number_failure);
	printf("如下是不及格的人：\n");
	for(p=head;p->next;p=p->next){
		if(p->scores[subject_choice] < FAIL_SCORE)printf("|【UID:%d】  姓名：%s\t\t分数：%d\n",p->user_id,p->name,p->scores[subject_choice]);
	}
}

//=========================================================
//数据排序，根据程序 冒泡排序
void swap_node_info(Record *pre,Record *a,Record *b){
	if(pre==NULL||a==NULL||b==NULL){
		printf("传入无效节点，无法交换");
		return;
	}
	pre->next = b;
	a->next = b->next;
	b->next = a;
	return;
} 

void bubble_sort_score(Record *head){
	if(empty(head))return ;
	
	printf("请输入你要查询分数段的科目：\n");
	printf("科目一（1） 科目二（2） 科目三（3） 科目四（4）：");
	int subject_choice = 0;
	safe_input_int(&subject_choice,1,4);
	subject_choice--; 
	
	Record *p,*q;
	for(p=head;p->next;p=p->next){
		int swapped = 0;
		for(q=head;q->next->next;q=q->next){
			if(q->next->scores[subject_choice] < q->next->next->scores[subject_choice] ){
				swap_node_info(q,q->next,q->next->next);
				swapped = 1; 
			}
		}
		if(swapped == 0)break;
	}
	
	printf("学员信息已按成绩（由高到低）排好序\n");
} 

