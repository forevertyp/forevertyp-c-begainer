#include "record.h"
//====================================================================================
//=====================数据分析功能函数======================== 

//=========================================================
//得出平均分，分数最高，最低以及不合格的人 
void statistic_analysis(Record *head){
	if(empty(head))return ;
	
	Record *p = head->next;
	int sum = 0;
	double average = 0;
	int max,min;
	max = min=p->score;
	double cnt = 0;
	int number_failure = 0;
	
	for(;p;p=p->next){
		sum+=p->score;
		cnt++;
		
		if(p->score>max)
			max = p->score;
			
		if(p->score<min)
			min = p->score;
		if(p->score<FAIL_SCORE)
			number_failure++;	
	}
	
	average = sum/cnt;
	
	printf("统计并分析数据结果如下：\n");
	
	printf("平均分：%lf\n",average);
	
	printf("最高分为：%d  ",max);
	printf("最高分获得者如下：\n");
	for(p=head->next;p;p=p->next){
		if(p->score == max)printf("|【UID:%d】  %s\t",p->user_id,p->name);
	}
	printf("\n"); 
	
	printf("最低分为：%d  ",min);
	printf("最低分获得者如下：\n");
	for(p=head->next;p;p=p->next){
		if(p->score==min)printf("|【UID:%d】  %s\t",p->user_id,p->name);
	}
	printf("\n");
	
	printf("不及格的%d人有：\n",number_failure);
	for(p=head;p->next;p=p->next){
		if(p->score < FAIL_SCORE)printf("|【UID:%d】  姓名：%s\t\t分数：%d\n",p->user_id,p->name,p->score);
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
	
	Record *p,*q;
	for(p=head;p->next;p=p->next){
		int swapped = 0;
		for(q=head;q->next->next;q=q->next){
			if(q->next->score < q->next->next->score ){
				swap_node_info(q,q->next,q->next->next);
				swapped = 1; 
			}
		}
		if(swapped == 0)break;
	}
	
	printf("学员信息已按成绩（由高到低）排好序\n");
} 

