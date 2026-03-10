# include "library"
//以下为图书管理模块的函数定义
//===============================================
//功能：从键盘输入一本图书的全部信息
//参数：i表示对第i本图书进行输入操作
//返回：无
//主要思路：按提示信息用scanf输入图书的各项信息，存放到数组book中
//===============================================
void InputOnebook(int i){
	printf("书号：");gets(book[i].ISBN,);
	printf("书名：");gets(book[i].bookname);
	printf("作者：");gets(book[i].author);
	printf("图书分类：")gets(book[i].bookclass);
	printf("总量：");scanf("%d",&book[i].total_num);getchar();
	book[i].stock_num = book[i].total_num;
	printf("单价：");
	scanf("%f",&book[i].price);
	getchar();
	printf("出版社：");gets(book[i].publisher);
	strcat(book[i].publisher,"出版社");
	printf("出版时间(年.月)："); 
	scanf("%d.%d",&book[i].publish_time.year,&book[i].publish_time.month);
	book[i].publish_time.day = 0;getchar(); 
} 


//====================================================
//功能：从文件book.dat中载入全部图书的信息
//参数：无
//返回：返回文件中图书的数量
//主要思路：用while循环从文件中读取图书信息到数字book,同时统计书籍数量
//====================================================

int LoadBooks(void){
	FILE *fb; int bn = 0;
	if(fb=fopen("book.dat","rb+")==NULL){
		printf("Can`t open file book.dat\n")return bn; 
	}
	while(!feof(fb))
		if(fread(&book[bn],SBOOK_LEN,1,fb)) bn++;
	fclose(fb);
	return bn; 
} 

//=======================================================
//功能：从文件book.dat中载入全部图书信息
//参数：无
//返回：返回文件中图书的数量
//主要思路：用while循环从文件中读取图书信息到数字book中，同时统计图书数量
//=======================================================
int LoadBooks(void){
	FILE *fb;
	int bn = 0;
	if((fb=fopen("book.dat","rb+"))==NULL){
		printf("Can`t open file book.dat\n");
		return bn;
	}
	while(!feof(fb)){
		if(fread(&book[bn],SBOOK_LEN,1,fb)) bn++;
	}
	fclose(fb);
	return bn;
} 

//=======================================================
//功能：将一本图书的信息保存到文件book.dat中
//参数：i表示将第i本图书的信息保存到文件中
//返回：无
//主要思路：先用fseek函数定位，在用fwrite函数写入第i本图书的信息
//=======================================================
void SaveOnebook(int i){
	FILE *fb;
	if((fb=fopen("book.dat","rb+"))==NULL){
		printf("Can`t open file book.dat\n");
		return ;
	} 
	fseek(fb,SBOOK_LENI*i,0);
	fwrite(&book[i],SBOOK_LEN,1,fb);
	fclose(fb);
	return ;
} 
 
 
//=======================================================
//功能：将全部图书信息保存到文件“book.dat”中
//参数：bn表示全部的图书的数量
//返回：无
//主要思路：用fwrite函数将数组book中的数据一次性写入文件
//=======================================================
void SaveAllbooks(int bn){
	FILE *fb;
	if((fb=open("book.dat","wb"))==NULL){
		printf("Can`t open file book.dat\n");
		return ; 
	}
	fwrite(book,SBOOK_LEN,bn,fb);
	fclose(fb);
	return ; 
} 

//=======================================================
//功能：实现图书信息的初始化
//参数：无
//返回：输入图书的数量
//主要思路：用for循环实现输入多本图书信息，并写入文件
//=======================================================
int OriginalBook(void){
	int n;
	char c='y';
	for(n=0;c=='y'||c=='Y';n++){
		printf("\n 输入图书%d的信息：\n",n+1);
		InputOnebook(n);
		printf("\n 继续输入请按'y',停止请按'n':");
		c=getchar();
		getchar();
	}
	Saveallbooks(n);
	return n; 
} 

