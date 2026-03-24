//这个函数是个最简单的顺序表，用以练习一下我的数据结构,做个购买清单 
#include<stdio.h>
#include<string.h>
#include<stdlib.h> 

#define MAXSIZE 20
typedef int Status;
typedef int bool;

typedef struct{
	char name[40];//商品名称
	float price;//商品价格
	bool flag;	//是否购买 
}Item; 

//顺序表清单 
typedef struct{
	Item item[MAXSIZE]; 
	int length;
}ShoppingList;

//==============购物清单顺序表的函数声明=============================
ShoppingList* InitShoppingList(); //初始化一个列表清单
Item GetItem(ShoppingList *SL,int i);
int LocateItem(ShoppingList* SL,char* Itemname); 
ShoppingList* ShoppingListInsert(ShoppingList* SL,int i,Item item); 
ShoppingList* ShoppingListDelete(ShoppingList* SL,int i); 


int main(){
	ShoppingList *SL=InitShoppingList();
	printf("%d\n",SL->length);
	return 0;
}

//=====初始化函数实现==========
ShoppingList* InitShoppingList(){
	ShoppingList *SL;
	SL=(ShoppingList *)malloc(sizeof(ShoppingList));
	if(SL==NULL){
		printf("内存分配失败，请重进\n");
		return NULL;                   
	}
	SL->length=0;
	return SL;
}

//====取值函数实现============
Item GetItem(ShoppingList *SL,int i){
	//获取第i个位置的数据元素的值
	Item temp;
	Item empty={};
	if(SL==NULL){
		printf("SL ERROR\n");
		return empty;
	} 
	if(i<1||i>SL->length){
		printf("i is ERROR");
		return empty;
	}
	
	temp=SL->item[i-1];
	
	return temp;	
}

//====查找函数实现==========
int LocateItem(ShoppingList* SL,char* Itemname){
	int i=0;
	for(i;i<SL->length;i++)
		if(strcmp(SL->item[i].name,Itemname)==0)return i+1;
	if(i==SL->length)printf("没有此数据\n");
	return 0;
}

//===插入函数实现==========
ShoppingList* ShoppingListInsert(ShoppingList* SL,int i,Item item){
	int j;
	if((i<1)&&(i>SL->length+1))return NULL;
	if(SL->length==MAXSIZE)return NULL;
	for(j=SL->length;j>=i-1;j--){
		SL->item[j+1] = SL->item[j];
	}
	SL->item[i]=item;
	SL->length++;
	return SL; 
} 

//===删除函数实现===========
ShoppingList* ShoppingListDelete(ShoppingList* SL,int i){
	//在顺序表中删除第i个元素，i的范围是1<=i<=SL->length
	int j;
	if(i<1&&i>SL->length)return NULL;
	for(j=i;j<=SL->length-1;j++){
		SL->item[j-1] = SL->item[j];
	} 
	--SL->length;
	return SL;
} 

//===操作菜单实现============== 
void Menu(){
	printf("-----------------------------------\n");
	printf("\t欢迎来到宇平的购物清单\n");
	printf("-----------------------------------\n");
	printf("\t1.添加商品信息   5.输出所有商品信息\n");
	printf("\t2.删除商品信息     \n");
	printf("\t3.查找商品信息     \n");
	printf("\t4.获取商品信息     \n");
	printf("\n\t请选择要进行的操作\n");
	return ; 		
}

//===菜单功能实现函数=======
void MenuOperation(ShoppingList* SL){
	Menu();
	int select;
	while(scanf("%d",&select)!=1){
		printf("\n\t输入错误请重试 \n");
	} 
	switch
} 
