#include "record.h"


/*
功能函数
一、创建功能
有头节点版 
要保证有一个哨兵 
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

	//检查链表是否为空//看哨兵节点是否指向空节点 
int empty(struct Record *head){
	int ret = 0; 
	if(head->next==NULL) //:1 ?0;//！！！！！忘记：？ 
	{
		ret = 1;
		printf("链表为空\n"); 
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

	//释放内存 //无需改动 
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
//创建 //其他值可以不赋值 
struct Record * create_linkList(){
	struct Record * head = (struct Record*)malloc(sizeof(struct Record));
	if(check_malloc(head)){
		printf("头节点创建失败\n"); 
		 return NULL;
	}
	head->next = NULL;
	return head;
}				
		//有头节点版本 
//=============================================================
				//功能函数（右头节点版本） 
//添加功能 =======================================
	
	//节点赋值函数//无需改动 
struct Record* node_assignment(struct Record *newNode){
	
	printf("请输入新添加学员的姓名：");
	while(scanf("%NAME_MAX_LENs",newNode->name)!=1){
		printf("请输人有效的姓名\n");
		while(getchar()!= '\n');
	}
	
	printf("请输入新添加学员的成绩：");
	safe_input_int(&newNode->score,SCORE_MIN_LEN,SCORE_MAX_LEN);
	
	newNode->time = time(NULL);
	printf("正在录入中....\n");
	sleep(SLEEP_SEC); 
	
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
	//无需判断空头 
	while(p->next!=NULL)p=p->next;
		p->next = newNode; 
	
	
	//需要在内部输出新节点的信息吗？//不需要还是保证函数的纯洁性好一点 
	return head;
}
		//头插 
struct Record *head_add_one_node(struct Record *head){
	struct Record *newNode = (struct Record*)malloc(sizeof(struct Record));
	if(check_malloc(newNode))return NULL;
	
	newNode = node_assignment(newNode);

	//head不能动 
	//把首元节点的地址给newNode的指针域 
	newNode->next = head->next;
	//再把头节点的指针域指向newNode,让newNode作为首元节点，二newNode指针域与指向前首元节点 
	head->next = newNode;
	
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
	safe_input_int(&add_times,SCORE_MIN_LEN,SCORE_MAX_LEN);
	int choice = add_choice();
	switch(choice){
		case 1:
			for(int i = 0;i<add_times;i++){
				head = head_add_one_node(head);//千万记得把返回值传给head,更新head 
				printf("【记录】：姓名：%s\t\t分数：%d\t时间：%s",head->next->name,head->next->score,ctime(&(head->next->time)));
			}
			break;
		case 2:
			for(int i = 0;i<add_times;i++){
				head = tail_add_one_node(head);
				//不能这样，打印出来的不是要打印的记录 
				//if(tail==NULL)tail = head->next;
				struct Record *tail = head;
				while(tail->next != NULL) tail = tail->next;
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
	
	p = head->next;
	head->next = p->next;
	
	free(p);
	p=NULL;
	return head;
}
		//尾删 
struct Record *tail_delete_one_node(struct Record *head){
	if(empty(head))return NULL; 	
	struct Record *p=head;
	while(p->next->next!=NULL) p = p->next;
	struct Record *q;
	q = p->next;
	p->next = q->next;
	
	free(q);
	q=NULL;
	
	return head;
}

		//按名字删
struct Record* delete_one_node_by_name(struct Record *head){
	if(empty(head))return NULL; 
	char target_name[20];
	printf("请输入要删除学员的姓名：");
	scanf("%NAME_MAX_LENs",target_name);
	
	struct Record *p = head;
	
	int is_found = 0;
	while(p->next){
		if(strcmp(p->next->name,target_name)==0){
			struct Record *q = p->next;
			p->next = q->next;
			printf("找到姓名：[%s]   分数：%d\n",target_name,p->next->score);
			printf("删除中...\n");
			sleep(SLEEP_SEC);
			free(q);
			q=NULL;//free(p->next) p->next = NULL 
			is_found = 1;
			break;
		}
		p=p->next;
	}
	if(is_found==0) printf("查无此人\n");
	
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
	while(p->next){
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
	scanf("%NAME_MAX_LENs",target_name);
	
	struct Record *p = head; 
	int flag = 1;
	//p->next;
	while(p->next){
		if(strcmp(target_name,p->next->name)==0){
			printf("找到[%s] 当前分数为 %d \n",target_name,p->next->score);
			
			printf("请输入新的分数：");
			safe_input_int(&p->next->score,SCORE_MIN_LEN,SCORE_MAX_LEN);
			
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
	scanf("%NAME_MAX_LENs",target_name);
	
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
//显示功能 ======================================
void show(struct Record *head){
	if(empty(head))return ;
	struct Record *p = head;
	//bug3:不能是while(p)当走到最后p->next = NULL;与无头结点的不同 
	while(p->next){
		printf("【记录】：姓名：%s\t\t|分数：%d \t|时间：%s",p->next->name,p->next->score,ctime(&(p->next->time)));
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
	//老问题：我还是用了while(p) 到最后 p->next = NULL, 程序会对NULL 解引用，直接崩溃
	//为什么我会觉得while(p)可以呢，因为我觉得p可遍历地更多，而我程序内用的又是p->next,我以为是没错的 
	while(p->next!= NULL){
		fprintf(fp,"姓名：%s   | 分数：%d    |时间：%ld\n",p->next->name,p->next->score,(long)p->next->time);
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
	
	//建议改成现有的函数 head = create_linkList() 
	struct Record *head = (struct Record *)malloc(sizeof(struct Record));
	//bug1:没有给head->next赋值，出现野指针bug 
	head->next = NULL;
	
	if(check_malloc(head))return NULL;
	
	struct Record *tail = NULL;
	//fscanf()的内容要与fprintf()的一致 
	while(fscanf(fp,"姓名：%s   | 分数：%d    |时间：%ld\n",name,&score,&t)!=EOF){
		
		struct Record *newNode = (struct Record*)malloc(sizeof(struct Record));
		//bug2这里没有检查malloc分配
		if(check_malloc(newNode))return NULL; 
		
		strcpy(newNode->name,name);
		newNode->score = score;
		newNode->time = t;
		newNode->next = NULL;
		
		if(head->next==NULL){
			head->next = newNode;
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
	for(p=head;p->next;p=p->next){
		int swapped = 0;
		for(q=head;q->next->next;q=q->next){
			if(q->next->score < q->next->next->score ){
				swap_node_info(q->next,q->next->next);
				swapped = 1; 
			} 
		}
		if(swapped == 0)break;
	}
	
	printf("学员信息已按成绩（由高到低）排好序\n");
} 
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
//=============================================================
