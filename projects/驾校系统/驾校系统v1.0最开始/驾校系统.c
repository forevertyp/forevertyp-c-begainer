#include<stdio.h>     //printf() scanf()
#include<unistd.h>   //sleep()
#include<time.h>	//time() ctime()
#include<string.h>  //strcmp() 
#include<stdlib.h> //用于引入malloc()函数 
//用于记录学生成绩的结构体 
struct Record{
	int score;  //成绩 
	char name[20];  //姓名 
	time_t time;  //时间戳 
	struct Record *next;  //链表指针域 
}; 

struct Record *add_one_node(struct Record *head);//添加一个节点头插 
struct Record *get_info(struct Record *head);   //录入信息函数头 
void statistic_analysis(struct Record *head); //统计并分析信息 函数头 
void save_to_file(struct Record *head);  //将信息保存到文件函数头 
struct Record* load_from_file();//从文件中读取信息函数头 
void find_and_modify(struct Record *head);//修改成绩函数头 
void show(struct Record *head);//展示函数头 
void free_list(struct Record *head);//清除内存 
void menu(struct Record *head);//菜单函数头 

//主函数 
int main(){
	struct Record *head = NULL;
	menu(head);  //操作界面 
	return 0;   //返回值 
}


struct Record *add_one_node(struct Record *head){
	//申请内存 
	struct Record *newNode = (struct Record*)malloc(sizeof(struct Record));
	//检验 
	if(newNode == NULL){
		printf("内存分配失败！\n");
		return head; 
	}
	
	//填入数据 
	printf("请输入姓名：\n");
	scanf("%19s",newNode->name); //19控制宽度 确保'\0'的位置 
	
	//验证成绩输入 
	printf("请输入成绩：（0-100）\n");
	do{// 
		if(scanf("%d",&newNode->score)!= 1|| newNode->score>100||newNode->score<0){
			printf("非法输入，请重新输入\n");	
		}
		else break;
	} while(1);
	
	
	//记录时间戳 <time.h> 
	newNode->time = time(NULL);
	printf("录入中...请等待\n");
	sleep(2);
	
	//指针域
	newNode->next = NULL; 
	
	//挂载
	if(head == NULL){
		return newNode;
	}else{
		//temp结构体指针，移动至链表的最后一个节点 
		//*不能拿head本身来移动，要不然链表会被摧毁，temp的使用是为了预防这种情况 
		struct Record *temp = head;
		while(temp->next!=NULL)
		temp=temp->next;
		//循环完后temp指向链表的最后一个节点 
		temp->next = newNode;//挂上去
		return head; 
	}
	  
}
//实现多个输入 

struct Record *get_info(struct Record *head){ 
	int count;
	printf("请输入你要录入的学员的个数(0-100)：\n");
	scanf("%d",&count);
	struct Record *tp; 
	for(int i = 0;i<count;i++){
	//
	head = add_one_node(head);
	tp = head;
	//
	while(tp->next != NULL)tp=tp->next;
	printf("记录【%d】: 姓名：%s\t\t|分数：%d\t\t|时间：%s",i+1,tp->name,tp->score,ctime(&(tp->time)));
	}
	return head;
}
//数据统计分析：
void statistic_analysis(struct Record *head){
	
	if(head == NULL){
		printf("暂无数据进行统计分析\n");
		return;
	}
	//数据设置 
	int sum = 0;
	int count = 0;//总人数
	int cnt = 0; 
	int max = -1;
	char top_name[20];
	double average = 0; 
	struct Record *p = head;
	
	//处理数据 
	while(p!=NULL){
		//求和 
		sum+= p->score;
		//求最大，找状元 
		if(p->score>max){
			max = p->score;
			//把这一轮中的最高分数的人的姓名也记下来，可以简化流程，链表不方便得到j
			//如果不这么做而是用计数器的方法就要在遍历一遍链表 
			strcpy(top_name,p->name);
		}
		count++;//用于记录人数，平均成绩
		//不合格人数
		if(p->score<90)
		cnt++;
		//假设我要记下这些不合格的人的具体信息，我就需要在建一个不合格的链表用于输出（这样更方便一点）
		p=p->next; 
	}
	
	//平均分 
	average = sum / count;//开始忘记改了还是 /3.0 
	
	//输出 
	printf("\n[统计结果]\n");
	printf("学员平均分：%3lf\n",average);
	printf("状元：%s |分数：%d\n",top_name,max);
	printf("不合格人数：%d\n",cnt); 
	printf("[----------------------]\n");
}


