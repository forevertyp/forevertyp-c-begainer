#include "record.h"
void statistic_analysis(struct Record *head){
	//忘记加表为空的判断
	if(empty(head))return; 
	
	//计算平均分，分数最高最低的人，不及格的人数 
	int sum = 0;
	double average = 0;
	int max,min;
	double cnt = 0;
	int number_of_failure = 0;

	
	struct Record *p = head;
	//min是后min加的忘记赋值了 
	max = min = p->next->score;
	//这里还是以p作为了结尾，不行 
	for(;p->next;p=p->next){
		sum+=p->next->score;
		cnt++;
		
		if(p->next->score>max)
			max = p->next->score;
			
		if(p->next->score<min)
			min = p->next->score;
		if(p->next->score<FAIL_SCORE)
			number_of_failure++;
	} 
	
	average = sum/cnt;
	
	printf("统计并分析数据结果如下：\n");
	
	printf("平均分：%lf\n",average);
	
	printf("最高分为：%d  ",max);
	printf("最高分获得者如下：\n");
	for(p=head;p->next;p=p->next){
		if(p->next->score == max)printf("|%s\t",p->next->name);
	}
	printf("\n"); 
	
	printf("最低分为：%d  ",min);
	printf("最低分获得者如下：\n");
	for(p=head;p->next;p=p->next){
		if(p->next->score==min)printf("|%s\t",p->next->name);
	}
	printf("\n");
	
	printf("不及格的%d人有：\n",number_of_failure);
	for(p=head;p->next;p=p->next){
		if(p->next->score < FAIL_SCORE)printf("|姓名：%s\t\t分数：%d\n",p->next->name,p->next->score);
	}
} 
