#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
//用于记录学生成绩的结构体 
struct Record{
	int score;  //成绩 
	char name[20];  //姓名 
	time_t time;  //时间戳 
	struct Record *next;  //链表指针域 
}; 

void get_info(struct Record history[],int *count);   //录入信息函数头 
void statistic_analysis(struct Record history[],int count); //统计并分析信息 函数头 
void save_to_file(struct Record history[],int n);  //将信息保存到文件函数头 
void load_from_file(struct Record history[],int *count);//从文件中读取信息函数头 
void find_and_modify(struct Record history[],int count);//修改成绩函数头 
void show(struct Record history[],int count);//展示函数头 
void menu(struct Record history[]);//菜单函数头 

//主函数 
int main(){
	struct Record history[100];  //结构体声明，用于存储学员信息 
	menu(history);  //操作界面 
	return 0;   //返回值 
}

//录入数据;循环
//参数：传入数组 
void get_info(struct Record history[],int *count){ 
 		printf("请输入你要录入的学员的个数(0-100)：\n");
 		scanf("%d",count);
 		
		for(int i = 0;i<*count;i++){
		printf("请输入姓名：\n");
		scanf("%19s",history[i].name); //19控制宽度 确保'\0'的位置 
		
		//验证成绩输入 
		printf("请输入成绩：（0-100）\n");
		do{// 
			if(scanf("%d",&history[i].score)!= 1|| history[i].score>100||history[i].score<0){
				printf("非法输入，请重新输入\n");	
			}
			else break;
		} while(1);
		
		
		//记录时间戳 <time.h> 
		history[i].time = time(NULL);
		if(i<*count-1){
			printf("录入中...请等待\n");
			sleep(2);
		} 

		printf("记录【%d】: 姓名：%s   |分数：%d  |时间：%s",i+1,history[i].name,history[i].score,ctime(&history[i].time));
		printf("____________________________________________\n");
	} 
}
//数据统计分析：
void statistic_analysis(struct Record history[],int cnt){
	
	if(cnt==0){
		printf("暂无数据进行统计分析\n");
		return;
	}
	//数据设置 
	int sum=0;
	int max=-1;
	int number=0;
	double average=0;
	int fail[2]={0};
	int fail_count=0;
	
	//处理数据 
	for(int j = 0;j<3;j++){
		//求和 
		sum += history[j].score;
		//找最大值 
		if(history[j].score>max){
			max = history[j].score;
			number = j;
		}
		//不合格人数 
		if(history[j].score<90){
			fail[j] = 1; 
			fail_count++; 
		}
	} 
	//平均分 
	average = sum / 3.0;
	
	//输出 
	printf("\n[统计结果]\n");
	printf("学员平均分：%3lf\n",average);
	printf("状元：%s\n",history[number].name);
	printf("不合格人数：%d\n",fail_count); 
}


//固化信息 
void save_to_file(struct Record history[],int n){
	//存入文件，并决定计入模式 
	FILE *fp = fopen("students.txt","a");
	
	//检验 
	if(fp == NULL){
		printf("文件打开失败\n");
		return; 
	}
	
	//存数据的过程 
	for(int i = 0;i < n; i++){
		fprintf(fp,"%s %d %ld\n",history[i].name,history[i].score,(long)history[i].time);
	}
	//关闭文件 
	fclose(fp);
	printf("---数据已经保存到硬盘---\n"); 
	
}

//读取文件 
void load_from_file(struct Record history[],int *count){
	//决定读取的文件 
	FILE *fp = fopen("students.txt","r");
	
	//检验 
	if(fp==NULL){
		printf("暂时无历史数据。\n");
		return;
	}
	
	//读取并计数（指针确保值不会随函数接受而消失） 
	int i = 0;
	long temptime =(long)history[i].time;
	while(fscanf(fp,"%s %d %ld\n",history[i].name,&history[i].score,&temptime)!= EOF){
		i++;
		if(i>100) break;
		*count = i;
	}
	fclose(fp);
	printf("---已从硬盘加载%d条历史数据---\n",*count);
	
}

//修改：通过确定姓名来修改 
void find_and_modify(struct Record history[],int count){
	//输入名字 
	char targetName[20];
	//提示性输入 
	printf("请输入学员的姓名：");
	scanf("%s",targetName);
	
	//标志器：用于确定是否找到人了 
	int found = 0;
	
	//遍历寻找 forloop 
	for(int i = 0;i < count; i++){
		//strcmp(const *char1,const *char2)  0是相同 1是不同 
		if(strcmp(history[i].name,targetName)==0){
			printf("找到了！当前分数是%d\n",history[i].score);
			//改分数 
			printf("请输入新的分数：\n");
			scanf("%d",&history[i].score);
			//改动时间 
			history[i].time = time(NULL);
			found = 1;
			printf("修改成功\n"); 
			break;
		}
	} 
	//无此人时的处理 
	if(!found){
		printf("查无此人，请检查输入是否正确\n");
	}
}
//遍历展示 ctime()函数自带\n 
void show(struct Record history[],int count){
	for(int i = 0;i<count;i++){
		printf("记录【%d】: 姓名：%s\t\t|分数：%d\t\t|时间：%s",i+1,history[i].name,history[i].score,ctime(&history[i].time));
	}
}

//菜单 
void menu(struct Record history[]){
	int flag = 1;
	int current_count = 0;
	while(flag){
	int choice;
		printf("\t------操作菜单------\t\n");
		printf("\t1.录入学员信息\t\n");
		printf("\t2.统计分析信息\t\n");
		printf("\t3.保存至文件\t\n");
		printf("\t4.从文件中读取信息\t\n");
		printf("\t5.修改学员成绩\t\n");
		printf("\t6.查看学员内容\t\n");
		printf("\t0.退出程序\t\n");                            
		printf("\t--------------------\t\n");
		printf("\t请输入你的选项\t\n");
		scanf("%d",&choice);
		
 		switch(choice){
 			case 1:
 				get_info(history,&current_count);
 				break;
 			case 2:
 				statistic_analysis(history,current_count);
			 break;
			case 3:
				save_to_file(history,current_count);
				break;
			case 4:
				load_from_file(history,&current_count);
				break;
			case 5:
				find_and_modify(history,current_count);
				break;
			case 6:
				show(history,current_count);
				break;
			case 0:
				printf("你真的要退出吗\n");
				printf("是请输入'y/Y'，不是请输入'n/N'\n");
				char option;
				scanf(" %c",&option);
				if(option=='n'||option=='N'){
					continue;
				}
				else if(option=='y'||option=='Y'){
					return;
				}
				
			default:
				printf("请输入正确的选项（0-6）：\n");
				break;
		 }
	}	
}

