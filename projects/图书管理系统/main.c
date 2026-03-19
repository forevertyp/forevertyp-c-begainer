#include "library.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
SSTUD student[STUDNUM] = {0};
SBOOK book[BOOKNUM] = {0};

int main(int argc, char *argv[]) {
	int select,bn,sn;
	bn=LoadBooks();
	if(bn==0) printf("图书信息为空！\n\n");
	sn=LoadStuds(); 
	if(sn==0) printf("学生信息为空！\n\n");
	while(1){
		printf("\n\t----------------------------------\n");
		printf("\t*                                  *\n");
		printf("\t*          图书管理系统            *\n");
		printf("\t*                                  *\n");
		printf("\t*                                  *\n");
		printf("\t------------------------------------\n\n");
		printf("\t    1.管理员\n");
		printf("\t    2.学生\n");
		printf("\t    0.退出系统\n\n");
		printf("\t    请选择用户：");
		scanf("%d",&select);
		getchar();
		switch(select){
			case 1:ManagerLogin(&bn,&sn);break;
			case 2:StudentLogin(bn,sn);break;
			case 0:printf("\n 谢谢使用,再见 \n"); exit(1);
			default:printf("\n 按键错误，请重新选择!\n");
		}
	}
	return 0;
}
