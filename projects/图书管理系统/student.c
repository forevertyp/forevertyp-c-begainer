#include "library.h"
//以下为学生信息管理模块的函数定义
//==========================================
//功能：输入一个学生信息
//参数：i表示对对第i个学生进行输入操作
//返回：无
//主要思路：用gets函数输入学生的学号和姓名
//==========================================
void InputOnestud(int i){
	printf("\n");
	printf("学号：");	gets(student[i].num);
	printf("姓名：");   gets(student[i].name);
} 

//===========================================
//功能：从文件stud.dat中载入全部学生的信息
//参数：无
//返回：返回文件中的学生人数
//主要思路：用while循环从文件中读取学生信息到数组student,同时统计学生人数
//============================================
int LoadStuds(void){
	FILE *fb;
	int sn=0;
	if((fb=fopen("stud.dat","rb"))==NULL){
		printf("无法打开stud.dat文件\n");
		return sn;
	}
	while(!feof(fb)){
		if(fread(&student[sn],SSTUD_LEN,1,fb))	sn++;
	}
	fclose(fb);
	return sn;
} 

//============================================
//功能：保存一个学生信息
//参数：i表示将第i个学生的信息保存到文件中
//返回：无
//主要思路：先用fseek函数定位，再用fwrite函数写入第i个学生的信息
//=============================================
void SaveOnestud(int i){
	FILE *fb;
	if((fb=fopen("stud.dat","rb+"))==NULL){
		printf("can	t open file stud.dat\n");
		return ;
	}
	fseek(fb,SSTUD_LEN*i,0);
	fwrite(&student[i],SSTUD_LEN,1,fb);
	fclose(fb);
	return ;
} 

//===============================================
//功能：将全部信息保存到文件stud.dat文件中
//参数：sn表示学生人数
//返回：无
//主要思路：用fwrite函数将数组student中的数据一次性写入文件
//=============================================
void SaveAllstuds(int sn){
	FILE *fb;
	if((fb=fopen("stud.dat","wb"))==NULL){
		printf("Can	t open file stud.dat\n");
		return ;
	}
	fwrite(student,SSTUD_LEN,sn,fb);
	fclose(fb);
	return;
} 

//==================================================
//实现学生信息初始化
//参数：无
//返回：学生人数
//主要思路：用for循环多次调用InputOnestud函数实现输入多个学生信息，并写入文件
//==================================================
int OriginalStud(void){
	int n;
	char c='y';
	for(n=0;c=='y'||c=='Y';n++){
		printf("\n 输入学生%d的信息：\n",n+1);
		InputOnestud(n);
		printf("\n 继续输入请按'y',停止请按'n':");
		c=getchar();
		getchar();	
	}
	SaveAllstuds(n);
	return n;
} 
//====================================
//功能：修改学生信息 
//参数：sn表示学生人数
//返回：无
//主要思路：用switch实现修改学生的任意信息项，并将修改后的信息写入文件 
//====================================
void ModifyStud(int sn){
	int select,k=-1;
	char num[20],c1='y',c2;
	if(sn==0){
		printf("\n 暂无学生信息，无法进行操作\n");
		return ;
	}
	while(c1=='y'||c1=='Y'){
		c2 = 'y';
		printf("\n 请输入要修改的学生的学号：");gets(num);
		for(int i=0;i<sn;i++){
			if(strcmp(student[i].num,num)==0){
				k=i;
				break;
			}
		} 
		if(k<0)
			printf("请输入正确的学生学号\n");
		else{
			printf("\n 显示此学生的信息 \n");
				OutputOnestud(k);
				while(c2=='y'||c2=='Y'){
					printf("\n 学生信息包含以下数据项 \n");
					printf("-------------------------------\n");
					printf("\t 1.学号\n");
					printf("\t 2.姓名\n");
					printf("\t 3.借书卡\n");
					printf("-------------------------------");
					printf("\n 请选择要修改的数据项（1-3）：");
					scanf("%d",&select);getchar();
					switch(select){
						case 1:printf("学号：");gets(student[k].num); break;
						case 2:printf("姓名：");gets(student[k].name);break;
						case 3:
						printf("借记卡：");
						printf("请选择要修改的借记卡的内容：");
						printf("功能有待开发\n");
						break; 
						default:printf("\n 按键错误，请重新输入\n");break; 
					}
					printf("还有要修改此学生的其他信息吗？（y/n）:");
					c2=getchar();
					getchar();					
				} 
			}
			SaveOnestud(k); 
			printf("\n 还需要修改其他学生的信息吗？(y/n):");
			c1=getchar();
			getchar();
	}
} 

