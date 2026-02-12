#include "record.h"
		//有头节点版本 
//=============================================================
				//功能函数（右头节点版本） 
//添加功能 =======================================
	
	//节点赋值函数//无需改动 
//这里无需返回值了，传入指针 
void node_assignment(struct Record *newNode){
	
	printf("请输入新添加学员的姓名：");
	//不能用NAME_MAX_LEN 
	while(scanf("%19s",newNode->name)!=1){
		printf("请输人有效的姓名\n");
		while(getchar()!= '\n');
	}
	
	printf("请输入新添加学员的成绩：");
    safe_input_int(&newNode->score,SCORE_MIN,SCORE_MAX);
	
	newNode->time = time(NULL);
	printf("%s",ctime(&newNode->time));
	
	newNode->curr_subject=SUBJECT_1;
	newNode->curr_status=STATUS_UNREGISTERED; 

	
	printf("正在录入中....\n");
	sleep(SLEEP_SEC); 
	

	
	//忘记给指针域赋值了导致一直报错 !!这是其他函数能实现的基础 
	newNode->next = NULL; 
	
	
} 
	//加一个节点(尾插)
struct Record * tail_add_one_node(struct Record *head){
	
	//申请新的节点
	struct Record *newNode = (struct Record*)malloc(sizeof(struct Record));
	
	//！！！！！忘记对malloc做空处理 !!!!!!!!封装的时候，忘记加回来了
	 if(check_malloc(newNode))return NULL;
		//为新的节点赋值
	node_assignment(newNode);
	newNode->user_id=assignment_user_id(head);
	
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
	
	node_assignment(head);
	newNode->user_id=assignment_user_id(head);

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
	safe_input_int(&add_times,SCORE_MIN,SCORE_MAX);
	int choice = add_choice();
	switch(choice){
		case 1:
			for(int i = 0;i<add_times;i++){
				head = head_add_one_node(head);//千万记得把返回值传给head,更新head 
				printf("【UID:%d】：姓名：%s\t\t分数：%d\t时间：%s",head->next->user_id,head->next->name,head->next->score,ctime(&(head->next->time)));
				printf("--当前科目：%s\t科目状态：%s--\n",SubjectNames[head->next->curr_subject],StatusNames[head->next->curr_status]);
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
				printf("【UID:%d】：姓名：%s\t\t分数：%d\t时间：%s",tail->user_id,tail->name,tail->score,ctime(&(tail->time)));	
				printf("--当前科目：%s/t科目状态：%s--\n",SubjectNames[tail->curr_subject],StatusNames[tail->curr_status]);							
			}
			break;
	}
	
	return head;
}
//===============================================
