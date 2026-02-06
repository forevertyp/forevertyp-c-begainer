#include "record.h" 

Record * create_linkList();
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char *argv[]) {
	Record *head = create_linkList();
    
    if(head == NULL) {
        printf("初始化失败，程序退出！\n");
        return -1;
    }
    
    // 尝试从文件加载数据
    printf("正在从文件中加载数据...\n");
    sleep(SLEEP_SEC);
    
    Record *load_head = load_from_file();
    if(load_head != NULL) {
        // 释放初始创建的空链表
        free_linkList(head);
        head = load_head;
        printf("数据加载成功！\n");
        printf("当前学员记录如下：\n");
       show_all_progress(head);
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


Record * create_linkList(){
	struct Record * head = (struct Record*)malloc(sizeof(struct Record));
	if(head==NULL){
		printf("头节点创建失败\n"); 
		 return NULL;
	}
	head->next = NULL;
	return head;
}	


