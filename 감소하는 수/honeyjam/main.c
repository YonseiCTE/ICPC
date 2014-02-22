#include<stdio.h>
int Input();
int Calculate(int number);
void Output(int answer);
int main(int argc,char* argv[]){
	int number;
	int answer;
	number=Input();
	answer=Calculate(number);
	Output(answer);
	return 0;
}
int Input(){
	int number;
	scanf("%d",&number);
	return number;
}
int Calculate(int number){
	int i,j;
	int not;
	char dec[7];
	int count=0;
	for(i=0;count<number;i++){
		sprintf(dec,"%d",i);
		j=0;
		not=0;
		while(dec[j+1]!=NULL && not!=1){
			if(dec[j]<=dec[j+1]){
				not=1;
			}
			j++;
		}
		if(not==0){
			count++;
		}
	}
	return i;
}
void Output(int answer){
	printf("%d\n",answer);
}