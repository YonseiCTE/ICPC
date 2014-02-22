/*******
* acm_war game
* resolver : kong ji yeon
* date : 2014 / 02 / 22
* comment : 
*******/
#include<stdio.h>
#include<stdlib.h>
void Input(int *T,char ***soldiers);
char** Calculate(int T,char **soldiers);
void Output(int T,char **answer);
int main(int argc,char* argv[]){
	int T;	//test case
	char **soldiers;	//soldiers
	char **answer;
	Input(&T,&soldiers);
	answer=Calculate(T,soldiers);
	Output(T,answer);
	return 0;
}
void Input(int *T,char ***soldiers){
	int i,j;
	FILE *fp;
	char filename[80];
	scanf("%s",filename);
	fp=fopen(filename,"r");
	fscanf(fp,"%d",T);
	*soldiers=(char**)calloc(*T,sizeof(char*));
	for(i=0;i<*T;i++){
		*((*soldiers)+i)=(char*)calloc(80,sizeof(char));
		fscanf(fp,"%s",*((*soldiers)+i));
	}
}
char** Calculate(int T,char **soldiers){
	char **answer;
	int i,j;
	int enemy;
	answer=(char**)calloc(T,sizeof(char*));
	for(i=0;i<T;i++){
		*(answer+i)=(char*)calloc(80,sizeof(char));
		enemy=0;
		while(*(*(soldiers+i)+(enemy+1))!=NULL){
			enemy+=1;
		}
		j=0;
		while(enemy>=0){
			switch(*(*(soldiers+i)+enemy)){
			case 'A':*(*(answer+i)+j)='C';break;
			case 'B':*(*(answer+i)+j)='A';break;
			case 'C':*(*(answer+i)+j)='B';break;
			default:break;
			}
			if(j>0 && *(*(answer+i)+j)==*(*(answer+i)+(j-1))){
				j-=1;
			}
			enemy-=1;
			j+=1;	
		}
		*(*(answer+i)+j)='\0';
		if(*(soldiers+i)=NULL){
			free(*(soldiers+i));
			*(soldiers+i)=NULL;
		}
	}
	if(soldiers!=NULL){
		free(soldiers);
		soldiers=NULL;
	}
	return answer;
}
void Output(int T,char **answer){
	int i;
	for(i=0;i<T;i++){
		printf("%s\n",*(answer+i));
		if(*(answer+i)!=NULL){
			free(*(answer+i));
			*(answer+i)=NULL;
		}
	}
	if(answer!=NULL){
		free(answer);
		answer=NULL;
	}
}