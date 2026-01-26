//tic-tac-toe游戏
#include<stdio.h>

int main(){
	const int size =  3;
	int board[size][size];
	int i,j;
	int numOfX;
	int numOfO;
	int ret = -1;  //-1平局 1：x胜利 0:O胜利 
	 
	
	//输入 
	for(i=0;i<size;i++)
		for(j=0;j<size;j++){
			while(1){
				if(scanf("%d",&board[i][j])!=1){
					printf("请输入数字0 or 1\n");
					while(getchar()!='\n');
					continue; 
				}
				
				if(board[i][j]!=0&&board[i][j]!=1){
					printf("输入了不正确的数数字，请输入0 or 1\n");
					scanf("%d",&board[i][j]);
				}
				else break;
			}
		}
		printf("输入完成\n");	
			
	//检查行和列 
	for(i = 0;i<size && ret == -1;i++){
		numOfO = numOfX = 0;
		for(j=0;j<size;j++){
			if(board[i][j] == 1){
				numOfX++;
			}else{
				numOfO++;
			}
		}
		if(numOfO == size){
			ret = 0;
		}else if(numOfX == size){
			ret == 1;
		}
	}
	for(i = 0;i<size && ret == -1;i++){
		numOfO = numOfX = 0;
		for(j=0;j<size;j++){
			if(board[j][i] == 1){
				numOfX++;
			}else{
				numOfO++;
			}
		}
		if(numOfO == size){
			ret = 0;
		}else if(numOfX == size){
			ret == 1;
		}
	}
	//检查对角线 
		//正对角线 
	numOfO=numOfX=0;
	for(i = 0;i<size&&ret == -1;i++){
		if(board[i][i]==1){
			numOfX++;
		}else{
			numOfO++;
		}
		if(numOfO==size){
			ret == 0;
		}else if(numOfX == size){
			ret = 1;
		}
	}
		//负对角线
	for(i = 0;i<size&&ret == -1;i++){
		if(board[i][(size-1)-i]==1){
			numOfX++;
		}else{
			numOfO++;
		}
		if(numOfO==size){
			ret = 0;
		}else if(numOfX == size){
			ret = 1;
		}
	}	
	//输出结果 
	switch(ret){
		case -1:
			printf("平局\n");
			break;
		case 0:
			printf("Oplayer win\n");
			break;
		case 1:
			printf("Xplayer win\n");
			break;
	}
	
	return 0;
}


 
