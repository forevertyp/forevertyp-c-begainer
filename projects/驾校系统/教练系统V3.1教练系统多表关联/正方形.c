#include <stdio.h>

int main(){
	//double a[4][2]={{1,-1},{1,1},{-1,-1},{-1,1}};
	double a[1][2];
	
	for(int i=0;i<2;i++){
		scanf("%ld",&a[0][i]);
	}         
	
	int c=1;
	for(int i=0;i<2;i++){
		if(a[0][i]-1>1e-12){
			c=0;
			break;
		}
		else if(a[0][i]+1>1e-12)
		{
			c=0;
			break;
		}
	}
	
	if(c==1)printf("Yes");
	else if(c==0) printf("No");
	 
	
	return 0;
}
