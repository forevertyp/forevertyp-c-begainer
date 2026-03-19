#include "library.h"

//以下为用户登录模块函数的定义
//============================================
//功能：实现管理员登录，显示管理员用户的菜单，进行功能选择
//参数：pbn、pbs分别为main 函数中变量bn,sn的地址
//返回：无
//思路：用strcmp函数实现密码验证，用switch结构实现菜单功能
//===============================================

void ManagerLogin(int *pbn,int *psn){
	int select,flag=0;
	char password[11];
	printf("请输入密码：");
	fgets(password,11,stdin);
	password[strcspn(password,"\n")]=0; 
	if(strcmp(password,"123456")!=0){
		printf("\n密码错误\n");
		return;
	} 
	while(1){
		printf("\n        管理员你好             \n");
		printf("------------------------------------------------------------------------\n");
		printf("1.图书信息初始化\t\t7.学生信息初始化\n");
		printf("2.修改图书信息  \t\t8.修改学生信息\n");
		printf("3.增加学生信息  \t\t9.增加学生信息\n");
		printf("4.删除学生信息  \t\t10.删除学生信息\n");
		printf("5.输出图书信息  \t\t11.输出学生信息\n");
		printf("6.查询图书信息  \t\t0.返回主菜单\n");
		printf("------------------------------------------------------------------------\n");
		printf("请选择您需要的服务(0-11)");
		scanf("%d",&select);getchar();
		switch(select){
			case 1: *pbn = OriginalBook(); break;
			case 2:  ModifyBook(*pbn); break;
			case 3: *pbn=AddBook(*pbn) ; break;
			case 4: *pbn = DelBook(*pbn); break;
			case 5: printf("输出详细信息请按'1',输入简要信息请按'2':");
					scanf("%d",&flag);
					getchar();
					if(flag==1) OutputAllbooks(*pbn);
					else if(flag==2)OutputBrief(*pbn);
					else printf("输入错误，返回菜单\n");
					break;
			case 6: SearchMenu(*pbn); break;
			case 7: *psn=OriginalStud(); break;
			case 8: ModifyStud(*psn); break;
			case 9:*psn = AddStud(*psn);break;
			case 10:*psn = DelStud(*psn);break;
			case 11:OutputAllstuds(*psn);break;
			case 0:return;
			default:printf("\n 输入错误，请重新选择！\n"); 
			 
		}	
	}
}

//=================================================================
//功能：实现学生登录，显示学生用户菜单，进行功能选择
//参数：bn 表示图书数量，sn表示学生人数
//返回：无
//主要思路：用strcmp函数实现学号验证，用switch结构实现菜单功能选择
//=================================================================
void StudentLogin(int bn ,int sn){
	int select,j,m=-1;
	char snum[15];
	if(sn==0){
		printf("\n学生信息为空，无法执行操作\n");return;
	}
	while(1){
		printf("\n请输入你的学号：");
		gets(snum);
		for(j=0;j<sn;j++){
			if(strcmp(student[j].num,snum)==0){
				m = j;
				break;
			}
		} 
		if(m<0)printf("\n输入学号错误，请重新输入\n");
		else{
			while(1){
				printf("\n     同学，你好     ！\n");
				printf("----------------------------------------------\n");
				printf("\t1.输出个人借书信息\n");
				printf("\t2.图书信息查询\n");
				printf("\t3.借书\n");
				printf("\t4.还书\n");
				printf("\t0.返回主菜单\n");
				printf("----------------------------------------------\n");
				printf("请输入你的选择（0-4）:");
				scanf("%d",&select);getchar();
				switch(select){
					case 1:OutputOnestud(m);break;
					case 2:SearchMenu(bn);break;
					case 3:BorrowBook(bn,m);break;
					case 4:ReturnBook(bn,m);break; 
					case 0:return;
					default:printf("\n输入错误请重试\n");
				}
			}
		}
	}
} 