//固化信息 
void save_to_file(struct Record *head){
	//存入文件，并决定计入模式 
	FILE *fp = fopen("students.txt","a");
	
	//检验 
	if(fp == NULL){
		printf("文件打开失败\n");
		return; 
	}
	
	//存数据的过程 
	struct Record *p = head;
	while(p != NULL){
		fprintf(fp,"%s %d %ld\n",p->name,p->score,(long)(p->time));
		p=p->next;
	}
	
	//关闭文件 
	fclose(fp);
	printf("---数据已经保存到硬盘---\n"); 
	
}

//读取文件
//实现逻辑：重建火车，每读到一行 ，就得malloc一个节点，并把它挂载到末尾 
//实现功能：把从文件内读到的东西存入到新建的火车内 
struct Record* load_from_file(){
	//决定读取的文件 
	FILE *fp = fopen("students.txt","r");
	
	//检验 
	if(fp==NULL){
		printf("暂时无历史数据。\n");
		exit(2);
	}
	
	//重建过程 
	struct Record *head = NULL,*tail = NULL; 
	char name[20];
	int score;
	long t;
	//发现数据，立刻申请新车厢 
	while(fscanf(fp,"%s %d %ld\n",name,&score,&t)!= EOF){
		struct Record *newNode = (struct Record*)malloc(sizeof(struct Record));
		strcpy(newNode->name,name);
		newNode->score = score;
		newNode->time = (time_t)t;
		newNode->next = NULL;
		
		//挂载逻辑 
		if(head == NULL){
			head = newNode; //第一节车厢
			tail = newNode; 
		}else{
			tail->next = newNode; //
			tail = newNode;  //更新尾巴位置 
		} 
	}
	

	fclose(fp);
	
	return head;
	
}

//修改：通过确定姓名来修改 
void find_and_modify(struct Record *head){
	//检查链表 
	if(head==NULL){
		printf("当前无任何学员信息\n");
		return; 
	} 
	//输入名字 
	char targetName[20];
	//提示性输入 
	printf("请输入学员的姓名：");
	scanf("%s",targetName);
	
	struct Record *p = head;
	while(p!=NULL){
		//strcmp(const *char1,const *char2)  0是相同 1是不同 
		if(strcmp(p->name,targetName)==0){
			printf("找到%s！当分数是%d\n",p->name,p->score);
			//改分数 
			printf("请输入新的分数：\n");
			scanf("%d",&p->score);
			//改时间
			p->time = time(NULL); 
			break;
	 	}else{
	 		p = p->next; 
	 	}
	}
	//跑完后还没找到发出提示 
	if(!p) printf("查无此人，请检查是否输入正确\n");

}


//遍历展示 ctime()函数自带\n 
//链表遍历的逻辑最基础 
void show(struct Record *head){
	struct Record*p = head;
	while(p!= NULL){
		printf("姓名：%s |分数：%d |时间：%s",p->name,p->score,ctime(&(p->time)));
		p=p->next;
	}
}

//菜单 
void menu(struct Record *head){
	int flag = 1;
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
 				head = get_info(head);
 				break;
 			case 2:
 				statistic_analysis(head);
			 break;
			case 3:
				save_to_file(head);
				break;
			case 4:
				head = load_from_file();
				break;
			case 5:
				find_and_modify(head);
				break;
			case 6:
				show(head);
				break;
			case 0:
				printf("你真的要退出吗\n");
				printf("是请输入' y/ Y'，不是请输入' n/ N'\n");
				char option;
				scanf(" %c",&option);
				if(option=='n'||option=='N'){
					continue;
				}
				else if(option=='y'||option=='Y'){
					free_list(head); 
					flag = 0;
				}
				
			default:
				printf("请输入正确的选项（0-6）：\n");
				break;
		 }
	}	
}

void free_list(struct Record *head){
	struct Record *p;
	while(head!=NULL){
		p = head;
		head = head->next;
		free(p);
	} 
}
