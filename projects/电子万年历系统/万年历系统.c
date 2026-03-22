#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int g_MonthDays [13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

int LeapYear(int n);
int CountYearDays(int year);
int CountMonthDays(int month);
void Menu(void);
void ListMonth(int days,int t);
void Search1(void);
void Search2(void);
void Search3(void);

int main(){
	int select;
	while(1){
		Menu();
		scanf("%d",&select);
		switch(select){
			case 1:Search1();break;
			case 2:Search2();break;
			case 3:Search3();break;
			case 0:printf("\n\t谢谢使用!再见\n");exit(0);
			default:printf("\n\t按键错误，请重新选择！\n");
		}//switch 结束 
	}//while结束 
}

//===============================================================
//功能：判断是否是闰年
//参数：n为需要判断的年份
//返回：是闰年返回1，不是则0
//主要思路：用if语句判断某一年是否为闰年
//===============================================================
int LeapYear(int n){
	if(n%4==0&&n%100!=0||n%400==0)return 1;
	else return 0;
} 

//===============================================================
//功能：计算从公元元年到公元（year-1)年的总天数 
//参数：year为年份 
//返回：返回总天数 
//主要思路：用for循环计算天数 
//===============================================================
int CountYearDays(int year){
	int i,flag,days=0;
	for(i=1;i<year;i++){
		flag=LeapYear(i);
		if(flag) days=days+366;
		else days+=365;
	}
	return days;
}

//===============================================================
//功能：计算当年前（month-1)个月的天数 
//参数：month为月份 
//返回：返回前（month-1)个月的总天数 
//主要思路：用for循环计算天数 
//=============================================================== 
int CountMonthDays(int month){
	int i,days=0;
	for(i=1;i<month;i++)
		days+=g_MonthDays[i];
		
	return days;
} 


//===============================================================
//功能：显示系统菜单 
//参数：无 
//返回：无 
//主要思路：用printf输出菜单 
//===============================================================
void Menu(void){
	printf("\n");
	printf("\t--------------------------------\n");
	printf("\t*                              *\n");
	printf("\t*      欢迎使用万年历系统      *\n");
	printf("\t*                              *\n");
	printf("\t--------------------------------\n");
	printf("\n");
	printf("\t请选择你要查询的内容：\n\n");
	printf("\t 1. 显示某年的日历\n");
	printf("\t 2. 显示某年某月的日历\n");
	printf("\t 3. 显示某天是星期几\n");
	printf("\t 0. 退出系统\n\n");
	printf("\t 请选择按键（0-3）："); 
	
}

//===============================================================
//功能：按规定格式输出一个月的日历 
//参数：days表示要输出月份的天数，t表示要输出月份的1日是星期几 
//返回：无 
//主要思路：用for循环输出日历                                   
//===============================================================
void ListMonth(int day,int t){
	int i,j;         
	printf("星期日  星期一  星期二  星期三  星期四  星期五  星期六\n");
	for(i=1;i<=day;i++){
		if(i==1)
			for(j=0;j<t;j++)
				printf("         ");
		printf("  %-7d",i);
		if((i+t)%7==0)printf("\n");
	}
} 

//===============================================================
//功能：输出指定年份全年12月的日历 
//参数：无 
//返回：无 
//主要思路：用for循环输出每个月的日历 
//===============================================================
void Search1(void){
	int year,t,k,flag,days;
	printf("请输入年份：");
	scanf("%d",&year);
	flag=LeapYear(year);
	t=(CountYearDays(year)+1)%7;  //这年的第一天是星期几
	for(k=1;k<=12;k++){
		days=g_MonthDays[k];
		if(flag&&k==2)days=29;
		printf("\n %d月：\n",k);
		ListMonth(days,t);
		t=(t+days%7)%7;  //其实这才是我不会的部分 
		printf("\n");
		if(k%3==0){
			printf("\n 按任意键继续！\n");
			getch();
		} 
	}    //end for
} 

//===============================================================
//功能：输出某年某月的日历 
//参数：无 
//返回：无 
//主要思路：通过调用函数计算天数，再输出日历 
//===============================================================
void Search2(void){
	int t,year,month,flag,days,ydays,mdays,alldays;
	printf("\n 请输入年.月（如2008.9）：");
	scanf("%d.%d",&year,&month);
	ydays=CountYearDays(year);
	mdays=CountMonthDays(month);
	days=g_MonthDays[month];
	flag=LeapYear(year);
	if(flag){
		if(month>2) mdays++;
		else if(month==2) days=29;
	} 
	alldays=ydays+mdays+1;
	t=alldays%7;
	printf("\n%d年%d月：\n\n",year,month);
	ListMonth(days,t);
	printf("\n");
}

//===============================================================
//功能：输出某一天是星期几 
//参数：无 
//返回：无 
//主要思路：通过调用函数计算天数，再计算并输出这一天是星期几 
//===============================================================
void Search3(void){
	int t,year,month,day,flag,ydays,mdays,alldays;
	printf("\n 请输入年.月.日(如2009.3.25)：");
	scanf("%d.%d.%d",&year,&month,&day);
	ydays=CountYearDays(year);
	mdays=CountMonthDays(month);
	flag=LeapYear(year);
	if(flag&&month>2) mdays++;
	alldays=ydays+mdays+day;
	t=alldays%7;
	printf("%d年%d月%d日是",year,month,day);
	switch(t){
		case 0:printf("星期日\n");break;
		case 1:printf("星期一\n");break;
		case 2:printf("星期二\n");break;
		case 3:printf("星期三\n");break;
		case 4:printf("星期四\n");break;
		case 5:printf("星期五\n");break;
		case 6:printf("星期六\n");break;
	}
	printf("\n请按任意键结束\n");
	getch();
	
} 
