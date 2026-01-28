#include "record.h"


/*
功能函数
一、创建功能
要保证有一个链表 
二、基础功能 
//添加 1.（从无到有） 2.从少到多
//删除 1.（头删除）（） 
//修改 1.（修改name,score） 2.时间不改 
//查询	1.具体记录
//显示 
三、数据利用 
//数据保存 
//数据分析
四、程序安全 
//安全（鲁棒函数）用于保证程序和逻辑不崩盘
*/


//==========================================================
				//安全功能 
	//安全输入int
void safe_input_int(int *p,int min,int max){
	while(1){
		if(scanf("%d",p)!=1){
			printf("非法输入，请输入整数");
			while(getchar()!='\n');
			continue; 
		}
		if(*p<min || *p > max){
			printf("输入超出范围（%d-%d）\n",min,max);
			while(getchar()!='\n');
			continue;
		}
		break;
	}
} 

	//检查链表是否为空
int empty(struct Record *head){
	int ret=0;
	if(head==NULL){
		printf("链表不存在，请重试\n");
		ret = 1;
	}
	return ret;
}

	//检查malloc内存分配是否成功
int check_malloc(struct Record *node){
	int ret = 0;
	if(node==NULL){
		printf("内存未分配成功\n");
		ret = 1;
	}
	return ret; 
} 

	//释放内存 
void free_linkList(struct Record *head){
	struct Record *p;
	while(head){
		p = head;
		head = head->next;
		free(p);
		p=NULL;
	}
} 

//=============================================================
				//创建链表
//创建 
struct Record * create_linkList(){
	struct Record *head = NULL;
	return head;
}				
		//有待升级，现在是无头节点版本 
//=============================================================
				//功能函数（无头节点版本） 
//添加功能 =======================================
	
	//节点赋值函数
struct Record* node_assignment(struct Record *newNode){
	
	printf("请输入新添加学员的姓名："); 
	scanf("%19s",newNode->name);
	
	printf("请输入新添加学员的成绩：");
	safe_input_int(&newNode->score,0,100);
	
	newNode->time = time(NULL);
	printf("正在录入中....\n");
	sleep(2); 
	
	//忘记给指针域赋值了导致一直报错 
	newNode->next = NULL; 
	
	return newNode;
	
} 
	//加一个节点(尾插)
struct Record * tail_add_one_node(struct Record *head){
	
	//申请新的节点
	struct Record *newNode = (struct Record*)malloc(sizeof(struct Record));
	
	//！！！！！忘记对malloc做空处理 !!!!!!!!封装的时候，忘记加回来了
	 if(check_malloc(newNode))return NULL;
		//为新的节点赋值
	newNode=node_assignment(newNode);
	//挂载新节点
	struct Record *p=head;
	if(head == NULL) {
		head = newNode;
	}else{
		while(p->next!=NULL)p=p->next;
		p->next = newNode; 
	}
	
	//需要在内部输出新节点的信息吗？//不需要还是保证函数的纯洁性好一点 
	return head;
}
		//头插 
struct Record *head_add_one_node(struct Record *head){
	struct Record *newNode = (struct Record*)malloc(sizeof(struct Record));
	if(check_malloc(newNode))return NULL;
	
	newNode = node_assignment(newNode);
	
	struct Record *p=head;
	if(head == NULL) {
		head = newNode;
	}else{
		newNode->next = head;
		head = newNode;
	}
	
	return head;
}

	//批量添加 
		//选择添加模式
int add_choice(){
	int choice=1;
	printf("请选择添加方式："
	"头插（1）  尾插（2）\n");
	safe_input_int(&choice,1,2);
	return choice; 
}

