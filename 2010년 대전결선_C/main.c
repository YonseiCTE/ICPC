/*******
*	ACM_ICPC__Asia_Daejeon_2010
*		problem_C__password
*			
*	resolver : kong ji yeon
*	date : 2014 / 03 / 01
*			  
*******/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void Input(int *testcase,int **kNumber,char ****gridFront,char ****gridSecond);
char** Calculate(int testcase,int *kNumber,char ***gridFront,char ***gridSecond);
void Output(char **answer,int testcase);
int main(int argc,char* argv[]){
	int testcase;
	int *kNumber;
	char ***gridFront;
	char ***gridSecond;
	char **answer;
	Input(&testcase,&kNumber,&gridFront,&gridSecond);
	answer=Calculate(testcase,kNumber,gridFront,gridSecond);
	Output(answer,testcase);
	return 0;
}
void Input(int *testcase,int **kNumber,char ****gridFront,char ****gridSecond){
	int i,j,k;
	char filename[80];
	FILE *fp;
	scanf("%s",filename);
	fp=fopen(filename,"r");
	fscanf(fp,"%d",testcase);
	*kNumber=(int*)calloc(*testcase,sizeof(int));
	*gridFront=(char***)calloc(*testcase,sizeof(char**));
	*gridSecond=(char***)calloc(*testcase,sizeof(char**));
	for(i=0;i<*testcase;i++){
		fscanf(fp,"%d",*kNumber+i);
		*(*gridFront+i)=(char**)calloc(6,sizeof(char*));
		*(*gridSecond+i)=(char**)calloc(6,sizeof(char*));
		for(j=0;j<6;j++){
			*(*(*gridFront+i)+j)=(char*)calloc(6,sizeof(char));
			fscanf(fp,"%s",*(*(*gridFront+i)+j));
		}
		for(j=0;j<6;j++){
			*(*(*gridSecond+i)+j)=(char*)calloc(6,sizeof(char));
			fscanf(fp,"%s",*(*(*gridSecond+i)+j));
		}
	}
	fclose(fp);
}
char** Calculate(int testcase,int *kNumber,char ***gridFront,char ***gridSecond){
	int i,j,k,m;
	char **answer;
	char choice[5][7];
	int choiceIndex;
	int indexes[5];
	answer=(char**)calloc(testcase,sizeof(char*));
	for(i=0;i<testcase;i++){
		memset(indexes,0,5*sizeof(int));
		*(answer+i)=(char*)calloc(6,sizeof(char));
		for(k=0;k<5;k++){
			choiceIndex=0;
			for(j=0;j<6;j++){
				for(m=0;m<6;m++){
					if(*(*(*(gridFront+i)+j)+k)==*(*(*(gridSecond+i)+m)+k)){
						*(*(choice+k)+choiceIndex++)=*(*(*(gridFront+i)+j)+k);
					}
				}
				*(*(choice+k)+choiceIndex)=NULL;
			}
		}
		for(j=0;j<5;j++){
			for(m=0;*(*(choice+j)+m)!=NULL;m++){
				for(k=0;*(*(choice+j)+k+1)!=NULL;k++){
					if(*(*(choice+j)+k)>*(*(choice+j)+k+1)){
						*(*(choice+j)+k)=*(*(choice+j)+k)^*(*(choice+j)+k+1);
						*(*(choice+j)+k+1)=*(*(choice+j)+k+1)^*(*(choice+j)+k);
						*(*(choice+j)+k)=*(*(choice+j)+k)^*(*(choice+j)+k+1);
					}
				}
			}
		}
		for(j=0;j<*(kNumber+i)-1;j++){
			(*(indexes+4))++;
			if(*(*(choice+4)+*(indexes+4))==NULL){
				*(indexes+4)=0;
				(*(indexes+3))++;
			}
			if(*(*(choice+3)+*(indexes+3))==NULL){
				*(indexes+3)=0;
				(*(indexes+2))++;
			}
			if(*(*(choice+2)+*(indexes+2))==NULL){
				*(indexes+2)=0;
				(*(indexes+1))++;
			}
			if(*(*(choice+1)+*(indexes+1))==NULL){
				*(indexes+1)=0;
				(*(indexes))++;
			}
			if(*(*choice+*indexes)==NULL){
				j=7777;
			}
		}
		if(j!=7778){
			**(answer+i)=*(*choice+*indexes);
			*(*(answer+i)+1)=*(*(choice+1)+*(indexes+1));
			*(*(answer+i)+2)=*(*(choice+2)+*(indexes+2));
			*(*(answer+i)+3)=*(*(choice+3)+*(indexes+3));
			*(*(answer+i)+4)=*(*(choice+4)+*(indexes+4));
			*(*(answer+i)+5)=NULL;
		}else{
			**(answer+i)=NULL;
		}
	}
	for(i=0;i<testcase;i++){
		for(j=0;j<6;j++){
			if(*(*(gridFront+i)+j)!=NULL){
				free(*(*(gridFront+i)+j));
				*(*(gridFront+i)+j)=NULL;
			}
			if(*(*(gridSecond+i)+j)!=NULL){
				free(*(*(gridSecond+i)+j));
				*(*(gridSecond+i)+j)=NULL;
			}
		}
		if(*(gridFront+i)!=NULL){
			free(*(gridFront+i));
			*(gridFront+i)=NULL;
		}
		if(*(gridSecond+i)!=NULL){
			free(*(gridSecond+i));
			*(gridSecond+i)=NULL;
		}
	}
	if(gridFront!=NULL){
		free(gridFront);
		gridFront=NULL;
	}
	if(gridSecond!=NULL){
		free(gridSecond);
		gridSecond=NULL;
	}
	if(kNumber!=NULL){
		free(kNumber);
		kNumber=NULL;
	}
	return answer;
}
void Output(char **answer,int testcase){
	int i,j;
	for(i=0;i<testcase;i++){
		if(**(answer+i)!=NULL){
			printf("%s\n",*(answer+i));
		}else{
			printf("NO\n");
		}
		free(*(answer+i));
	}
	free(answer);
}

