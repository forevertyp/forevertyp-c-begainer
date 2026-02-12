#include "record.h"
//====================================================================================
//=====================用户交互功能函数======================== 

//=========================================================
//操作台首页
void show_choice(){
    printf("\n");
    printf("===================================\n");
    printf("========= 驾校学员管理系统 ========\n");
    printf("===================================\n");
    printf("  1. 添加学员记录\n");
    printf("  2. 删除学员记录\n");
    printf("  3. 保存记录到文件\n");
    printf("  4. 从文件读取记录\n");
    printf("  5. 手动修改学员科目状态\n");
    printf("  6. 自动修改学员科目状态\n");
    printf("  7. 查询学员记录\n");
    printf("  8. 显示所有记录\n");
    printf("  9. 科目成绩统计分析\n");
    printf(" 10. 按科目成绩排序\n");
    printf(" 11. 搜索科目成绩区间内的学员\n");
    printf("  0. 退出系统\n");
    printf("===================================\n");
    printf("请选择操作(0-11): ");
}
//=========================================================

//=========================================================
//操作台首页实现
Record* menu(Record* head){
	int flag = 1;
	while(flag){
		show_choice();
		int choice=0;
		safe_input_int(&choice,0,11);
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
			{
			Record *new_head = load_from_file();
				if(new_head != NULL){
					free_linkList(head);
					head = new_head;
					printf("数据加载成功\n"); 
					show_all_progress(head);
				}else{
					printf("数据加载失败\n");
				}	
			}
			break; 
			case 5:
				update_subject_score(head);
				break;
			case 6:
				process_subject_progress(head);
				break;
			case 7:
				inquire_by_uid(head);
				break;
			case 8:
				show_all_progress(head);
				break;
			case 9:
				statistic_analysis(head);
				break;
			case 10:
				bubble_sort_score(head);
				show_all_progress(head);
				break;
			case 11:
				inquire_range(head);
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
					flag = 0; 
				}
				break;
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

 