struct Record *batch_add_node(struct Record *head){
	int add_times;
	printf("请输入你要添加的学员的个数：");
	safe_input_int(&add_times,0,100);
	int choice = add_choice();
	struct Record *p,*tail;
	switch(choice){
		case 1:
			for(int i = 0;i<add_times;i++){
				head = head_add_one_node(head);//千万记得把返回值传给head,更新head 
				printf("【记录】：姓名：%s\t\t分数：%d\t时间：%s",head->name,head->score,ctime(&(head->time)));
			}
			break;
		case 2:
			for(int i = 0;i<add_times;p=p->next,i++){
				head = tail_add_one_node(head);
				//这样太低效了，应该用tail记录尾巴指针避免重复遍历 
				//p = head;
				//while(p->next)p=p->next;
				//这样做
				if(tail==NULL)tail = head;
				else tail = tail->next;
				//改动代码后没有吧p->name 改了 
				printf("【记录】：姓名：%s\t\t分数：%d\t时间：%s",tail->name,tail->score,ctime(&(tail->time)));				
			}
			break;
	}
	return head;
}
//===============================================
//删除功能 ======================================
	//删除一个节点
		//头删 

struct Record * head_delete_one_node(struct Record *head){
	if(empty(head))return NULL; 
	struct Record *p;
	p = head;
	head = head->next;
	
	free(p);
	p=NULL;
	return head;
}
		//尾删 
struct Record *tail_delete_one_node(struct Record *head){
	if(empty(head))return NULL; 	
	struct Record *p=head,*pre=NULL;
	while(p->next!=NULL){
		pre = p;
		p = p->next;
	}
	//!!!!!!最后的需要指向NULL!!!! 
	//没有考虑到单节点的条件
	//如果pre=NULL 还用pre->next ,就会崩溃执行 pre->next = NULL;  对 NULL 指针解引用，直接触发程序崩溃。
	if(pre==NULL){
		free(p);
		head = NULL;
	}else{
	pre->next = NULL; 
	free(p);
	//！！！！！注意free后p会变成野指针，free(p) 只释放「指向的内存」，不修改「指针变量 p」，释放后 p 变为野指针 
	p=NULL;	
	}

	return head;
}

		//按名字删
struct Record* delete_one_node_by_name(struct Record *head){
	if(empty(head))return NULL; 
	char target_name[20];
	printf("请输入要删除学员的姓名：");
	scanf("%19s",target_name);
	
	struct Record *pre=NULL,*p=head;
	int flag = 1;
	while(p){
		if(strcmp(target_name,p->name)==0){
			//找到了
			if(p==head){
				head = head->next;
			}else{
				pre->next = p->next; 
			}
			free(p);
			//这里忘记写target_name了 
			printf("找到[%s],已经成功删除\n",target_name);
			flag = 0;
		}
		pre = p;
		p = p->next;
	}
	if(flag == 1)printf("查无此人\n");
	return head; 
}
		//批量删除 
struct Record * batch_delete_node(struct Record *head){
	if(empty(head))return NULL;
	
	int choice = 1;
	printf("请输入你的删除方式：""头删（1） 尾删（2） 按名字删（3）\n");
	safe_input_int(&choice,1,3);
	
	struct Record *p = head;
	int cnt = 0;
	while(p){
		p=p->next;
		cnt++;
	}	
	
	int delete_times;
	printf("请输入你要删除学员的人数(0-%d)：",cnt); 
	safe_input_int(&delete_times,0,cnt);
	
	switch(choice){
		case 1:
			//把choice改成cnt才对，写快了//cnt 也不对 是delete_time才对太急了 
			for(int i=0;i<delete_times;i++)head = head_delete_one_node(head);
			break;
		case 2:
			for(int i=0;i<delete_times;i++)head = tail_delete_one_node(head);
			break;
		case 3:
			for(int i=0;i<delete_times;i++)head = delete_one_node_by_name(head);
			break;						
	}
	
