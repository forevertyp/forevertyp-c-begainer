#include "library.h"
//图书借阅管理模块函数定义
//==============================================
//功能：实现借书操作 
//参数：bn表示图书的数量 ，m表示第m个学生进行借书 
//返回：无
//主要思路：先输入要借阅的图书书号，找到该书后进行借书操作，并保存借书操作完成后的图书信息和学生信息 
//============================================== 
void BorrowBook(int bn,int m){
	int i,j,k=-1;
	char c='y';
	char isbn[20];
	struct tm d;
	
	while(c=='y'||c=='Y'){
		for(j=0;j<5;j++){
			if(student[m].card[j].flag==0){
				printf("\n 请输入要借入图书的书号："); gets(isbn);
				for(i=0;i<bn;i++){
					if(strcmp(book[i].ISBN,isbn)==0){
						k=i;break;
					}
				
				if(k>=0){
					if(book[k].stock_num>0){
						book[k].stock_num--;
						student[m].card[j].flag=1;
						strcpy(student[m].card[j].ISBN,isbn);
						_getsystime(&d);
						if(d.tm_year/100>=1)
							student[m].card[j].bor_time.year=2000+d.tm_year%100;
						else{
							student[m].card[j].bor_time.year=1900+d.tm_year;
							}
							student[m].card[j].bor_time.month=d.tm_mon+1;  
							student[m].card[j].bor_time.day=d.tm_mday;  
							SaveOnebook(k);
							SaveOnestud(m);
							printf("\n 你已成功借阅该书籍 \n");
					}
					else{
						printf("\n 抱歉！该书的库存量为0，无法借阅 \n");
						break;    //终止for(j)循环 
					}
						
				}
				else{
					printf("输入的图书号有误，请重新输入！\n");
					j--;
					}
			}//end for(i) 
		}//end for(flag)
	 }//end for(j) 
	if(j==5){
			printf("\n 你已借5本书籍，无法多借");
			break; 
		}
		printf("\n 要继续借书吗？（y/n):");
		c=getch();
		getchar();	 
	}//end while
	printf("\n 按任意键继续！\n");
	getch();
} 

//================================================================
//功能：实现还书操作
//参数：bn表示图书数量，m表示第m个学生还书
//返回：无
//主要思路：先输入要归还的图书的书号，找到该书后进行还书操作，并保存还书操作完成后的图书和学生信息 
//================================================================
void ReturnBook(int bn,int m){
	int i,j,k,t;
	char isbn[20],c='y';
	printf("\n 你借阅的图书如下：\n");
	printf("        书号          借阅时间\n");
	for(j=0,t=0;j<5;j++){
		if(student[m].card[j].flag){
			t++;
			printf("  %-20s",student[m].card[j].ISBN);
			printf("%d.%d.%d\n",student[m].card[j].bor_time.year,student[m].card[j].bor_time.month,student[m].card[j].bor_time.day);
		}
	}
	if(t==0)printf("\n 暂无借阅图书,无需进行还书操作 \n");
	else{
		while(c=='y'||c=='Y'){
			printf("请输入要归还的图书的书号：");gets(isbn);
			for(j=0;j<5;j++){
				if(strcmp(student[m].card[j].ISBN,isbn)==0){
					student[m].card[j].flag=0;
					strcpy(student[m].card[j].ISBN,"");
					student[m].card[j].bor_time.year=0;
					student[m].card[j].bor_time.month=0;
					student[m].card[j].bor_time.day=0;
					t--;
					for(i=0;i<bn;i++){
						if(strcmp(book[i].ISBN,isbn)==0){
							k=i;break;
						}
					}
					book[k].stock_num++;
					SaveOnebook(k);
					SaveOnestud(m);
					printf("\n 你已成功归还该书\n");
					break;
				}//end if
			}            //end for(j=0)
			if(j==5) printf("\n 输入的书号有误，请重新输入！\n");
			if(t==0){
				printf("\n 你已经归还全部书籍 \n"); break; 
			}
			printf("\n 继续还书吗?(y/n):");
			c=getchar();
			getchar();
		}//end while(c==y)
	}//end else
	printf("请按任意键继续！\n");getch();
} 