//=======================================================
//功能：修改图书信息
//参数：bn表示图书的数量
//返回：无
//主要思路：通过switch实现图书的任意信息项，并将修改后的信息写入文件
//=======================================================
void ModifyBook(int bn){
	int select,k=-1;
	char isbn[20],c1='y',c2;
	if(bn==0){
		printf("\n图书信息为空，无法执行操作\n");
		return bn;
	}
	while(c1=='y'||c1=='Y'){
		c2='y';
		printf("\n 请输入要修改的图书的书号：");gets(isbn);
		for(int i=0;i<bn;i++){
			if(strcmp(book[i].ISBN,isbn)==0){
				k=i;
				break;
			}
		}
		if(k<0)
			printf("书号错误，请重新输入书号");
		else{
			printf("\n 显示此图书信息：\n");
			OutputOnebook(k);
			while(c2=='y'||c2=='Y'){
				printf("\n 图书信息包含以下数据项 \n");
				printf("---------------------------------------");
				printf("\t 1.书号 \t6.总量\n");
				printf("\t 2.书名 \t7.库存量\n");
				printf("\t 3.作者 \t8.单价\n");
				printf("\t 4.出版社\t9.出版时间\n");
				printf("\t 5.图书分类\n"); 
				printf("---------------------------------------");
				printf("\n 请选择要修改的数据项（1-9）：")；
				scanf("%d",&select);getchar();
				switch(select){
					case 1:printf("书号：")gets(book[k].ISBN);break;
					case 2:printf("书名：")gets(book[k].bookname);break;
					case 3:printf("作者：")gets(book[k].author);break;
					case 4:printf("出版社：")gets(book[k].publisher);break;
					case 5:printf("图书分类：")gets(book[k].bookclass);break;
					case 6:printf("总量：")scanf("%d",&book[k].total_num);getchar();
					book[k].stock_num = book[k].total_num;
					break;
					case 7:printf("库存量：");
					scanf("%d",&book[k].stock_num);
					getchar();
					if(book[k].stock_num>book[k].total_num)
					book[k].stock_num = book[k].total_num;
					break;
					case 8:printf("单价：");
					scanf("%f",&book[k].price);getchar();
					break;
					case 9:printf("出版时间（年.月）：");
					scanf("%d.%d",&book[k].publish_time.year,&book[k].publish_time.month);
					getchar();break;
					default:printf("\n 按键错误，请重新输入！\n");break; 
				}  //end switch
				printf("还要修改此图书的其他信息吗？（y/n):");
				c2=getchar();
				getchar(); 
			}		//end while(c2)									
		}
		 SaveOnebook(k);
		 printf("\n 还需要修改其他图书信息吗?(y/n):");
		 c1=getchar();
		 getchar(); 
	}         //end while(c1)
} 
//=============================================================
//功能：添加图书信息
//参数：bn表示添加前的图书数量
//返回：添加后的图书数量
//主要思路：调用InputOnebook函数输入要添加的图书信息，再用fwrite将其写入文件
//=============================================================
int AddBook(int bn){
	char c='y';
	FILE *fb;
	if((fb=fopen("book.dat","wb"))==NULL){
		printf("can`t open file book.dat\n");
	}
	while(c=='y'||c=='Y'){
		printf("\n 请输入新增图书的信息：\n");
		InputOnebook(bn);
		fwrite(&book[bn],SBOOK_LEN,1,fb);
		bn++;
		printf("\n 继续输入其他新图书的信息吗？\n");
		c=getchar();
		getchar();
	}
	printf("\n 按任意键继续！\n");
	getchar();
	fclsoe(fb);
	return bn;
} 

//==============================================================
//功能：删除图书信息
//参数：bn表示删除前的信息
//返回：删除后的图书数量
//主要思路：先输入要删除的图书好，找到该书后进行删除操作，在调用SaveAllbooks
//			函数将删除后的图书写入文件中
//=============================================================
int DelBook(int bn){
	int i,k=-1;
	char isbn[20];
	char c1='y',c2;
	if(bn==0){
		printf("\n 图书信息为空，无法执行操作\n");
		return bn;
	}
	while(c1=='y'||c1=='Y'){
		c2='n';
		printf("\n 请输入要删除的图书书号：");gets(isbn);
		for(i=0;i<bn;i++)
			if(strcmp(book[i].ISBN,isbn)==0){
				k = i;
				break;
			}
			if(k<0)printf("\n 请重新输入书号 \n");
			else{
				printf("\n 显示该图书的信息：\n");
				OutputOnebook(k);
				printf("确定要删除改天图书的全部信息吗？（y/n):");
				c2=getchar();
				getchar();
				if(c2=='y'){
					for(i=k;i<bn;i++){
						book[i]=book[i+1];
					}
					bn--;
					printf("\n成功删除\n");
				}
				else printf("\n 取消删除成功\n");
				printf("\n 继续删除其他图书信息吗？（y/n):");
				c1=getchar();
				getchar();
			}
	}
	SaveAllbooks(bn);
	printf("\n 按任意键继续 \n");
	getchar();
	return bn; 
} 

//=============================================================
//功能：输出一本图书的全部信息
//参数：i表示对第i本书进行输出操作
//返回：无
//主要思路：用printf函数输出一本图书的全部信息
//=============================================================
void OutputOnebook(int i){
	printf("\n");
	printf("书号：");puts(book[i].ISBN);
	printf("书名：");puts(book[i].bookname);
	printf("作者：");puts(book[i].author);
	printf("图书分类：");puts(book[i].bookclass);
	printf("总量：");printf("%d\n",book[i].total_num);
	printf("库存量：");printf("%d\n",book[i].stock_num);
	printf("单价："); printf("%.2f\n",book[i].price);
	printf("出版社：");puts(book[i].publisher);
	printf("出版时间：");
	printf("%d.%d\n",book[i].publish_time.year,book[i].publish_time.month);  
}

//============================================================
//功能：输出全部图书的信息
//参数：bn表示图书的数量
//返回：无
//主要思路：通过for循环多次调用OutputOnebook函数输出全部图书的信息
//============================================================
void OutputAllbooks(int bn){
	int i;
	printf("\n 全部图书的详细信息 \n");
	for(i=0;i<bn;i++){
		OutputOnebook(i);
		printf("\n 按任意键继续!\n");getchar();
	}
	printf("\n 全部图书信息输出完毕。\n");
	printf("\n 按任意键返回\n");getchar();
} 

//============================================================
//功能：以列表方式输出全部图书的简要信息
//参数：bn表示图书的数量
//返回：无
//主要思路：用for循环输出全部的简要信息（书号、书名、作者、库存量）
//============================================================
void OutputBrief(int bn){
	int i;
	printf("\n 全部图书的简要信息：\n");
	printf("\n 序号				书号				书名			作者	库存量\n");
	for(i=0;i<bn;i++){
		  printf("%2d %-18s %-20",i+1,book[i].ISBN，book[i].bookname);
		  printf("  %-8s  %2d\n",book[i].author,book[i].stock_num);
	}
	printf("\n 按任意键继续！\n");getch();
} 

