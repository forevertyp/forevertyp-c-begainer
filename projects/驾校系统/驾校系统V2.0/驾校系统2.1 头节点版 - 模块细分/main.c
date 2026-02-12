#include "record.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void show_choice();

int main(int argc, char *argv[]) {
    struct Record *head = create_linkList();
    
    if(head == NULL) {
        printf("初始化失败，程序退出！\n");
        return -1;
    }
    
    // 尝试从文件加载数据
    printf("正在从文件中加载数据...\n");
    sleep(SLEEP_SEC);
    
    struct Record *load_head = load_from_file();
    if(load_head != NULL) {
        // 释放初始创建的空链表
        free_linkList(head);
        head = load_head;
        printf("数据加载成功！\n");
        printf("当前学员记录如下：\n");
        show(head);
    } else {
        printf("未找到数据文件，创建新的记录。\n");
    }
    
    printf("\n===================================\n");
    printf("欢迎使用驾校学员管理系统\n");
    printf("===================================\n");
    
    // 进入主菜单
    head = menu(head);
    
    // 退出前保存数据
    printf("正在将当前数据保存至文件...\n");
    save_to_file(head);
    printf("数据保存完成！\n");
    
    // 释放内存
    free_linkList(head);
    
    printf("\n===================================\n");
    printf("感谢您的使用，再见！\n");
    printf("===================================\n");
    
    return 0;
}

// 可以添加一些分隔线，使输出更清晰
void show_choice(){
    printf("\n");
    printf("===================================\n");
    printf("========= 驾校学员管理系统 ========\n");
    printf("===================================\n");
    printf("  1. 添加学员记录\n");
    printf("  2. 删除学员记录\n");
    printf("  3. 保存记录到文件\n");
    printf("  4. 从文件读取记录\n");
    printf("  5. 修改学员记录\n");
    printf("  6. 查询学员记录\n");
    printf("  7. 显示所有记录\n");
    printf("  8. 统计分析\n");
    printf("  9. 按成绩排序\n");
    printf("  0. 退出系统\n");
    printf("===================================\n");
    printf("请选择操作(0-9): ");
}


//由于要保存文件内容，menu要返回正确的head 
struct Record* menu(struct Record* head){
	int flag = 1;
	while(flag){
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
				//head 被直接覆盖，会导致内存泄漏 
//			case 4:
//				head = load_from_file();
//				show(head);
//				break;
			case 4:
			{
			struct Record *new_head = load_from_file();
				if(new_head != NULL){
					free_linkList(head);
					head = new_head;
					printf("数据加载成功\n"); 
					show(head);
				}else{
					printf("数据加载失败\n");
				}	
			}
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
				bubble_sort_score(head);
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
					//也不能用exit(0),会直接退出程序，导致后面的free_linkList()函数失效导致内存泄露 
					//exit(0);
					flag = 0; 
				}
				//我这里漏了一个break;现在的是后面加的 
				break;
				//补上，以防万一 
			default:
				printf("无效的选择，请重新输入\n");
				break;
		}
		
		// 每次操作后暂停一下，让用户看清结果
        if(flag && choice != 0) {
            printf("\n按Enter键继续...");
            while(getchar() != '\n');  // 清空输入缓冲区
            getchar();  // 等待用户按Enter
        }
	}
	
	return head;
 }