	return head;
}
//===============================================
//修改功能 ======================================
void find_and_modify(struct Record *head){
	if(empty(head))return;
	
	char target_name[20];
	printf("请输入你要修改的学员的姓名：");
	scanf("%19s",target_name);
	
	struct Record *p = head; 
	int flag = 1;
	while(p){
		if(strcmp(target_name,p->name)==0){
			printf("找到[%s] 当前分数为 %d \n",target_name,p->score);
			
			printf("请输入新的分数：");
			safe_input_int(&p->score,0,100);
			
			printf("修改中.....\n");
			sleep(2);
			printf("修改成功！姓名：%s  分数：%d\n",target_name,p->score);
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
	while(p!=NULL){
		if(strcmp(target_name,p->name)==0){

			printf("查找中.....\n");
			sleep(2);
			printf("查找成功！姓名：%s  分数：%d  时间：%s",target_name,p->score,ctime(&(p->time)));
			flag = 0;
		}
		p = p->next;
	}
	
	if(flag == 1)printf("查无此人\n");	
} 
//===============================================
//显示功能 ======================================
void show(struct Record *head){
	if(empty(head))return ;
	struct Record *p = head;
	while(p){
		printf("【记录】：姓名：%s\t\t|分数：%d \t|时间：%s",p->name,p->score,ctime(&(p->time)));
		p =p->next; 
	}
} 
//=============================================================
				//数据利用
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
	while(p){
		fprintf(fp,"姓名：%s   | 分数：%d    |时间：%ld\n",p->name,p->score,(long)p->time);
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
	
	struct Record *head=NULL,*tail = NULL;
	while(fscanf(fp,"姓名：%s   | 分数：%d    |时间：%ld",name,&score,&t)!=EOF){
		
		struct Record *newNode = (struct Record*)malloc(sizeof(struct Record));
		
		strcpy(newNode->name,name);
		newNode->score = score;
		newNode->time = t;
		newNode->next = NULL;
		
		if(head==NULL){
			head = newNode;
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
//分析数据========================================
void swap_node_info(struct Record *p,struct Record *q){
	char temp_name[20];
	strcpy(temp_name,p->name);
	strcpy(p->name,q->name);
	strcpy(q->name,temp_name);
	
	int temp_score;
	temp_score = p->score;
	p->score = q->score;
	q->score = temp_score;
	
	long temp_time;
	temp_time = p->time;
	p->time = q->time;
	q->time = temp_time;
	
} 

void bubble_resort_score(struct Record *head){
	if(empty(head))return ;
	
	struct Record *p,*q;
	for(p=head;p;p=p->next){
		int swapped = 0;
		for(q=head;q->next;q=q->next){
			if(q->score < q->next->score ){
				swap_node_info(q,q->next);
				swapped = 1; 
			} 
		}
		if(swapped == 0)break;
	}
	
	printf("学员信息已按成绩（由高到低）排好序\n");
} 
void statistic_analysis(struct Record *head){
	//计算平均分，分数最高最低的人，不及格的人数 
	int sum = 0;
	double average = 0;
	int max,min;
	double cnt = 0;
	int number_of_failure = 0;

	
	struct Record *p = head;
	//min是后min加的忘记赋值了 
	max = min = p->score;
	for(;p;p=p->next){
		sum+=p->score;
		cnt++;
		
		if(p->score>max)
			max = p->score;
		if(p->score<min)
			min = p->score;
		if(p->score<90)
			number_of_failure++;
	} 
	
	average = sum/cnt;
	
	printf("统计并分析数据结果如下：\n");
	
	printf("平均分：%lf\n",average);
	
	printf("最高分为：%d  ",max);
	printf("最高分获得者如下：\n");
	for(p=head;p;p=p->next){
		if(p->score == max)printf("|%s\t",p->name);
	}
	printf("\n"); 
	
	printf("最低分为：%d  ",min);
	printf("最低分获得者如下：\n");
	for(p=head;p;p=p->next){
		if(p->score==min)printf("|%s\t",p->name);
	}
	printf("\n");
	
	printf("不及格的%d人有：\n",number_of_failure);
	for(p=head;p;p=p->next){
		if(p->score < 90)printf("|姓名：%s\t\t分数：%d\n",p->name,p->score);
	}
} 
//=============================================================