//=============================================================
//功能：添加学生信息
//参数：sn表示添加前的学生数量
//返回：添加后的学生数量
//主要思路：调用InputOnestud函数输入要添加的学生信息，再用fwrite将其写入文件
//=============================================================
int AddStud(int sn){
	char c='y';
	FILE *fb;
	if((fb=fopen("stud.dat","rb+"))==NULL){
		printf("can`t open file stud.dat\n");
		return sn; 
	}
	while(c=='y'||c=='Y'){
		printf("\n 请输入新增学生的信息：\n");
		InputOnestud(sn);
		fwrite(&student[sn],SSTUD_LEN,1,fb);
		sn++;
		printf("\n 继续输入其他新学生的信息吗？ \n");
		c=getchar();
		getchar(); 
	}
	printf("\n 按任意键继续！\n");
	getchar();
	fclose(fb);
	return sn;
} 

//==============================================================
//功能：删除学生信息
//参数：sn表示删除前的信息数量 
//返回：删除后的学生数量
//主要思路：先输入要删除的学号，找到该学生信息后进行删除操作，在调用SaveAllstuds() 
//			函数将删除后的学生信息写入文件中
//=============================================================
int DelStud(int sn){
	int i,k=-1;
	char num[20];
	char c1='y',c2;
	if(sn==0){
		printf("\n 学生信息为空，无法执行操作\n"); 
		return sn; 
	}
	while(c1=='y'||c1=='Y'){
		c2='n';
		printf("\n 请输入要删除的学生学号：");gets(num);
		for(i=0;i<sn;i++){
			if(strcmp(student[i].num,num)==0){
				k=i;
				break;
			}
		}
		if(k<0)printf("\n 请重新输入学号 \n");
		else{
			printf("\n 显示该学生信息 \n");
			OutputOnestud(k);
			printf("确定要删除该学生的信息吗？（y/n）:");
			c2=getchar();
			getch();
			if(c2=='y'){
				for(i=k;i<sn;i++){
					student[i]=student[i+1];
				}
				sn--;
				printf("\n删除成功\n");
			}
			else{
				printf("\n 取消删除成功 \n");
			} 
			printf("\n 继续删除其他学生信息吗？(y/n):");
			c1=getchar();
			getchar();
		}
	}
	SaveAllstuds(sn);
	printf("\n 按任意键继续 \n");
	getchar();
	return sn; 
} 

//=======================================================
//功能：输出一个学生信息
//参数：i表示输出第i个学生的信息
//返回：无
//主要思路：输出一个学生信息，并输出目前所解图书的书号和借阅时间
//=======================================================
void OutputOnestud(int i){
	int j,t;
	printf("\n");
	printf("学号："); puts(student[i].num);
	printf("姓名："); puts(student[i].name);
	for(j=0,t=0;j<5;j++){
		if(student[i].card[j].flag) t++;
	}
	if(t==0)printf("借书卡均为空！\n");
	else{
		printf("已借图书信息如下：\n");
		printf("       书号      借阅时间\n");
		for(j=0;j<5;j++){
			if(student[i].card[j].flag){
				printf("   %-20s",student[i].card[j].ISBN);
				printf("%d.%d.%d\n",student[i].card[j].bor_time.year,
				student[i].card[j].bor_time.month,
				student[i].card[j].bor_time.day);
			}
		}
	} 
	printf("\n 按任意键继续 \n"); getchar();
}

//=================================================================
//功能：输出全部学生信息
//参数：sn表示学生人数
//返回：无
//主要思路：用for循环输出全部学生的信息
//=================================================================
void OutputAllstuds(int sn){
	int i,j,t;
	printf("\n 全部学生信息：\n");
	printf("\n序号     学号        姓名      所借图书书号     借阅时间\n");
	for(i=0;i<sn;i++){
		printf("  %2d  %10s  %6s",i+1,student[i].num,student[i].name);
		for(j=0,t=0;j<5;j++){
			if(student[i].card[j].flag){
				if(t)printf("\n%26c",' ');
				printf("  %-20s",student[i].card[j].ISBN);
				printf("%d.%d.%d\n",student[i].card[j].bor_time.year,
				student[i].card[j].bor_time.month,
				student[i].card[j].bor_time.day);
				t=1;
			}
		}
		printf("\n\n");
	} 
	printf("\n 按任意键继续 \n"); getch(); 
} 
