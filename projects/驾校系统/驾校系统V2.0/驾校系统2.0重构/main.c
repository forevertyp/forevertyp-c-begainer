#include "record.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	struct Record *head = create_linkList();
	menu(head);
	//想错了没想到用的是free(),我以为用的是free_linkList() 
	//free(head);
	free_linkList(head);
	return 0;
}

void show_choice(){
	printf("=========驾校系统=========\n");
	printf("\t1.添加记录\t\t\n");
	printf("\t2.删除记录\t\t\n");
	printf("\t3.保存记录\t\t\n");
	printf("\t4.读取记录\t\t\n");
	printf("\t5.修改记录\t\t\n");
	printf("\t6.查询记录\t\t\n");
	printf("\t7.展示记录\t\t\n");
	printf("\t8.统计分析\t\t\n");
	printf("\t9.记录排序\t\t\n");
	printf("\t0.退出系统\t\t\n"); 
	printf("===========================\n");
	printf("请输入以上选项(0-9):\n"); 
}

void menu(struct Record* head){
	while(1){
		show_choice();
		int choice=0;
		safe_input_int(&choice,0,9);
		switch(choice){
			case 1:
				head = batch_add_node(head);
				break;
			case 2:
				head = batch_delete_node(head);
				break;
			case 3:
				save_to_file(head);
				break;
			case 4:
				head = load_from_file();
				show(head);
				break;
			case 5:
				find_and_modify(head);
				break;
			case 6:
				inquire_info(head);
				break;
			case 7:
				show(head);
				break;
			case 8:
				statistic_analysis(head);
				break;
			case 9:
				bubble_resort_score(head);
				show(head);
				break;
			case 0:
				printf("你确定要退出系统吗\n");
				printf("如果是请输入'1',不是请输入'0'\n");
				int confirm = 0;
				safe_input_int(&confirm,0,1);
				if(confirm==0){
					printf("返回到系统中...\n");
					sleep(2);
					continue;
				}else if(confirm==1){
					printf("退出系统中...\n");
					sleep(2);
					//不能用break ，用来break只会跳出switch(与case 并用的) ，而应该用exit(0); 
					//break;
					exit(0);
					
				}
				//我这里漏了一个break;现在的是后面加的 
				break;
		}
	}

}
