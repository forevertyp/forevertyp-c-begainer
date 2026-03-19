#include "library.h"
//以下为图书查询模块函数定义
//===============================================
//功能：显示图书查询菜单，实现功能选择
//参数：bn表示图书数量
//返回：无
//主要思路：采用switch结构实现图书查询功能
//===============================================
void SearchMenu(int bn){
	int select;
	while(1){
		printf("\n       欢迎使用图书查询服务 \n");
		printf("-------------------------------------------------------\n");
		printf("1.按书名查询            2.按作者查询\n");
		printf("3.按出版社查询          4.按出版时间查询\n");
		printf("5.按图书分类查询        0.退出查询服务\n");
		printf("-------------------------------------------------------\n");
		printf("\n 请选择查询方式（0-5）："); 
		scanf("%d",&select); getchar();
		switch(select){
			case 1:SearchBname(bn);break; 
			case 2:SearchAuthor(bn);break; 
			case 3:SearchPublisher(bn);break; 
			case 4:SearchPubtime(bn);break; 
			case 5:SearchBclass(bn);break; 
			case 0:return ;
			default:printf("\n 按键错误，请重新选择 \n");
		} 
	} 
} 

//==============================================
//功能：按书名进行图书查询
//参数：bn表示图书的数量
//返回：无
//主要思路：输入书名，先用strcmmp进行精确查询，若无查询结果，再用strstr函数进行模糊查询
//==============================================
void SearchBname(int bn){
	int i,j,k;
	char bname[40],c='y';
	while(c=='y'||c=='Y'){
		k=-1;
		printf("\n 请输入书名："); gets(bname);
		for(i=0,j=1;i<bn;i++){
			if(strcmp(book[i].bookname,bname)==0){
				k=i;
				printf("\n 图书%d的信息：\n",j++);
				OutputOnebook(k);
				printf("\n 请按任意键继续 \n");getch(); 
			}
		}
		if(k==-1){
			printf("\n 模糊查询结果如下：\n");
			for(i=0,j=1;i<bn;i++){
				if(strstr(book[i].bookname,bname)!=NULL){
					k=i;
					printf("\n 图书%d的信息：\n",j++);
					OutputOnebook(k);
					printf("\n 请按任意键继续 \n");
					getch();
				}
			}
			if(j==1)printf("\n 抱歉！没有相应的图书信息");
		}
		printf("\n 继续查询其他图书的信息吗 \n");
		c=getchar();getchar(); 
	}
	printf("\n 请按任意键继续 \n"); getch(); 
} 

//==============================================
//功能：按作者姓名进行图书查询
//参数：bn表示图书的数量
//返回：无
//主要思路：输入作者，先用strcmmp进行精确查询，若无查询结果，再用strstr函数进行模糊查询
//==============================================
void SearchAuthor(int bn){
	int i,j,k;
	char bauthor[20],c='y';
	while(c=='y'||c=='Y'){
		k=-1;
		printf("\n 请输入作者名称："); gets(bauthor);
		for(i=0,j=1;i<bn;i++){
			if(strcmp(book[i].author,bauthor)==0){
				k=i;
				printf("\n 图书%d的信息：\n",j++);
				OutputOnebook(k);
				printf("\n 请按任意键继续 \n");getch(); 
			}
		}
		if(k==-1){
			printf("\n 模糊查询结果如下：\n");
			for(i=0,j=1;i<bn;i++){
				if(strstr(book[i].author,bauthor)!=NULL){
					k=i;
					printf("\n 图书%d的信息：\n",j++);
					OutputOnebook(k);
					printf("\n 请按任意键继续 \n");
					getch();
				}
			}
			if(j==1)printf("\n 抱歉！没有相应的图书信息");
		}
		printf("\n 继续查询其他图书的信息吗 \n");
		c=getchar();getchar(); 
	}
	printf("\n 请按任意键继续 \n"); getch(); 
} 

//==============================================
//功能：按图书分类进行图书查询
//参数：bn表示图书的数量
//返回：无
//主要思路：输入图书分类，直接用strstr函数进行模糊查询 
//==============================================
void SearchBclass(int bn){
	int i,j,k;
	char bclass[20];
	char c='y';
	while(c=='y'||c=='Y'){
		k=-1;
		printf("\n请输入图书分类：");gets(bclass);
		for(i=0,j=1;i<bn;i++){
			if(strstr(book[i].bookclass,bclass)!=NULL){
				k=i;
				printf("\n 图书%d的信息 \n ",j++);
				OutputOnebook(i);
				printf("\n 请按任意键继续 \n"); getch();
			}
		}
		if(k==-1)printf("\n 抱歉！没有相应的图书的信息 \n");
		printf("\n 继续查询其他图书的信息吗 \n");
		c=getchar();getchar();
	}
	 printf("\n 请按任意键继续 \n"); getch();
} 

//==============================================
//功能：按出版社进行图书查询
//参数：bn表示图书的数量
//返回：无
//主要思路：输入出版社名称，直接用strstr函数进行模糊查询 
//==============================================
void SearchPublisher(int bn){
	int i,j,k;
	char publisher[30];
	char c='y';
	while(c=='y'||c=='Y'){
		k=-1;
		printf("\n请输入出版社名称：");gets(publisher);
		for(i=0,j=1;i<bn;i++){
			if(strstr(book[i].publisher,publisher)!=NULL){
				k=i;
				printf("\n 图书%d的信息 \n ",j++);
				OutputOnebook(i);
				printf("\n 请按任意键继续 \n"); getch();
			}
		}
		if(k==-1)printf("\n 抱歉！没有相应的图书的信息 \n");
		printf("\n 继续查询其他图书的信息吗 \n");
		c=getchar();getchar();
	}
	 printf("\n 请按任意键继续 \n"); getch();
} 

//==============================================
//功能：按出版社时间进行图书查询
//参数：bn表示图书的数量
//返回：无
//主要思路：用嵌套的if语句实现出版时间的查询 
//==============================================
void SearchPubtime(int bn){
	int i,j,k,year,month;
	char c='y';
	while(c=='y'||c=='Y'){
		k=-1;
		month=0;
		printf("\n 若只知道图书出版于2020年，则输入2020 \n");
		printf("请输入时间（年.月）：");
		scanf("%d.%d",&year,&month);getchar();
		for(i=0,j=1;i<bn;i++){
			if(book[i].publish_time.year==year){
				k=i;
				if(month!=0){
					if(book[i].publish_time.month!=month)
						continue;
				}
				printf("图书%d的信息：\n",j++);
				OutputOnebook(k);
				printf("\n 请按任意键继续!\n");
				getch();
			}
		}
		if(k==-1||j==1) printf("\n 抱歉！没有相应的图书信息！\n");
		printf("\n 继续查询其他图书信息吗？（y/n）:");
		c=getch();
		getchar(); 
	}
	printf("\n 请按任意键继续 \n"); 
} 

