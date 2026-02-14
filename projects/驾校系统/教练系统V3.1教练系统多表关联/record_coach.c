#include "record.h"

//=========coach_基本函数=================

//====================================
//初始化教练链表
Coach *create_coach_linkList(){
	Coach* coach_head = (Coach*)malloc(sizeof(Coach));
	if(coach_head==NULL){
		printf("教练链表未分配内存\n");
		return NULL;
	}
	coach_head->next=NULL;
	
	return coach_head;
} 
//====================================

//====================================
//free掉coach链表，避免内存泄漏
void free_coach_linkList(Coach *coach_head){
	
	while(coach_head){
		Coach *p = coach_head;
		coach_head = p->next;
		free(p);
		p=NULL;
	}
	
	return ;
}
//====================================

//====================================
//用于判断空的coach链表
int empty_coach(Coach *coach_head){
	int ret=1;
	if(coach_head==NULL){
		printf("教练链表不存在\n");
		ret = -1;
	}
	else if(coach_head->next==NULL){
		printf("教练链表为空\n");
	}
	else ret = 0;
	
	return ret;
} 
//==================================== 

//====================================
//获取coach链表的长度
int get_coach_linkList_len(Coach *coach_head){
	if(empty_coach(coach_head))return 0;

	Coach* p = coach_head->next;
	int cnt=0;
	while(p){
		cnt++;
		p=p->next;
	}
	
	return cnt;
} 
//==================================== 

//==================================== 
//为教练附上id
int get_cid(Coach* coach_head){
	//无coach链表 
	if(coach_head==NULL){
		printf("教练链表初始化失败\n");
		return -1;
	}
	//有表无人
	else if(coach_head->next==NULL) return CID_START;
	
	//有人
	else{
		int max_cid=coach_head->next->coach_id;
		Coach *p = coach_head->next;
		while(p){
			if(p->coach_id>max_cid)max_cid=p->coach_id;
			p=p->next;
		}
		return max_cid+1;
	}
	
} 
//=========================================

//===================================================


//=========coach_添加函数=================

//====================================
//尾插一个coach节点
Coach* coach_tail_add_node(Coach* coach_head){
	if(coach_head==NULL){
		printf("教练链表初始化失败\n");
		return NULL;
	}
	
	Coach* coach_new_node = (Coach*)malloc(sizeof(Coach));
	
	//赋值 
	coach_new_node->coach_id = get_cid(coach_head);
	
	printf("请输入教练的姓名：");
	while(scanf("%19s",coach_new_node->coach_name)!=1){
		printf("请输入正确的姓名！\n");
		while(getchar()!='\n');
	}
	coach_new_node->next = NULL;

	printf("正在录入中...");
	sleep(SLEEP_SEC);
		
	//挂载
	if(coach_head->next==NULL){
		coach_head->next=coach_new_node;
	}else{
		Coach *p= coach_head->next;
		while(p->next)p=p->next;
		p->next=coach_new_node;
	}
	return coach_head;
}
//===========================================

//==================================================


//=========coach_删除函数=================

//====================================
//根据CID删除节点
Coach* coach_cid_delete_node(Coach* coach_head){
	if(empty_coach(coach_head))return NULL;
	
	int cid=2000; 
	printf("请输入你要删除的教练的id:");
	safe_input_int(&cid,2001,get_cid(coach_head)-1);
	
	Coach* p = coach_head;
	int is_found = 0;
	while(p->next){
		if(p->next->coach_id==cid){
			is_found = 1;
			printf("找到CID:【%d】 姓名为%s 的驾校教练\n",cid,p->next->coach_name);
			printf("正在删除中...\n");
			sleep(SLEEP_SEC);
			Coach* q = p->next;
			p=q->next;
			free(q);
			q=NULL;
			break; 
			}
		}
		p=p->next; 
	
	if(is_found==0)printf("没有查到这个人\n");
	return coach_head;
}

//==========================================

//==================================================


//=========coach_查询函数=================

//====================================
//根据CID查询教练信息
void coach_inquire_by_cid(Coach* coach_head){
	if(empty_coach(coach_head))return NULL;
	
	int cid=2000; 
	printf("请输入你要查找的教练的id:");
	safe_input_int(&cid,2001,get_cid(coach_head)-1);
	
	Coach* p = coach_head;
	int is_found = 0;
	while(p->next){
		if(p->next->coach_id==cid){
			is_found = 1;
			printf("正在查询中...\n");
			sleep(SLEEP_SEC);
			printf("找到CID:【%d】 姓名为%s 的驾校教练\n",cid,p->next->coach_name);
			//有待添加学员信息 
		}
		p=p->next;
	} 
	
	if(is_found==0)printf("没有查到这个教练\n");
	return ; 
}
//====================================

