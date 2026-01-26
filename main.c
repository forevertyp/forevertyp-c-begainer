#include "record.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	struct Record *head = NULL;
	menu(head);  //操作界面 
	return 0;
}

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
		printf("\t6.查看学员信息\t\n");
		printf("\t7.删除学员信息\t\n");
		printf("\t8.学员信息排序\t\n");
		printf("\t9.不合格学员\t\n");
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
				show(head); 
				break;
			case 5:
				find_and_modify(head);
				break;
			case 6:
				show(head);
				break;
			case 7:
				head = delete_info(head);
				break;
			case 8:
				bubbleSort_records(head);
				show(head);
				break;
			case 9:
				find_fail_student(head);
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
				break;
			default:
				printf("请输入正确的选项（0-7）：\n");
				break;
		 }
	}	
}
