/*******
* Acm_Problem_KTX
* resolver : Kong ji yeon
* date: 2014/02/09
* comment : 폴더만드는법을 몰라 소스만 첨부합니다.
*******/
#include<stdio.h>
#include<stdlib.h>
void Input(int *T,int **M,int ***N);
int* Calculate(int T,int *M,int **N);
void Output(int T,int *answer);
int main(int argc,char *argv[]){
	int T;		//test case
	int *M;		//train 
	int **N;	//train level
	int *answer;
	Input(&T,&M,&N);
	answer=Calculate(T,M,N);
	Output(T,answer);
	return 0;
}
void Input(int *T,int **M,int ***N){
	int i,j;	//for loop control
	char filename[32];	//input file
	FILE *fp;
	printf("Input filename : ");
	scanf("%s",filename);
	fp=fopen(filename,"r");
	fscanf(fp,"%d",T);
	*M=(int*)calloc(*T,sizeof(int));
	*N=(int**)calloc(*T,sizeof(int*));
	for(i=0;i<*T;i++){
		fscanf(fp,"%d",(*M)+i);
		*((*N)+i)=(int*)calloc(*(*M+i),sizeof(int));
		for(j=0;j<*(*M+i);j++){
			fscanf(fp,"%d",(*((*N)+i)+j));
		}
	}
	fclose(fp);
}
int* Calculate(int T,int *M,int **N){
	int i,j,k;		//for loop control
	int *answer;	//answer
	int destination=1;	//train level
	int pass;		//testing train
	int count;		//pass count
	answer=(int*)calloc(T,sizeof(int));
	for(i=0;i<T;i++){
		destination=1;
		pass=3;
		count=0;
		for(j=0;j<*(M+i);j++){	
			k=0;
			while(k<pass && destination>j){
				if(*(*(N+i)+k)==destination){
					destination+=1;
					pass+=1;
					count+=1;
				}
				k++;
			}
		}
		if(*(N+i)!=NULL){
			free(*(N+i));
			*(N+i)=NULL;
		}
		if(count==*(M+i)){
			*(answer+i)=1;
		}
	}
	if(M!=NULL){
		free(M);
		M=NULL;
	}
	if(N!=NULL){
		free(N);
		N=NULL;
	}
	return answer;
}
void Output(int T,int *answer){
	int i;
	for(i=0;i<T;i++){
		if(*(answer+i)==0){
			printf("NO\n");
		}else{
			printf("YES\n");
		}
	}
	if(answer!=NULL){
		free(answer);
		answer=NULL;
	}
}