//====================================
//查询所有教练信息 
void show_all_coach(Coach *coach_head){
	if(empty_coach(coach_head))return ;
	Coach* p = coach_head->next;
	printf("以下是所有教练的信息\n\n");
	while(p){
		printf("|CID:【%d】 姓名为%s 的驾校教练|\n",p->coach_id,p->coach_name);
		//学员信息待展示 
		p=p->next;
	}
	return ;
}

//=========================================

//====================================================


//=========coach_修改函数=================

//=======================================
//修改功能 
void coach_modify(Coach *coach_head){
	if(empty_coach(coach_head))return ;
	
	int cid=2000; 
	printf("请输入你要修改信息的教练的id:");
	safe_input_int(&cid,2001,get_cid(coach_head)-1);
	
	Coach *p = coach_head->next;
	
	int is_found = 0; 
	while(p){
		if(p->coach_id==cid){
			is_found = 1;
			printf("当前此教练的信息：\n");
			printf("|CID:【%d】 姓名为%s 的驾校教练|\n",p->coach_id,p->coach_name);
			printf("此功能还有待添加\n");
			//学员信息待展示 
			//还没有什么好更改的 
			break;
		}
	} 
	if(is_found==0)printf("查无此教练\n");
}
//======================================

//=============coach_file函数(二进制读取)===================

//=============================================
//二进制形式保存到文件 
void coach_save_to_file (Coach *coach_head){
	if(empty_coach(coach_head))return ;
	
	FILE *fp = fopen("coach.dat","wb");
	if(fp==NULL){
		printf("文件未打开，不能进行保存\n");
		return ;
	}
	
	int cnt_coach = get_coach_linkList_len(coach_head); 
	fwrite(&cnt_coach,sizeof(int),1,fp);
	fwrite(Coach,sizeof(Coach),1,fp);
	
	fclose(fp);
	printf("已将%d条教练信息保存至硬盘\n",cnt_coach);
	
	return;
}
//=============================================

//=============================================
//二进制形式读取文件
Coach* coach_load_from_file(){
	FILE *fp = fopen("coach.dat","rb");
	if(fp==NULL){
		printf("文件未打开，不能进行读取\n");
		return NULL;
	}
	
	int cnt_coach = 0;
	if(fread(&cnt_coach,sizeof(int),1,fp)!=1){
		printf("读取教练数量失败\n");
		fclose(fp);
		return NULL;
	}
	
	Coach *coach_head = create_coach_linkList();
	if(coach_head==NULL){
		printf("创建链表头节点失败\n");
		fclose(fp);
		return NULL;
	}
	//这样做不对，没有初始化个节点的next指针，导致其他功能都会坏掉 
//	Coach *coach_body = (Coach*)malloc(cnt_coach*sizeof(Coach));
//	if(coach_body==NULL){
//		printf("内存分配失败\n");
//		return NULL;
//	}
//	
//	fread(coach_body,sizeof(Coach),cnt_coach,fp);
//	
//	coach_head->next = coach_body;
//	
//	fclose(fp);
//	
//	printf("成功从文件中读取%d个教练的信息\n",cnt_coach);

	Coach *coach_tail =  coach_head;
	for(int i=0;i<cnt_coach;i++){
		Coach temp;
		if(fread(&temp,sizeof(Coach),1,fp)!=1){
			printf("读取第%d个教练数据失败\n",i+1);
			free_coach_linkList(coach_head);
			fclose(fp);
			return NULL;
		}
		
		Coach *new_node = (Coach*)malloc(sizeof(Coach));
		if(new_node==NULL){
			printf("内存分配失败\n");
			free_coach_linkList(coach_head);
			fclose(fp); 
			return NULL;
		}
		
		*new_node = temp;
		new_node->next = NULL;
		
		coach_tail->next = new_node;
		coach_tail = new_node;
	}
	fclose(fp);
	printf("成功从文件中读取%d个教练的信息\n",cnt_coach);
	return coach_head;
	
	return coach_head;
} 







